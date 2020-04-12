#include "modelgrille.h"

modelgrille::modelgrille(QObject *parent) :
    QAbstractListModel(parent)
{
    // établir une connection entre les signales emit par la grille et le modèle
    connect(&grille, &Grille::mouvement_fait, this, &modelgrille::mise_a_jour);// si signale mouvement_fait emit par la grille, alors l'execution de mise_a_jour()
    connect(&grille, &Grille::chgt_score, this, &modelgrille::chgt_score);
    connect(&grille, &Grille::chgt_best_score, this, &modelgrille::chgt_best_score);
    connect(&grille, &Grille::fin_ou_gagne, this, &modelgrille::fin_ou_gagne);

}

// override methode: pour retourner le nombre de tuiles de la grille.
int modelgrille::rowCount(const QModelIndex &parent) const{
    Q_UNUSED(parent)
    return taille_grille*taille_grille;
}

// override methode: pour retourner les données stockées sous le rôle donné pour le tuile référencé par "index".
QVariant modelgrille::data(const QModelIndex &index, int role) const{
    int v_index, h_index;
    if (index.row() < 0 || index.row() >= taille_grille * taille_grille) {
        return QVariant(); // if  index out of bound return invalid
    }
    if (role == Qt::DisplayRole) {
        v_index = index.row() % taille_grille; //l'indice de ligne correspond à cette tuile
        h_index = index.row() / taille_grille;// l'indice de la colonne correspond à cette tuile
        QString str = QString::number(grille.getval(v_index, h_index));// obtenir le contenu de cette tuile
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
    emit dataChanged(createIndex(0, 0), createIndex(taille_grille*taille_grille, 0)); //signaler un changement de contenu dans la grille,
                                                                                      //relancer le Repeater dans le fichier "Grillee.qml" pour reconstruire la grille
}
void modelgrille::chgt_Taille(int taille){
    taille_grille=taille;
    grille.setTaille(taille);
    emit endResetModel();//signaler un changement dans le structure de la grille, relancer le Repeater dans le fichier "Grillee.qml" pour reconstruire la grille
}
void modelgrille::charger_historique_grille(){
    grille.charger_historique_grille();
    mise_a_jour();
    emit fin_ou_gagne();// tester l'état de jeu après chaque changement de données.
}


// jouer!
void modelgrille::nouvelle_partie(){
    grille.debut_jeu();
    mise_a_jour();
    emit fin_ou_gagne(); //tester l'état de jeu après chaque changement de données.
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







