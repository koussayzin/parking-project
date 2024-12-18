#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>

#include "callbacks.h"
#include "interface.h"
#include "support.h"


#include <stdio.h>
#include <string.h>

#include "citoyen.c"


char sexe[30];
int check=0;
int checkm=0;
void show_error_dialog(const char *message) {
    GtkWidget *dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_ERROR, GTK_BUTTONS_OK, "%s", message);
    gtk_window_set_title(GTK_WINDOW(dialog), "Erreur");
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}





void on_buttonAjouter_clicked(GtkButton       *button,
                                        gpointer         citoyen_data) {




    // Déclaration des widgets
    GtkWidget *gestioncitoyen,*treeviewcitoyenA;
    gestioncitoyen = lookup_widget(GTK_WIDGET(button), "gestioncitoyen");

    citoyen d;  // Déclaration d'un utilisateur

    // Récupération des champs du formulaire
    GtkWidget *cin, *nom, *prenom, *jour, *mois, *annee, *mdp, *email, *telephone;

    cin = lookup_widget(GTK_WIDGET(button), "entryCINA");
    nom = lookup_widget(GTK_WIDGET(button), "entryNomA");
    prenom = lookup_widget(GTK_WIDGET(button), "entryPrenomA");
    jour = lookup_widget(GTK_WIDGET(button), "spinbuttonJourA");
    mois = lookup_widget(GTK_WIDGET(button), "combobox1");
    annee = lookup_widget(GTK_WIDGET(button), "spinbuttonAnneeA");
    mdp = lookup_widget(GTK_WIDGET(button), "entryVilleA");
    email = lookup_widget(GTK_WIDGET(button), "entryEmailA");
    telephone = lookup_widget(GTK_WIDGET(button), "entryTelephoneA");

    // Récupération du CIN
    strcpy(d.cin, gtk_entry_get_text(GTK_ENTRY(cin)));
    if (strlen(d.cin) == 0) {
        show_error_dialog("Le CIN ne doit pas être vide");
        return;
    }

    if (strlen(d.cin) != 8||!is_all_digits(d.cin)) {
        show_error_dialog("Le CIN ne respecte pas la forme (contient 8 chiffres)");
        return;
    }


    if (cin_exists(d.cin)) {
        show_error_dialog("Le CIN existe déjà");
        return;
    }

    // Récupération et validation du nom
    strcpy(d.First_name, gtk_entry_get_text(GTK_ENTRY(nom)));
    if (strlen(d.First_name) == 0) {
        show_error_dialog("Le nom ne doit pas être vide");
        return;
    }

    // Récupération et validation du prénom
    strcpy(d.Last_name, gtk_entry_get_text(GTK_ENTRY(prenom)));
    if (strlen(d.Last_name) == 0) {
        show_error_dialog("Le prénom ne doit pas être vide");
        return;
    }



    int j = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(jour));
    int a = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(annee));
    
    sprintf(d.day, "%d", j);  
    if (strlen(d.day) == 0) {
        show_error_dialog("Le jour ne doit pas être vide");
        return;
    }

    sprintf(d.year, "%d", a);  
    if (strlen(d.year) == 0) {
        show_error_dialog("L'année ne doit pas être vide");
        return;
    }



    strcpy(d.month, gtk_combo_box_get_active_text(GTK_COMBO_BOX(mois)));
    if (strlen(d.month) == 0) {
        show_error_dialog("Le mois doit être sélectionné");
        return;
    }

    //mdp
    strcpy(d.mdp, gtk_entry_get_text(GTK_ENTRY(mdp)));
    if (strlen(d.mdp) == 0) {
        show_error_dialog("Le mdp ne doit pas être vide");
        return;
    }


    // Récupération et validation de l'email
    strcpy(d.email, gtk_entry_get_text(GTK_ENTRY(email)));
    if (strlen(d.email) == 0) {
        show_error_dialog("L'email ne doit pas être vide");
        return;
    }
    // Récupération et validation du numéro de téléphone
    strcpy(d.phone_number, gtk_entry_get_text(GTK_ENTRY(telephone)));
    if (strlen(d.phone_number) != 8 ||!is_all_digits(d.phone_number)) {
        show_error_dialog("Le numéro de téléphone est incorrect");
        return;
    }

    strcpy(d.gender, sexe);
  if (strlen(d.gender) == 0) {
        show_error_dialog("selectioner le sexe d'utilisateur");
        return;
    }

    if (!check) {
        show_error_dialog("Il faut accepter les conditions de confidentialité");
        return;
    }


    add_account(d);
