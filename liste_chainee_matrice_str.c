#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "liste_chainee_matrice_str.h"

struct liste_chainee_matrice_str* creer_matrice() {
    // Allouer de la mémoire pour une nouvelle structure liste_chainee_matrice_str
    struct liste_chainee_matrice_str* nouvelle_matrice = (struct liste_chainee_matrice_str*) malloc(sizeof(struct liste_chainee_matrice_str));
    
    if (nouvelle_matrice == NULL) {
        printf("Erreur : impossible d'allouer la mémoire pour la matrice.\n");
        exit(EXIT_FAILURE);
    }

    // Initialiser les champs de la structure
    nouvelle_matrice->tete = NULL;
    nouvelle_matrice->longueur = 0;

    return nouvelle_matrice;
}

void supprime_matrice(struct liste_chainee_matrice_str* matrice) {
    if (matrice == NULL) {
        return;
    }

    struct noeud_matrice_str* courant = matrice->tete;
    struct noeud_matrice_str* suivant;

    // Parcourir chaque ligne (chaque noeud_str de la liste chaînée de la matrice)
    while (courant != NULL) {
        suivant = courant->suivant; // Sauvegarder le pointeur vers le noeud_str suivant
        supprime_liste(courant->liste);
        free(courant);
        courant = suivant;
    }
    
    free(matrice);
}

void ajouter_ligne_en_tete(struct liste_chainee_matrice_str* matrice, struct liste_chainee_str* nouvelle_ligne) {

    struct noeud_matrice_str* nouveau_noeud = (struct noeud_matrice_str*) malloc(sizeof(struct noeud_matrice_str));

    if (nouveau_noeud == NULL) {
        printf("Erreur : impossible d'allouer la mémoire pour le nouveau noeud_str de la matrice.\n");
        exit(EXIT_FAILURE);
    }

    nouveau_noeud->liste = nouvelle_ligne;
    nouveau_noeud->suivant = matrice->tete;
    matrice->tete = nouveau_noeud;

    matrice->longueur++; //longueur:nombre de listes chainées (lignes) de la matrice
}

void ajouter_ligne_en_queue(struct liste_chainee_matrice_str* matrice, struct liste_chainee_str* nouvelle_ligne) {

    struct noeud_matrice_str* nouveau_noeud = (struct noeud_matrice_str*) malloc(sizeof(struct noeud_matrice_str));

    if (nouveau_noeud == NULL) {
        printf("Erreur : impossible d'allouer la mémoire pour le nouveau noeud_str de la matrice.\n");
        exit(EXIT_FAILURE);
    }

    nouveau_noeud->liste = nouvelle_ligne;
    nouveau_noeud->suivant = NULL;

    // Si la matrice est vide, le nouveau noeud_str devient la tête
    if (matrice->tete == NULL) {
        matrice->tete = nouveau_noeud;
    } else {
        // Sinon, parcourir jusqu'au dernier noeud_str
        struct noeud_matrice_str* courant = matrice->tete;
        while (courant->suivant != NULL) {
            courant = courant->suivant;
        }
        courant->suivant = nouveau_noeud;
    }

    matrice->longueur++;
}

void supprimer_ligne(struct liste_chainee_matrice_str* matrice, int index) {

    if (matrice == NULL || matrice->tete == NULL || index < 0 || index >= matrice->longueur) {
        printf("Erreur : index invalide ou matrice vide.\n");
        return;
    }

    struct noeud_matrice_str* courant = matrice->tete;
    struct noeud_matrice_str* precedent = NULL;

    // Si la ligne à supprimer est la première
    if (index == 0) {
        matrice->tete = courant->suivant;
    } else {
        for (int i = 0; i < index; i++) {
            precedent = courant;
            courant = courant->suivant;
        }
        // Relier le nœud précédent au nœud suivant
        precedent->suivant = courant->suivant;
    }

    supprime_liste(courant->liste);
    free(courant);

    matrice->longueur--;
}

