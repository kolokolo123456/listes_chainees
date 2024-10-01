#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "listes_chainees_str.h"


// Fonction pour créer une nouvelle liste chaînée
struct liste_chainee_str* creer_liste() {
    struct liste_chainee_str* liste = (struct liste_chainee_str*)malloc(sizeof(struct liste_chainee_str));

    if (liste == NULL) { 
        printf("Erreur d'allocation mémoire pour la liste chainée\n");
        exit(1);
    }

    liste->tete = NULL;
    liste->length = 0;

    return liste;
}

// Fonction qui crée une liste chaînée à partir d'un tableau
struct liste_chainee_str* convert_tab_liste(char** tableau, int taille) {

    struct liste_chainee_str* liste = creer_liste();


    for (int i = 0; i < taille; i++) {
        // Créer un nouveau nœud
        struct noeud_str* nouveau_noeud = (struct noeud_str*)malloc(sizeof(struct noeud_str));
        if (nouveau_noeud == NULL) {
            fprintf(stderr, "Erreur d'allocation de mémoire pour le nœud\n");
            exit(EXIT_FAILURE);
        }

        // Initialiser le nœud avec la chaîne de caractères du tableau
        nouveau_noeud->text = tableau[i];
        nouveau_noeud->suiv = NULL;

        // Ajouter le nœud à la fin de la liste chaînée
        if (liste->tete == NULL) {
            // Si la liste est vide, le nœud devient la tête
            liste->tete = nouveau_noeud;
        } else {
            // Sinon, on parcourt jusqu'à la fin de la liste pour ajouter le nœud
            struct noeud_str* temp = liste->tete;
            while (temp->suiv != NULL) {
                temp = temp->suiv;
            }
            temp->suiv = nouveau_noeud;
        }

        // Incrémenter la longueur de la liste
        liste->length++;
    }

    // Retourner la liste chaînée créée
    return liste;
}

// Fonction qui affiche la liste chainées
void afficher_liste(struct liste_chainee_str* liste) {
    struct noeud_str* courant = liste->tete;
    printf("| ");
    while (courant != NULL) {
        printf("%s | ", courant->text);
        courant = courant->suiv;
    }
    printf("\n");
}

// Fonction pour supprimer une liste chaînée
void supprime_liste(struct liste_chainee_str* liste) {
    struct noeud_str *temp;

    while (liste->tete != NULL) {
        temp = liste->tete;
        liste->tete = liste->tete->suiv;
        free(temp);
    }

    free(liste);
}

// Fonction qui vérifie si un texte est présente dans une liste chaînée
bool in(struct liste_chainee_str *liste, char* text) {
    struct noeud_str *courant = liste->tete;
    
    while (courant != NULL) {
        // Si la text est trouvée, retourne true
        if (strcmp(courant->text, text) == 0) {
            return true;
        }
        courant = courant->suiv;
    }

    // Si la text n'est pas trouvée, retourne false
    return false;
}


// Fonction pour ajouter un élément à la fin de la liste chaînée
void ajouter_en_queue(struct liste_chainee_str* liste, char* text) {
    struct noeud_str* nouveau = (struct noeud_str*)malloc(sizeof(struct noeud_str));
    if (nouveau == NULL) {
        printf("Erreur d'allocation mémoire pour le nouveau noeud_str\n");
        exit(1);
    }

    nouveau->text = text;
    nouveau->suiv = NULL;

    if (liste->tete == NULL) {
        liste->tete = nouveau;
    } else {
        struct noeud_str* temp = liste->tete;
        while (temp->suiv != NULL) {
            temp = temp->suiv;
        }
        temp->suiv = nouveau;
    }

    liste->length++;
}

// Fonction pour ajouter un élément au début de la liste chaînée
void ajouter_en_tete(struct liste_chainee_str* liste, char* text) {
    struct noeud_str* nouveau = (struct noeud_str*)malloc(sizeof(struct noeud_str));
    if (nouveau == NULL) {
        printf("Erreur d'allocation mémoire pour le nouveau noeud_str\n");
        exit(1);
    }

    nouveau->text = text;
    nouveau->suiv = liste->tete;

    liste->tete = nouveau;
    liste->length++;
}