check=0;
    GtkWidget *dialog = gtk_message_dialog_new(NULL,
                                    GTK_DIALOG_DESTROY_WITH_PARENT,
                                    GTK_MESSAGE_OTHER,
                                    GTK_BUTTONS_OK,
                                    "Ajout réussi avec succès ✔");
    gtk_window_set_title(GTK_WINDOW(dialog), "Succès");
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);

  gtk_widget_destroy(gestioncitoyen);
        gestioncitoyen = create_gestioncitoyen();
        gtk_widget_show(gestioncitoyen);
    treeviewcitoyenA = lookup_widget(gestioncitoyen, "treeviewcitoyenA");
    show_citoyen(treeviewcitoyenA);

}
void
on_checkbutton1_toggled                (GtkToggleButton *togglebutton,
                                        gpointer         citoyen_data)
{
if (gtk_toggle_button_get_active(togglebutton)) {
        check = 1;
    } else {
        check = 0; 
    }
}


void
on_radioHommeA_toggled                 (GtkToggleButton *togglebutton,
                                        gpointer         citoyen_data)
{
if (gtk_toggle_button_get_active(togglebutton)){
strcpy(sexe,"homme");}
}


void
on_radioFemmeA_toggled                 (GtkToggleButton *togglebutton,
                                        gpointer         citoyen_data)
{
if (gtk_toggle_button_get_active(togglebutton)){
strcpy(sexe,"femme");}
}


void
on_treeviewcitoyenA_row_activated      (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         citoyen_data)
{

}


void
on_checkbutton2_toggled                (GtkToggleButton *togglebutton,
                                        gpointer         citoyen_data)
{
if (gtk_toggle_button_get_active(togglebutton)) {
        checkm = 1;
    } else {
        checkm = 0; 
    }
}


void
on_radiobuttonHommemodif_toggled       (GtkToggleButton *togglebutton,
                                        gpointer         citoyen_data)
{
if (gtk_toggle_button_get_active(togglebutton)){
strcpy(sexe,"homme");}
}


void
on_radiobuttonFemmemodif_toggled       (GtkToggleButton *togglebutton,
                                        gpointer         citoyen_data)
{
if (gtk_toggle_button_get_active(togglebutton)){
strcpy(sexe,"femme");}
}


void
on_buttonRafraichir_clicked            (GtkButton       *button,
                                        gpointer         citoyen_data)
{
 GtkWidget *gestioncitoyen,*treeviewcitoyenA;
gestioncitoyen = lookup_widget(GTK_WIDGET(button), "gestioncitoyen");
   gtk_widget_destroy(gestioncitoyen);
        gestioncitoyen = create_gestioncitoyen();
        gtk_widget_show(gestioncitoyen);
  treeviewcitoyenA = lookup_widget(gestioncitoyen, "treeviewcitoyenA");
    show_citoyen(treeviewcitoyenA);
}


void
on_buttonsupprimer_clicked             (GtkButton       *button,
                                        gpointer         citoyen_data)
{

 GtkWidget *gestioncitoyen;
    GtkTreeSelection *selection1;
    GtkTreeIter iter;
    GtkTreeModel *model;
    GtkWidget *treeviewcitoyenA;

    // Declare variables to hold the citoyen's details
    gchar *first_name, *last_name, *cin, *phone_number, *email, *address, *gender, *mdp;
    gchar *day, *month, *year;


    treeviewcitoyenA = lookup_widget(GTK_WIDGET(button), "treeviewcitoyenA");
    selection1 = gtk_tree_view_get_selection(GTK_TREE_VIEW(treeviewcitoyenA));

    // Initialize gestioncitoyen widget (assuming it's the parent window or a relevant container)
    gestioncitoyen = lookup_widget(GTK_WIDGET(button), "gestioncitoyen");

    // Check if a row is selected in the treeview
    if (gtk_tree_selection_get_selected(selection1, &model, &iter)) {
        // Retrieve the values of the selected citoyen
        gtk_tree_model_get(GTK_LIST_STORE(model), &iter,
            0, &cin,
            1, &first_name,
            2, &last_name,
            3, &phone_number,
            4, &day,
            5, &month,
            6, &year,
            7, &gender,
            8, &email,
            9, &mdp,
            -1);


        gtk_list_store_remove(GTK_LIST_STORE(model), &iter);



delete_citoyen(cin);

    } else {

        show_error_dialog("Please select an agent to delete.");
    }


}


