#ifndef CALLBACKS_H
#define CALLBACKS_H

#include <gtk/gtk.h>
void on_buttonAjouter_clicked(GtkButton *button, gpointer user_data);
void on_buttonconfirmer_clicked(GtkButton *button, gpointer user_data);
void on_buttonEntrer_clicked(GtkButton *button, gpointer user_data);
void on_buttonRafraichir_clicked(GtkButton *button, gpointer user_data);
void on_buttonQuitter_clicked(GtkButton *button, gpointer user_data);
void on_buttonModifier_clicked(GtkButton *button, gpointer user_data);
void on_buttonsupprimer_clicked(GtkButton *button, gpointer user_data);



void
on_checkbutton1_toggled                (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_radioHommeA_toggled                 (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_radioFemmeA_toggled                 (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_treeviewcitoyenA_row_activated      (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data);

void
on_checkbutton2_toggled                (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_radiobuttonHommemodif_toggled       (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_radiobuttonFemmemodif_toggled       (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_buttonRafraichir_clicked            (GtkButton       *button,
                                        gpointer         user_data);

void
on_buttonsupprimer_clicked             (GtkButton       *button,
                                        gpointer         user_data);

void
on_buttonmodif_clicked                 (GtkButton       *button,
                                        gpointer         user_data);

void
on_buttonImprimer_clicked              (GtkButton       *button,
                                        gpointer         user_data);

void
on_buttonModifier_clicked              (GtkButton       *button,
                                        gpointer         user_data);
#endif 

void
on_recherchehome_clicked               (GtkButton       *button,
                                        gpointer         user_data);

void
on_enregisteravis_clicked              (GtkButton       *button,
                                        gpointer         user_data);