void supprimer_colonne(struct liste_chainee_matrice_str* matrice, int index_colonne) {
    if (matrice == NULL || index_colonne < 0) {
        printf("Erreur: Matrice non valide ou indice de colonne incorrect.\n");
        return;
    }

    struct noeud_matrice_str* ligne_actuelle = matrice->tete;
    
    // Parcourir chaque ligne de la matrice
    while (ligne_actuelle != NULL) {
        struct liste_chainee_str* ligne = ligne_actuelle->liste;

        if (ligne != NULL && index_colonne < ligne->length) {
            // Supprimer le noeud_str correspondant à la colonne
            supprimer_noeud(ligne, index_colonne);
        }
        
        ligne_actuelle = ligne_actuelle->suivant;
    }
}


struct liste_chainee_str* obtenir_ligne(struct liste_chainee_matrice_str* matrice, int index) {

    if (matrice == NULL || matrice->tete == NULL || index < 0 || index >= matrice->longueur) {
        printf("Erreur : index invalide ou matrice vide.\n");
        return NULL;
    }

    struct noeud_matrice_str* courant = matrice->tete;

    // Parcourir la matrice jusqu'à atteindre l'index
    for (int i = 0; i < index; i++) {
        courant = courant->suivant;
    }

    // Copier la ligne obtenue et retourner la copie
    return copier_liste(courant->liste);
}

struct liste_chainee_str* obtenir_colonne(struct liste_chainee_matrice_str* matrice, int index_colonne) {

    if (matrice == NULL || index_colonne < 0) {
        printf("Erreur : Matrice non valide ou indice de colonne incorrect.\n");
        return NULL;
    }

    // Créer une nouvelle liste chaînée pour stocker la colonne extraite
    struct liste_chainee_str* colonne = creer_liste();

    struct noeud_matrice_str* ligne_actuelle = matrice->tete;

    while (ligne_actuelle != NULL) {
        struct liste_chainee_str* ligne = ligne_actuelle->liste;

        // Vérifier que l'indice de la colonne est dans les limites de la ligne
        if (ligne != NULL && index_colonne < ligne->length) {
            char* text = obtenir_element(ligne, index_colonne);
            ajouter_en_queue(colonne, text);
        }

        ligne_actuelle = ligne_actuelle->suivant;
    }

    return colonne;
}

char* obtenir_element_matrice(struct liste_chainee_matrice_str* matrice, int index_ligne, int index_colonne) {

    if (matrice == NULL || matrice->tete == NULL || index_ligne < 0 || index_ligne >= matrice->longueur) {
        printf("Erreur : index de ligne invalide ou matrice vide.\n");
        return NULL;
    }

    struct noeud_matrice_str* courant = matrice->tete;

    // Parcourir la liste chaînée de la matrice pour atteindre l'index de ligne
    for (int i = 0; i < index_ligne; i++) {
        courant = courant->suivant;
    }

    // Vérifier si l'index de colonne est valide dans la ligne obtenue
    if (index_colonne < 0 || index_colonne >= len(courant->liste)) {
        printf("Erreur : index de colonne invalide.\n");
        return NULL;
    }

    // Obtenir et retourner l'élément à l'index de colonne spécifié
    return obtenir_element(courant->liste, index_colonne);
}

void modifier_element(struct liste_chainee_matrice_str* matrice, int index_ligne, int index_colonne, char* text) {
    // Vérifier si la matrice est valide et si l'index de ligne est correct
    if (matrice == NULL || matrice->tete == NULL || index_ligne < 0 || index_ligne >= matrice->longueur) {
        printf("Erreur : index de ligne invalide ou matrice vide.\n");
        return; // Retourner sans effectuer la modification
    }

    struct noeud_matrice_str* courant = matrice->tete;

    // Parcourir la liste chaînée de la matrice pour atteindre l'index de ligne
    for (int i = 0; i < index_ligne; i++) {
        courant = courant->suivant;
    }

    // Vérifier si l'index de colonne est valide dans la ligne obtenue
    if (index_colonne < 0 || index_colonne >= len(courant->liste)) {
        printf("Erreur : index de colonne invalide.\n");
        return; // Retourner sans effectuer la modification
    }

    // Modifier l'élément à l'index de colonne spécifié dans la ligne obtenue
    modifier_valeur(courant->liste, index_colonne, text);
}

