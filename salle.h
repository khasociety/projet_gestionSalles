#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>
#include <windows.h> // pour Sleep
//#define  fsalle "salle.txt"
typedef struct salle {
    int capacite, code_unique;
    char  position[25], disponibilite_machines[5];
}salle ;
//Gestion des salles

int est_ce_que_le_code_existe(int code, char* fname){
   FILE * fp;
   salle salle;
   fp = fopen (fname, "r");
   if(fp == NULL){
    printf("Echec de l'Ouverture du fichier !!\n");
	  return 2;
   }
   while ( fscanf(fp,"%d\t%s\t%d\t%s\n", &salle.code_unique, salle.position, &salle.capacite, &salle.disponibilite_machines) == 4)
   {
     if(code == salle.code_unique){
        return 1;
     }
   }
   fclose(fp);
   return 0;
}

void Ajouter_une_nouvelle_salle(char * fname){
	  FILE * fp;
	  int code;
	  int dispo_machine;
	  salle salle;
	  fp = fopen ( fname, "a");
	  if(fp == NULL){
	    printf("Echec de l'Ouverture du fichier !!\n");
		return;
	   }
	  system("cls");
	  printf("________________________________________________\n");
	  printf("     === AJOUT D'UNE NOUVELLE SALLE ===\n");    
	  printf("------------------------------------------------\n");
	  printf("Entrer le code : ");
	  scanf("%d", &code);
	  while(est_ce_que_le_code_existe(code, fname) == 1){
	    printf("Le code existe !\n");
	    printf("Entrer le code : ");
	    scanf("%d", &code); 
	  }
	  salle.code_unique = code;
	  getchar();
	  printf("Position: ");
	  fgets(salle.position, sizeof(salle.position), stdin);
      salle.position[strcspn(salle.position, "\n")] = '\0'; // retirer le saut de ligne

	  do{
	    printf("Capacite : ");
	    scanf("%d", &salle.capacite);
	  }while(salle.capacite < 0);
	  
	  do{
	    printf("Disponibilite machines:\n1:Oui\n2:Non\n");
	    printf("Entrer votre choix: ");
	    scanf("%d", &dispo_machine);
	  }while(dispo_machine != 1 && dispo_machine != 2);
	  
	  if (dispo_machine == 1)
	  strcpy (salle.disponibilite_machines, "Oui");
	  else
	  strcpy (salle.disponibilite_machines, "Non");
	  
	  fprintf(fp,"%d\t%s\t%d\t%s\n", salle.code_unique, salle.position, salle.capacite, salle.disponibilite_machines);
	  fclose(fp);
	   printf("Salle ajoutée avec succès ! \n");
	   printf("\nAppuyez sur Entrée pour continuer...\n");
       getchar(); getchar();
}

void Afficher_la_liste_des_salles_connues(char * fname){
	 FILE * fp;
	 salle salle;
	 fp = fopen ( fname, "r");
	 if(fp == NULL){
	    printf("Echec de l'Ouverture du fichier !!\n");
		return;
	   }
	   system("cls");
	   printf("_______________________________________________________________\n");
	   printf("     === AFFICHAGE DE LA LISTES DES SALLES CONNUES ===\n");    
	   printf("---------------------------------------------------------------\n");
		
	    while ( fscanf(fp,"%d\t%[^\t]\t%d\t%s\n", &salle.code_unique, salle.position, &salle.capacite, salle.disponibilite_machines) == 4){
	 	printf("=== SALLE ===\n");
        printf("Code                   : %d\n", salle.code_unique);
        printf("Position               : %s\n", salle.position);
        printf("Capacité               : %d\n", salle.capacite);
        printf("Disponibilité machines : %s\n\n", salle.disponibilite_machines);

	 }
	fclose(fp);
	printf("\nAppuyez sur Entrée pour continuer...\n");
    getchar(); getchar();
}

void Rechercher_une_salle_a_partir_de_son_code(char * fname){
	FILE * fp;
	 salle salle;
	 int code;
	 fp = fopen ( fname, "r");
	 if(fp == NULL){
	    printf("Echec de l'Ouverture du fichier !!\n");
		return;
	   }

	    system("cls");
	   printf("_______________________________________________________________\n");
	   printf("     === RECHERCHE D'UNE SALLE A PARTIR DE SON CODE  ===\n");    
	   printf("---------------------------------------------------------------\n");

	   printf("Donner le code de la salle a rechercher: ");
		scanf("%d", &code);
		getchar();
	if (est_ce_que_le_code_existe(code, fname) == 1){
		 while ( fscanf(fp,"%d\t%[^\t]\t%d\t%s\n", &salle.code_unique, salle.position, &salle.capacite, salle.disponibilite_machines) == 4){
			if(salle.code_unique == code){
				printf("=== SALLE ===\n");
				printf("Code                   : %d\n", salle.code_unique);
				printf("Position               : %s\n", salle.position);
				printf("Capacité               : %d\n", salle.capacite);
				printf("Disponibilité machines : %s\n\n", salle.disponibilite_machines);
			}
		 }  
    }
	else 
	{
		printf("Salle non trouvee !! \n");
	}
	fclose(fp);
	printf("\nAppuyez sur Entrée pour continuer...\n");
    getchar(); //getchar();
}
	                                       	
