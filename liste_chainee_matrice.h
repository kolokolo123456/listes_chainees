#ifndef LISTE_CHAINEE_MATRICE_H
#define LISTE_CHAINEE_MATRICE_H

#include "listes_chainees.h"  // Inclusion du module de listes chaînées

// Définition de la structure d'un nœud de la liste chaînée de listes chaînées (matrice)
struct noeud_matrice {
    struct liste_chainee* liste;      // Pointeur vers une liste chaînée (ligne de la matrice)
    struct noeud_matrice* suivant;    // Pointeur vers le nœud suivant (ligne suivante)
};

// Définition de la structure de la liste chaînée de listes chaînées (matrice)
struct liste_chainee_matrice {
    struct noeud_matrice* tete;  // Pointeur vers la tête de la matrice (première ligne)
    int longueur;                // Nombre de lignes dans la matrice
};

// Fonctions pour la gestion de la matrice

// Création et destruction
struct liste_chainee_matrice* creer_matrice();
void supprime_matrice(struct liste_chainee_matrice* matrice);

// Gestion des lignes
void ajouter_ligne_en_tete(struct liste_chainee_matrice* matrice, struct liste_chainee* nouvelle_ligne);
void ajouter_ligne_en_queue(struct liste_chainee_matrice* matrice, struct liste_chainee* nouvelle_ligne);
void supprimer_ligne(struct liste_chainee_matrice* matrice, int index);
void supprimer_colonne(struct liste_chainee_matrice* matrice, int index_colonne);
struct liste_chainee* obtenir_ligne(struct liste_chainee_matrice* matrice, int index);
struct liste_chainee* obtenir_colonne(struct liste_chainee_matrice* matrice, int index_colonne);

// Gestion des éléments dans la matrice
float obtenir_element_matrice(struct liste_chainee_matrice* matrice, int index_ligne, int index_colonne);
void modifier_element(struct liste_chainee_matrice* matrice, int index_ligne, int index_colonne, float nouvelle_valeur);
void modifier_ligne(struct liste_chainee_matrice* matrice, int index_ligne, struct liste_chainee* nouvelle_ligne);
void ajouter_element_en_tete(struct liste_chainee_matrice* matrice, int index_ligne, float valeur);
void ajouter_element_en_queue(struct liste_chainee_matrice* matrice, int index_ligne, float valeur);
void ajouter_element_indice(struct liste_chainee_matrice* matrice, int index_ligne, int index_colonne, float valeur);

// Utilitaires
bool est_matrice_valide(struct liste_chainee_matrice* matrice); // Vérifie si la matrice est valide
int nombre_de_lignes(struct liste_chainee_matrice* matrice);
int nombre_de_colonnes(struct liste_chainee_matrice* matrice, int index_ligne);
struct liste_chainee_matrice* creer_matrice_zeros(int taille);
struct liste_chainee_matrice* creer_matrice_identite(int taille);

// Opérations sur la matrice
void afficher_matrice(struct liste_chainee_matrice* matrice);
void inverser_lignes(struct liste_chainee_matrice* matrice); // On inverse les lignes de la matrice
void inverser_colonnes(struct liste_chainee_matrice* matrice); // On inverse les colonnes de la matrice
struct liste_chainee_matrice* copier_matrice(struct liste_chainee_matrice* source);
struct liste_chainee_matrice* copier_tranche_matrice(struct liste_chainee_matrice* source, int i, int j);
struct liste_chainee_matrice* concatener_lignes(struct liste_chainee_matrice* matrice1, struct liste_chainee_matrice* matrice2);
struct liste_chainee_matrice* concatener_colonnes(struct liste_chainee_matrice* matrice1, struct liste_chainee_matrice* matrice2);
void echanger_lignes(struct liste_chainee_matrice* matrice, int ligne1, int ligne2);
void echanger_colonnes(struct liste_chainee_matrice* matrice, int colonne1, int colonne2);// Il faut que les matrices soient valides (utliser est_matrice_valide)

// Fonctions supplémentaires
float min_matrice(struct liste_chainee_matrice* matrice);
float max_matrice(struct liste_chainee_matrice* matrice);
struct liste_chainee_matrice* transposer_matrice(struct liste_chainee_matrice* matrice); // Transpose la matrice
void supprimer_doublons_matrice(struct liste_chainee_matrice* matrice); // Supprime les doublons de lignes
void trier_lignes_matrice(struct liste_chainee_matrice* matrice); // Trie les éléments dans chaque ligne de la matrice
struct liste_chainee_matrice* extraire_sous_matrice(struct liste_chainee_matrice* matrice, struct liste_chainee* lignes_a_supprimer, struct liste_chainee* colonnes_a_supprimer);
struct liste_chainee_matrice* rotation_matrice(struct liste_chainee_matrice* matrice, bool sens_horaire);//matrice valide
bool est_symetrique(struct liste_chainee_matrice* matrice);//matrice valide
float trace_matrice(struct liste_chainee_matrice* matrice);//matrice valide
struct liste_chainee_matrice* produit_matriciel(struct liste_chainee_matrice* matrice1, struct liste_chainee_matrice* matrice2);//matrice valide
struct liste_chainee_matrice* transformation_diagonale(struct liste_chainee_matrice* matrice); //Crée une matrice diagonale à partir de la diagonale principale d'une matrice donnée.(matrice valide)
struct liste_chainee_matrice* puissance_matrice(struct liste_chainee_matrice* matrice, int n);//atrice valide
void decomposition_LU(struct liste_chainee_matrice* matrice, struct liste_chainee_matrice** L, struct liste_chainee_matrice** U);
float calculer_determinant(struct liste_chainee_matrice* matrice);
struct liste_chainee_matrice* inverser_matrice(struct liste_chainee_matrice* matrice);

#endif /* LISTE_CHAINEE_MATRICE_H */