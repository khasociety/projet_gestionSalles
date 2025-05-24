#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>
//#define  fsalle "salle.txt"

typedef struct {
    char nom[25], niveau[20];
    int code_unique, effectif;
}classe;
//Gestion des classe

int est_ce_que_la_classe_existe(int code, char* fname){
   FILE * fp;
   classe classe;
   fp = fopen (fname, "r");
   if(fp == NULL){
    printf("Echec de l'Ouverture du fichier !!\n");
	  return 2;
   }
   while ( fscanf(fp,"%d\t%s\t%s\t%d\n", &classe.code_unique, classe.nom, classe.niveau, &classe.effectif) == 4)
   {
     if(code == classe.code_unique){
        return 1;
     }
   }
   fclose(fp);
   return 0;
}


void Ajouter_une_nouvelle_classe(char * fname){
	
	  FILE * fp;
	  int code;
      classe classe;
	  fp = fopen ( fname, "a");
	  if(fp == NULL){
	    printf("Echec de l'Ouverture du fichier !!\n");
		return;
	   }
	  system("cls");
	  printf("________________________________________________\n");
	  printf("     === AJOUT D'UNE NOUVELLE CLASSE ===\n");    
	  printf("------------------------------------------------\n");
	  
	  printf("Entrer le code : ");
	  scanf("%d", &code);
	  while(est_ce_que_la_classe_existe(code, fname) == 1){
	    printf("Le code existe !\n");
	    printf("Entrer le code : ");
	    scanf("%d", &code); 
	  }
	  classe.code_unique = code;
     getchar();
	  printf("Nom: ");
	  fgets(classe.nom, sizeof(classe.nom), stdin);
      classe.nom[strcspn(classe.nom, "\n")] = '\0'; // retirer le saut de ligne
      
     
	  printf("Niveau : ");
	  fgets(classe.niveau, sizeof(classe.niveau), stdin);
      classe.niveau[strcspn(classe.niveau, "\n")] = '\0'; // retirer le saut de ligne
	 

     do{
	    printf("Effectif : ");
	    scanf("%d", &classe.effectif);
	  }while( classe.effectif < 0);
	
	   
      fprintf(fp,"%d\t%s\t%s\t%d\n", classe.code_unique, classe.nom, classe.niveau, classe.effectif);
	  fclose(fp);
	   
	   printf("Classe ajoutée avec succès ! \n");
	   printf("\nAppuyez sur Entrée pour continuer...\n");
       getchar(); getchar();
}
void Afficher_la_liste_des_classes_connues(char * fname){
	 FILE * fp;
	 classe classe;
	 fp = fopen ( fname, "r");
	 if(fp == NULL){
	    printf("Echec de l'Ouverture du fichier !!\n");
		return;
	   }
	   system("cls");
	   printf("_______________________________________________________________\n");
	   printf("     === AFFICHAGE DE LA LISTES DES CLASSES CONNUES ===\n");    
	   printf("---------------------------------------------------------------\n");
		
	    while ( fscanf(fp,"%d\t%s\t%s\t%d\n", &classe.code_unique, classe.nom, classe.niveau, &classe.effectif )== 4){
	 	  printf("=== CLASSE ===\n");
        printf("Code     : %d\n", classe.code_unique);
        printf("Nom      : %s\n", classe.nom);
        printf("Niveau   : %s\n", classe.niveau);
        printf("Effectif : %d\n\n", classe.effectif);

	 }
	fclose(fp);
	printf("\nAppuyez sur Entrée pour continuer...\n");
    getchar(); getchar();
}

