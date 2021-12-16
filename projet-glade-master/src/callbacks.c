#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>
#include "fonction.h"
#include "callbacks.h"
#include "interface.h"
#include "support.h"


void
on_buttonajouter_ghassen_clicked               (GtkWidget	 *objet_graphique,
                                        gpointer         user_data)
{

	GtkWidget *id_menu,*journee_menu,*temp_menu,*entree_menu,*pp_menu,*dessert_menu,*dechet_menu;
	menu m;
	
	id_menu=lookup_widget(objet_graphique,"entryid_ghassen");
	
	journee_menu=lookup_widget(objet_graphique,"spinbutton_journee_ghassen");
        temp_menu=lookup_widget(objet_graphique,"comboboxtemp_ghassen");
	
	entree_menu=lookup_widget(objet_graphique,"entryentree_ghassen");
	
	pp_menu=lookup_widget(objet_graphique,"entryplat_principale_ghassen");
	
	dessert_menu=lookup_widget(objet_graphique,"entrydessert_ghassen");
	dechet_menu=lookup_widget(objet_graphique,"spinbuttondechet_ghassen");
	strcpy(m.id,gtk_entry_get_text(GTK_ENTRY(id_menu)));
	m.journee=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(journee_menu));
        if(strcmp("Diner",gtk_combo_box_get_active_text(GTK_COMBO_BOX(temp_menu)))==0){
		m.temp=3;
	}
        else if(strcmp("Dejeune",gtk_combo_box_get_active_text(GTK_COMBO_BOX(temp_menu)))==0){
		m.temp=2;
	}
        else{
		m.temp=1;
	}	

	strcpy(m.entree,gtk_entry_get_text(GTK_ENTRY(entree_menu)));

	strcpy(m.plat_principale,gtk_entry_get_text(GTK_ENTRY(pp_menu)));
	strcpy(m.dessert,gtk_entry_get_text(GTK_ENTRY(dessert_menu)));

	m.dechet=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(dechet_menu));

	ajouter(m);


}


void
on_buttonafficher_ghassen_clicked              (GtkWidget	 *objet_graphique,
                                        gpointer         user_data)
{
	GtkWidget *windowajouter_ghassen,*windowafficher_ghassen,*treeviewmenu;
	windowajouter_ghassen=lookup_widget(objet_graphique,"windowajouter_ghassen");
	gtk_widget_destroy(windowajouter_ghassen);

	windowafficher_ghassen=lookup_widget(objet_graphique,"windowafficher_ghassen");
	windowafficher_ghassen=create_windowafficher_ghassen();
	gtk_widget_show(windowafficher_ghassen);

	treeviewmenu=lookup_widget(windowafficher_ghassen,"treeviewmenu");
	afficher(treeviewmenu,"menu.txt");

}


void
on_buttonmodifier_ghassen_clicked              (GtkWidget	 *objet_graphique,
                                        gpointer         user_data)
{
	GtkWidget *id_menu,*journee_menu,*temp_menu,*entree_menu,*pp_menu,*dessert_menu,*dechet_menu;
	menu m;
	
	id_menu=lookup_widget(objet_graphique,"entryid_ghassen");
	
	journee_menu=lookup_widget(objet_graphique,"spinbutton_journee_ghassen");
        temp_menu=lookup_widget(objet_graphique,"comboboxtemp_ghassen");
	
	entree_menu=lookup_widget(objet_graphique,"entryentree_ghassen");
	
	pp_menu=lookup_widget(objet_graphique,"entryplat_principale_ghassen");
	
	dessert_menu=lookup_widget(objet_graphique,"entrydessert_ghassen");
	dechet_menu=lookup_widget(objet_graphique,"spinbuttondechet_ghassen");
	strcpy(m.id,gtk_entry_get_text(GTK_ENTRY(id_menu)));
	m.journee=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(journee_menu));
        if(strcmp("Diner",gtk_combo_box_get_active_text(GTK_COMBO_BOX(temp_menu)))==0){
		m.temp=3;
	}
        else if(strcmp("Dejeune",gtk_combo_box_get_active_text(GTK_COMBO_BOX(temp_menu)))==0){
		m.temp=2;
	}
        else{
		m.temp=1;
	}

	strcpy(m.entree,gtk_entry_get_text(GTK_ENTRY(entree_menu)));

	strcpy(m.plat_principale,gtk_entry_get_text(GTK_ENTRY(pp_menu)));
	strcpy(m.dessert,gtk_entry_get_text(GTK_ENTRY(dessert_menu)));

	m.dechet=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(dechet_menu));
	modifier(m.id,m);

}


void
on_treeviewmenu_row_activated          (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data)
{

 GtkTreeIter iter;

 gchar *id ;


GtkTreeModel *model=gtk_tree_view_get_model(treeview);
 if(gtk_tree_model_get_iter(model,&iter,path)){
   gtk_tree_model_get(GTK_LIST_STORE(model),&iter,6,&id,-1);
   supprimer(id);
   afficher(treeview,"menu.txt");

 }
	
}


