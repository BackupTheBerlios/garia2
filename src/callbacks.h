#include <gtk/gtk.h>


void
on_new_activate                        (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_play_activate                       (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_pause_activate                      (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_delete_activate                     (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_up_activate                         (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_down_activate                       (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_quit1_activate                      (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_preferences_activate                (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_about_activate                      (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_btnDownloadDir_clicked              (GtkButton       *button,
                                        gpointer         user_data);

void
on_cbUseScheduler_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data);
