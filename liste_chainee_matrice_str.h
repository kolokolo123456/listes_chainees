#ifndef LISTE_CHAINEE_MATRICE_STR_H
#define LISTE_CHAINEE_MATRICE_STR_H

#include "listes_chainees_str.h"  // Inclusion du module de listes chaînées

// Définition de la structure d'un nœud de la liste chaînée de listes chaînées (matrice)
struct noeud_matrice_str {
    struct liste_chainee_str* liste;      // Pointeur vers une liste chaînée (ligne de la matrice)
    struct noeud_matrice_str* suivant;    // Pointeur vers le nœud suivant (ligne suivante)
};

// Définition de la structure de la liste chaînée de listes chaînées (matrice)
struct liste_chainee_matrice_str {
    struct noeud_matrice_str* tete;  // Pointeur vers la tête de la matrice (première ligne)
    int longueur;                // Nombre de lignes dans la matrice
};

// Fonctions pour la gestion de la matrice

// Création et destruction
struct liste_chainee_matrice_str* creer_matrice();
void supprime_matrice(struct liste_chainee_matrice_str* matrice);

// Gestion des lignes
void ajouter_ligne_en_tete(struct liste_chainee_matrice_str* matrice, struct liste_chainee_str* nouvelle_ligne);
void ajouter_ligne_en_queue(struct liste_chainee_matrice_str* matrice, struct liste_chainee_str* nouvelle_ligne);
void supprimer_ligne(struct liste_chainee_matrice_str* matrice, int index);
void supprimer_colonne(struct liste_chainee_matrice_str* matrice, int index_colonne);
struct liste_chainee_str* obtenir_ligne(struct liste_chainee_matrice_str* matrice, int index);
struct liste_chainee_str* obtenir_colonne(struct liste_chainee_matrice_str* matrice, int index_colonne);

// Gestion des éléments dans la matrice
char* obtenir_element_matrice(struct liste_chainee_matrice_str* matrice, int index_ligne, int index_colonne);
void modifier_element(struct liste_chainee_matrice_str* matrice, int index_ligne, int index_colonne, char* text);
void modifier_ligne(struct liste_chainee_matrice_str* matrice, int index_ligne, struct liste_chainee_str* nouvelle_ligne);
void ajouter_element_en_tete(struct liste_chainee_matrice_str* matrice, int index_ligne, char* text);
void ajouter_element_en_queue(struct liste_chainee_matrice_str* matrice, int index_ligne, char* text);
void ajouter_element_indice(struct liste_chainee_matrice_str* matrice, int index_ligne, int index_colonne, char* text);

// Utilitaires
bool est_matrice_valide(struct liste_chainee_matrice_str* matrice); // Vérifie si la matrice est valide
int nombre_de_lignes(struct liste_chainee_matrice_str* matrice);
int nombre_de_colonnes(struct liste_chainee_matrice_str* matrice, int index_ligne);

// Opérations sur la matrice
void afficher_matrice(struct liste_chainee_matrice_str* matrice);
void inverser_lignes(struct liste_chainee_matrice_str* matrice); // On inverse les lignes de la matrice
void inverser_colonnes(struct liste_chainee_matrice_str* matrice); // On inverse les colonnes de la matrice
struct liste_chainee_matrice_str* copier_matrice(struct liste_chainee_matrice_str* source);
struct liste_chainee_matrice_str* copier_tranche_matrice(struct liste_chainee_matrice_str* source, int i, int j);
struct liste_chainee_matrice_str* concatener_lignes(struct liste_chainee_matrice_str* matrice1, struct liste_chainee_matrice_str* matrice2);
struct liste_chainee_matrice_str* concatener_colonnes(struct liste_chainee_matrice_str* matrice1, struct liste_chainee_matrice_str* matrice2);
void echanger_lignes(struct liste_chainee_matrice_str* matrice, int ligne1, int ligne2);
void echanger_colonnes(struct liste_chainee_matrice_str* matrice, int colonne1, int colonne2);// Il faut que les matrices soient valides (utliser est_matrice_valide)

// Fonctions supplémentaires
struct liste_chainee_matrice_str* transposer_matrice(struct liste_chainee_matrice_str* matrice); // Transpose la matrice
void supprimer_doublons_matrice(struct liste_chainee_matrice_str* matrice); // Supprime les doublons de lignes
void trier_lignes_matrice(struct liste_chainee_matrice_str* matrice); // Trie les éléments dans chaque ligne de la matrice
struct liste_chainee_matrice_str* rotation_matrice(struct liste_chainee_matrice_str* matrice, bool sens_horaire);//matrice valide
bool est_symetrique(struct liste_chainee_matrice_str* matrice);//matrice valide

#endif /* LISTE_CHAINEE_MATRICE_STR_H */