void modifier_ligne(struct liste_chainee_matrice_str* matrice, int index_ligne, struct liste_chainee_str* nouvelle_ligne) {
    if (matrice == NULL || matrice->tete == NULL) {
        printf("La matrice est vide ou invalide.\n");
        return;
    }

    if (index_ligne < 0 || index_ligne >= matrice->longueur) {
        printf("Index de ligne invalide.\n");
        return;
    }

    struct noeud_matrice_str* courant = matrice->tete;
    struct noeud_matrice_str* precedent = NULL;

    // Trouver la ligne à modifier
    for (int i = 0; i < index_ligne; i++) {
        if (courant == NULL) {
            printf("Erreur: La ligne spécifiée n'existe pas.\n");
            return;
        }
        precedent = courant;
        courant = courant->suivant;
    }

    // Supprimer la ligne existante
    if (courant != NULL) {
        supprime_liste(courant->liste); // Libérer la mémoire de l'ancienne ligne
        courant->liste = NULL; // Optionnel: Pour éviter l'accès à la mémoire libérée
    } else {
        printf("Erreur: La ligne spécifiée n'existe pas.\n");
        return;
    }

    // Insérer la nouvelle ligne
    struct noeud_matrice_str* nouveau_noeud = (struct noeud_matrice_str*)malloc(sizeof(struct noeud_matrice_str));
    if (nouveau_noeud == NULL) {
        printf("Erreur d'allocation mémoire.\n");
        return;
    }

    nouveau_noeud->liste = nouvelle_ligne;
    nouveau_noeud->suivant = courant->suivant; // Lier au suivant de l'ancien noeud_str

    if (precedent == NULL) {
        // On modifie la tête de la matrice
        matrice->tete = nouveau_noeud;
    } else {
        // On modifie un noeud_str intermédiaire
        precedent->suivant = nouveau_noeud;
    }

    // Mettre à jour le prochain noeud_str du nouvel élément
    if (courant != NULL) {
        free(courant); // Libérer l'ancien noeud_str
    }
}

void ajouter_element_en_tete(struct liste_chainee_matrice_str* matrice, int index_ligne, char* text) {

    if (matrice == NULL || matrice->tete == NULL || index_ligne < 0 || index_ligne >= matrice->longueur) {
        printf("Erreur : index de ligne invalide ou matrice vide.\n");
        return;
    }

    struct noeud_matrice_str* courant = matrice->tete;

    // Parcourir la liste chaînée de la matrice pour atteindre l'index de ligne
    for (int i = 0; i < index_ligne; i++) {
        courant = courant->suivant;
    }

    // Ajouter l'élément en tête de la ligne obtenue
    ajouter_en_tete(courant->liste, text);
}

void ajouter_element_en_queue(struct liste_chainee_matrice_str* matrice, int index_ligne, char* text) {

    if (matrice == NULL || matrice->tete == NULL || index_ligne < 0 || index_ligne >= matrice->longueur) {
        printf("Erreur : index de ligne invalide ou matrice vide.\n");
        return;
    }

    struct noeud_matrice_str* courant = matrice->tete;

    // Parcourir la liste chaînée de la matrice pour atteindre l'index de ligne
    for (int i = 0; i < index_ligne; i++) {
        courant = courant->suivant;
    }

    // Ajouter l'élément en queue de la ligne obtenue
    ajouter_en_queue(courant->liste, text);
}

void ajouter_element_indice(struct liste_chainee_matrice_str* matrice, int index_ligne, int index_colonne, char* text) {
    // Vérifier si la matrice est valide
    if (matrice == NULL || index_ligne < 0 || index_colonne < 0 || index_ligne >= matrice->longueur) {
        fprintf(stderr, "Erreur : Indices invalides ou matrice NULL.\n");
        return;
    }

    // Trouver la ligne spécifiée
    struct noeud_matrice_str* courant = matrice->tete;
    for (int i = 0; i < index_ligne; ++i) {
        if (courant == NULL) {
            fprintf(stderr, "Erreur : Index de ligne en dehors des limites.\n");
            return;
        }
        courant = courant->suivant;
    }

    // Vérifier si la ligne est trouvée
    if (courant == NULL) {
        fprintf(stderr, "Erreur : La ligne spécifiée n'existe pas.\n");
        return;
    }

    // Insérer l'élément dans la ligne spécifiée à la colonne spécifiée
    inserer_noeud(courant->liste, index_colonne, text);
}

