#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "listes_chainees.h"


// Fonction pour créer une nouvelle liste chaînée
struct liste_chainee* creer_liste() {
    struct liste_chainee* liste = (struct liste_chainee*)malloc(sizeof(struct liste_chainee));

    if (liste == NULL) { 
        printf("Erreur d'allocation mémoire pour la liste chainée\n");
        exit(1);
    }

    liste->tete = NULL;
    liste->length = 0;

    return liste;
}

// Fonction qui crée une liste chaînée à partir d'un tableau
struct liste_chainee* convert_tab_liste(float *tableau, int taille) {
    // Allouer de la mémoire pour la liste chaînée
    struct liste_chainee *liste = (struct liste_chainee*) malloc(sizeof(struct liste_chainee));
    liste->tete = NULL;
    liste->length = 0;

    // Vérifier si le tableau est vide
    if (taille == 0) {
        return liste;
    }

    // Allouer de la mémoire pour le premier noeud
    struct noeud *courant = (struct noeud*) malloc(sizeof(struct noeud));
    courant->val = tableau[0];
    courant->suiv = NULL;
    liste->tete = courant;
    liste->length = 1;

    // Ajouter les autres éléments du tableau à la liste chaînée
    for (int i = 1; i < taille; i++) {
        struct noeud *nouveau_noeud = (struct noeud*) malloc(sizeof(struct noeud));
        nouveau_noeud->val = tableau[i];
        nouveau_noeud->suiv = NULL;
        courant->suiv = nouveau_noeud;
        courant = nouveau_noeud;
        liste->length++;
    }

    return liste;
}

// Fonction qui affiche la liste chainées
void afficher_liste(struct liste_chainee* liste) {
    struct noeud* courant = liste->tete;
    while (courant != NULL) {
        printf("%f -> ", courant->val);
        courant = courant->suiv;
    }
    printf("FIN\n");
}

// Fonction pour supprimer une liste chaînée
void supprime_liste(struct liste_chainee* liste) {
    struct noeud *temp;

    while (liste->tete != NULL) {
        temp = liste->tete;
        liste->tete = liste->tete->suiv;
        free(temp);
    }

    free(liste);
}

// Fonction qui vérifie si une valeur est présente dans une liste chaînée
bool in(struct liste_chainee *liste, float valeur) {
    struct noeud *courant = liste->tete;
    
    while (courant != NULL) {
        // Si la valeur est trouvée, retourne true
        if (courant->val == valeur) {
            return true;
        }
        courant = courant->suiv;
    }

    // Si la valeur n'est pas trouvée, retourne false
    return false;
}


// Fonction pour ajouter un élément à la fin de la liste chaînée
void ajouter_en_queue(struct liste_chainee* liste, float valeur) {
    struct noeud* nouveau = (struct noeud*)malloc(sizeof(struct noeud));
    if (nouveau == NULL) {
        printf("Erreur d'allocation mémoire pour le nouveau noeud\n");
        exit(1);
    }

    nouveau->val = valeur;
    nouveau->suiv = NULL;

    if (liste->tete == NULL) {
        liste->tete = nouveau;
    } else {
        struct noeud* temp = liste->tete;
        while (temp->suiv != NULL) {
            temp = temp->suiv;
        }
        temp->suiv = nouveau;
    }

    liste->length++;
}

// Fonction pour ajouter un élément au début de la liste chaînée
void ajouter_en_tete(struct liste_chainee* liste, float valeur) {
    struct noeud* nouveau = (struct noeud*)malloc(sizeof(struct noeud));
    if (nouveau == NULL) {
        printf("Erreur d'allocation mémoire pour le nouveau noeud\n");
        exit(1);
    }

    nouveau->val = valeur;
    nouveau->suiv = liste->tete;

    liste->tete = nouveau;
    liste->length++;
}

// Fonction qui renvoie la longueur de la liste chainée
int len(struct liste_chainee* liste) {
    return liste->length;
}

