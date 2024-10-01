#ifndef LISTE_CHAINEE_H
#define LISTE_CHAINEE_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

// Structure pour un noeud de la liste chaînée
struct noeud {
    float val;
    struct noeud *suiv;
};

// Structure pour la liste chaînée
struct liste_chainee {
    struct noeud *tete;
    int length;
};

// Prototypes des fonctions

// Fonction pour créer une nouvelle liste chaînée
struct liste_chainee* creer_liste();

// Fonction qui crée une liste chaînée à partir d'un tableau
struct liste_chainee* convert_tab_liste(float *tableau, int taille);

// Fonction qui affiche la liste chaînée
void afficher_liste(struct liste_chainee* liste);

// Fonction pour supprimer une liste chaînée
void supprime_liste(struct liste_chainee* liste);

// Fonction qui vérifie si une valeur est présente dans une liste chaînée
bool in(struct liste_chainee *liste, float valeur);

// Fonction pour ajouter un élément à la fin de la liste chaînée
void ajouter_en_queue(struct liste_chainee* liste, float valeur);

// Fonction pour ajouter un élément au début de la liste chaînée
void ajouter_en_tete(struct liste_chainee* liste, float valeur);

// Fonction qui renvoie la longueur de la liste chaînée
int len(struct liste_chainee* liste);

// Fonction pour obtenir l'élément à l'indice i de la liste chainée
float obtenir_element(struct liste_chainee* liste, int index);

// Fonction qui modifie la valeur d'un noeud à un indice donné
void modifier_valeur(struct liste_chainee* liste, int i, float nouvelle_valeur);

// Fonction pour inverser la liste chaînée
void inverser_liste(struct liste_chainee* liste);

// Fonction qui supprime un noeud d'indice donné
void supprimer_noeud(struct liste_chainee* liste, int i);

// Fonction pour trouver l'indice de la première occurrence d'une valeur
int trouver_indice(struct liste_chainee* liste, float valeur);

// Fonction pour copier une liste chaînée
struct liste_chainee* copier_liste(struct liste_chainee* liste_source);

// Fonction pour copier une tranche de la liste chaînée
struct liste_chainee* copier_tranche(struct liste_chainee* liste_source, int i, int j);

// Fonction pour concaténer deux listes chaînées
struct liste_chainee* concatener_listes(struct liste_chainee* liste1, struct liste_chainee* liste2);

// Fonction pour trouver la valeur maximale dans une liste chaînée
float max(struct liste_chainee* liste);

// Fonction pour trouver la valeur minimale dans une liste chaînée
float min(struct liste_chainee* liste);

// Fonction pour supprimer les doublons dans une liste chaînée
void supprimer_doublons(struct liste_chainee* liste);

// Fonction pour insérer un noeud à un indice donné
void inserer_noeud(struct liste_chainee* liste, int indice, float valeur);

// Fonction pour échanger les valeurs de 2 noeuds d'une liste chainée
void echanger_valeurs(struct liste_chainee* liste, int index1, int index2);

// Fonction pour comparer si 2 listes sont identiques
bool comparer_listes(struct liste_chainee* liste1, struct liste_chainee* liste2);

// Fonction pour trier la liste chaînée (tri rapide)
void trier_liste(struct liste_chainee* liste);

#endif // LISTE_CHAINEE_H