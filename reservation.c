#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_VOLS 100
#define FICHIER_VOLS "vols.txt"

typedef struct {
    char code[10];
    char destination[50];
    char date[11];
    int sieges_disponibles;
} Vol;

// Prototypes
void charger_vols(Vol vols[], int *nb_vols);
void sauvegarder_vols(Vol vols[], int nb_vols);
void ajouter_vol(Vol vols[], int *nb_vols);
void reserver_siege(Vol vols[], int nb_vols);
void annuler_reservation(Vol vols[], int nb_vols);
void afficher_vols(Vol vols[], int nb_vols);

int main() {
    Vol vols[MAX_VOLS];
    int nb_vols = 0;
    int choix;

    charger_vols(vols, &nb_vols);

    do {
        printf("\nSystème de réservation de vols\n");
        printf("1. Ajouter un vol\n");
        printf("2. Réserver un siège\n");
        printf("3. Annuler une réservation\n");
        printf("4. Afficher les vols\n");
        printf("5. Quitter\n");
        printf("Votre choix : ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                ajouter_vol(vols, &nb_vols);
                break;
            case 2:
                reserver_siege(vols, nb_vols);
                break;
            case 3:
                annuler_reservation(vols, nb_vols);
                break;
            case 4:
                afficher_vols(vols, nb_vols);
                break;
            case 5:
                sauvegarder_vols(vols, nb_vols);
                printf("Données sauvegardées. Au revoir !\n");
                break;
            default:
                printf("Choix invalide. Réessayez.\n");
        }
    } while (choix != 5);

    return 0;
}

// Charger les vols depuis un fichier
void charger_vols(Vol vols[], int *nb_vols) {
    FILE *fichier = fopen(FICHIER_VOLS, "r");
    if (fichier == NULL) {
        printf("Aucun fichier de vols trouvé. Création d'un nouveau fichier.\n");
        return;
    }

    while (fscanf(fichier, "%s %s %s %d", vols[*nb_vols].code, vols[*nb_vols].destination,
                  vols[*nb_vols].date, &vols[*nb_vols].sieges_disponibles) != EOF) {
        (*nb_vols)++;
    }

    fclose(fichier);
}

// Sauvegarder les vols dans un fichier
void sauvegarder_vols(Vol vols[], int nb_vols) {
    FILE *fichier = fopen(FICHIER_VOLS, "w");
    if (fichier == NULL) {
        printf("Erreur lors de la sauvegarde des vols.\n");
        return;
    }

    for (int i = 0; i < nb_vols; i++) {
        fprintf(fichier, "%s %s %s %d\n", vols[i].code, vols[i].destination, vols[i].date,
                vols[i].sieges_disponibles);
    }

    fclose(fichier);
}

// Ajouter un vol
void ajouter_vol(Vol vols[], int *nb_vols) {
    if (*nb_vols >= MAX_VOLS) {
        printf("Capacité maximale atteinte !\n");
        return;
    }

    printf("Code du vol : ");
    scanf("%s", vols[*nb_vols].code);
    printf("Destination : ");
    scanf("%s", vols[*nb_vols].destination);
    printf("Date (YYYY-MM-DD) : ");
    scanf("%s", vols[*nb_vols].date);
    printf("Nombre de sièges disponibles : ");
    scanf("%d", &vols[*nb_vols].sieges_disponibles);

    (*nb_vols)++;
    printf("Vol ajouté avec succès !\n");
}

// Réserver un siège
void reserver_siege(Vol vols[], int nb_vols) {
    char code[10];
    printf("Code du vol : ");
    scanf("%s", code);

    for (int i = 0; i < nb_vols; i++) {
        if (strcmp(vols[i].code, code) == 0) {
            if (vols[i].sieges_disponibles > 0) {
                vols[i].sieges_disponibles--;
                printf("Réservation effectuée. Sièges restants : %d\n", vols[i].sieges_disponibles);
                return;
            } else {
                printf("Aucun siège disponible pour ce vol.\n");
                return;
            }
        }
    }

    printf("Vol introuvable.\n");
}

// Annuler une réservation
void annuler_reservation(Vol vols[], int nb_vols) {
    char code[10];
    printf("Code du vol : ");
    scanf("%s", code);

    for (int i = 0; i < nb_vols; i++) {
        if (strcmp(vols[i].code, code) == 0) {
            vols[i].sieges_disponibles++;
            printf("Réservation annulée. Sièges restants : %d\n", vols[i].sieges_disponibles);
            return;
        }
    }

    printf("Vol introuvable.\n");
}

// Afficher les vols
void afficher_vols(Vol vols[], int nb_vols) {
    printf("\nListe des vols :\n");
    for (int i = 0; i < nb_vols; i++) {
        printf("Code : %s, Destination : %s, Date : %s, Sièges disponibles : %d\n",
               vols[i].code, vols[i].destination, vols[i].date, vols[i].sieges_disponibles);
            
}
}