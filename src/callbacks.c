#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>

#include "callbacks.h"
#include "interface.h"
#include "support.h"

#include "garia2.h"

void
on_new_activate                        (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{

}


void
on_play_activate                       (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{

}


void
on_pause_activate                      (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{

}


void
on_delete_activate                     (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{

}


void
on_up_activate                         (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{

}


void
on_down_activate                       (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{

}

void
on_preferences_activate                (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
	GtkWidget *dialog;
	gint ret;
	
	dialog = create_preferences ();
	preference_to_gui(dialog, &g_preference);
	ret = gtk_dialog_run(GTK_DIALOG(dialog));
	switch (ret) {
	case GTK_RESPONSE_OK:
		gui_to_preference(dialog, &g_preference);
		save_settings(&g_preference);
		break;
      default:
         break;
    }
	gtk_widget_destroy (dialog);	
}


void
on_about_activate                      (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
	GtkWidget *aboutdialog;
	
	aboutdialog = create_aboutdialog ();
	gtk_dialog_run(GTK_DIALOG(aboutdialog));
	gtk_widget_destroy(aboutdialog);
}


void
on_btnDownloadDir_clicked              (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_cbUseScheduler_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{

}


void
on_quit_activate                       (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
	gtk_main_quit();
}


gboolean
on_GAria2_delete_event                 (GtkWidget       *widget,
                                        GdkEvent        *event,
                                        gpointer         user_data)
{
	gtk_main_quit();
	return FALSE;
}