// Fonction qui renvoie la longueur de la liste chainée
int len(struct liste_chainee_str* liste) {
    return liste->length;
}

// Fonction pour obtenir l'élément à l'indice i de la liste chainée
char* obtenir_element(struct liste_chainee_str* liste, int index) {

    if (liste == NULL || index < 0 || index >= liste->length) {
        printf("Erreur : index invalide ou liste vide.\n");
        return NULL;
    }

    struct noeud_str* courant = liste->tete;

    // Parcourir la liste jusqu'à l'index spécifié
    for (int i = 0; i < index; i++) {
        courant = courant->suiv;
    }
    
    return courant->text;
}

// Fonction qui modifie la text du noeud_str d'indice i de la liste chainée liste par la nouvelle text
void modifier_valeur(struct liste_chainee_str* liste, int i, char* nouveau_texte) {
    if (i < 0 || i >= liste->length) {
        printf("Erreur : Indice hors limites\n");
        return;
    }

    struct noeud_str* current = liste->tete;
    int count = 0;

    // Parcourir la liste jusqu'au nœud d'indice `i`
    while (count < i && current != NULL) {
        current = current->suiv;
        count++;
    }

    // Modifier la text du nœud à l'indice `i`
    if (current != NULL) {
        current->text = nouveau_texte;
    }
}