void on_buttonmodif_clicked(GtkButton *button, gpointer citoyen_data) {
    GtkWidget *gestioncitoyen;
    GtkTreeSelection *selection2;
    GtkTreeIter iter;
    GtkTreeModel *model;
    GtkWidget *treeviewcitoyenA;

    // Declare variables to hold the citoyen's details
    gchar *first_name, *last_name, *cin, *phone_number, *email, *address, *gender, *mdp;
    gchar *day, *month, *year;

    int jj, mm, aa; // day, month, and year as integers
    treeviewcitoyenA = lookup_widget(GTK_WIDGET(button), "treeviewcitoyenA");
    selection2 = gtk_tree_view_get_selection(GTK_TREE_VIEW(treeviewcitoyenA));

    // Initialize gestioncitoyen widget (assuming it's the parent window or a relevant container)
    gestioncitoyen = lookup_widget(GTK_WIDGET(button), "gestioncitoyen");

    // Check if a row is selected in the treeview
    if (gtk_tree_selection_get_selected(selection2, &model, &iter)) {
        // Retrieve the values of the selected citoyen
        gtk_tree_model_get(GTK_LIST_STORE(model), &iter,
            0, &cin,
            1, &first_name,
            2, &last_name,
            3, &phone_number,
            4, &day,
            5, &month,
            6, &year,
            7, &gender,
            8, &email,
            9, &mdp,
            -1);


        gtk_list_store_remove(GTK_LIST_STORE(model), &iter);


        gtk_entry_set_text(GTK_ENTRY(lookup_widget(gestioncitoyen, "entryCINmodif")), cin);
        gtk_entry_set_text(GTK_ENTRY(lookup_widget(gestioncitoyen, "entryNommodif")), last_name);
        gtk_entry_set_text(GTK_ENTRY(lookup_widget(gestioncitoyen, "entryPrenommodif")), first_name);
        gtk_entry_set_text(GTK_ENTRY(lookup_widget(gestioncitoyen, "entryVillemodif")), mdp);
        gtk_entry_set_text(GTK_ENTRY(lookup_widget(gestioncitoyen, "entryEmailmodif")), email);
        gtk_entry_set_text(GTK_ENTRY(lookup_widget(gestioncitoyen, "entryTelephonemodif")), phone_number);

      

        // Convert day and year to integers
        jj = atoi(day);
        aa = atoi(year);

        // Set the values in the spin buttons for the day and year
        gtk_spin_button_set_value(GTK_SPIN_BUTTON(lookup_widget(gestioncitoyen, "spinbuttonJourmodif")), jj);
        gtk_spin_button_set_value(GTK_SPIN_BUTTON(lookup_widget(gestioncitoyen, "spinbuttonAnneemodif")), aa);


        if (strcmp(month, "Janvier") == 0) {
            gtk_combo_box_set_active(GTK_COMBO_BOX(lookup_widget(gestioncitoyen, "combobox2")), 0);
        } else if (strcmp(month, "Février") == 0) {
            gtk_combo_box_set_active(GTK_COMBO_BOX(lookup_widget(gestioncitoyen, "combobox2")), 1);
        } else if (strcmp(month, "Mars") == 0) {
            gtk_combo_box_set_active(GTK_COMBO_BOX(lookup_widget(gestioncitoyen, "combobox2")), 2);
        } else if (strcmp(month, "Avril") == 0) {
            gtk_combo_box_set_active(GTK_COMBO_BOX(lookup_widget(gestioncitoyen, "combobox2")), 3);
        } else if (strcmp(month, "Mai") == 0) {
            gtk_combo_box_set_active(GTK_COMBO_BOX(lookup_widget(gestioncitoyen, "combobox2")), 4);
        } else if (strcmp(month, "Juin") == 0) {
            gtk_combo_box_set_active(GTK_COMBO_BOX(lookup_widget(gestioncitoyen, "combobox2")), 5);
        } else if (strcmp(month, "Juillet") == 0) {
            gtk_combo_box_set_active(GTK_COMBO_BOX(lookup_widget(gestioncitoyen, "combobox2")), 6);
        } else if (strcmp(month, "Août") == 0) {
            gtk_combo_box_set_active(GTK_COMBO_BOX(lookup_widget(gestioncitoyen, "combobox2")), 7);
        } else if (strcmp(month, "Septembre") == 0) {
            gtk_combo_box_set_active(GTK_COMBO_BOX(lookup_widget(gestioncitoyen, "combobox2")), 8);
        } else if (strcmp(month, "Octobre") == 0) {
            gtk_combo_box_set_active(GTK_COMBO_BOX(lookup_widget(gestioncitoyen, "combobox2")), 9);
        } else if (strcmp(month, "Novembre") == 0) {
            gtk_combo_box_set_active(GTK_COMBO_BOX(lookup_widget(gestioncitoyen, "combobox2")), 10);
        } else if (strcmp(month, "Décembre") == 0) {
            gtk_combo_box_set_active(GTK_COMBO_BOX(lookup_widget(gestioncitoyen, "combobox2")), 11);
        }


    } else {

        show_error_dialog("Please select an agent to modify.");
    }
}

