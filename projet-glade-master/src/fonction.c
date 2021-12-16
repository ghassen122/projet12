#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include "fonction.h"
enum{
  MJOURNEE,
  MTEMP,
  MENTREE,
  MPLAT_PRINCIPALE,
  MDESSERT,
  MDECHET,
  MID,
  COLUNMS
};
void ajouter(menu m)
{ 
	FILE *f=NULL;
	f=fopen("menu.txt","a+");
	if(f!=NULL)
	{ 
		fprintf(f,"%d %d %s %s %s %d %s \n",m.journee,m.temp,m.entree,m.plat_principale,m.dessert,m.dechet,m.id);
	
	}
	fclose(f);
}

void afficher(GtkWidget *liste,char file[20])
{

	GtkCellRenderer *renderer;
	GtkTreeViewColumn *column;
	GtkTreeIter iter ;
	GtkListStore *store;
	int journee;
	int temp;
	char entree[20];
	char plat_principale[20];
	char dessert[20];
	int dechet;
	char id[20];
	store=NULL;
	FILE *f;
	store=gtk_tree_view_get_model(liste);
	if(store==NULL){
		
		renderer=gtk_cell_renderer_text_new();
		column=gtk_tree_view_column_new_with_attributes("journee",renderer,"text",MJOURNEE,NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

		renderer=gtk_cell_renderer_text_new();
		column=gtk_tree_view_column_new_with_attributes("temp",renderer,"text",MTEMP,NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);
				
		renderer=gtk_cell_renderer_text_new();
		column=gtk_tree_view_column_new_with_attributes("entree",renderer,"text",MENTREE,NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);
		
		renderer=gtk_cell_renderer_text_new();
		column=gtk_tree_view_column_new_with_attributes("plat_principal",renderer,"text",MPLAT_PRINCIPALE,NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column); 
		
		renderer=gtk_cell_renderer_text_new();
		column=gtk_tree_view_column_new_with_attributes("dessert",renderer,"text",MDESSERT,NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column); 
		
		renderer=gtk_cell_renderer_text_new();
		column=gtk_tree_view_column_new_with_attributes("dechet",renderer,"text",MDECHET,NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);
		
		renderer=gtk_cell_renderer_text_new();
		column=gtk_tree_view_column_new_with_attributes("id",renderer,"text",MID,NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);
		 
	}
		  
	store=gtk_list_store_new(COLUNMS,G_TYPE_INT,G_TYPE_INT,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_INT,G_TYPE_STRING);
	f=fopen(file,"r");
	if(f==NULL){return;}
	else
	{
		 while(fscanf(f,"%d %d %s %s %s %d %s \n",&journee,&temp,entree,plat_principale,dessert,&dechet,id)!=EOF)
		 {
			gtk_list_store_append(store,&iter);
		  	gtk_list_store_set(store,&iter,MJOURNEE,journee,MTEMP,temp,MENTREE,entree,MPLAT_PRINCIPALE,plat_principale,MDESSERT,dessert,MDECHET,dechet,MID,id,-1);
		 }
	 fclose(f);
	 gtk_tree_view_set_model(GTK_TREE_VIEW(liste),GTK_TREE_MODEL(store));
	 g_object_unref(store);
	}

}

void supprimer(char id_supp[20])
{

	menu m;
	FILE *f,*ftmp;

	f=fopen("menu.txt","r");

	ftmp=fopen("tmp.txt","a+");
	while(fscanf(f,"%d %d %s %s %s %d %s \n",&m.journee,&m.temp,m.entree,m.plat_principale,m.dessert,&m.dechet,m.id)!=EOF)
		{
			if(strcmp(m.id,id_supp)!=0){
				fprintf(ftmp,"%d %d %s %s %s %d %s \n",m.journee,m.temp,m.entree,m.plat_principale,m.dessert,m.dechet,m.id);			
			}
		}

	fclose(ftmp);
	fclose(f);
	remove("menu.txt");
	rename("tmp.txt","menu.txt");

	
}
void modifier(char id_modif[20],menu m){
	
	int jour;
	int temp;
	char entree[20];
	char plat_principale[20];
	char dessert [20];
	int dechet;
	char id[20];
	FILE *f=NULL ,*g=NULL;
	f=fopen("menu.txt","r");
	g=fopen("dump.txt","a+");
	if(f==NULL)
		return; 
	else{ 
		while (fscanf(f,"%d %d %s %s %s %d %s \n",&jour,&temp,entree,plat_principale,dessert,&dechet,id)!=EOF)
		{
			if ( strcmp(id,id_modif)!=0)
			{
				fprintf(g,"%d %d %s %s %s %d %s \n",jour,temp,entree,plat_principale,dessert,dechet,id);
			}
			else{
				fprintf(g,"%d %d %s %s %s %d %s \n",m.journee,m.temp,m.entree,m.plat_principale,m.dessert,m.dechet,m.id);
			}
		}
		
	}
	fclose(f);
	fclose(g);
	remove("menu.txt");
	rename("dump.txt","menu.txt");
}
void rechercher(char id[20]){
	menu m;
	FILE *f =NULL,*g;
	f=fopen("menu.txt","r");
	g=fopen("recherche.txt","a+");
	if(f!=NULL){
		while (fscanf(f,"%d %d %s %s %s %d %s \n",&m.journee,&m.temp,m.entree,m.plat_principale,m.dessert,&m.dechet,m.id)!=EOF){
			if(strcmp(m.id,id)==0){
				fprintf(g,"%d %d %s %s %s %d %s \n",m.journee,m.temp,m.entree,m.plat_principale,m.dessert,m.dechet,m.id);
			}
		
		}

	}
	fclose(f);
	fclose(g);
}
void afficher2(){
	menu m;
	FILE *f =NULL;
	f=fopen("menu.txt","r");
	if(f!=NULL)
	{
		while (fscanf(f,"%d %d %s %s %s %d %s \n",&m.journee,&m.temp,m.entree,m.plat_principale,m.dessert,&m.dechet,m.id)!=EOF)
		{
			
			printf("%d %d %s %s %s %d %s \n",m.journee,m.temp,m.entree,m.plat_principale,m.dessert,m.dechet,m.id);
		
		}

	}
}
void meilleur_menu()
{
	FILE *f,*g;
	dechet min,d,d1;
	f=fopen("dechets.txt","r");
	g=fopen("tmp.txt","a+");
	if(f!=NULL)
	{
		
		fscanf(f,"%d %d %f\n",&min.jour,&min.temp,&min.valeur);
		

		while(fscanf(f,"%d %d %f\n",&d.jour,&d.temp,&d.valeur)!=EOF)
		{
			
			if(min.valeur>d.valeur)
			{
				min=d;
				
			}
			
		}
		
	}
	fclose(f);
	f=fopen("dechets.txt","r");
	while(fscanf(f,"%d %d %f\n",&d1.jour,&d1.temp,&d1.valeur)!=EOF)
		{
			if(d1.valeur==min.valeur)
			{ 
				fprintf(g,"%d %d %f\n",d1.jour,d1.temp,d1.valeur);
			}
		}
	
	fclose(f);
	fclose(g);
}































