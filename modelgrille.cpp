#include "modelgrille.h"

modelgrille::modelgrille(QObject *parent) :
    QAbstractListModel(parent)
{
    // établir une connection entre les signales emit par la grille et le modèle
    connect(&grille, &Grille::mouvement_fait, this, &modelgrille::mise_a_jour);// si signele mouvement_fait emit par la grille, alors l'execution de mise_a_jour()
    connect(&grille, &Grille::chgt_score, this, &modelgrille::chgt_score);
    connect(&grille, &Grille::chgt_best_score, this, &modelgrille::chgt_best_score);
    connect(&grille, &Grille::fin_ou_gagne, this, &modelgrille::fin_ou_gagne);

}

// override methode:
int modelgrille::rowCount(const QModelIndex &parent) const{
    Q_UNUSED(parent)
    return taille_grille*taille_grille;
}

// orride methode:
QVariant modelgrille::data(const QModelIndex &index, int role) const{
    int v_index, h_index;
    if (index.row() < 0 || index.row() >= taille_grille * taille_grille) {
        return QVariant();
    }
    if (role == Qt::DisplayRole) {
        v_index = index.row() % taille_grille;
        h_index = index.row() / taille_grille;
        QString str = QString::number(grille.getval(v_index, h_index));
        return str;
    }
    return QVariant();
}

// getters
int modelgrille::get_score() const{
    return grille.get_score();
}
int modelgrille::get_best_score() const{
    return grille.get_best_score();
}
int modelgrille::get_Taille(){
    return taille_grille;
}
QString modelgrille::get_text(){
    if (grille.a_gagne()) {
        return "YOU WIN !";
    } else if (grille.finJeu()) {
        return "GAME OVER";
    } else {
        return "";
    }
}

//tester l'état du jeu
bool modelgrille::finJeu(){
    return grille.finJeu();
}
bool modelgrille::a_gagne(){
    return grille.a_gagne();
}

//signaler un mise à jour
void modelgrille::mise_a_jour(){
    emit dataChanged(createIndex(0, 0), createIndex(taille_grille*taille_grille, 0));
}
void modelgrille::chgt_Taille(int taille){
    taille_grille=taille;
    grille.setTaille(taille);
    emit fin_ou_gagne();
    emit endResetModel();
}
void modelgrille::charger_historique_grille(){
    grille.charger_historique_grille();
    mise_a_jour();
    //emit fin_ou_gagne();
}

// jouer!
void modelgrille::nouvelle_partie(){
    grille.debut_jeu();
    mise_a_jour();
    //emit fin_ou_gagne();
}
void modelgrille::mvtH(){
    grille.seDeplacerHaut();
}
void modelgrille::mvtB(){
    grille.seDeplacerBas();
}
void modelgrille::mvtG(){
    grille.seDeplacerGauche();
}
void modelgrille::mvtD(){
    grille.seDeplacerDroite();
}