bool est_matrice_valide(struct liste_chainee_matrice_str* matrice) {

    if (matrice == NULL || matrice->tete == NULL) {
        return false; // La matrice est invalide si elle est NULL ou si la tête est NULL
    }

    struct noeud_matrice_str* courant = matrice->tete;
    
    int longueur_ligne = len(courant->liste);
    if (longueur_ligne < 0) {
        return false; // La longueur de la ligne ne doit pas être négative
    }

    while (courant != NULL) {

        if (courant->liste == NULL) {
            return false; // La matrice est invalide si une ligne est NULL
        }

        if (len(courant->liste) != longueur_ligne) {
            return false; // Les longueurs des lignes ne sont pas les mêmes
        }

        courant = courant->suivant;
    }

    return true;
}

int nombre_de_lignes(struct liste_chainee_matrice_str* matrice) {

    if (matrice == NULL) {
        printf("Erreur : matrice invalide.\n");
        return -1;
    }

    return matrice->longueur;
}

int nombre_de_colonnes(struct liste_chainee_matrice_str* matrice, int index_ligne) {

    if (matrice == NULL || matrice->tete == NULL || index_ligne < 0 || index_ligne >= matrice->longueur) {
        printf("Erreur : index de ligne invalide ou matrice vide.\n");
        return -1;
    }

    struct noeud_matrice_str* courant = matrice->tete;

    for (int i = 0; i < index_ligne; i++) {
        courant = courant->suivant;
    }

    return len(courant->liste);
}

void afficher_matrice(struct liste_chainee_matrice_str* matrice) {

    if (matrice == NULL || matrice->tete == NULL) {
        printf("La matrice est vide ou invalide.\n");
        return;
    }

    struct noeud_matrice_str* courant = matrice->tete;

    while (courant != NULL) {
        struct liste_chainee_str* ligne = courant->liste;
        
        // Vérifier si la ligne est non nulle
        if (ligne == NULL) {
            printf("Ligne invalide.\n");
            courant = courant->suivant;
            continue; // Passer à la ligne suivante
        }

        afficher_liste(ligne);
        courant = courant->suivant;
    }

    printf("\n");

}

void inverser_lignes(struct liste_chainee_matrice_str* matrice) {
    if (matrice == NULL || matrice->tete == NULL) {
        printf("La matrice est vide ou invalide.\n");
        return;
    }

    struct noeud_matrice_str* prev = NULL;
    struct noeud_matrice_str* courant = matrice->tete;
    struct noeud_matrice_str* suivant = NULL;

    // Inverser la liste chaînée des lignes
    while (courant != NULL) {
        suivant = courant->suivant;
        courant->suivant = prev;
        prev = courant;
        courant = suivant;
    }

    matrice->tete = prev;
}

void inverser_colonnes(struct liste_chainee_matrice_str* matrice) {
    if (matrice == NULL || matrice->tete == NULL) {
        printf("La matrice est vide ou invalide.\n");
        return;
    }

    struct noeud_matrice_str* courant = matrice->tete;

    // Inverser chaque liste chaînée (chaque ligne) dans la matrice
    while (courant != NULL) {
        inverser_liste(courant->liste);
        courant = courant->suivant;
    }
}

struct liste_chainee_matrice_str* copier_matrice(struct liste_chainee_matrice_str* source) {
    if (source == NULL || source->tete == NULL) {
        return NULL;
    }

    struct liste_chainee_matrice_str* copie = creer_matrice(); // Créer une nouvelle matrice vide
    struct noeud_matrice_str* courant_source = source->tete;
    struct noeud_matrice_str* courant_copie = NULL;
    struct noeud_matrice_str* prev_copie = NULL;