// Fonction pour inverser la liste chainée
void inverser_liste(struct liste_chainee_str* liste) {
    struct noeud_str *precedent = NULL;
    struct noeud_str *courant = liste->tete;
    struct noeud_str *suivant = NULL;

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

// Fonction qui supprime le noeud_str d'indice i de la liste chainée
void supprimer_noeud(struct liste_chainee_str* liste, int indice) {
    if (indice < 0 || indice >= liste->length) {
        printf("Erreur : Indice hors limites\n");
        return;
    }

    struct noeud_str* courant = liste->tete;

    if (indice == 0) {
        // Cas spécial : suppression du premier nœud
        liste->tete = courant->suiv;
        // Libérer le nœud lui-même
        free(courant);
    } else {
        // Trouver le nœud précédent du nœud à supprimer
        struct noeud_str* precedent = NULL;
        for (int j = 0; j < indice; j++) {
            precedent = courant;
            courant = courant->suiv;
        }

        precedent->suiv = courant->suiv;
        free(courant);
    }

    liste->length--;
}

//Fonction pour Trouver l'Indice de la Première Occurrence d'un texte
int trouver_indice(struct liste_chainee_str* liste, char* text) {
    struct noeud_str* courant = liste->tete;
    int indice = 0;

    // Parcourir la liste et chercher la text
    while (courant != NULL) {
        if (strcmp(courant->text, text) == 0) {
            return indice;
        }
        courant = courant->suiv;
        indice++;
    }

    // Si la text n'est pas trouvée, retourner -1
    return -1;
}

// Fonction pour copier une liste chaînée
struct liste_chainee_str* copier_liste(struct liste_chainee_str* liste_source) {
    if (liste_source == NULL || liste_source->tete == NULL) {
        // Si la liste source est vide ou NULL, retourner une nouvelle liste vide
        struct liste_chainee_str* liste_copie = (struct liste_chainee_str*)malloc(sizeof(struct liste_chainee_str));
        if (liste_copie == NULL) {
            printf("Erreur d'allocation mémoire pour la copie\n");
            exit(1);
        }
        liste_copie->tete = NULL;
        liste_copie->length = 0;
        return liste_copie;
    }

    // Création de la nouvelle liste
    struct liste_chainee_str* liste_copie = (struct liste_chainee_str*)malloc(sizeof(struct liste_chainee_str));
    if (liste_copie == NULL) {
        printf("Erreur d'allocation mémoire pour la copie\n");
        exit(1);
    }

    // Initialisation de la liste copiée
    liste_copie->tete = NULL;
    liste_copie->length = 0;

    // Variables pour parcourir la liste source et construire la liste copiée
    struct noeud_str* courant_source = liste_source->tete;
    struct noeud_str* courant_copie = NULL;
    struct noeud_str* precedent_copie = NULL;

    while (courant_source != NULL) {
        // Création du nouveau nœud pour la liste copiée
        struct noeud_str* nouveau_noeud = (struct noeud_str*)malloc(sizeof(struct noeud_str));
        if (nouveau_noeud == NULL) {
            printf("Erreur d'allocation mémoire\n");
            exit(1);
        }

        // Dupliquer le texte du nœud source
        nouveau_noeud->text = courant_source->text;
        if (nouveau_noeud->text == NULL) {
            printf("Erreur d'allocation mémoire pour le texte\n");
            exit(1);
        }

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
struct liste_chainee_str* copier_tranche(struct liste_chainee_str* liste_source, int i, int j) {
    if (i < 0 || j < i || j >= liste_source->length) {
        printf("Erreur : Indices hors limites\n");
        return NULL;
    }

    // Création de la nouvelle liste pour la tranche copiée
    struct liste_chainee_str* liste_copie = (struct liste_chainee_str*)malloc(sizeof(struct liste_chainee_str));
    if (liste_copie == NULL) {
        printf("Erreur d'allocation mémoire\n");
        exit(1);
    }
    liste_copie->tete = NULL;
    liste_copie->length = 0;

    // Parcourir la liste source jusqu'à l'indice `i`
    struct noeud_str* courant_source = liste_source->tete;
    for (int k = 0; k < i; k++) {
        if (courant_source == NULL) {
            printf("Erreur : Indice `i` trop grand\n");
            free(liste_copie);
            return NULL;
        }
        courant_source = courant_source->suiv;
    }

    // Copier les nœuds de `i` à `j`
    struct noeud_str* courant_copie = NULL;
    struct noeud_str* precedent_copie = NULL;
    for (int k = i; k <= j; k++) {
        // Création du nouveau nœud pour la tranche copiée
        struct noeud_str* nouveau_noeud = (struct noeud_str*)malloc(sizeof(struct noeud_str));
        if (nouveau_noeud == NULL) {
            printf("Erreur d'allocation mémoire\n");
            exit(1);
        }

        // Dupliquer le texte du nœud source
        nouveau_noeud->text = courant_source->text;
        if (nouveau_noeud->text == NULL) {
            printf("Erreur d'allocation mémoire pour le texte\n");
            exit(1);
        }

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
struct liste_chainee_str* concatener_listes(struct liste_chainee_str* liste1, struct liste_chainee_str* liste2) {
    // Création de la nouvelle liste concaténée
    struct liste_chainee_str* liste_concatenee = (struct liste_chainee_str*)malloc(sizeof(struct liste_chainee_str));
    if (liste_concatenee == NULL) {
        printf("Erreur d'allocation mémoire pour la liste concaténée\n");
        exit(1);
    }
    liste_concatenee->tete = NULL;
    liste_concatenee->length = 0;

    struct noeud_str* dernier_noeud = NULL; // Pour suivre le dernier nœud de la liste concaténée

    // Fonction pour ajouter les nœuds d'une liste à la liste concaténée en les copiant
    struct noeud_str* courant = liste1->tete;
    while (courant != NULL) {
        // Création d'un nouveau nœud pour la liste concaténée
        struct noeud_str* nouveau = (struct noeud_str*)malloc(sizeof(struct noeud_str));
        if (nouveau == NULL) {
            printf("Erreur d'allocation mémoire pour le nouveau noeud_str\n");
            exit(1);
        }

        // Duplication du texte du nœud source
        nouveau->text = courant->text;
        if (nouveau->text == NULL) {
            printf("Erreur d'allocation mémoire pour le texte\n");
            exit(1);
        }

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
        struct noeud_str* nouveau = (struct noeud_str*)malloc(sizeof(struct noeud_str));
        if (nouveau == NULL) {
            printf("Erreur d'allocation mémoire pour le nouveau noeud_str\n");
            exit(1);
        }

        // Duplication du texte du nœud source
        nouveau->text = courant->text;
        if (nouveau->text == NULL) {
            printf("Erreur d'allocation mémoire pour le texte\n");
            exit(1);
        }

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

// Fonction pour supprimer les doublons dans une liste chaînée
void supprimer_doublons(struct liste_chainee_str* liste) {
    if (liste == NULL || liste->tete == NULL) {
        return; // Liste vide ou NULL, rien à faire
    }

    struct noeud_str *courant = liste->tete;
    while (courant != NULL) {
        struct noeud_str *prev = courant;
        struct noeud_str *comp = courant->suiv;

        while (comp != NULL) {
            if (strcmp(comp->text, courant->text) == 0) {
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
void inserer_noeud(struct liste_chainee_str* liste, int indice, char* text) {
    if (indice < 0 || indice > liste->length) {
        printf("Erreur : Indice hors limites\n");
        return;
    }

    struct noeud_str* nouveau = (struct noeud_str*)malloc(sizeof(struct noeud_str));
    if (nouveau == NULL) {
        printf("Erreur d'allocation mémoire pour le nouveau noeud_str\n");
        exit(1);
    }
    nouveau->text = text;

    if (indice == 0) {
        // Insertion au début
        nouveau->suiv = liste->tete;
        liste->tete = nouveau;
    } else {
        // Insertion ailleurs
        struct noeud_str* courant = liste->tete;
        for (int i = 0; i < indice - 1; i++) {
            courant = courant->suiv;
        }
        nouveau->suiv = courant->suiv;
        courant->suiv = nouveau;
    }

    liste->length++;
}

// Fonction pour échanger les valeurs de 2 noeuds d'une liste chainée
void echanger_valeurs(struct liste_chainee_str* liste, int index1, int index2) {
    // Vérification des paramètres
    if (liste == NULL || index1 < 0 || index2 < 0) {
        printf("Erreur : Paramètres non valides pour l'échange de valeurs des nœuds.\n");
        return;
    }

    // Trouver les nœuds aux indices index1 et index2
    struct noeud_str* noeud1 = NULL;
    struct noeud_str* noeud2 = NULL;
    struct noeud_str* courant = liste->tete;
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
    char* temp = noeud1->text;
    noeud1->text = noeud2->text;
    noeud2->text = temp;
}

// Fonction pour comparer si deux listes sont identiques
bool comparer_listes(struct liste_chainee_str* liste1, struct liste_chainee_str* liste2) {
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
    struct noeud_str* courant1 = liste1->tete;
    struct noeud_str* courant2 = liste2->tete;

    while (courant1 != NULL && courant2 != NULL) {
        if (strcmp(courant1->text, courant2->text) != 0) {
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
struct noeud_str* dernier_noeud(struct noeud_str* tete) {
    while (tete != NULL && tete->suiv != NULL) {
        tete = tete->suiv;
    }
    return tete;
}

// Fonction pour partitionner la liste et retourner le pivot
struct noeud_str* partition(struct noeud_str* debut, struct noeud_str* fin, struct noeud_str** nouv_debut, struct noeud_str** nouv_fin) {
    struct noeud_str* pivot = fin;
    struct noeud_str* precedent = NULL, * courant = debut, * queue = pivot;

    while (courant != pivot) {
        if (strcmp(courant->text, pivot->text) < 0) {
            if ((*nouv_debut) == NULL) {
                (*nouv_debut) = courant;
            }
            precedent = courant;
            courant = courant->suiv;
        } else {
            if (precedent != NULL) {
                precedent->suiv = courant->suiv;
            }
            struct noeud_str* temp = courant->suiv;
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
struct noeud_str* tri_rapide_recur(struct noeud_str* debut, struct noeud_str* fin) {
    if (!debut || debut == fin) {
        return debut;
    }

    struct noeud_str* nouv_debut = NULL, * nouv_fin = NULL;

    struct noeud_str* pivot = partition(debut, fin, &nouv_debut, &nouv_fin);

    if (nouv_debut != pivot) {
        struct noeud_str* temp = nouv_debut;
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
void trier_liste_alph(struct liste_chainee_str* liste) {
    if (liste == NULL || liste->tete == NULL) {
        return;
    }

    liste->tete = tri_rapide_recur(liste->tete, dernier_noeud(liste->tete));
}

/*######################################################################################################################*/