/*void Modifier_une_salle_connue(char * fname){
	
	 FILE * fp , *fp_edit;
	 int code, dispo_machine;
	 salle new_salle, salle_tmp;

	   
	    system("cls");
		printf("________________________________________________\n");
		printf("     === MODIFICATION D'UNE SALLE ===\n");    
		printf("------------------------------------------------\n");
		
		printf("Donner le code de la salle a modifier: ");
		scanf("%d", &code);
		getchar();
		
	if (est_ce_que_le_code_existe(code, fname) == 1){
		// Ouvrir le fichier temporaire
		fp_edit = fopen ("new_file.txt", "wt");
	    if(fp_edit == NULL){
		    printf("Echec de l'ouverture du fichier temporaire !!\n");
			return;
	    }
	    
	        // Saisir les nouvelles données
			 new_salle.code_unique = code;
			printf("Position: ");
			fgets(new_salle.position, sizeof(new_salle.position), stdin);
			new_salle.position[strcspn(new_salle.position, "\n")] = '\0'; // retirer le saut de ligne

			do{
				printf("Capacite : ");
				scanf("%d", &new_salle.capacite);
			}while(new_salle.capacite < 0);
			
			do{
				printf("Disponibilite machines:\n1:Oui\n2:Non\n");
				printf("Entrer votre choix: ");
				scanf("%d", &dispo_machine);
			}while(dispo_machine != 1 && dispo_machine != 2);
			
			if (dispo_machine == 1)
			strcpy (new_salle.disponibilite_machines, "Oui");
			else
			strcpy (new_salle.disponibilite_machines, "Non");
            
		
		    fp = fopen ( fname, "rt");
			 if(fp == NULL){
				    printf("Echec de l'Ouverture du fichier !!\n");
				    fclose(fp_edit); // Important : fermer le fichier temporaire
					return;
			   }
	   
			while ( fscanf(fp,"%d\t%[^\t]\t%d\t%s\n", &salle_tmp.code_unique, salle_tmp.position, &salle_tmp.capacite, &salle_tmp.disponibilite_machines) == 4){
			    if(code == salle_tmp.code_unique){
					fprintf(fp_edit,"%d\t%s\t%d\t%s\n", new_salle.code_unique, new_salle.position, new_salle.capacite, new_salle.disponibilite_machines);
			}
			else{
			fprintf(fp_edit,"%d\t%s\t%d\t%s\n", salle_tmp.code_unique, salle_tmp.position, salle_tmp.capacite, salle_tmp.disponibilite_machines);
			}
		}
	   fflush(fp_edit);  // Force l'écriture du buffer vers le disque
       fclose(fp);
	   fclose(fp_edit);
	   
	   printf("Tentative de suppression du fichier : %s\n", fname);
	   
	   if (remove(fname) != 0) {
         perror("Erreur de suppression");
         //return; // Arreter si la suppression echoue
		}
	  
	     if (rename("new_file.txt", fname) != 0) {
	     perror("Erreur de renommage");
		 }
	  }
	else{
        printf("La salle avec le code %d n'existe pas !\n", code);
	} 
	 
   	printf("\nAppuyez sur Entrée pour continuer...\n");
    getchar(); getchar();
}*/