    // Copier chaque ligne de la matrice source
    while (courant_source != NULL) {
        struct liste_chainee_str* ligne_copie = copier_liste(courant_source->liste);

        // Créer un nouveau nœud pour la matrice copiée
        courant_copie = (struct noeud_matrice_str*)malloc(sizeof(struct noeud_matrice_str));
        if (courant_copie == NULL) {
            printf("Erreur d'allocation mémoire.\n");
            supprime_matrice(copie);
            supprime_liste(ligne_copie);
            return NULL;
        }

        courant_copie->liste = ligne_copie;
        courant_copie->suivant = NULL;

        // Ajouter le nœud à la fin de la matrice copiée
        if (copie->tete == NULL) {
            copie->tete = courant_copie; // Premier élément de la liste
        } else {
            prev_copie->suivant = courant_copie;
        }

        prev_copie = courant_copie; // Mettre à jour le précédent

        courant_source = courant_source->suivant;
    }

    copie->longueur = source->longueur;

    return copie;
}

struct liste_chainee_matrice_str* copier_tranche_matrice(struct liste_chainee_matrice_str* source, int i, int j) {
    if (source == NULL || source->tete == NULL || i < 0 || j < 0 || i > j || i >= source->longueur || j >= source->longueur) {
        printf("Erreur : indices invalides ou matrice vide.\n");
        return NULL;
    }

    struct liste_chainee_matrice_str* tranche = creer_matrice();
    struct noeud_matrice_str* courant_source = source->tete;
    struct noeud_matrice_str* courant_tranche = NULL;
    struct noeud_matrice_str* prev_tranche = NULL;

    // Avancer jusqu'à la ligne de début (i)
    for (int k = 0; k < i; k++) {
        courant_source = courant_source->suivant;
    }

    for (int k = i; k <= j; k++) {
        if (courant_source == NULL) {
            break; // Si la source est plus courte que prévu
        }

        struct liste_chainee_str* ligne_copie = copier_liste(courant_source->liste);

        // Créer un nouveau nœud pour la tranche
        courant_tranche = (struct noeud_matrice_str*)malloc(sizeof(struct noeud_matrice_str));
        if (courant_tranche == NULL) {
            printf("Erreur d'allocation mémoire.\n");
            supprime_matrice(tranche); // Libérer la mémoire allouée jusqu'à présent
            supprime_liste(ligne_copie);
            return NULL;
        }

        courant_tranche->liste = ligne_copie;
        courant_tranche->suivant = NULL;

        // Ajouter le nœud à la fin de la tranche
        if (tranche->tete == NULL) {
            tranche->tete = courant_tranche; // Premier élément de la liste
        } else {
            prev_tranche->suivant = courant_tranche;
        }

        prev_tranche = courant_tranche; // Mettre à jour le précédent
        courant_source = courant_source->suivant; // Passer à la ligne suivante dans la source
    }

    tranche->longueur = j - i + 1; // Longueur de la tranche copiée

    return tranche;
}

struct liste_chainee_matrice_str* concatener_lignes(struct liste_chainee_matrice_str* matrice1, struct liste_chainee_matrice_str* matrice2) {
    if (matrice1 == NULL || matrice2 == NULL) {
        printf("Une ou les deux matrices sont NULL.\n");
        return NULL;
    }

    // Créer une nouvelle matrice vide pour le résultat
    struct liste_chainee_matrice_str* matrice_concatenee = (struct liste_chainee_matrice_str*)malloc(sizeof(struct liste_chainee_matrice_str));
    if (matrice_concatenee == NULL) {
        printf("Erreur d'allocation mémoire pour la matrice concaténée.\n");
        return NULL;
    }
    matrice_concatenee->tete = NULL;
    matrice_concatenee->longueur = 0;

    // Copier toutes les lignes de la première matrice
    struct noeud_matrice_str* courant1 = matrice1->tete;
    struct noeud_matrice_str* dernier_noeud = NULL;

