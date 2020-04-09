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