void on_buttonImprimer_clicked(GtkButton *button, gpointer citoyen_data) {
    char cin[60];
    char mois[60];
    char annee[60];

    GtkWidget *gestioncitoyen, *treeviewcitoyenC;
    GtkWidget *mois1, *annee1, *id_client, *totale;
    
    gestioncitoyen = lookup_widget(GTK_WIDGET(button), "gestioncitoyen");
    id_client = lookup_widget(GTK_WIDGET(button), "entryCINC");
    mois1 = lookup_widget(GTK_WIDGET(button), "combobox3");
    annee1 = lookup_widget(GTK_WIDGET(button), "spinbuttonMoisC");
    totale = lookup_widget(GTK_WIDGET(button), "label59"); // Label to show the total price

    // Get CIN
    strcpy(cin, gtk_entry_get_text(GTK_ENTRY(id_client)));
    if (strlen(cin) == 0) {
        show_error_dialog("Entrer le CIN du client");
        return;
    }

    // Get month
    strcpy(mois, gtk_combo_box_get_active_text(GTK_COMBO_BOX(mois1)));
    if (strlen(mois) == 0) {
        show_error_dialog("Le mois doit être sélectionné");
        return;
    }

    // Get year
    int a = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(annee1));
    sprintf(annee, "%d", a);  
    if (strlen(annee) == 0) {
        show_error_dialog("L'année ne doit pas être vide");
        return;
    }

    // Calculate total price
    double total = calculerPrixTotal(cin, mois, annee);

    // Create a string to display the total
    char totalStr[100];
    sprintf(totalStr, "Total: %.2f", total);  // Format the total with 2 decimal places

    // Set the text of the label to the total amount
    gtk_label_set_text(GTK_LABEL(totale), totalStr);

    // Update the treeview (optional, depending on your implementation)
    treeviewcitoyenC = lookup_widget(gestioncitoyen, "treeviewcitoyenC");
    mes_services(treeviewcitoyenC, cin, mois, annee);
}



void
on_buttonModifier_clicked              (GtkButton       *button,
                                        gpointer         citoyen_data)
{

    GtkWidget *gestioncitoyen,*treeviewcitoyenA;
    gestioncitoyen = lookup_widget(GTK_WIDGET(button), "gestioncitoyen");

    citoyen d; 


    GtkWidget *cin, *nom, *prenom, *jour, *mois, *annee, *mdp, *email, *telephone;

    cin = lookup_widget(GTK_WIDGET(button), "entryCINmodif");
    nom = lookup_widget(GTK_WIDGET(button), "entryNommodif");
    prenom = lookup_widget(GTK_WIDGET(button), "entryPrenommodif");
    jour = lookup_widget(GTK_WIDGET(button), "spinbuttonJourmodif");
    mois = lookup_widget(GTK_WIDGET(button), "combobox2");
    annee = lookup_widget(GTK_WIDGET(button), "spinbuttonAnneemodif");
    mdp = lookup_widget(GTK_WIDGET(button), "entryVillemodif");
    email = lookup_widget(GTK_WIDGET(button), "entryEmailmodif");
    telephone = lookup_widget(GTK_WIDGET(button), "entryTelephonemodif");


    strcpy(d.cin, gtk_entry_get_text(GTK_ENTRY(cin)));
    if (strlen(d.cin) == 0) {
        show_error_dialog("Le CIN ne doit pas être vide");
        return;
    }

    // Vérifier si le CIN existe déjà
    if (!cin_exists(d.cin)) {
        show_error_dialog("le cin est unique ne change pas");
        return;
    }

    // Récupération et validation du nom
    strcpy(d.First_name, gtk_entry_get_text(GTK_ENTRY(nom)));
    if (strlen(d.First_name) == 0) {
        show_error_dialog("Le nom ne doit pas être vide");
        return;
    }

    // Récupération et validation du prénom
    strcpy(d.Last_name, gtk_entry_get_text(GTK_ENTRY(prenom)));
    if (strlen(d.Last_name) == 0) {
        show_error_dialog("Le prénom ne doit pas être vide");
        return;
    }


    // Récupération et validation de la date de naissance
    int j = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(jour));
    int a = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(annee));
    
    sprintf(d.day, "%d", j);  
    if (strlen(d.day) == 0) {
        show_error_dialog("Le jour ne doit pas être vide");
        return;
    }

    sprintf(d.year, "%d", a);  
    if (strlen(d.year) == 0) {
        show_error_dialog("L'année ne doit pas être vide");
        return;
    }

    // Récupérer le mois sélectionné

    strcpy(d.month, gtk_combo_box_get_active_text(GTK_COMBO_BOX(mois)));
    if (strlen(d.month) == 0) {
        show_error_dialog("Le mois doit être sélectionné");
        return;
    }

    //mdp
    strcpy(d.mdp, gtk_entry_get_text(GTK_ENTRY(mdp)));
    if (strlen(d.mdp) == 0) {
        show_error_dialog("Le mdp ne doit pas être vide");
        return;
    }


    // Récupération et validation de l'email
    strcpy(d.email, gtk_entry_get_text(GTK_ENTRY(email)));
    if (strlen(d.email) == 0) {
        show_error_dialog("L'email ne doit pas être vide");
        return;
    }
    // Récupération et validation du numéro de téléphone
    strcpy(d.phone_number, gtk_entry_get_text(GTK_ENTRY(telephone)));
    if (strlen(d.phone_number) != 8 ||!is_all_digits(d.phone_number)) {
        show_error_dialog("Le numéro de téléphone est incorrect");
        return;
    }

    strcpy(d.gender, sexe);
  if (strlen(d.gender) == 0) {
        show_error_dialog("selectioner le sexe d'utilisateur");
        return;
    }

    if (!checkm) {
        show_error_dialog("Il faut accepter les conditions de confidentialité");
        return;
    }


    update_citoyen(d);