    while (courant1 != NULL) {
        // Créer un nouveau nœud pour la matrice concaténée
        struct noeud_matrice_str* nouveau_noeud = (struct noeud_matrice_str*)malloc(sizeof(struct noeud_matrice_str));
        if (nouveau_noeud == NULL) {
            printf("Erreur d'allocation mémoire\n");
            supprime_matrice(matrice_concatenee);
            return NULL;
        }
        // Copier la liste de la ligne courante
        nouveau_noeud->liste = copier_liste(courant1->liste);
        if (nouveau_noeud->liste == NULL) {
            printf("Erreur lors de la copie de la liste de la ligne.\n");
            supprime_matrice(matrice_concatenee);
            return NULL;
        }
        nouveau_noeud->suivant = NULL;

        // Ajouter le nouveau nœud à la fin de la matrice concaténée
        if (matrice_concatenee->tete == NULL) {
            matrice_concatenee->tete = nouveau_noeud;
        } else {
            dernier_noeud->suivant = nouveau_noeud;
        }
        dernier_noeud = nouveau_noeud; // Mettre à jour le dernier nœud
        matrice_concatenee->longueur++;

        courant1 = courant1->suivant;
    }

    // Ajouter les lignes de la deuxième matrice
    struct noeud_matrice_str* courant2 = matrice2->tete;

    while (courant2 != NULL) {
        // Créer un nouveau nœud pour la matrice concaténée
        struct noeud_matrice_str* nouveau_noeud = (struct noeud_matrice_str*)malloc(sizeof(struct noeud_matrice_str));
        if (nouveau_noeud == NULL) {
            printf("Erreur d'allocation mémoire\n");
            supprime_matrice(matrice_concatenee);
            return NULL;
        }
        // Copier la liste de la ligne courante
        nouveau_noeud->liste = copier_liste(courant2->liste);
        if (nouveau_noeud->liste == NULL) {
            printf("Erreur lors de la copie de la liste de la ligne.\n");
            supprime_matrice(matrice_concatenee);
            return NULL;
        }
        nouveau_noeud->suivant = NULL;

        // Ajouter le nouveau nœud à la fin de la matrice concaténée
        if (dernier_noeud == NULL) {
            matrice_concatenee->tete = nouveau_noeud;
        } else {
            dernier_noeud->suivant = nouveau_noeud;
        }
        dernier_noeud = nouveau_noeud; // Mettre à jour le dernier nœud
        matrice_concatenee->longueur++;

        courant2 = courant2->suivant;
    }

    return matrice_concatenee;
}

struct liste_chainee_matrice_str* concatener_colonnes(struct liste_chainee_matrice_str* matrice1, struct liste_chainee_matrice_str* matrice2) {
    if (matrice1 == NULL || matrice2 == NULL) {
        printf("Une ou les deux matrices sont NULL.\n");
        return NULL;
    }

    // Vérifier que les matrices ont le même nombre de lignes
    if (matrice1->longueur != matrice2->longueur) {
        printf("Les matrices n'ont pas le même nombre de lignes.\n");
        return NULL;
    }

    // Créer une nouvelle matrice vide pour le résultat
    struct liste_chainee_matrice_str* matrice_concatenee = (struct liste_chainee_matrice_str*)malloc(sizeof(struct liste_chainee_matrice_str));
    if (matrice_concatenee == NULL) {
        printf("Erreur d'allocation mémoire pour la matrice concaténée.\n");
        return NULL;
    }
    matrice_concatenee->tete = NULL;
    matrice_concatenee->longueur = 0;

    struct noeud_matrice_str* courant1 = matrice1->tete;
    struct noeud_matrice_str* courant2 = matrice2->tete;
    struct noeud_matrice_str* dernier_noeud = NULL;