void Modifier_une_salle_connue(char * fname){
    FILE *fp = NULL, *fp_edit = NULL;
    int code, dispo_machine;
    salle salle, salle_temp;

    system("cls");
    printf("________________________________________________\n");
    printf("     === MODIFICATION D'UNE SALLE ===\n");
    printf("------------------------------------------------\n");

    printf("Donner le code de la salle a modifier: ");
    scanf("%d", &code);
    getchar();

    if (est_ce_que_le_code_existe(code, fname) == 1){
        // Ouvre l'original en lecture
        fp = fopen(fname, "rt");
        if (fp == NULL) {
            printf("Erreur d'ouverture de %s\n", fname);
            return;
        }

        // Ouvre le fichier temporaire
        fp_edit = fopen("new_file.txt", "wt");
        if (fp_edit == NULL) {
            printf("Erreur d'ouverture du fichier temporaire\n");
            fclose(fp);
            return;
        }

        // Saisie des nouvelles infos
        salle.code_unique = code;
        printf("Position: ");
        fgets(salle.position, sizeof(salle.position), stdin);
        salle.position[strcspn(salle.position, "\n")] = '\0';

        do {
            printf("Capacite : ");
            scanf("%d", &salle.capacite);
        } while(salle.capacite < 0);

        do {
            printf("Disponibilite machines:\n1:Oui\n2:Non\nEntrer votre choix: ");
            scanf("%d", &dispo_machine);
        } while(dispo_machine != 1 && dispo_machine != 2);

        strcpy(salle.disponibilite_machines, (dispo_machine == 1) ? "Oui" : "Non");

        // Lecture de l'ancien fichier et copie dans le nouveau
        while (fscanf(fp, "%d\t%[^\t]\t%d\t%s\n", &salle_temp.code_unique,
                      salle_temp.position, &salle_temp.capacite,
                      salle_temp.disponibilite_machines) == 4) {
            if (salle_temp.code_unique == code) {
                fprintf(fp_edit, "%d\t%s\t%d\t%s\n", salle.code_unique, salle.position, salle.capacite, salle.disponibilite_machines);
            } else {
                fprintf(fp_edit, "%d\t%s\t%d\t%s\n", salle_temp.code_unique, salle_temp.position, salle_temp.capacite, salle_temp.disponibilite_machines);
            }
        }
fflush(fp_edit);
        if (fp) fclose(fp);
       if (fp_edit) fclose(fp_edit);
		         
				FILE *test = fopen(fname, "a");
		if (test == NULL) {
		    printf("[DEBUG] Le fichier %s est ENCORE VERROUILLÉ\n", fname);
		} else {
		    printf("[DEBUG] Le fichier %s est LIBRE\n", fname);
		    fclose(test);
		}

        if (remove(fname) != 0) {
            perror("Erreur de suppression");
        } else if (rename("new_file.txt", fname) != 0) {
            perror("Erreur de renommage");
        } else {
            printf("Modification réussie !\n");
        }
    } else {
        printf("La salle avec le code %d n'existe pas !\n", code);
    }

    printf("\nAppuyez sur Entrée pour continuer...\n");
    getchar(); getchar();
}


void Supprimer_une_salle_connue(char * fname){
	
	 FILE * fp , *fp_edit;
	 int code;
	 salle salle;
	 
	 fp = fopen (fname, "rt");
	 if(fp == NULL){
	    printf("Echec de l'Ouverture du fichier !!\n");
		return;
	   }

	fp_edit = fopen ("new_file.txt", "wt");
	 if(fp_edit == NULL){
	    printf("Echec de l'ouverture du fichier !!\n");
		return;
	   }
	
	    system("cls");
		printf("________________________________________________\n");
		printf("     === SUPPRESSION D'UNE SALLE ===\n");    
		printf("------------------------------------------------\n");
		
		printf("Donner le code de la salle a supprimer: ");
		scanf("%d", &code);
		getchar();
	if (est_ce_que_le_code_existe(code, fname) == 1){

			while ( fscanf(fp,"%d\t%[^\t]\t%d\t%s\n", &salle.code_unique, salle.position, &salle.capacite, &salle.disponibilite_machines) == 4){
			    if(salle.code_unique != code){
				fprintf(fp_edit,"%d\t%s\t%d\t%s\n", salle.code_unique, salle.position, salle.capacite, salle.disponibilite_machines);
			}
		}
       fclose(fp);
	   fclose(fp_edit);
	   
	   printf("Tentative de suppression du fichier : %s\n", fname);
	   
	   if (remove(fname) != 0) {
         perror("Erreur de suppression");
		}
	  
	     if (rename("new_file.txt", fname) != 0) {
	     perror("Erreur de renommage");
		 }
	  printf("Salle supprimee avec succès !\n");
	  }
	else{
		fclose(fp);
        fclose(fp_edit);
        remove("new_file.txt");
        printf("La salle avec le code %d n'existe pas !\n", code);
	   } 
	 
   	printf("\nAppuyez sur Entrée pour continuer...\n");
    getchar(); getchar();
	
}

void menu_Gestion_des_salles(){

int choix;  
char fsalle[] = "salle.txt";
	

	do {    
	    /*#ifdef _WIN32
	        system("cls");
	    #else
	        system("clear");
	    #endif  pour la portablite du programme*/
		system("cls");
		printf("1:Ajouter une nouvelle salle\n");
		printf("2:Afficher la liste des salles connues\n");
		printf("3:Rechercher une salle a partir de son code\n");
		printf("4:Modifier une salle connue\n");
	    printf("5:Supprimer une salle connue\n");
	    printf("6:Retour au menu principal\n");
		printf("Entrer votre choix: ");
		scanf("%d", &choix);

		switch (choix) {
			case 1:
				Ajouter_une_nouvelle_salle(fsalle);
				break;
			case 2:
				Afficher_la_liste_des_salles_connues(fsalle);
				break;
			case 3:
				Rechercher_une_salle_a_partir_de_son_code(fsalle);
				break;
			case 4:
                  Modifier_une_salle_connue(fsalle);
				break;
            case 5:
                Supprimer_une_salle_connue(fsalle);
				break;
             case 6:
				break;
			default:
				printf("Choix invalide\a");
		}
		   //printf("\nAppuyez sur Entrée pour continuer...\n");
			//getchar();getchar();
	} while (choix != 6);
}