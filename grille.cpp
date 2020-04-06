#include "grille.h"

#include <iostream>
using namespace std;

Grille::Grille(QObject *parent) :
    QObject(parent) {
    init_rand();
    debut_jeu();
}