    while (courant1 != NULL && courant2 != NULL) {
        // Concaténer les listes de chaque ligne
        struct liste_chainee_str* ligne_concatenee = concatener_listes(courant1->liste, courant2->liste);
        if (ligne_concatenee == NULL) {
            printf("Erreur lors de la concaténation des colonnes.\n");
            supprime_matrice(matrice_concatenee);
            return NULL;
        }

        // Créer un nouveau nœud pour la matrice concaténée
        struct noeud_matrice_str* nouveau_noeud = (struct noeud_matrice_str*)malloc(sizeof(struct noeud_matrice_str));
        if (nouveau_noeud == NULL) {
            printf("Erreur d'allocation mémoire\n");
            supprime_matrice(matrice_concatenee);
            return NULL;
        }
        nouveau_noeud->liste = ligne_concatenee;
        nouveau_noeud->suivant = NULL;

        // Ajouter le nouveau nœud à la fin de la matrice concaténée
        if (matrice_concatenee->tete == NULL) {
            matrice_concatenee->tete = nouveau_noeud;
        } else {
            dernier_noeud->suivant = nouveau_noeud;
        }
        dernier_noeud = nouveau_noeud; // Mettre à jour le dernier nœud
        matrice_concatenee->longueur++;

        courant1 = courant1->suivant;
        courant2 = courant2->suivant;
    }

    return matrice_concatenee;
}

void echanger_lignes(struct liste_chainee_matrice_str* matrice, int ligne1, int ligne2) {
    // Vérification des paramètres
    if (matrice == NULL || ligne1 < 0 || ligne2 < 0 || ligne1 == ligne2) {
        printf("Erreur : Paramètres non valides pour l'échange de lignes.\n");
        return;
    }

    // Trouver les lignes à échanger
    struct noeud_matrice_str* ligne_actuelle = matrice->tete;
    struct noeud_matrice_str* ligne1_ptr = NULL;
    struct noeud_matrice_str* ligne2_ptr = NULL;
    int index_ligne = 0;

    while (ligne_actuelle != NULL) {
        if (index_ligne == ligne1) {
            ligne1_ptr = ligne_actuelle;
        }
        if (index_ligne == ligne2) {
            ligne2_ptr = ligne_actuelle;
        }
        ligne_actuelle = ligne_actuelle->suivant;
        index_ligne++;
    }

    // Vérifier que les deux lignes ont été trouvées
    if (ligne1_ptr == NULL || ligne2_ptr == NULL) {
        printf("Erreur : Une ou les deux lignes à échanger ne sont pas présentes dans la matrice.\n");
        return;
    }

    // Échanger les lignes
    struct liste_chainee_str* temp = ligne1_ptr->liste;
    ligne1_ptr->liste = ligne2_ptr->liste;
    ligne2_ptr->liste = temp;
}

void echanger_colonnes(struct liste_chainee_matrice_str* matrice, int colonne1, int colonne2) {
    // Vérification des paramètres
    if (matrice == NULL || colonne1 < 0 || colonne2 < 0) {
        printf("Erreur : Paramètres non valides pour l'échange de colonnes.\n");
        return;
    }

    // Parcourir chaque ligne de la matrice
    struct noeud_matrice_str* ligne_actuelle = matrice->tete;

    while (ligne_actuelle != NULL) {
        // Échanger les colonnes dans la ligne actuelle
        echanger_valeurs(ligne_actuelle->liste, colonne1, colonne2);
        ligne_actuelle = ligne_actuelle->suivant;
    }
}

struct liste_chainee_matrice_str* transposer_matrice(struct liste_chainee_matrice_str* matrice) {
    if (matrice == NULL || matrice->tete == NULL) {
        return NULL; // Si la matrice est vide ou nulle, on ne fait rien
    }

    // Obtenir le nombre de lignes et de colonnes
    int nb_lignes = nombre_de_lignes(matrice);
    int nb_colonnes = nombre_de_colonnes(matrice, 0); //il faut impérativement travailler avec des matrices valides (utiliser alors est_matrice_valide pour d'assurer que cette fonction est appliquable sur la matrice)

    // Créer une nouvelle matrice pour la transposition
    struct liste_chainee_matrice_str* matrice_transposee = creer_matrice();

    // Initialiser les nouvelles lignes de la matrice transposée
    struct noeud_matrice_str* dernier_noeud = NULL;
    for (int i = 0; i < nb_colonnes; i++) {
        struct noeud_matrice_str* nouveau_noeud = (struct noeud_matrice_str*)malloc(sizeof(struct noeud_matrice_str));
        nouveau_noeud->liste = creer_liste();
        nouveau_noeud->suivant = NULL;

        if (matrice_transposee->tete == NULL) {
            matrice_transposee->tete = nouveau_noeud;
        } else {
            dernier_noeud->suivant = nouveau_noeud;
        }
        dernier_noeud = nouveau_noeud;
        matrice_transposee->longueur++;
    }

