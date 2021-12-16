#ifndef FONCTIONS_H_
#define FONCTIONS_H_
typedef struct{
int jour;
int temp;
float valeur;}dechet;
typedef struct
{ int journee;
int temp;
 char entree[10];
char plat_principale[10];
char dessert[10];
int dechet;
char id[10];
}menu;
void ajouter(menu m);
void supprimer(char id_supp[20]);
void modifier(char id[20],menu m);
void afficher(GtkWidget *liste,char file[20]);
void afficher2();
void rechercher(char id[20]);
void meilleur_menu();
#endif