void Rechercher_une_classe_a_partir_de_son_code(char * fname){
   FILE * fp;
	 classe classe;
	 int code;
	 fp = fopen ( fname, "r");
	 if(fp == NULL){
	    printf("Echec de l'Ouverture du fichier !!\n");
		return;
	   }

	    system("cls");
	   printf("_______________________________________________________________\n");
	   printf("     === RECHERCHE D'UNE CLASSE A PARTIR DE SON CODE  ===\n");    
	   printf("---------------------------------------------------------------\n");

	   printf("Donner le code de la classe a rechercher: ");
		scanf("%d", &code);
		getchar();
	if (est_ce_que_la_classe_existe(code, fname) == 1){
       while ( fscanf(fp,"%d\t%s\t%s\t%d\n", &classe.code_unique, classe.nom, classe.niveau, &classe.effectif )== 4){
         if(code == classe.code_unique){
            printf("=== CLASSE ===\n");
            printf("Code     : %d\n", classe.code_unique);
            printf("Nom      : %s\n", classe.nom);
            printf("Niveau   : %s\n", classe.niveau);
            printf("Effectif : %d\n\n", classe.effectif); 
         }
      }
   }
   else{
		printf("classe non trouvee !! \n");
	}
	fclose(fp);
	printf("\nAppuyez sur Entrée pour continuer...\n");
   getchar(); //getchar();
} 

void  Modifier_une_classe_connue(char * fname){

   
	 FILE * fp , *fp_edit;
	 int code;
	 classe classe;
	
	    system("cls");
		printf("________________________________________________\n");
		printf("     === MODIFICATION D'UNE CLASSE ===\n");    
		printf("------------------------------------------------\n");
		
		printf("Donner le code de la classe a modifier: ");
		scanf("%d", &code);
		getchar();
	if (est_ce_que_la_classe_existe(code, fname) == 1){

      fp_edit = fopen ("new_file.txt", "wt");
      if(fp_edit == NULL){
         printf("Echec de l'ouverture du fichier !!\n");
         return;
         }
			classe.code_unique = code;

      
      printf("Nom: ");
      fgets(classe.nom, sizeof(classe.nom), stdin);
      classe.nom[strcspn(classe.nom, "\n")] = '\0'; // retirer le saut de ligne
      
     
	  printf("Niveau : ");
	  fgets(classe.niveau, sizeof(classe.niveau), stdin);
     classe.niveau[strcspn(classe.niveau, "\n")] = '\0'; // retirer le saut de ligne
	 
     do{
	    printf("Effectif : ");
	    scanf("%d", &classe.effectif);
	  }while( classe.effectif < 0);

     fprintf(fp_edit,"%d\t%s\t%s\t%d\n", classe.code_unique, classe.nom, classe.niveau, classe.effectif );


      while ( fscanf(fp,"%d\t%s\t%s\t%d\n", &classe.code_unique, classe.nom, classe.niveau, &classe.effectif )== 4){
         if(code != classe.code_unique){
            fprintf(fp_edit,"%d\t%s\t%s\t%d\n", classe.code_unique, classe.nom, classe.niveau, classe.effectif );
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
			printf("Classe modifiée avec succès !\n");
  }
  else{
    printf("La classe avec le code %d n'existe pas !\n", code);
  }
   
   printf("\nAppuyez sur Entrée pour continuer...\n");
   getchar(); getchar();
}

void Supprimer_une_classe_connue(void);


void menu_Gestion_des_classes(){
int choix;  
char fclasse[] = "classe.txt";
	

	do {    
	    /*#ifdef _WIN32
	        system("cls");
	    #else
	        system("clear");
	    #endif  pour la portablite du programme*/
		system("cls");
		printf("1:Ajouter une nouvelle classe\n");
		printf("2:Afficher la liste des classes connues\n");
		printf("3:Rechercher une classe a partir de son code\n");
		printf("4:Modifier une classe connue\n");
	    printf("5:Supprimer une classe connue\n");
	    printf("6:Retour au menu principal\n");
		printf("Entrer votre choix: ");
		scanf("%d", &choix);

		switch (choix) {
			case 1:
				Ajouter_une_nouvelle_classe(fclasse);
				break;
			case 2:
		    	Afficher_la_liste_des_classes_connues(fclasse);
				break;
			case 3:
				Rechercher_une_classe_a_partir_de_son_code(fclasse);
				break;
			case 4:
                Modifier_une_classe_connue(fclasse);
				break;
            case 5:
               // Supprimer_une_classe_connue(fclasse);
				break;
             case 6:
				break;
			default:
				printf("Choix invalide\a");
		   //printf("\nAppuyez sur Entrée pour continuer...\n");
			//getchar();getchar();
      }
	} while (choix != 6);

}