// Fonction pour obtenir l'élément à l'indice i de la liste chainée
float obtenir_element(struct liste_chainee* liste, int index) {

    if (liste == NULL || index < 0 || index >= liste->length) {
        printf("Erreur : index invalide ou liste vide.\n");
        return -1;
    }

    struct noeud* courant = liste->tete;

    // Parcourir la liste jusqu'à l'index spécifié
    for (int i = 0; i < index; i++) {
        courant = courant->suiv;
    }
    
    return courant->val;
}

// Fonction qui modifie la valeur du noeud d'indice i de la liste chainée liste par la nouvelle valeur
void modifier_valeur(struct liste_chainee* liste, int i, float nouvelle_valeur) {
    if (i < 0 || i >= liste->length) {
        printf("Erreur : Indice hors limites\n");
        return;
    }

    struct noeud* current = liste->tete;
    int count = 0;

    // Parcourir la liste jusqu'au nœud d'indice `i`
    while (count < i && current != NULL) {
        current = current->suiv;
        count++;
    }

    // Modifier la valeur du nœud à l'indice `i`
    if (current != NULL) {
        current->val = nouvelle_valeur;
    }
}

// Fonction pour inverser la liste chainée
void inverser_liste(struct liste_chainee* liste) {
    struct noeud *precedent = NULL;
    struct noeud *courant = liste->tete;
    struct noeud *suivant = NULL;

    // Parcourir la liste et inverser les pointeurs
    while (courant != NULL) {
        suivant = courant->suiv;
        courant->suiv = precedent;
        precedent = courant;
        courant = suivant;
    }

    // Mettre à jour le pointeur de tête pour pointer vers le nouveau premier nœud
    liste->tete = precedent;
}

// Fonction qui supprime le noeud d'indice i de la liste chainée
void supprimer_noeud(struct liste_chainee* liste, int i) {
    if (i < 0 || i >= liste->length) {
        printf("Erreur : Indice hors limites\n");
        return;
    }

    struct noeud* courant = liste->tete;

    if (i == 0) {
        // Cas spécial : suppression du premier nœud
        liste->tete = courant->suiv;
        free(courant);
    } else {
        // Trouver le nœud précédent du nœud à supprimer
        struct noeud* precedent = NULL;
        for (int j = 0; j < i; j++) {
            precedent = courant;
            courant = courant->suiv;
        }

        precedent->suiv = courant->suiv;
        free(courant);
    }

    liste->length--;
}

//Fonction pour Trouver l'Indice de la Première Occurrence d'une Valeur
int trouver_indice(struct liste_chainee* liste, float valeur) {
    struct noeud* courant = liste->tete;
    int indice = 0;

    // Parcourir la liste et chercher la valeur
    while (courant != NULL) {
        if (courant->val == valeur) {
            return indice;
        }
        courant = courant->suiv;
        indice++;
    }

    // Si la valeur n'est pas trouvée, retourner -1
    return -1;
}

// Fonction pour copier une liste chaînée
struct liste_chainee* copier_liste(struct liste_chainee* liste_source) {
    if (liste_source == NULL || liste_source->tete == NULL) {
        // Si la liste source est vide ou NULL, retourner une nouvelle liste vide
        struct liste_chainee* liste_copie = (struct liste_chainee*)malloc(sizeof(struct liste_chainee));
        if (liste_copie == NULL) {
            printf("Erreur d'allocation mémoire pour la copie\n");
            exit(1);
        }
        liste_copie->tete = NULL;
        liste_copie->length = 0;
        return liste_copie;
    }

    // Création de la nouvelle liste
    struct liste_chainee* liste_copie = (struct liste_chainee*)malloc(sizeof(struct liste_chainee));
    if (liste_copie == NULL) {
        printf("Erreur d'allocation mémoire pour la copie\n");
        exit(1);
    }

    // Initialisation de la liste copiée
    liste_copie->tete = NULL;
    liste_copie->length = 0;

    // Variables pour parcourir la liste source et construire la liste copiée
    struct noeud* courant_source = liste_source->tete;
    struct noeud* courant_copie = NULL;
    struct noeud* precedent_copie = NULL;

