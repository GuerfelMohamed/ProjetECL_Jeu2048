#include "grille.h"

#include <iostream>
using namespace std;

#include <QTime>


Grille::Grille(QObject *parent) :
    QObject(parent) {
    init_rand();
    debut_jeu();
}

// pour faire du random
void Grille::init_rand() {
    auto time = QTime::currentTime();
    qsrand((uint) time.msec());
}

// les get et set de la classe
int Grille::getval(const int x, const int y) const {
    return grl[x][y];
}

int Grille::get_score() const {
    return score;
}


int Grille::get_best_score() const{
    return best_score;
}


void Grille::setTaille(int taille){
    taille_grille=taille;
}


// nouvelle valeur pour la nouvelle cellule en respectant la loi de probabilite
int Grille::new_val() const {
    if (qrand()%10 == 9) { return 4;} else {return 2;}
}

bool Grille::a_gagne() {
    return cellule_max == 2048;// on peut modofoer ici et diminuet le but
}

// On crée une nouvelle cellule et nouvelle val
void Grille::new_cellule() {
    int i, j;
    int rand; // emplacement random pour la nouvelle cellule
    int liste_cellules_libres[taille_grille*taille_grille][2]; // Liste des coordonnées des emplacements libres pour une nouvelle cellule (au maximum le nombre de cellules)
    int l = 0; //nbr cellules vides

    for(i = 0; i < taille_grille; i++) {
        for(j = 0; j < taille_grille; j++) {
            if(grl[i][j] == 0) {
                liste_cellules_libres[l][0] = i;
                liste_cellules_libres[l][1] = j; // On enregistre les emplacements libres
                l++; // Et on augmente la taille (pour savoir combien on en a)
            }
        }
    }

    if (l > 0) { // Si il y a au moins un emplacement libre
        rand = qrand() % l;
        i = liste_cellules_libres[rand][0];
        j = liste_cellules_libres[rand][1];
        grl[i][j] = new_val();
    }
}


// gerer l'historique
void Grille::enregistrer_historique(){
    int i, j, index;
    //cas ou on a pas encore atteint le nombre maximum de historique qu'on peut enregistrer
    //dans ce cas on enregistre l'historique dans l'index suivante
    if(historique_index<nb_retour_max-1){

        historique_index++;
        for(i = 0; i<taille_grille; i++){
            for(j = 0; j<taille_grille; j++){
                grille_historique[historique_index][i][j] = grl[i][j];
            }
        }
        score_historique[historique_index] = score;
    }else{
        //Si nous avons atteint le nombre maximum de historique qu'on peut enregistrer
        //dans ce cas on supprime la plus ancienne historique et on déplace les autres pour avoir de la place
        for(index = 1; index<nb_retour_max; index++){
            for(i = 0; i<taille_grille; i++){
                for(j = 0; j<taille_grille; j++){
                    grille_historique[index-1][i][j] = grille_historique[index][i][j];
                }
            }
            score_historique[index-1] = score_historique[index];
        }
        //Enfin on enregistre l'historique dans la dernière case de notre vercteur d'historique
        for(i = 0; i<taille_grille; i++){
            for(j = 0; j<taille_grille; j++){
                grille_historique[historique_index][i][j] = grl[i][j];
            }
        }
        score_historique[historique_index] = score;
    }

}

void Grille::charger_historique_grille(){
    int i, j;
    //On ne charche l'historique que lorsqu'on a pas encore dépassé le nombre maximal d'historique qu'on peut enregistrer.
    if(historique_index>=0){
        for(i = 0; i<taille_grille; i++){
            for(j = 0; j<taille_grille; j++){
                grl[i][j] = grille_historique[historique_index][i][j];
            }
        }
        score = score_historique[historique_index];
        historique_index--;
        emit mouvement_fait();
        emit chgt_score();
    }


}

// initialisation du jeu pour commencer à jouer (utile pour les boutons fait)
void Grille::debut_jeu() {
    memset(grl, 0, sizeof(grl));
    memset(grille_historique, 0, sizeof(grille_historique)); //On reinitialise la valeur de l'historique
    memset(score_historique, 0, sizeof(score_historique)); //On reinitialise les scores liés a l'historique
    historique_index = -1; //On reinitialise l'index de l'historique
//////////////////Pour gerer le meilleur sscore/////////////////////////////
    if(score > best_score){ //On ne met à jour le score que si le score courant est supérieur au score précedant
        best_score = score;
        emit chgt_best_score();
    }
    score = 0;
    emit chgt_score();


    cellule_max = 0;
    // On fait apparaître deux cellules comme dans l'otiginal
    new_cellule();
    new_cellule();
    enregistrer_historique();
}

