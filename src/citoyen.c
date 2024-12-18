#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>  
#include<gtk/gtk.h>
#include "citoyen.h"
#include "service.h"



enum {
    EcitoyenCIN,
    EcitoyenFirstName,
    EcitoyenLastName,
    EcitoyenPhoneNumber,
    EcitoyenDay,
    EcitoyenMonth,
    EcitoyenYear,
    EcitoyenGender,
    EcitoyenEmail,
    Ecitoyenmdp,
    COLUMNS_citoyen
};

enum {

    EServiceID,
    EServiceType,
    EServicePrix,
    EServicePaiement,
    EServiceDuree,
    EServicejour,
    EServicemois,
    EServiceannee,
    COLUMNS_SERVICE
};

int cin_exists(char *cin1) {
    FILE *f = fopen("citoyens.txt", "r");
    citoyen temp;
    

    while (fscanf(f, "%59[^;];%59[^;];%59[^;];%59[^;];%59[^;];%59[^;];%59[^;];%59[^;];%59[^;];%59[^\n]\n",
       &temp.cin, temp.First_name, temp.Last_name, temp.phone_number,
       &temp.day, temp.month, &temp.year, temp.gender,
       temp.email,temp.mdp) != EOF) {
	if (strcmp(temp.cin, cin1) == 0) {

            fclose(f);
            return 1; 
        }
    }

    fclose(f);
    return 0; 
}

int is_all_digits(const char *str) {

    for (int i = 0; i < strlen(str); i++) {
        if (!isdigit(str[i])) {
            return 0; 
        }
    }
    return 1; 
}



void add_account(citoyen u) {
    FILE *f = fopen("citoyens.txt", "a+");

    fprintf(f, "%s;%s;%s;%s;%s;%s;%s;%s;%s;%s\n", 
            u.cin,
            u.First_name,
            u.Last_name,
            u.phone_number,
            u.day,
            u.month,
            u.year,  
            u.gender,
            u.email  ,
            u.mdp  
      );

    fclose(f);

}

void update_citoyen(citoyen updated_citoyen) {
    FILE *f = fopen("citoyens.txt", "r");
    FILE *f_temp = fopen("citoyens_temp.txt", "w");
    citoyen temp;
    int found = 0;



    while (fscanf(f, "%59[^;];%59[^;];%59[^;];%59[^;];%59[^;];%59[^;];%59[^;];%59[^;];%59[^;];%59[^\n]\n",
                  temp.cin, temp.First_name, temp.Last_name, temp.phone_number, temp.day, temp.month, temp.year,
                  temp.gender, temp.email, temp.mdp) != EOF) {

        if (strcmp(temp.cin, updated_citoyen.cin) == 0) {

            fprintf(f_temp, "%s;%s;%s;%s;%s;%s;%s;%s;%s;%s\n",
                updated_citoyen.cin,
		updated_citoyen.First_name, 
		updated_citoyen.Last_name,
 		updated_citoyen.phone_number,
                updated_citoyen.day, 
		updated_citoyen.month, 
		updated_citoyen.year,
		updated_citoyen.gender,
                updated_citoyen.email,
		updated_citoyen.mdp
);

        } else {

            fprintf(f_temp, "%s;%s;%s;%s;%s;%s;%s;%s;%s;%s\n",
                    temp.cin, temp.First_name, temp.Last_name, temp.phone_number, temp.day, temp.month,
                    temp.year, temp.gender, temp.email, temp.mdp);
        }
    }

    fclose(f);
    fclose(f_temp);



        remove("citoyens.txt");
        rename("citoyens_temp.txt", "citoyens.txt");
}



void delete_citoyen(const char *cin_to_delete) {
    FILE *f = fopen("citoyens.txt", "r");
    FILE *f_temp = fopen("citoyens_temp.txt", "w");
    citoyen temp;
    int found = 0;

    if (f == NULL) {
        printf("Error opening citoyens file for reading.\n");
        return;
    }

    if (f_temp == NULL) {
        printf("Error opening temporary file for writing.\n");
        fclose(f);
        return;
    }


    while (fscanf(f, "%59[^;];%59[^;];%59[^;];%59[^;];%59[^;];%59[^;];%59[^;];%59[^;];%59[^;];%59[^\n]\n",
                  temp.cin, temp.First_name, temp.Last_name, temp.phone_number, temp.day, temp.month, temp.year,
                  temp.gender, temp.email, temp.mdp) != EOF) {

        if (strcmp(temp.cin, cin_to_delete) != 0) {

            fprintf(f_temp, "%s;%s;%s;%s;%s;%s;%s;%s;%s;%s\n",
                    temp.cin, temp.First_name, temp.Last_name, temp.phone_number, temp.day, temp.month,
                    temp.year, temp.gender, temp.email, temp.mdp);
        } else {

            found = 1;
        }
    }

    fclose(f);
    fclose(f_temp);

    if (found) {
        remove("citoyens.txt");
        rename("citoyens_temp.txt", "citoyens.txt");
        printf("citoyen with CIN %s deleted successfully.\n", cin_to_delete);
    } else {
        remove("citoyens_temp.txt");
        printf("citoyen with CIN %s not found.\n", cin_to_delete);
    }
}





