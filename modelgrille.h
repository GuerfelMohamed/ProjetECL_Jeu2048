#ifndef MODELGRILLE_H
#define MODELGRILLE_H


#include <QAbstractListModel>
#include <string>
#include "grille.h"

///// Classe hérité de QAbstractListModel pour communiquer avec la qml et crée le modele pour le repeater //////


class modelgrille  : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(int get_score READ get_score NOTIFY chgt_score)// Quant une signal Chgt_score est emit, mettre à jour le Qml property get_score de type int
    Q_PROPERTY(int get_best_score READ get_best_score NOTIFY chgt_best_score)// Quant une signal Chgt_best_score est emit, mettre à jour le Qml property get_best_score de type int
    Q_PROPERTY(bool finJeu READ finJeu NOTIFY fin_ou_gagne) //Quant une signal fin_ou_gagne est emit, mettre à jour le Qml property finJeu de type bool
    Q_PROPERTY(bool a_gagne READ a_gagne NOTIFY fin_ou_gagne) //Quant une signal fin_ou_gagne est emit, mettre à jour le Qml property a_gagne de type bool
    Q_PROPERTY(int get_Taille READ get_Taille NOTIFY fin_ou_gagne)//Quant une signal fin_ou_gagne est emit, mettre à jour le Qml property getTaille de type int(3,4,5)
    Q_PROPERTY(QString get_text READ get_text NOTIFY fin_ou_gagne)//Quant une signal fin_ou_gagne est emit, mettre à jour le Qml property get_text(YOU WIN / GameOver)


public:

    explicit modelgrille(QObject *parent = 0);
    int rowCount(const QModelIndex &parent = QModelIndex()) const;// override  la méthode rowCount
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;//override  la méthode data

    // les méthodes invoquées par le qml
    Q_INVOKABLE void mvtH();
    Q_INVOKABLE void mvtD();
    Q_INVOKABLE void mvtB();
    Q_INVOKABLE void mvtG();
    Q_INVOKABLE void nouvelle_partie();//pour commencer une nouvelle partie(méthode invoquer quand le bouton "nouvelle partie" est cliqué)
    Q_INVOKABLE void  chgt_Taille(int taille);//pour changer le taille de la grille(méthode invoquer quand le bouton "3x3", "4x4" ou "5x5" est cliqué)
    Q_INVOKABLE void charger_historique_grille(); //Pour gerer l'historique(méthode invoquer quand le bouton 'Retour" est cliqué)


    int get_score() const; //Obtenir le score
    int get_Taille();//Obtenir le taille de grille
    int get_best_score() const; //pour le meilleur score
    bool finJeu(); // retourne vrai si jeu terminé, faux sinon
    bool a_gagne();// retourne vair si état gagnant, faux sinon
    QString get_text();// retourne "YOU WIN" si a_gagne est vrai, "GameOver" sinon

signals:
    void chgt_score();// signale emit quand il y a un changement de score
    void chgt_best_score();//signale emit quand il y a un nouveau best score
    void fin_ou_gagne();// signale emit quand il y a le jeu termine ou le joueur gagne



public slots:
    void mise_a_jour();//signale pour mettre à jour le grille arès chauque mouvement

private:
    int taille_grille=4;// taile de grille, par défault 4x4
    Grille grille;// l'attribute de type "grille" de notre "modelgrille"




};

#endif // MODELGRILLE_H