///Cette fonction permet de savoir si deux tuiles sont adjacents sont égaux ou pas dans le but de savoir si le jeu est fini///
bool Grille::tuilesEgaux() const {
    int i, j;
    for (i = 0; i < taille_grille; i++) {
        for (j = 0; j < taille_grille - 1; j++) {
            if (grl[i][j+1] == grl[i][j]) return true; //Dés que deux cases sont égaux on arret l'iteration et on retourne true
        }
    }
    return false; //S'il n'y a aucune égalité alors on retourne false
}


///Cette fonction permet de déterminer le nombre de case vide pour savoir si les jeu est fini ou pas///
int Grille::compterCasesVides() const {
    int i, j;
    int nb_cases_vides = 0;
    for (i = 0; i < taille_grille; i++) {
        for (j = 0; j < taille_grille; j++) {
            if (grl[i][j] == 0) { //Une case vide est une case dont le chiffre est 0 donc cela nous permet de détecter les cases vides
                nb_cases_vides++; //A chaque fois qu'une case est vide on incremente le nombre de de case vides
            }
        }
    }
    return nb_cases_vides; //En fin on retourne le nombre trouvé
}

///ici il s'agit de la fonction qui est tout le temps appelé pour savoir si le jeu est fini ou pas en fonction du nombre nombre de case vide et des tuiles adjacents et égaux///
bool Grille::finJeu() {
    if (compterCasesVides() > 0) { // S'il reste des cases vides alors le jeu n'est pas fni
        return false;
    }
    if (tuilesEgaux()) { // Oubien même s'il ne reste plus de case vide mais si deux tuiles égaux sont adjecents alors le jeu n'est pas encore fini
        return false;
    }

    tournerDroite(); // Ceci permet de verifier selon l'autre direction
    if (tuilesEgaux()) {
        tournerDroite();
        tournerDroite();
        tournerDroite();// Permet de remettre les tuiles dans le bon sens
        return false;
    }
    tournerDroite();
    tournerDroite();
    tournerDroite();// Permet de remettre les tuiles dans le bon sens
    return true;
}


///Cette fonction permet de connaitre la position suivante d'un tuile///
int Grille::positionSuivante(int colonne[], const int position, const int stop) const {

    int fut_pos; // la future position su tuile
    if (position == 0) {//Si nous sommes dans les bords alors on reste dans les bords
        return position;
    }
    //dans cette boucle, on cherche la futur position d'un tuile en cherchant la position vide la plus éloigné du tuile dans la direction et le sens du mouvement
    for (fut_pos = position - 1; fut_pos >= 0; fut_pos--) {
        if (colonne[fut_pos] != 0) { //Si la case contient un tuile
            if (colonne[fut_pos] != colonne[position]) { // Et si la valeur de la tuile est differente de celle de la tuile presente
                return fut_pos + 1; // Alors on s'arret avant cette tuile
            }
            //Par contre si les deux tuiles sont de meme valeurs alors on revoie la cette position
            return fut_pos;
        } else { // Mais si la case ne contient pas de tuile
            if (fut_pos == stop) { // Et qu'on a atteint les bords
                return fut_pos; //alors on renvoi la position courante
            }
        }
    }
    return position; // Enfin si la case la plus proche contient un tuile alors on renvoi la position données en entrée
}



///Cette fonction permet de faire des rotations dans le sens trigonometrique ///
void Grille::tournerDroite() {
    int i, j;

    //declaration de la grille temporaire par allocation dynamique
    int** grille_temp = new int*[taille_grille];
    for(i = 0; i<taille_grille; i++){
        grille_temp[i] = new int[taille_grille];
    }

    //initialisation de la grille temporaire
    for(i = 0; i<taille_grille; i++){
        for(j = 0; j<taille_grille; j++){
            grille_temp[i][j] = grl[i][j];
        }
    }
    //Rotation de la grille
    for(i = 0; i<taille_grille; i++){
        for(j = 0; j<taille_grille; j++){
            grl[j][i] = grille_temp[i][taille_grille-j-1];
        }
    }

    //supression de la grille temporaire
    for(i = 0; i<taille_grille; i++){
        delete[] grille_temp[i];
    }
    delete[] grille_temp;
}


