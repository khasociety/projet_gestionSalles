#include <stdio.h>
typedef struct {
    char code_unique[25], position[25], disponibilite_machines[5];
    int capacit;
}salle;
typedef struct {
    char code_unique[25], nom[25];
    int niveau, effectif;
}classe;

typedef struct {
    char code_de_sall[25], code_de_class[25], date[10], heure_de_debut[8], heure_de_fin[8], motif[20], etat[10];
    int numero_unique;
}reservation;
//Gestion des salles
void Ajouter_une_nouvelle_salle(void);
void Afficher_la_liste_des_salles_connues(void);
void Rechercher_une_salle_a_partir_de_son_code(void);
void Modifier_une_salle_connue(void);
void Supprimer_une_salle_connue(void);
void menuClients() {
	int choix;
	char fichierClients[] = "clients.txt";

	do {
		printf("\n");
		printf("1. Ajouter un client\n");
		printf("2. Afficher les clients\n");
		printf("3. Rechercher un client\n");
		printf("4. Retour au menu principal\n");
		printf("Entrer votre choix: ");
		scanf("%d", &choix);

		switch (choix) {
			case 1:
				ajouterClient(fichierClients);
				break;
			case 2:
				afficherClients(fichierClients);
				break;
			case 3:
				rechercherClient(fichierClients);
				break;
			case 4:
				break;
			default:
				printf("Choix invalide\n");
		}
	} while (choix != 4);
}
//Gestion des classes
void Ajouter_une_nouvelle_class(void);
void Afficher_la_liste_des_classes_connues(void);
void Rechercher_une_classe_a_partir_de_son_code(void);
void Modifier_une_classe_connue(void);
void Supprimer_une_classe_connue(void);