    while (courant_source != NULL) {
        // Création du nouveau nœud pour la liste copiée
        struct noeud* nouveau_noeud = (struct noeud*)malloc(sizeof(struct noeud));
        if (nouveau_noeud == NULL) {
            printf("Erreur d'allocation mémoire\n");
            exit(1);
        }
        nouveau_noeud->val = courant_source->val;
        nouveau_noeud->suiv = NULL;

        // Ajout du nouveau nœud à la liste copiée
        if (liste_copie->tete == NULL) {
            // Si la liste copiée est vide, le nouveau nœud devient la tête
            liste_copie->tete = nouveau_noeud;
        } else {
            // Sinon, ajoute le nouveau nœud à la fin de la liste copiée
            precedent_copie->suiv = nouveau_noeud;
        }
        precedent_copie = nouveau_noeud;
        liste_copie->length++;

        // Avancer au nœud suivant dans la liste source
        courant_source = courant_source->suiv;
    }

    return liste_copie;
}

// Fonction pour copier une tranche de la liste chaînée
struct liste_chainee* copier_tranche(struct liste_chainee* liste_source, int i, int j) {
    if (i < 0 || j < i || j >= liste_source->length) {
        printf("Erreur : Indices hors limites\n");
        return NULL;
    }

    // Création de la nouvelle liste pour la tranche copiée
    struct liste_chainee* liste_copie = (struct liste_chainee*)malloc(sizeof(struct liste_chainee));
    if (liste_copie == NULL) {
        printf("Erreur d'allocation mémoire\n");
        exit(1);
    }
    liste_copie->tete = NULL;
    liste_copie->length = 0;

    // Parcourir la liste source jusqu'à l'indice `i`
    struct noeud* courant_source = liste_source->tete;
    for (int k = 0; k < i; k++) {
        if (courant_source == NULL) {
            printf("Erreur : Indice `i` trop grand\n");
            free(liste_copie);
            return NULL;
        }
        courant_source = courant_source->suiv;
    }

    // Copier les nœuds de `i` à `j`
    struct noeud* courant_copie = NULL;
    struct noeud* precedent_copie = NULL;
    for (int k = i; k <= j; k++) {
        // Création du nouveau nœud pour la tranche copiée
        struct noeud* nouveau_noeud = (struct noeud*)malloc(sizeof(struct noeud));
        if (nouveau_noeud == NULL) {
            printf("Erreur d'allocation mémoire\n");
            exit(1);
        }
        nouveau_noeud->val = courant_source->val;
        nouveau_noeud->suiv = NULL;

        // Ajouter le nouveau nœud à la liste copiée
        if (liste_copie->tete == NULL) {
            liste_copie->tete = nouveau_noeud;
        } else {
            precedent_copie->suiv = nouveau_noeud;
        }
        precedent_copie = nouveau_noeud;
        liste_copie->length++;

        // Avancer dans la liste source
        courant_source = courant_source->suiv;
    }

    return liste_copie;
}

// Fonction pour concaténer deux listes chaînées en copiant les nœuds
struct liste_chainee* concatener_listes(struct liste_chainee* liste1, struct liste_chainee* liste2) {
    // Création de la nouvelle liste concaténée
    struct liste_chainee* liste_concatenee = (struct liste_chainee*)malloc(sizeof(struct liste_chainee));
    if (liste_concatenee == NULL) {
        printf("Erreur d'allocation mémoire pour la liste concaténée\n");
        exit(1);
    }
    liste_concatenee->tete = NULL;
    liste_concatenee->length = 0;

    struct noeud* dernier_noeud = NULL; // Pour suivre le dernier nœud de la liste concaténée

    // Fonction pour ajouter les nœuds d'une liste à la liste concaténée en les copiant
    struct noeud* courant = liste1->tete;
    while (courant != NULL) {
        // Création d'un nouveau nœud pour la liste concaténée
        struct noeud* nouveau = (struct noeud*)malloc(sizeof(struct noeud));
        if (nouveau == NULL) {
            printf("Erreur d'allocation mémoire pour le nouveau noeud\n");
            exit(1);
        }
        nouveau->val = courant->val;
        nouveau->suiv = NULL;

        // Ajouter le nouveau nœud à la fin de la liste concaténée
        if (liste_concatenee->tete == NULL) {
            liste_concatenee->tete = nouveau;
        } else {
            dernier_noeud->suiv = nouveau;
        }
        dernier_noeud = nouveau;
        liste_concatenee->length++;

        courant = courant->suiv;
    }