    // Parcourir chaque ligne de la matrice originale et remplir les nouvelles colonnes
    struct noeud_matrice_str* noeud_ligne = matrice->tete;
    while (noeud_ligne != NULL) {
        struct noeud_str* noeud_colonne = noeud_ligne->liste->tete;
        struct noeud_matrice_str* noeud_transpose = matrice_transposee->tete;

        while (noeud_colonne != NULL && noeud_transpose != NULL) { // Je sais qu'il suffit de vérifier l'une des 2 conditions
            // Ajouter l'élément de la colonne à la nouvelle ligne correspondante
            ajouter_en_queue(noeud_transpose->liste, noeud_colonne->text);
            noeud_colonne = noeud_colonne->suiv;
            noeud_transpose = noeud_transpose->suivant;
        }

        noeud_ligne = noeud_ligne->suivant;
    }

    return matrice_transposee;
}

void supprimer_doublons_matrice(struct liste_chainee_matrice_str* matrice) {
    if (matrice == NULL || matrice->tete == NULL) {
        return; // Si la matrice est vide ou NULL, rien à faire
    }

    struct noeud_matrice_str *ligne_courante = matrice->tete;

    while (ligne_courante != NULL) {
        struct noeud_matrice_str *prev = ligne_courante;
        struct noeud_matrice_str *ligne_comp = ligne_courante->suivant;

        while (ligne_comp != NULL) {
            if (comparer_listes(ligne_courante->liste, ligne_comp->liste)) {
                // Doublon trouvé, suppression de la ligne doublon
                prev->suivant = ligne_comp->suivant; // Ignorer la ligne doublon
                matrice->longueur--; // Mise à jour de la longueur
                supprime_liste(ligne_comp->liste);
                free(ligne_comp);
            } else {
                prev = ligne_comp;
            }
            ligne_comp = prev->suivant; // Mise à jour de `ligne_comp`
        }

        ligne_courante = ligne_courante->suivant;
    }
}

void trier_lignes_matrice(struct liste_chainee_matrice_str* matrice) {
    if (matrice == NULL || matrice->tete == NULL) {
        return; // Si la matrice est vide ou NULL, rien à faire
    }

    struct noeud_matrice_str* ligne = matrice->tete;

    while (ligne != NULL) {
        trier_liste_alph(ligne->liste);
        ligne = ligne->suivant;
    }
}

struct liste_chainee_matrice_str* rotation_matrice(struct liste_chainee_matrice_str* matrice, bool sens_horaire) {
    if (matrice == NULL || matrice->tete == NULL) {
        printf("Erreur : Matrice invalide ou vide.\n");
        return NULL;
    }

    // Transposer la matrice
    struct liste_chainee_matrice_str* matrice_transposee = transposer_matrice(matrice);
    if (matrice_transposee == NULL) {
        return NULL;
    }

    // Inverser les colonnes ou les lignes en fonction du sens de rotation
    if (sens_horaire) {
        inverser_colonnes(matrice_transposee);
    } else {
        inverser_lignes(matrice_transposee);
    }

    return matrice_transposee;
}

bool est_symetrique(struct liste_chainee_matrice_str* matrice) {
    if (matrice == NULL || matrice->tete == NULL) {
        return false;
    }

    // Vérifier si la matrice est carrée
    int nb_lignes = nombre_de_lignes(matrice);
    int nb_colonnes = nombre_de_colonnes(matrice, 0); // Nombre de colonnes dans la première ligne
    if (nb_lignes != nb_colonnes) {
        return false;
    }

    // Vérifier la symétrie
    for (int i = 0; i < nb_lignes; i++) {
        for (int j = i; j < nb_colonnes; j++) {
            char* text1 = obtenir_element_matrice(matrice, i, j);
            char* text2 = obtenir_element_matrice(matrice, j, i);
            if (strcmp(text1, text2) != 0) {
                return false;
            }
        }
    }

    return true;
}