///Cette fonction permet de se deplacer dans une direction et un sens donnees en fonction du parametre qui lui est passe///
/// 0 pour le haut, 1 pour gauche, 2 pour le bas, 3 pour la droite///
bool Grille::seDeplacer(int sens) {
    enregistrer_historique(); //On enregistre d'abord l'état courant du jeu avant d'effectuer le mouvement
    bool mouvementEffectue = false;

    int i;
    for(i = 0; i < sens; i++) {
        tournerDroite(); // On tourne à droite le nombre necessaire de fois pour que le sens devient le haut
    }
    mouvementEffectue = deplacerToutLesTuilesEnHaut(); // On fait monter les tuiles vers le haut
    for(i = sens; i < 4; i++) {
        tournerDroite(); // on tourne autant de fois que necessaire pour retrouver le bon ordre
    }

    if (mouvementEffectue) {//si le mouvement a été effectué avec succes
        new_cellule();  //alors on crée une nouvelle tuile
        emit mouvement_fait(); //Puis on notifie que le mouvement est effectuer pour la mise a jour de l'interface graphique
    }
    if(a_gagne() || finJeu()) { //Si aprés le mouvement on se rend compte que le jeu est terminé
        emit fin_ou_gagne(); //alors on notifie que le jeu est fini
        return false;
    }
    return mouvementEffectue;
}


 /// Se deplacer vers le haut ///
bool Grille::seDeplacerHaut() {
    return seDeplacer(0);
}

/// Se déplacer vers la gauche///
bool Grille::seDeplacerGauche() {
    return seDeplacer(1);
}

/// Se déplacer vers le bas///
bool Grille::seDeplacerBas() {
    return seDeplacer(2);
}

/// Se déplacer vers la droite///
bool Grille::seDeplacerDroite() {
    return seDeplacer(3);
}


///Cette fonction permet de deplacer tous les tuiles vers le haut///
bool Grille::deplacerToutLesTuilesEnHaut() {
    if (a_gagne() || finJeu()) {//si le jeu est fini on retourne false
        return false;
    }
    bool mouvementEffectue = false;
    int x;
    for (x = 0; x < taille_grille; x++) {
        mouvementEffectue |= monterColonne(grl[x]); // On fait monter les tuiles de chaque colonne vers le haut
    }
    return mouvementEffectue;
}


/// Cette fonction permet de faire monter une colonne de la grille vers le haut ///
bool Grille::monterColonne(int col[]) {
    bool peut_bouger = false;
    int position, fut_pos, stop = 0;
    // position parcoura les positions des cellules dans la colonne
    // fut_pos indique quelle est la position que la cellule aura après le mouvement
    // stop est une valeur de contrôle, à ne pas dépasser (utile dans "future_position")

    int valeur_fusion; // Donne la nouvelle valeur après fusion entre deux cellules

    for (position = 0; position < taille_grille; position++) { // On parcoure les positions
        if (col[position] != 0) { //Cas où on n'est pas tout en haut (car alors, aucun mouvement n'est possible, elle est à l'extrémité
            fut_pos = positionSuivante(col, position, stop); // Donne la future position de la cellule en mouvement
            if (fut_pos != position) { // Si il y a effectivement un mouvement (sinon, rien à faire)
                if (col[fut_pos] != 0) { // Dans le cas où la cellule va à l'extrémité, c'est tout bon, il n'y a rien à faire. Sinon :
                    stop = fut_pos + 1; // Pour contrôler qu'on ne chevauche pas les cellules
                    valeur_fusion = col[fut_pos] + col[position]; // On calcule la somme les valeurs
                    score += valeur_fusion; // On rajoute cette valeur au score
                    emit chgt_score(); // On signale le changement de score
                    cellule_max = max(cellule_max, valeur_fusion); // On emt à jour si nécessaire la valeur maximale de cellule
                }
                col[fut_pos] += col[position]; // On met à jour la valeur dans la nouvelle position (avec fusion si nécessaire)
                col[position] = 0; // La position d'où elle vient est vide : on le met à 0
                peut_bouger = true; // On a effectivement bougé
            }
        }
    }

    return peut_bouger;
}