checkm=0;
    GtkWidget *dialog = gtk_message_dialog_new(NULL,
                                    GTK_DIALOG_DESTROY_WITH_PARENT,
                                    GTK_MESSAGE_OTHER,
                                    GTK_BUTTONS_OK,
                                    "modification réussi avec succès ✔");
    gtk_window_set_title(GTK_WINDOW(dialog), "Succès");
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);

  gtk_widget_destroy(gestioncitoyen);
        gestioncitoyen = create_gestioncitoyen();
        gtk_widget_show(gestioncitoyen);
    treeviewcitoyenA = lookup_widget(gestioncitoyen, "treeviewcitoyenA");
    show_citoyen(treeviewcitoyenA);
}


void
on_recherchehome_clicked               (GtkButton       *button,
                                        gpointer         citoyen_data)
{


GtkWidget *treeviewcitoyenA, *dialog;
    GtkWidget *entry;

    char cherche[30];
	citoyen u;
    entry = lookup_widget(GTK_WIDGET(button), "entryrecherchehome");
   treeviewcitoyenA = lookup_widget(GTK_WIDGET(button), "treeviewcitoyenA");
    strcpy(cherche, gtk_entry_get_text(GTK_ENTRY(entry)));

    FILE *f;
    f = fopen("citoyens.txt", "r");

    if (strcmp(cherche, "") == 0)
    {        dialog = gtk_message_dialog_new(GTK_WINDOW(dialog),
                                        GTK_DIALOG_DESTROY_WITH_PARENT,
                                        GTK_MESSAGE_WARNING,
                                        GTK_BUTTONS_OK,
                                        "le champs est vide");
        gtk_window_set_title(GTK_WINDOW(dialog), "Alerte");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
    }
    else if (f != NULL)
    {
        int found = 0; 

        while (fscanf(f, "%59[^;];%59[^;];%59[^;];%59[^;];%59[^;];%59[^;];%59[^;];%59[^;];%59[^;];%59[^\n]\n", 
                  u.cin, u.First_name, u.Last_name, u.phone_number, u.day, u.month, u.year, u.gender, u.email, u.mdp) != EOF)
        {
            if ((strcmp(cherche, u.First_name) == 0)||(strcmp(cherche,u.Last_name) == 0)||(strcmp(cherche,u.cin) == 0)||(strcmp(cherche,u.phone_number) == 0))
            {
                found = 1;
                break; 
            }
        }

        fclose(f);

        if (found == 0)
        {
            dialog = gtk_message_dialog_new(GTK_WINDOW(dialog),
                                            GTK_DIALOG_DESTROY_WITH_PARENT,
                                            GTK_MESSAGE_WARNING,
                                            GTK_BUTTONS_OK,
                                            "Aucun résultat trouvé pour votre recherche");
            gtk_window_set_title(GTK_WINDOW(dialog), "Alerte");
            gtk_dialog_run(GTK_DIALOG(dialog));
            gtk_widget_destroy(dialog);
        }
        else
        {
            chercher(treeviewcitoyenA, cherche);
        }
    }




}



