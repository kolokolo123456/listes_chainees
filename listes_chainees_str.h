#ifndef LISTE_CHAINEE_STR_H
#define LISTE_CHAINEE_STR_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

// Structure pour un noeud de la liste chaînée
struct noeud_str {
    char* text;
    struct noeud_str *suiv;
};

// Structure pour la liste chaînée
struct liste_chainee_str {
    struct noeud_str *tete;
    int length;
};

// Prototypes des fonctions

// Fonction pour créer une nouvelle liste chaînée
struct liste_chainee_str* creer_liste();

// Fonction qui crée une liste chaînée à partir d'un tableau
struct liste_chainee_str* convert_tab_liste(char** tableau, int taille);

// Fonction qui affiche la liste chaînée
void afficher_liste(struct liste_chainee_str* liste);

// Fonction pour supprimer une liste chaînée
void supprime_liste(struct liste_chainee_str* liste);

// Fonction qui vérifie si un text est présente dans une liste chaînée
bool in(struct liste_chainee_str *liste, char* text);

// Fonction pour ajouter un élément à la fin de la liste chaînée
void ajouter_en_queue(struct liste_chainee_str* liste, char* text);

// Fonction pour ajouter un élément au début de la liste chaînée
void ajouter_en_tete(struct liste_chainee_str* liste, char* text);

// Fonction qui renvoie la longueur de la liste chaînée
int len(struct liste_chainee_str* liste);

// Fonction pour obtenir l'élément à l'indice i de la liste chainée
char* obtenir_element(struct liste_chainee_str* liste, int index);

// Fonction qui modifie le text d'un noeud à un indice donné
void modifier_valeur(struct liste_chainee_str* liste, int i, char* nouveau_texte);

// Fonction pour inverser la liste chaînée
void inverser_liste(struct liste_chainee_str* liste);

// Fonction qui supprime un noeud d'indice donné
void supprimer_noeud(struct liste_chainee_str* liste, int i);

// Fonction pour trouver l'indice de la première occurrence d'un text
int trouver_indice(struct liste_chainee_str* liste, char* text);

// Fonction pour copier une liste chaînée
struct liste_chainee_str* copier_liste(struct liste_chainee_str* liste_source);

// Fonction pour copier une tranche de la liste chaînée
struct liste_chainee_str* copier_tranche(struct liste_chainee_str* liste_source, int i, int j);

// Fonction pour concaténer deux listes chaînées
struct liste_chainee_str* concatener_listes(struct liste_chainee_str* liste1, struct liste_chainee_str* liste2);

// Fonction pour supprimer les doublons dans une liste chaînée
void supprimer_doublons(struct liste_chainee_str* liste);

// Fonction pour insérer un noeud à un indice donné
void inserer_noeud(struct liste_chainee_str* liste, int indice, char* text);

// Fonction pour échanger les valeurs de 2 noeuds d'une liste chainée
void echanger_valeurs(struct liste_chainee_str* liste, int index1, int index2);

// Fonction pour comparer si 2 listes sont identiques
bool comparer_listes(struct liste_chainee_str* liste1, struct liste_chainee_str* liste2);

// Fonction pour trier la liste chaînée (tri rapide)
void trier_liste_alph(struct liste_chainee_str* liste);

#endif // LISTE_CHAINEE_STR_H