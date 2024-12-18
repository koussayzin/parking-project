#ifndef CITOYEN_H
#define CITOYEN_H

#include <stdio.h>
#include <string.h>

#include <gtk/gtk.h>



typedef struct {
    char cin[60];
    char First_name[60];
    char Last_name[60];
    char phone_number[60];
    char day[60];
    char month[60];
    char year[60];
    char gender[60];  
    char email[60];
    char mdp[60];
}citoyen;

int cin_exists( char *cin1);
int is_all_digits(const char *str) ;
void add_account(citoyen u);
void update_citoyen(citoyen updated_citoyen);
void delete_citoyen(const char *cin_to_delete);
void show_citoyen(GtkWidget *fr) ;
void chercher(GtkWidget *fr,char *cherche) ;
void mes_services(GtkWidget *treeview,char *cin,char *mois,char *annee);
double calculerPrixTotal(const char* cin, const char* mois, const char* annee) ;
#endif 