    courant = liste2->tete;
    while (courant != NULL) {
        // Création d'un nouveau nœud pour la liste concaténée
        struct noeud* nouveau = (struct noeud*)malloc(sizeof(struct noeud));
        if (nouveau == NULL) {
            printf("Erreur d'allocation mémoire pour le nouveau noeud\n");
            exit(1);
        }
        nouveau->val = courant->val;
        nouveau->suiv = NULL;

        // Ajouter le nouveau nœud à la fin de la liste concaténée
        if (liste_concatenee->tete == NULL) {
            liste_concatenee->tete = nouveau;
        } else {
            dernier_noeud->suiv = nouveau;
        }
        dernier_noeud = nouveau;
        liste_concatenee->length++;

        courant = courant->suiv;
    }

    return liste_concatenee;
}

// Fonction pour trouver la valeur maximale dans une liste chaînée
float max(struct liste_chainee* liste) {
    if (liste == NULL || liste->tete == NULL) {
        printf("Erreur : Liste vide ou NULL\n");
        return -1; // Indique une erreur
    }

    float max = liste->tete->val; // Initialisation avec la première valeur
    struct noeud* courant = liste->tete;

    while (courant != NULL) {
        if (courant->val > max) {
            max = courant->val;
        }
        courant = courant->suiv;
    }

    return max;
}

// Fonction pour trouver la valeur minimale dans une liste chaînée
float min(struct liste_chainee* liste) {
    if (liste == NULL || liste->tete == NULL) {
        printf("Erreur : Liste vide ou NULL\n");
        return -1; // Indique une erreur
    }

    float min = liste->tete->val; // Initialisation avec la première valeur
    struct noeud* courant = liste->tete;

    while (courant != NULL) {
        if (courant->val < min) {
            min = courant->val;
        }
        courant = courant->suiv;
    }

    return min;
}

// Fonction pour supprimer les doublons dans une liste chaînée
void supprimer_doublons(struct liste_chainee* liste) {
    if (liste == NULL || liste->tete == NULL) {
        return; // Liste vide ou NULL, rien à faire
    }

    struct noeud *courant = liste->tete;
    while (courant != NULL) {
        struct noeud *prev = courant;
        struct noeud *comp = courant->suiv;

        while (comp != NULL) {
            if (comp->val == courant->val) {
                // Doublon trouvé, suppression du nœud doublon
                prev->suiv = comp->suiv;
                free(comp);
                comp = prev->suiv; // Mise à jour de `comp` après suppression
                liste->length--;
            } else {
                prev = comp;
                comp = comp->suiv;
            }
        }

        courant = courant->suiv;
    }
}

// Fonction pour insérer un nœud à un indice donné
void inserer_noeud(struct liste_chainee* liste, int indice, float valeur) {
    if (indice < 0 || indice > liste->length) {
        printf("Erreur : Indice hors limites\n");
        return;
    }

    struct noeud* nouveau = (struct noeud*)malloc(sizeof(struct noeud));
    if (nouveau == NULL) {
        printf("Erreur d'allocation mémoire pour le nouveau noeud\n");
        exit(1);
    }
    nouveau->val = valeur;

    if (indice == 0) {
        // Insertion au début
        nouveau->suiv = liste->tete;
        liste->tete = nouveau;
    } else {
        // Insertion ailleurs
        struct noeud* courant = liste->tete;
        for (int i = 0; i < indice - 1; i++) {
            courant = courant->suiv;
        }
        nouveau->suiv = courant->suiv;
        courant->suiv = nouveau;
    }

    liste->length++;
}

