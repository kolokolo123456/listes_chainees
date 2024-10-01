#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "liste_chainee_matrice.h"

struct liste_chainee_matrice* creer_matrice() {
    // Allouer de la mémoire pour une nouvelle structure liste_chainee_matrice
    struct liste_chainee_matrice* nouvelle_matrice = (struct liste_chainee_matrice*) malloc(sizeof(struct liste_chainee_matrice));
    
    if (nouvelle_matrice == NULL) {
        printf("Erreur : impossible d'allouer la mémoire pour la matrice.\n");
        exit(EXIT_FAILURE);
    }

    // Initialiser les champs de la structure
    nouvelle_matrice->tete = NULL;
    nouvelle_matrice->longueur = 0;

    return nouvelle_matrice;
}

void supprime_matrice(struct liste_chainee_matrice* matrice) {
    if (matrice == NULL) {
        return;
    }

    struct noeud_matrice* courant = matrice->tete;
    struct noeud_matrice* suivant;

    // Parcourir chaque ligne (chaque noeud de la liste chaînée de la matrice)
    while (courant != NULL) {
        suivant = courant->suivant; // Sauvegarder le pointeur vers le noeud suivant
        supprime_liste(courant->liste);
        free(courant);
        courant = suivant;
    }
    
    free(matrice);
}

void ajouter_ligne_en_tete(struct liste_chainee_matrice* matrice, struct liste_chainee* nouvelle_ligne) {

    struct noeud_matrice* nouveau_noeud = (struct noeud_matrice*) malloc(sizeof(struct noeud_matrice));

    if (nouveau_noeud == NULL) {
        printf("Erreur : impossible d'allouer la mémoire pour le nouveau noeud de la matrice.\n");
        exit(EXIT_FAILURE);
    }

    nouveau_noeud->liste = nouvelle_ligne;
    nouveau_noeud->suivant = matrice->tete;
    matrice->tete = nouveau_noeud;

    matrice->longueur++; //longueur:nombre de listes chainées (lignes) de la matrice
}

void ajouter_ligne_en_queue(struct liste_chainee_matrice* matrice, struct liste_chainee* nouvelle_ligne) {

    struct noeud_matrice* nouveau_noeud = (struct noeud_matrice*) malloc(sizeof(struct noeud_matrice));

    if (nouveau_noeud == NULL) {
        printf("Erreur : impossible d'allouer la mémoire pour le nouveau noeud de la matrice.\n");
        exit(EXIT_FAILURE);
    }

    nouveau_noeud->liste = nouvelle_ligne;
    nouveau_noeud->suivant = NULL;

    // Si la matrice est vide, le nouveau noeud devient la tête
    if (matrice->tete == NULL) {
        matrice->tete = nouveau_noeud;
    } else {
        // Sinon, parcourir jusqu'au dernier noeud
        struct noeud_matrice* courant = matrice->tete;
        while (courant->suivant != NULL) {
            courant = courant->suivant;
        }
        courant->suivant = nouveau_noeud;
    }

    matrice->longueur++;
}