void show_citoyen(GtkWidget *fr) {
    citoyen u; 
    GtkCellRenderer *renderer;
    GtkTreeViewColumn *column;
    GtkTreeIter iter;
    GtkListStore *store;
    FILE *f;

    store = gtk_list_store_new(COLUMNS_citoyen, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);

    if (store == NULL) {
        fprintf(stderr, "Error: Failed to create GtkListStore\n");
        return; 
    }

    if (gtk_tree_view_get_model(GTK_TREE_VIEW(fr)) == NULL) {

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("CIN", renderer, "text", EcitoyenCIN, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(fr), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("First Name", renderer, "text", EcitoyenFirstName, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(fr), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Last Name", renderer, "text", EcitoyenLastName, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(fr), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Phone Number", renderer, "text", EcitoyenPhoneNumber, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(fr), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Day", renderer, "text", EcitoyenDay, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(fr), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Month", renderer, "text", EcitoyenMonth, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(fr), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Year", renderer, "text", EcitoyenYear, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(fr), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Gender", renderer, "text", EcitoyenGender, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(fr), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Email", renderer, "text", EcitoyenEmail, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(fr), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("mot de passe", renderer, "text", Ecitoyenmdp, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(fr), column);
    }

    f = fopen("citoyens.txt", "r");
    if (f == NULL) {
        perror("Unable to open file");
        return;
    }


    while (fscanf(f, "%59[^;];%59[^;];%59[^;];%59[^;];%59[^;];%59[^;];%59[^;];%59[^;];%59[^;];%59[^\n]\n", 
                  u.cin, u.First_name, u.Last_name, u.phone_number, u.day, u.month, u.year, u.gender, u.email, u.mdp) != EOF) {
        gtk_list_store_append(store, &iter);
        gtk_list_store_set(store, &iter,
                           EcitoyenCIN, u.cin,
                           EcitoyenFirstName, u.First_name,
                           EcitoyenLastName, u.Last_name,
                           EcitoyenPhoneNumber, u.phone_number,
                           EcitoyenDay, u.day,
                           EcitoyenMonth, u.month,
                           EcitoyenYear, u.year,
                           EcitoyenGender, u.gender,
                           EcitoyenEmail, u.email,
                           Ecitoyenmdp, u.mdp,
                           -1);
    }


    gtk_tree_view_set_model(GTK_TREE_VIEW(fr), GTK_TREE_MODEL(store));
    g_object_unref(store); 
    fclose(f); 
}











void chercher(GtkWidget *fr,char *cherche) {
    citoyen u; 
    GtkCellRenderer *renderer;
    GtkTreeViewColumn *column;
    GtkTreeIter iter;
    GtkListStore *store;
    FILE *f;

    store = gtk_list_store_new(COLUMNS_citoyen, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);

    if (store == NULL) {
        fprintf(stderr, "Error: Failed to create GtkListStore\n");
        return; 
    }

    if (gtk_tree_view_get_model(GTK_TREE_VIEW(fr)) == NULL) {

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("CIN", renderer, "text", EcitoyenCIN, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(fr), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("First Name", renderer, "text", EcitoyenFirstName, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(fr), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Last Name", renderer, "text", EcitoyenLastName, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(fr), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Phone Number", renderer, "text", EcitoyenPhoneNumber, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(fr), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Day", renderer, "text", EcitoyenDay, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(fr), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Month", renderer, "text", EcitoyenMonth, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(fr), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Year", renderer, "text", EcitoyenYear, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(fr), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Gender", renderer, "text", EcitoyenGender, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(fr), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Email", renderer, "text", EcitoyenEmail, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(fr), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("City", renderer, "text", Ecitoyenmdp, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(fr), column);
    }

    f = fopen("citoyens.txt", "r");
    if (f == NULL) {
        perror("Unable to open file");
        return;
    }


    while (fscanf(f, "%59[^;];%59[^;];%59[^;];%59[^;];%59[^;];%59[^;];%59[^;];%59[^;];%59[^;];%59[^\n]\n", 
                  u.cin, u.First_name, u.Last_name, u.phone_number, u.day, u.month, u.year, u.gender, u.email, u.mdp) != EOF) {

if ((strcmp(u.First_name, cherche) == 0)||(strcmp(u.Last_name,cherche) == 0)||(strcmp(u.cin,cherche) == 0)||(strcmp(u.phone_number,cherche) == 0)){
        gtk_list_store_append(store, &iter);
        gtk_list_store_set(store, &iter,
                           EcitoyenCIN, u.cin,
                           EcitoyenFirstName, u.First_name,
                           EcitoyenLastName, u.Last_name,
                           EcitoyenPhoneNumber, u.phone_number,
                           EcitoyenDay, u.day,
                           EcitoyenMonth, u.month,
                           EcitoyenYear, u.year,
                           EcitoyenGender, u.gender,
                           EcitoyenEmail, u.email,
                           Ecitoyenmdp, u.mdp,
                           -1);
    }
}

    gtk_tree_view_set_model(GTK_TREE_VIEW(fr), GTK_TREE_MODEL(store));
    g_object_unref(store); 
    fclose(f); 
}
void mes_services(GtkWidget *treeview,char *cin,char *mois,char *annee) {
    service s; 
    GtkCellRenderer *renderer;
    GtkTreeViewColumn *column;
    GtkTreeIter iter;
    GtkListStore *store;
    FILE *f;

    store = gtk_list_store_new(COLUMNS_SERVICE, 
                               G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, 
                               G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);

    if (store == NULL) {
        fprintf(stderr, "Error: Failed to create GtkListStore\n");
        return; 
    }

     if (gtk_tree_view_get_model(GTK_TREE_VIEW(treeview)) == NULL) {
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Service ID", renderer, "text", EServiceID, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Type", renderer, "text", EServiceType, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Prix", renderer, "text", EServicePrix, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Paiement", renderer, "text", EServicePaiement, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Durée", renderer, "text", EServiceDuree, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Jour", renderer, "text", EServicejour, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Mois", renderer, "text", EServicemois, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Année", renderer, "text", EServiceannee, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);
}
    // Open the file to read the data
    f = fopen("services.txt", "r");
    if (f == NULL) {
        perror("Unable to open file");
        return;
    }

    // Read the file line by line and insert data into the TreeView
    while (fscanf(f, "%49[^;];%49[^;];%49[^;];%49[^;];%49[^;];%49[^;];%49[^;];%49[^;];%59[^\n]\n", 
                  s.idclient, s.id_service, s.type, s.prix, s.paiement, s.duree, 
                  s.jour, s.mois, s.annee) == 9) {
		if ((strcmp(s.idclient, cin) == 0)&&(strcmp(s.mois,mois) == 0)&&(strcmp(s.annee,annee) == 0)){
        gtk_list_store_append(store, &iter);
        gtk_list_store_set(store, &iter,

            EServiceID, s.id_service,
            EServiceType, s.type,
            EServicePrix, s.prix,
            EServicePaiement, s.paiement,
            EServiceDuree, s.duree,
            EServicejour, s.jour,
            EServicemois, s.mois,
            EServiceannee, s.annee,
            -1);
	}
    }

    // Set the model for the TreeView
    gtk_tree_view_set_model(GTK_TREE_VIEW(treeview), GTK_TREE_MODEL(store));
    g_object_unref(store);  // Free the store when done

    // Close the file
    fclose(f);
}


double calculerPrixTotal(const char* cin, const char* mois, const char* annee) {
    FILE *f;
    service s;
    double total = 0.0;  // Variable pour stocker le prix total

    // Ouvrir le fichier pour lire les données
    f = fopen("services.txt", "r");
    if (f == NULL) {
        perror("Impossible d'ouvrir le fichier");
        return;
    }

    // Lire chaque ligne du fichier et appliquer les conditions
    while (fscanf(f, "%49[^;];%49[^;];%49[^;];%49[^;];%49[^;];%49[^;];%49[^;];%49[^;];%59[^\n]\n", 
                  s.idclient, s.id_service, s.type, s.prix, s.paiement, s.duree, 
                  s.jour, s.mois, s.annee) == 9) {
        
        // Vérifier les conditions (idclient, mois, annee)
        if ((strcmp(s.idclient, cin) == 0) && (strcmp(s.mois, mois) == 0) && (strcmp(s.annee, annee) == 0)) {
            

            double prix = atof(s.prix);  
            total += prix;
        }
    }


 return total;


    fclose(f);
}