void
on_buttonretour_ghassen_clicked                (GtkWidget	 *objet_graphique,
                                        gpointer         user_data)
{
	GtkWidget *windowajouter_ghassen,*windowafficher_ghassen;
	windowafficher_ghassen=lookup_widget(objet_graphique,"windowafficher_ghassen");
	gtk_widget_destroy(windowafficher_ghassen);
	windowajouter_ghassen=lookup_widget(objet_graphique,"windowajouter_ghassen");
	windowajouter_ghassen=create_windowajouter_ghassen();
	gtk_widget_show(windowajouter_ghassen);

}


void
on_buttongotomodifier_ghassen_clicked          (GtkWidget	 *objet_graphique,
                                        gpointer         user_data)
{
 GtkWidget *windowafficher_ghassen,*windowajouter_ghassen,*treeviewmenu,*id_menu,*entree_menu,*pp_menu,*dessert_menu,*journee_menu,*temp_menu,*dechet_menu;
	GtkTreeModel *model;
	GtkTreeSelection *selection;
	GtkTreeIter iter;
	gchar *id,*entree,*pp,*dessert;
	gint journee,temp,dechet;
	windowafficher_ghassen=lookup_widget(objet_graphique,"windowafficher_ghassen");
	treeviewmenu=lookup_widget(windowafficher_ghassen,"treeviewmenu");
	selection=gtk_tree_view_get_selection(GTK_TREE_VIEW(treeviewmenu));
	if(gtk_tree_selection_get_selected(selection,&model,&iter))
	{
		gtk_tree_model_get(model,&iter,0,&journee,1,&temp,2,&entree,3,&pp,4,&dessert,5,&dechet,6,&id,-1);
		gtk_widget_destroy(windowafficher_ghassen);
		windowajouter_ghassen=lookup_widget(objet_graphique,"windowajouter_ghassen");
		windowajouter_ghassen=create_windowajouter_ghassen();
		gtk_widget_show(windowajouter_ghassen);

		id_menu=lookup_widget(windowajouter_ghassen,"entryid_ghassen");
		gtk_entry_set_text(GTK_ENTRY(id_menu),id);

		entree_menu=lookup_widget(windowajouter_ghassen,"entryentree_ghassen");
		gtk_entry_set_text(GTK_ENTRY(entree_menu),entree);

		pp_menu=lookup_widget(windowajouter_ghassen,"entryplat_principale_ghassen");
		gtk_entry_set_text(GTK_ENTRY(pp_menu),pp);

		dessert_menu=lookup_widget(windowajouter_ghassen,"entrydessert_ghassen");
		gtk_entry_set_text(GTK_ENTRY(dessert_menu),dessert);

		journee_menu=lookup_widget(windowajouter_ghassen,"spinbutton_journee_ghassen");
		gtk_spin_button_set_value(GTK_SPIN_BUTTON(journee_menu),journee);

		dechet_menu=lookup_widget(windowajouter_ghassen,"spinbuttondechet_ghassen");
		gtk_spin_button_set_value(GTK_SPIN_BUTTON(dechet_menu),dechet);

		temp_menu=lookup_widget(windowajouter_ghassen,"comboboxtemp_ghassen");

		gtk_combo_box_set_active(GTK_COMBO_BOX(temp_menu),temp-1);
		
	}

}


void
on_buttonrechercher_ghassen_clicked            (GtkWidget	 *objet_graphique,
                                        gpointer         user_data)
{
	GtkWidget *windowafficher_ghassen,*treeviewmenu,*id;
	char id1[20];
	windowafficher_ghassen=lookup_widget(objet_graphique,"windowafficher_ghassen");
	treeviewmenu=lookup_widget(windowafficher_ghassen,"treeviewmenu");
	id=lookup_widget(objet_graphique,"entryrecherche_ghassen");
	strcpy(id1,gtk_entry_get_text(GTK_ENTRY(id)));
	if(strcmp(id1,"")==0)
		afficher(treeviewmenu,"menu.txt");
	else{
		rechercher(id1);
		afficher(treeviewmenu,"recherche.txt");
		remove("recherche.txt");
	}


}


void
on_buttonmeilleurmenu_ghassen_clicked          (GtkWidget	 *objet_graphique,
                                        gpointer         user_data)
{
	meilleur_menu();

}


void
on_buttongotomeilleurmenu_ghassen_clicked      (GtkWidget	 *objet_graphique,
                                        gpointer         user_data)
{
	GtkWidget *windowmeilleurmenu_ghassen,*windowafficher_ghassen;
	windowafficher_ghassen=lookup_widget(objet_graphique,"windowafficher_ghassen");
	gtk_widget_destroy(windowafficher_ghassen);
	windowmeilleurmenu_ghassen=lookup_widget(objet_graphique,"windowmeilleurmenu_ghassen");
	windowmeilleurmenu_ghassen=create_windowmeilleurmenu_ghassen();
	gtk_widget_show(windowmeilleurmenu_ghassen);
}