// Fonction pour échanger les valeurs de 2 noeuds d'une liste chainée
void echanger_valeurs(struct liste_chainee* liste, int index1, int index2) {
    // Vérification des paramètres
    if (liste == NULL || index1 < 0 || index2 < 0) {
        printf("Erreur : Paramètres non valides pour l'échange de valeurs des nœuds.\n");
        return;
    }

    // Trouver les nœuds aux indices index1 et index2
    struct noeud* noeud1 = NULL;
    struct noeud* noeud2 = NULL;
    struct noeud* courant = liste->tete;
    int index_courant = 0;

    while (courant != NULL) {
        if (index_courant == index1) {
            noeud1 = courant;
        }
        if (index_courant == index2) {
            noeud2 = courant;
        }
        courant = courant->suiv;
        index_courant++;
    }

    // Vérifier que les deux nœuds ont été trouvés
    if (noeud1 == NULL || noeud2 == NULL) {
        printf("Erreur : Un ou les deux indices spécifiés ne sont pas présents dans la liste.\n");
        return;
    }

    // Échanger les valeurs des deux nœuds
    float temp = noeud1->val;
    noeud1->val = noeud2->val;
    noeud2->val = temp;
}

// Fonction pour comparer si deux listes sont identiques
bool comparer_listes(struct liste_chainee* liste1, struct liste_chainee* liste2) {
    // Vérifier si les deux listes sont NULL
    if (liste1 == NULL && liste2 == NULL) {
        return true;
    }

    // Vérifier si une seule des listes est NULL
    if (liste1 == NULL || liste2 == NULL) {
        return false;
    }

    // Vérifier si les longueurs des listes sont différentes
    if (liste1->length != liste2->length) {
        return false;
    }

    // Comparer les éléments des listes
    struct noeud* courant1 = liste1->tete;
    struct noeud* courant2 = liste2->tete;

    while (courant1 != NULL && courant2 != NULL) {
        if (courant1->val != courant2->val) {
            return false;
        }
        courant1 = courant1->suiv;
        courant2 = courant2->suiv;
    }

    // Si nous avons parcouru les deux listes entièrement, elles sont identiques
    return (courant1 == NULL && courant2 == NULL);
}

/*############################ tri de liste chainée (tri rapide) #######################################################*/

// Fonction pour partitionner la liste
// Retourne la tête de la liste partitionnée autour du pivot
// Fonction pour obtenir le dernier nœud de la liste
struct noeud* dernier_noeud(struct noeud* tete) {
    while (tete != NULL && tete->suiv != NULL) {
        tete = tete->suiv;
    }
    return tete;
}

// Fonction pour partitionner la liste et retourner le pivot
struct noeud* partition(struct noeud* debut, struct noeud* fin, struct noeud** nouv_debut, struct noeud** nouv_fin) {
    struct noeud* pivot = fin;
    struct noeud* precedent = NULL, * courant = debut, * queue = pivot;

    while (courant != pivot) {
        if (courant->val < pivot->val) {
            if ((*nouv_debut) == NULL) {
                (*nouv_debut) = courant;
            }
            precedent = courant;
            courant = courant->suiv;
        } else {
            if (precedent != NULL) {
                precedent->suiv = courant->suiv;
            }
            struct noeud* temp = courant->suiv;
            courant->suiv = NULL;
            queue->suiv = courant;
            queue = courant;
            courant = temp;
        }
    }

    if ((*nouv_debut) == NULL) {
        (*nouv_debut) = pivot;
    }

    (*nouv_fin) = queue;

    return pivot;
}

// Fonction principale de tri rapide
struct noeud* tri_rapide_recur(struct noeud* debut, struct noeud* fin) {
    if (!debut || debut == fin) {
        return debut;
    }

    struct noeud* nouv_debut = NULL, * nouv_fin = NULL;

    struct noeud* pivot = partition(debut, fin, &nouv_debut, &nouv_fin);

    if (nouv_debut != pivot) {
        struct noeud* temp = nouv_debut;
        while (temp->suiv != pivot) {
            temp = temp->suiv;
        }
        temp->suiv = NULL;

        nouv_debut = tri_rapide_recur(nouv_debut, temp);

        temp = dernier_noeud(nouv_debut);
        temp->suiv = pivot;
    }

    pivot->suiv = tri_rapide_recur(pivot->suiv, nouv_fin);

    return nouv_debut;
}

// Fonction pour trier la liste
void trier_liste(struct liste_chainee* liste) {
    if (liste == NULL || liste->tete == NULL) {
        return;
    }

    liste->tete = tri_rapide_recur(liste->tete, dernier_noeud(liste->tete));
}

/*######################################################################################################################*/