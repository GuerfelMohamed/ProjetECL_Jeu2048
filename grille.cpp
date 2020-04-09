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

// On crée une nouvelle cellule et nouvelle val
void Grille::new_cellule() { // Génère une nouvelle cellule
    int i, j;
    int liste_cellules_libres[taille_grille*taille_grille][2]; // Liste des coordonnées des emplacements libres pour une nouvelle cellule (au maximum le nombre de cellules)
    int l = 0; //nbr cellules vides
    int rand; // emplacement random pour la nouvelle cellule

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