void supprimer_ligne(struct liste_chainee_matrice* matrice, int index) {

    if (matrice == NULL || matrice->tete == NULL || index < 0 || index >= matrice->longueur) {
        printf("Erreur : index invalide ou matrice vide.\n");
        return;
    }

    struct noeud_matrice* courant = matrice->tete;
    struct noeud_matrice* precedent = NULL;

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

void supprimer_colonne(struct liste_chainee_matrice* matrice, int index_colonne) {
    if (matrice == NULL || index_colonne < 0) {
        printf("Erreur: Matrice non valide ou indice de colonne incorrect.\n");
        return;
    }

    struct noeud_matrice* ligne_actuelle = matrice->tete;
    
    // Parcourir chaque ligne de la matrice
    while (ligne_actuelle != NULL) {
        struct liste_chainee* ligne = ligne_actuelle->liste;

        if (ligne != NULL && index_colonne < ligne->length) {
            // Supprimer le noeud correspondant à la colonne
            supprimer_noeud(ligne, index_colonne);
        }
        
        ligne_actuelle = ligne_actuelle->suivant;
    }
}


struct liste_chainee* obtenir_ligne(struct liste_chainee_matrice* matrice, int index) {

    if (matrice == NULL || matrice->tete == NULL || index < 0 || index >= matrice->longueur) {
        printf("Erreur : index invalide ou matrice vide.\n");
        return NULL;
    }

    struct noeud_matrice* courant = matrice->tete;

    // Parcourir la matrice jusqu'à atteindre l'index
    for (int i = 0; i < index; i++) {
        courant = courant->suivant;
    }

    // Copier la ligne obtenue et retourner la copie
    return copier_liste(courant->liste);
}

struct liste_chainee* obtenir_colonne(struct liste_chainee_matrice* matrice, int index_colonne) {

    if (matrice == NULL || index_colonne < 0) {
        printf("Erreur : Matrice non valide ou indice de colonne incorrect.\n");
        return NULL;
    }

    // Créer une nouvelle liste chaînée pour stocker la colonne extraite
    struct liste_chainee* colonne = creer_liste();

    struct noeud_matrice* ligne_actuelle = matrice->tete;

    while (ligne_actuelle != NULL) {
        struct liste_chainee* ligne = ligne_actuelle->liste;

        // Vérifier que l'indice de la colonne est dans les limites de la ligne
        if (ligne != NULL && index_colonne < ligne->length) {
            float valeur = obtenir_element(ligne, index_colonne);
            ajouter_en_queue(colonne, valeur);
        }

        ligne_actuelle = ligne_actuelle->suivant;
    }

    return colonne;
}

float obtenir_element_matrice(struct liste_chainee_matrice* matrice, int index_ligne, int index_colonne) {

    if (matrice == NULL || matrice->tete == NULL || index_ligne < 0 || index_ligne >= matrice->longueur) {
        printf("Erreur : index de ligne invalide ou matrice vide.\n");
        return -1;// -1: val d'erreur
    }

    struct noeud_matrice* courant = matrice->tete;

    // Parcourir la liste chaînée de la matrice pour atteindre l'index de ligne
    for (int i = 0; i < index_ligne; i++) {
        courant = courant->suivant;
    }

    // Vérifier si l'index de colonne est valide dans la ligne obtenue
    if (index_colonne < 0 || index_colonne >= len(courant->liste)) {
        printf("Erreur : index de colonne invalide.\n");
        return -1;
    }

    // Obtenir et retourner l'élément à l'index de colonne spécifié
    return obtenir_element(courant->liste, index_colonne);
}

void modifier_element(struct liste_chainee_matrice* matrice, int index_ligne, int index_colonne, float nouvelle_valeur) {
    // Vérifier si la matrice est valide et si l'index de ligne est correct
    if (matrice == NULL || matrice->tete == NULL || index_ligne < 0 || index_ligne >= matrice->longueur) {
        printf("Erreur : index de ligne invalide ou matrice vide.\n");
        return; // Retourner sans effectuer la modification
    }

    struct noeud_matrice* courant = matrice->tete;

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
    modifier_valeur(courant->liste, index_colonne, nouvelle_valeur);
}

void modifier_ligne(struct liste_chainee_matrice* matrice, int index_ligne, struct liste_chainee* nouvelle_ligne) {
    if (matrice == NULL || matrice->tete == NULL) {
        printf("La matrice est vide ou invalide.\n");
        return;
    }

    if (index_ligne < 0 || index_ligne >= matrice->longueur) {
        printf("Index de ligne invalide.\n");
        return;
    }

    struct noeud_matrice* courant = matrice->tete;
    struct noeud_matrice* precedent = NULL;

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
    struct noeud_matrice* nouveau_noeud = (struct noeud_matrice*)malloc(sizeof(struct noeud_matrice));
    if (nouveau_noeud == NULL) {
        printf("Erreur d'allocation mémoire.\n");
        return;
    }

    nouveau_noeud->liste = nouvelle_ligne;
    nouveau_noeud->suivant = courant->suivant; // Lier au suivant de l'ancien noeud

    if (precedent == NULL) {
        // On modifie la tête de la matrice
        matrice->tete = nouveau_noeud;
    } else {
        // On modifie un noeud intermédiaire
        precedent->suivant = nouveau_noeud;
    }

    // Mettre à jour le prochain noeud du nouvel élément
    if (courant != NULL) {
        free(courant); // Libérer l'ancien noeud
    }
}

void ajouter_element_en_tete(struct liste_chainee_matrice* matrice, int index_ligne, float valeur) {

    if (matrice == NULL || matrice->tete == NULL || index_ligne < 0 || index_ligne >= matrice->longueur) {
        printf("Erreur : index de ligne invalide ou matrice vide.\n");
        return;
    }

    struct noeud_matrice* courant = matrice->tete;

    // Parcourir la liste chaînée de la matrice pour atteindre l'index de ligne
    for (int i = 0; i < index_ligne; i++) {
        courant = courant->suivant;
    }

    // Ajouter l'élément en tête de la ligne obtenue
    ajouter_en_tete(courant->liste, valeur);
}

void ajouter_element_en_queue(struct liste_chainee_matrice* matrice, int index_ligne, float valeur) {

    if (matrice == NULL || matrice->tete == NULL || index_ligne < 0 || index_ligne >= matrice->longueur) {
        printf("Erreur : index de ligne invalide ou matrice vide.\n");
        return;
    }

    struct noeud_matrice* courant = matrice->tete;

    // Parcourir la liste chaînée de la matrice pour atteindre l'index de ligne
    for (int i = 0; i < index_ligne; i++) {
        courant = courant->suivant;
    }

    // Ajouter l'élément en queue de la ligne obtenue
    ajouter_en_queue(courant->liste, valeur);
}

void ajouter_element_indice(struct liste_chainee_matrice* matrice, int index_ligne, int index_colonne, float valeur) {
    // Vérifier si la matrice est valide
    if (matrice == NULL || index_ligne < 0 || index_colonne < 0 || index_ligne >= matrice->longueur) {
        fprintf(stderr, "Erreur : Indices invalides ou matrice NULL.\n");
        return;
    }

    // Trouver la ligne spécifiée
    struct noeud_matrice* courant = matrice->tete;
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
    inserer_noeud(courant->liste, index_colonne, valeur);
}

bool est_matrice_valide(struct liste_chainee_matrice* matrice) {

    if (matrice == NULL || matrice->tete == NULL) {
        return false; // La matrice est invalide si elle est NULL ou si la tête est NULL
    }

    struct noeud_matrice* courant = matrice->tete;
    
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

int nombre_de_lignes(struct liste_chainee_matrice* matrice) {

    if (matrice == NULL) {
        printf("Erreur : matrice invalide.\n");
        return -1;
    }

    return matrice->longueur;
}

int nombre_de_colonnes(struct liste_chainee_matrice* matrice, int index_ligne) {

    if (matrice == NULL || matrice->tete == NULL || index_ligne < 0 || index_ligne >= matrice->longueur) {
        printf("Erreur : index de ligne invalide ou matrice vide.\n");
        return -1;
    }

    struct noeud_matrice* courant = matrice->tete;

    for (int i = 0; i < index_ligne; i++) {
        courant = courant->suivant;
    }

    return len(courant->liste);
}

struct liste_chainee_matrice* creer_matrice_zeros(int taille) {
    struct liste_chainee_matrice* matrice = creer_matrice();
    for (int i = 0; i < taille; i++) {
        struct liste_chainee* ligne = creer_liste();
        for (int j = 0; j < taille; j++) {
            ajouter_en_queue(ligne, 0.0f);
        }
        ajouter_ligne_en_queue(matrice, ligne);
    }
    return matrice;
}

struct liste_chainee_matrice* creer_matrice_identite(int taille) {
    struct liste_chainee_matrice* identite = creer_matrice();
    for (int i = 0; i < taille; i++) {
        struct liste_chainee* ligne = creer_liste();
        for (int j = 0; j < taille; j++) {
            if (i == j) {
                ajouter_en_queue(ligne, 1.0f);
            } else {
                ajouter_en_queue(ligne, 0.0f);
            }
        }
        ajouter_ligne_en_queue(identite, ligne);
    }
    return identite;
}

void afficher_matrice(struct liste_chainee_matrice* matrice) {

    if (matrice == NULL || matrice->tete == NULL) {
        printf("La matrice est vide ou invalide.\n");
        return;
    }

    struct noeud_matrice* courant = matrice->tete;

    while (courant != NULL) {
        struct liste_chainee* ligne = courant->liste;
        
        // Vérifier si la ligne est non nulle
        if (ligne == NULL) {
            printf("Ligne invalide.\n");
            courant = courant->suivant;
            continue; // Passer à la ligne suivante
        }

        struct noeud* noeud_ligne = ligne->tete;

        // Afficher les éléments de la ligne
        while (noeud_ligne != NULL) {
            printf("%f ", noeud_ligne->val);
            noeud_ligne = noeud_ligne->suiv;
        }

        printf("\n"); // Passer à la ligne suivante

        courant = courant->suivant;
    }

    printf("\n");

}

void inverser_lignes(struct liste_chainee_matrice* matrice) {
    if (matrice == NULL || matrice->tete == NULL) {
        printf("La matrice est vide ou invalide.\n");
        return;
    }

    struct noeud_matrice* prev = NULL;
    struct noeud_matrice* courant = matrice->tete;
    struct noeud_matrice* suivant = NULL;

    // Inverser la liste chaînée des lignes
    while (courant != NULL) {
        suivant = courant->suivant;
        courant->suivant = prev;
        prev = courant;
        courant = suivant;
    }

    matrice->tete = prev;
}

void inverser_colonnes(struct liste_chainee_matrice* matrice) {
    if (matrice == NULL || matrice->tete == NULL) {
        printf("La matrice est vide ou invalide.\n");
        return;
    }

    struct noeud_matrice* courant = matrice->tete;

    // Inverser chaque liste chaînée (chaque ligne) dans la matrice
    while (courant != NULL) {
        inverser_liste(courant->liste);
        courant = courant->suivant;
    }
}

struct liste_chainee_matrice* copier_matrice(struct liste_chainee_matrice* source) {
    if (source == NULL || source->tete == NULL) {
        return NULL;
    }

    struct liste_chainee_matrice* copie = creer_matrice(); // Créer une nouvelle matrice vide
    struct noeud_matrice* courant_source = source->tete;
    struct noeud_matrice* courant_copie = NULL;
    struct noeud_matrice* prev_copie = NULL;

    // Copier chaque ligne de la matrice source
    while (courant_source != NULL) {
        struct liste_chainee* ligne_copie = copier_liste(courant_source->liste);

        // Créer un nouveau nœud pour la matrice copiée
        courant_copie = (struct noeud_matrice*)malloc(sizeof(struct noeud_matrice));
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

struct liste_chainee_matrice* copier_tranche_matrice(struct liste_chainee_matrice* source, int i, int j) {
    if (source == NULL || source->tete == NULL || i < 0 || j < 0 || i > j || i >= source->longueur || j >= source->longueur) {
        printf("Erreur : indices invalides ou matrice vide.\n");
        return NULL;
    }

    struct liste_chainee_matrice* tranche = creer_matrice();
    struct noeud_matrice* courant_source = source->tete;
    struct noeud_matrice* courant_tranche = NULL;
    struct noeud_matrice* prev_tranche = NULL;

    // Avancer jusqu'à la ligne de début (i)
    for (int k = 0; k < i; k++) {
        courant_source = courant_source->suivant;
    }

    for (int k = i; k <= j; k++) {
        if (courant_source == NULL) {
            break; // Si la source est plus courte que prévu
        }

        struct liste_chainee* ligne_copie = copier_liste(courant_source->liste);

        // Créer un nouveau nœud pour la tranche
        courant_tranche = (struct noeud_matrice*)malloc(sizeof(struct noeud_matrice));
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

struct liste_chainee_matrice* concatener_lignes(struct liste_chainee_matrice* matrice1, struct liste_chainee_matrice* matrice2) {
    if (matrice1 == NULL || matrice2 == NULL) {
        printf("Une ou les deux matrices sont NULL.\n");
        return NULL;
    }

    // Créer une nouvelle matrice vide pour le résultat
    struct liste_chainee_matrice* matrice_concatenee = (struct liste_chainee_matrice*)malloc(sizeof(struct liste_chainee_matrice));
    if (matrice_concatenee == NULL) {
        printf("Erreur d'allocation mémoire pour la matrice concaténée.\n");
        return NULL;
    }
    matrice_concatenee->tete = NULL;
    matrice_concatenee->longueur = 0;

    // Copier toutes les lignes de la première matrice
    struct noeud_matrice* courant1 = matrice1->tete;
    struct noeud_matrice* dernier_noeud = NULL;

    while (courant1 != NULL) {
        // Créer un nouveau nœud pour la matrice concaténée
        struct noeud_matrice* nouveau_noeud = (struct noeud_matrice*)malloc(sizeof(struct noeud_matrice));
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
    struct noeud_matrice* courant2 = matrice2->tete;

    while (courant2 != NULL) {
        // Créer un nouveau nœud pour la matrice concaténée
        struct noeud_matrice* nouveau_noeud = (struct noeud_matrice*)malloc(sizeof(struct noeud_matrice));
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

struct liste_chainee_matrice* concatener_colonnes(struct liste_chainee_matrice* matrice1, struct liste_chainee_matrice* matrice2) {
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
    struct liste_chainee_matrice* matrice_concatenee = (struct liste_chainee_matrice*)malloc(sizeof(struct liste_chainee_matrice));
    if (matrice_concatenee == NULL) {
        printf("Erreur d'allocation mémoire pour la matrice concaténée.\n");
        return NULL;
    }
    matrice_concatenee->tete = NULL;
    matrice_concatenee->longueur = 0;

    struct noeud_matrice* courant1 = matrice1->tete;
    struct noeud_matrice* courant2 = matrice2->tete;
    struct noeud_matrice* dernier_noeud = NULL;

    while (courant1 != NULL && courant2 != NULL) {
        // Concaténer les listes de chaque ligne
        struct liste_chainee* ligne_concatenee = concatener_listes(courant1->liste, courant2->liste);
        if (ligne_concatenee == NULL) {
            printf("Erreur lors de la concaténation des colonnes.\n");
            supprime_matrice(matrice_concatenee);
            return NULL;
        }

        // Créer un nouveau nœud pour la matrice concaténée
        struct noeud_matrice* nouveau_noeud = (struct noeud_matrice*)malloc(sizeof(struct noeud_matrice));
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

void echanger_lignes(struct liste_chainee_matrice* matrice, int ligne1, int ligne2) {
    // Vérification des paramètres
    if (matrice == NULL || ligne1 < 0 || ligne2 < 0 || ligne1 == ligne2) {
        printf("Erreur : Paramètres non valides pour l'échange de lignes.\n");
        return;
    }

    // Trouver les lignes à échanger
    struct noeud_matrice* ligne_actuelle = matrice->tete;
    struct noeud_matrice* ligne1_ptr = NULL;
    struct noeud_matrice* ligne2_ptr = NULL;
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
    struct liste_chainee* temp = ligne1_ptr->liste;
    ligne1_ptr->liste = ligne2_ptr->liste;
    ligne2_ptr->liste = temp;
}

void echanger_colonnes(struct liste_chainee_matrice* matrice, int colonne1, int colonne2) {
    // Vérification des paramètres
    if (matrice == NULL || colonne1 < 0 || colonne2 < 0) {
        printf("Erreur : Paramètres non valides pour l'échange de colonnes.\n");
        return;
    }

    // Parcourir chaque ligne de la matrice
    struct noeud_matrice* ligne_actuelle = matrice->tete;

    while (ligne_actuelle != NULL) {
        // Échanger les colonnes dans la ligne actuelle
        echanger_valeurs(ligne_actuelle->liste, colonne1, colonne2);
        ligne_actuelle = ligne_actuelle->suivant;
    }
}

float min_matrice(struct liste_chainee_matrice* matrice) {
    if (matrice == NULL || matrice->tete == NULL) {
        printf("La matrice est vide ou invalide.\n");
        return -1; // Valeur indiquant que la matrice est invalide
    }

    // Assumer que la première ligne et liste sont valides
    struct noeud_matrice* courant = matrice->tete;
    float min_global = min(courant->liste); // Initialiser avec la première ligne
    courant = courant->suivant; // Passer à la ligne suivante

    // Parcourir toutes les lignes de la matrice
    while (courant != NULL) {
        float min_ligne = min(courant->liste); // Trouver le minimum dans la ligne courante
        if (min_ligne < min_global) {
            min_global = min_ligne;
        }
        courant = courant->suivant; // Passer à la ligne suivante
    }

    return min_global;
}

float max_matrice(struct liste_chainee_matrice* matrice) {
    if (matrice == NULL || matrice->tete == NULL) {
        printf("La matrice est vide ou invalide.\n");
        return -1; // Valeur indiquant que la matrice est invalide
    }

    // Assumer que la première ligne et liste sont valides
    struct noeud_matrice* courant = matrice->tete;
    float max_global = max(courant->liste); // Initialiser avec la première ligne
    courant = courant->suivant; // Passer à la ligne suivante

    // Parcourir toutes les lignes de la matrice
    while (courant != NULL) {
        float max_ligne = max(courant->liste); // Trouver le maximum dans la ligne courante
        if (max_ligne > max_global) {
            max_global = max_ligne;
        }
        courant = courant->suivant; // Passer à la ligne suivante
    }

    return max_global;
}

struct liste_chainee_matrice* transposer_matrice(struct liste_chainee_matrice* matrice) {
    if (matrice == NULL || matrice->tete == NULL) {
        return NULL; // Si la matrice est vide ou nulle, on ne fait rien
    }

    // Obtenir le nombre de lignes et de colonnes
    int nb_lignes = nombre_de_lignes(matrice);
    int nb_colonnes = nombre_de_colonnes(matrice, 0); //il faut impérativement travailler avec des matrices valides (utiliser alors est_matrice_valide pour d'assurer que cette fonction est appliquable sur la matrice)

    // Créer une nouvelle matrice pour la transposition
    struct liste_chainee_matrice* matrice_transposee = creer_matrice();

    // Initialiser les nouvelles lignes de la matrice transposée
    struct noeud_matrice* dernier_noeud = NULL;
    for (int i = 0; i < nb_colonnes; i++) {
        struct noeud_matrice* nouveau_noeud = (struct noeud_matrice*)malloc(sizeof(struct noeud_matrice));
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
    struct noeud_matrice* noeud_ligne = matrice->tete;
    while (noeud_ligne != NULL) {
        struct noeud* noeud_colonne = noeud_ligne->liste->tete;
        struct noeud_matrice* noeud_transpose = matrice_transposee->tete;

        while (noeud_colonne != NULL && noeud_transpose != NULL) { // Je sais qu'il suffit de vérifier l'une des 2 conditions
            // Ajouter l'élément de la colonne à la nouvelle ligne correspondante
            ajouter_en_queue(noeud_transpose->liste, noeud_colonne->val);
            noeud_colonne = noeud_colonne->suiv;
            noeud_transpose = noeud_transpose->suivant;
        }

        noeud_ligne = noeud_ligne->suivant;
    }

    return matrice_transposee;
}

void supprimer_doublons_matrice(struct liste_chainee_matrice* matrice) {
    if (matrice == NULL || matrice->tete == NULL) {
        return; // Si la matrice est vide ou NULL, rien à faire
    }

    struct noeud_matrice *ligne_courante = matrice->tete;

    while (ligne_courante != NULL) {
        struct noeud_matrice *prev = ligne_courante;
        struct noeud_matrice *ligne_comp = ligne_courante->suivant;

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

void trier_lignes_matrice(struct liste_chainee_matrice* matrice) {
    if (matrice == NULL || matrice->tete == NULL) {
        return; // Si la matrice est vide ou NULL, rien à faire
    }

    struct noeud_matrice* ligne = matrice->tete;

    while (ligne != NULL) {
        trier_liste(ligne->liste);
        ligne = ligne->suivant;
    }
}

struct liste_chainee_matrice* extraire_sous_matrice(struct liste_chainee_matrice* matrice, struct liste_chainee* lignes_a_supprimer, struct liste_chainee* colonnes_a_supprimer) {
    // Vérification des paramètres
    if (matrice == NULL || lignes_a_supprimer == NULL || colonnes_a_supprimer == NULL) {
        printf("Erreur : Matrice ou listes de suppression non valides.\n");
        return NULL;
    }

    // Créer une nouvelle matrice pour la sous-matrice
    struct liste_chainee_matrice* sous_matrice = creer_matrice();
    if (sous_matrice == NULL) {
        printf("Erreur : Impossible de créer la sous-matrice.\n");
        return NULL;
    }

    // Initialiser les pointeurs pour parcourir les lignes à supprimer et les colonnes à supprimer
    struct noeud_matrice* ligne_actuelle = matrice->tete;
    int index_ligne = 0;

    while (ligne_actuelle != NULL) {
        // Vérifier si la ligne actuelle doit être supprimée
        if (!in(lignes_a_supprimer, (float)index_ligne)) {
            // Créer une nouvelle ligne pour la sous-matrice
            struct liste_chainee* nouvelle_ligne = creer_liste();
            if (nouvelle_ligne == NULL) {
                printf("Erreur : Impossible de créer une ligne de la sous-matrice.\n");
                supprime_matrice(sous_matrice);
                return NULL;
            }

            // Parcourir chaque élément de la ligne actuelle
            struct noeud* noeud_actuel = ligne_actuelle->liste->tete;
            int index_colonne = 0;

            while (noeud_actuel != NULL) {
                // Vérifier si la colonne actuelle doit être supprimée
                if (!in(colonnes_a_supprimer, (float)index_colonne)) {
                    // Ajouter l'élément à la nouvelle ligne
                    ajouter_en_queue(nouvelle_ligne, noeud_actuel->val);
                }

                noeud_actuel = noeud_actuel->suiv;
                index_colonne++;
            }

            // Ajouter la nouvelle ligne à la sous-matrice
            ajouter_ligne_en_queue(sous_matrice, nouvelle_ligne);
        }

        ligne_actuelle = ligne_actuelle->suivant;
        index_ligne++;
    }

    return sous_matrice;
}

struct liste_chainee_matrice* rotation_matrice(struct liste_chainee_matrice* matrice, bool sens_horaire) {
    if (matrice == NULL || matrice->tete == NULL) {
        printf("Erreur : Matrice invalide ou vide.\n");
        return NULL;
    }

    // Transposer la matrice
    struct liste_chainee_matrice* matrice_transposee = transposer_matrice(matrice);
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

bool est_symetrique(struct liste_chainee_matrice* matrice) {
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
            float val1 = obtenir_element_matrice(matrice, i, j);
            float val2 = obtenir_element_matrice(matrice, j, i);
            if (val1 != val2) {
                return false;
            }
        }
    }

    return true;
}

float trace_matrice(struct liste_chainee_matrice* matrice) {
    // Vérifier que la matrice est valide
    if (matrice == NULL) {
        return 0.0f;  // La trace d'une matrice invalide est considérée comme 0
    }

    // Déterminer le nombre de lignes de la matrice
    int nb_lignes = nombre_de_lignes(matrice);
    int nb_colonnes = nombre_de_colonnes(matrice, 0);

    // La matrice doit être carrée pour que la trace soit bien définie
    if (nb_colonnes != nb_lignes) {
        printf("Erreur : La matrice doit être carrée.\n");
        return 0.0f;  // La trace d'une matrice non carrée est considérée comme 0
    }

    // Initialiser la somme pour la trace
    float trace = 0.0f;

    // Parcourir les lignes de la matrice
    struct noeud_matrice* ligne_courante = matrice->tete;
    int index_ligne = 0;

    while (ligne_courante != NULL && index_ligne < nb_lignes) {
        // Parcourir les éléments de la ligne pour trouver l'élément diagonal
        struct noeud* element_courant = ligne_courante->liste->tete;
        int index_colonne = 0;

        // Avancer jusqu'à l'élément diagonal
        while (element_courant != NULL && index_colonne < index_ligne) {
            element_courant = element_courant->suiv;
            index_colonne++;
        }

        // Ajouter l'élément diagonal à la trace
        if (element_courant != NULL && index_colonne == index_ligne) {
            trace += element_courant->val;
        }

        // Passer à la ligne suivante
        ligne_courante = ligne_courante->suivant;
        index_ligne++;
    }

    return trace;
}

struct liste_chainee_matrice* produit_matriciel(struct liste_chainee_matrice* matrice1, struct liste_chainee_matrice* matrice2) {
    
    if (matrice1 == NULL || matrice2 == NULL) {
        printf("Erreur : Matrices invalides ou vides.\n");
        return NULL;
    }

    // Vérification des dimensions
    if (nombre_de_colonnes(matrice1, 0) != nombre_de_lignes(matrice2)) {
        printf("Erreur: Les dimensions des matrices ne sont pas compatibles pour le produit.\n");
        return NULL;
    }

    // Création de la matrice résultat
    struct liste_chainee_matrice* resultat = creer_matrice();

    // Parcours des lignes de matrice1
    struct noeud_matrice* ligne1 = matrice1->tete;
    while (ligne1 != NULL) {
        // Création d'une nouvelle ligne pour le résultat
        struct liste_chainee* nouvelle_ligne = creer_liste();

        // Parcours des colonnes de matrice2
        for (int j = 0; j < nombre_de_colonnes(matrice2, 0); j++) {
            float somme = 0.0;

            // Parcours des éléments de la ligne de matrice1 et de la colonne correspondante de matrice2
            struct noeud* element1 = ligne1->liste->tete;
            struct noeud_matrice* ligne2 = matrice2->tete;

            while (element1 != NULL && ligne2 != NULL) {//une condition suffit,c'est juste pour vérifier que tout est cohérent
                // Accéder à l'élément correspondant dans la colonne j de matrice2
                struct noeud* element2 = ligne2->liste->tete;
                for (int k = 0; k < j && element2 != NULL; k++) {
                    element2 = element2->suiv;
                }

                if (element2 != NULL) {
                    somme += element1->val * element2->val;
                }

                element1 = element1->suiv;
                ligne2 = ligne2->suivant;
            }

            // Ajout de l'élément calculé à la nouvelle ligne
            ajouter_en_queue(nouvelle_ligne, somme);
        }

        // Ajout de la nouvelle ligne au résultat
        ajouter_ligne_en_queue(resultat, nouvelle_ligne);

        ligne1 = ligne1->suivant;
    }

    return resultat;
}

struct liste_chainee_matrice* transformation_diagonale(struct liste_chainee_matrice* matrice) {
    // Vérification si la matrice est valide
    if (matrice == NULL || matrice->tete == NULL) {
        printf("Erreur : Matrice invalide ou vide.\n");
        return NULL;
    }

    // Création de la nouvelle matrice diagonale
    struct liste_chainee_matrice* matrice_diagonale = creer_matrice();

    // Parcours de la diagonale principale
    struct noeud_matrice* ligne_courante = matrice->tete;
    int indice_ligne = 0;

    while (ligne_courante != NULL) {
        // Création d'une nouvelle ligne pour la matrice diagonale
        struct liste_chainee* nouvelle_ligne = creer_liste();

        struct noeud* element_courant = ligne_courante->liste->tete;
        int indice_colonne = 0;

        // Remplissage de la ligne avec des 0, sauf à la position de la diagonale
        while (indice_colonne < indice_ligne) {
            ajouter_en_queue(nouvelle_ligne, 0.0);
            indice_colonne++;
        }

        // Ajouter l'élément de la diagonale
        if (element_courant != NULL) {
            for (int i = 0; i < indice_ligne && element_courant != NULL; i++) {
                element_courant = element_courant->suiv;
            }
            ajouter_en_queue(nouvelle_ligne, element_courant != NULL ? element_courant->val : 0.0);
        }

        // Compléter la ligne avec des 0
        while (indice_colonne < nombre_de_colonnes(matrice, 0) - 1) {
            ajouter_en_queue(nouvelle_ligne, 0.0);
            indice_colonne++;
        }

        // Ajouter la nouvelle ligne à la matrice diagonale
        ajouter_ligne_en_queue(matrice_diagonale, nouvelle_ligne);

        // Passer à la ligne suivante
        ligne_courante = ligne_courante->suivant;
        indice_ligne++;
    }

    return matrice_diagonale;
}

struct liste_chainee_matrice* puissance_matrice(struct liste_chainee_matrice* matrice, int n) {
    // Vérification si la matrice est valide
    if (matrice == NULL || matrice->tete == NULL) {
        printf("Erreur : Matrice invalide ou vide.\n");
        return NULL;
    }

    // Vérifier que la matrice est carrée
    int nb_lignes = nombre_de_lignes(matrice);
    int nb_colonnes = nombre_de_colonnes(matrice, 0);
    if (nb_lignes != nb_colonnes) {
        printf("Erreur : La matrice doit être carrée.\n");
        return NULL;
    }

    // Si n est 0, retourner la matrice identité
    if (n == 0) {
        return creer_matrice_identite(nb_lignes);
    }

    // Si n est 1, retourner une copie de la matrice d'origine
    if (n == 1) {
        return copier_matrice(matrice);
    }

    // Initialiser la matrice résultat comme une copie de la matrice d'origine
    struct liste_chainee_matrice* resultat = copier_matrice(matrice);

    // Multiplier la matrice par elle-même n-1 fois
    for (int i = 1; i < n; i++) {
        struct liste_chainee_matrice* temp = produit_matriciel(resultat, matrice);
        supprime_matrice(resultat); // Libérer la mémoire de l'ancienne matrice
        resultat = temp;
    }

    return resultat;
}

void decomposition_LU(struct liste_chainee_matrice* matrice, struct liste_chainee_matrice** L, struct liste_chainee_matrice** U) {
    // Vérifier si la matrice est valide
    if (matrice == NULL || matrice->tete == NULL) {
        printf("Erreur : Matrice invalide ou vide.\n");
        *L = NULL;
        *U = NULL;
        return;
    }

    int n = nombre_de_lignes(matrice);
    if (n != nombre_de_colonnes(matrice, 0)) {
        printf("Erreur : La matrice doit être carrée.\n");
        *L = NULL;
        *U = NULL;
        return;
    }

    // Créer la matrice U comme une copie de la matrice d'origine
    *U = copier_matrice(matrice);

    // Créer la matrice L comme une matrice identité
    *L = creer_matrice_identite(n);

    // Décomposition LU
    for (int k = 0; k < n; k++) {
        float pivot = obtenir_element_matrice(*U, k, k);
        
        if (pivot == 0.0f) {
            printf("Erreur : La matrice est singulière ou un pivot est nul.\n");
            supprime_matrice(*L);
            supprime_matrice(*U);
            *L = NULL;
            *U = NULL;
            return;
        }

        // Pour chaque ligne au-dessous du pivot
        for (int i = k + 1; i < n; i++) {
            // Calculer le facteur de réduction
            float facteur = obtenir_element_matrice(*U, i, k) / pivot;
            modifier_element(*L, i, k, facteur);

            // Réduire la ligne i de U
            for (int j = k; j < n; j++) {
                float nouvelle_valeur = obtenir_element_matrice(*U, i, j) - facteur * obtenir_element_matrice(*U, k, j);
                modifier_element(*U, i, j, nouvelle_valeur);
            }
        }
    }
}

float calculer_determinant(struct liste_chainee_matrice* matrice) {
    // Vérifier si la matrice est valide
    if (matrice == NULL || matrice->tete == NULL) {
        printf("Erreur : Matrice invalide ou vide.\n");
        return 0.0f;
    }

    int n = nombre_de_lignes(matrice);
    if (n != nombre_de_colonnes(matrice, 0)) {
        printf("Erreur : La matrice doit être carrée.\n");
        return 0.0f;
    }

    // Matrices L et U pour la décomposition LU
    struct liste_chainee_matrice* L = NULL;
    struct liste_chainee_matrice* U = NULL;

    // Décomposition LU de la matrice
    decomposition_LU(matrice, &L, &U);

    if (L == NULL || U == NULL) {
        printf("Erreur : La matrice probablement inversible.\n");
        return 0.0f;
    }

    // Calcul du déterminant en multipliant les éléments diagonaux de U
    float determinant = 1.0f;
    struct noeud_matrice* ligne = U->tete;
    for (int i = 0; i < n; i++) {
        struct noeud* diag_element = ligne->liste->tete;
        for (int j = 0; j < i; j++) {
            diag_element = diag_element->suiv; // Aller jusqu'à l'élément diagonal
        }
        determinant *= diag_element->val;
        ligne = ligne->suivant;
    }

    // Libérer la mémoire
    supprime_matrice(L);
    supprime_matrice(U);

    return determinant;
}

//########################### Inverse d'une matrice par la méthode de décomposition LU ###################################################
// Fonction pour résoudre un système triangulaire inférieur
void resolver_systeme_triangular_inf(struct liste_chainee_matrice* L, struct liste_chainee_matrice* B, struct liste_chainee_matrice* X) {
    int n = nombre_de_lignes(L);

    for (int i = 0; i < n; i++) {
        float somme = obtenir_element_matrice(B, i, 0);
        for (int j = 0; j < i; j++) {
            somme -= obtenir_element_matrice(L, i, j) * obtenir_element_matrice(X, j, 0);
        }
        modifier_element(X, i, 0, somme / obtenir_element_matrice(L, i, i));
    }
}

// Fonction pour résoudre un système triangulaire supérieur
void resolver_systeme_triangular_sup(struct liste_chainee_matrice* U, struct liste_chainee_matrice* B, struct liste_chainee_matrice* X) {
    int n = nombre_de_lignes(U);

    for (int i = n - 1; i >= 0; i--) {
        float somme = obtenir_element_matrice(B, i, 0);
        for (int j = i + 1; j < n; j++) {
            somme -= obtenir_element_matrice(U, i, j) * obtenir_element_matrice(X, j, 0);
        }
        modifier_element(X, i, 0, somme / obtenir_element_matrice(U, i, i));
    }
}

// Fonction pour inverser une matrice carrée
struct liste_chainee_matrice* inverser_matrice(struct liste_chainee_matrice* matrice) {
    // Vérifier si la matrice est valide
    if (matrice == NULL || matrice->tete == NULL) {
        printf("Erreur : Matrice invalide ou vide.\n");
        return NULL;
    }

    int n = nombre_de_lignes(matrice);
    if (n != nombre_de_colonnes(matrice, 0)) {
        printf("Erreur : La matrice doit être carrée.\n");
        return NULL;
    }

    // Créer les matrices L et U
    struct liste_chainee_matrice* L = NULL;
    struct liste_chainee_matrice* U = NULL;
    decomposition_LU(matrice, &L, &U);

    if (L == NULL || U == NULL) {
        printf("Erreur lors de la décomposition LU.\n");
        return NULL;
    }

    // Matrice pour stocker l'inverse
    struct liste_chainee_matrice* inverse = creer_matrice_zeros(n);

    // Calculer chaque colonne de l'inverse
    for (int i = 0; i < n; i++) {
        // Colonne i de la matrice identité
        struct liste_chainee_matrice* I_colonne = creer_matrice_zeros(n);
        modifier_element(I_colonne, i, 0, 1.0);

        // Résoudre L * Y = I_colonne
        struct liste_chainee_matrice* Y = creer_matrice_zeros(n);
        resolver_systeme_triangular_inf(L, I_colonne, Y);

        // Résoudre U * X = Y pour obtenir la colonne i de l'inverse
        struct liste_chainee_matrice* X = creer_matrice_zeros(n);
        resolver_systeme_triangular_sup(U, Y, X);

        // Copier les résultats dans la matrice inverse
        for (int j = 0; j < n; j++) {
            float valeur = obtenir_element_matrice(X, j, 0);
            modifier_element(inverse, j, i, valeur);
        }

        // Nettoyer
        supprime_matrice(I_colonne);
        supprime_matrice(Y);
        supprime_matrice(X);
    }

    // Nettoyer les matrices L et U
    supprime_matrice(L);
    supprime_matrice(U);

    return inverse;
}

//##########################################################################################################################