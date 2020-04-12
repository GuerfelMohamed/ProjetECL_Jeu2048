#ifndef GRILLE_H
#define GRILLE_H

#include <QObject>
#include <QStringList>


class Grille : public QObject {
    Q_OBJECT

public:
    explicit Grille(QObject *parent = 0);

    bool seDeplacerHaut(); /// Se deplacer vers le haut ///
    bool seDeplacerGauche(); /// Se déplacer vers la gauche///
    bool seDeplacerBas(); /// Se déplacer vers le bas///
    bool seDeplacerDroite(); /// Se déplacer vers la droite///

    int getval(const int x, const int y) const; // Obtenir la valeur de la cellule (x,y)
    int get_score() const; // Donne le score
    int get_best_score() const ;////////// pour le meilleur score/////////////

    bool finJeu(); ///ici il s'agit de la fonction qui est tout le temps appelé pour savoir si le jeu est fini ou pas en fonction du nombre nombre de case vide et des tuiles adjacents et égaux///
    bool a_gagne(); // Retourne vrai si le joueur a gagne


    void debut_jeu(); //initialisation jeu

    void setTaille(int taille);
    int taille_grille=4; // initialiser à 4 pour démarrer le jeu

///////////// Pour gerer le bouton de retour////////////////////////
    void enregistrer_historique();
    void charger_historique_grille();

signals:
    void mouvement_fait(); //mvt fait
    void chgt_score(); // modif score
    void fin_ou_gagne(); // jeu terminé
    void charger_historique(); ///////////////pour gerer le bouton de retour//////////////////
    void chgt_best_score();////////// pour le meilleur score/////////////

private:
    int grl[5][5]; // Valeurs des cellules
    short nb_retour_max = 50; //Le nombre de retour maximale qu'on peut effectuer (intervient dans l'historique)
    short historique_index = -1; //L'indexe courante de l'historique dans la liste des historiques
    int grille_historique[50][5][5]; ////////////pour gerer l'historique//////////////////
    int score_historique[50]; ////////////pour gerer le bouton de retour////////////////////
    int score = 0;////////// pour score/////////////
    int best_score = 0;////////// pour le meilleur score/////////////
    int cellule_max; //Pour le tester gagnant si 2048 ou autre


    void init_rand(); // aléatoir
    int new_val() const; // donner une nouvelle valeur de cellule (0.1-> 4 et 0.9-> 2: regle internet)
    void new_cellule(); // Créer une nouvelle cellule

    bool seDeplacer(int sens); ///Cette fonction permet de se deplacer dans une direction et un sens donnees en fonction du parametre qui lui est passe///
                               /// 0 pour le haut, 1 pour gauche, 2 pour le bas, 3 pour la droite///
    void tournerDroite(); /////Cette fonction permet de faire des rotations dans le sens trigonometrique///
    bool tout_bouger_haut(); // Gère tout ce qui concerne le mouvement vers le haut : déplacements et fusions
    bool mouvement(int array[]); // Effectue le mouvement d'une colonne (dans la array), et retourne false s'il n'y a aucun mouvement

    int positionSuivante(int array[], const int pos, const int stop) const; ///Cette fonction permet de connaitre la position suivante d'un tuile///
    bool tuilesEgaux() const; ////Cette fonction permet de savoir si deux tuiles sont adjacents sont égaux ou pas dans le but de savoir si le jeu est fini///
    int compterCasesVides() const; ///Cette fonction permet de déterminer le nombre de case vide pour savoir si les jeu est fini ou pas///
};

#endif // GRILLE_H
