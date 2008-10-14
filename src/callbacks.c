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
	GtkTreeIter iter;
	GtkTreeIter iter_prev;
	GtkTreeView *treeview;
	GtkTreePath *path;
	GtkTreePath *path_prev;

	treeview = GTK_TREE_VIEW(lookup_widget(GTK_WIDGET(g_GAria2), "treeview"));
	gtk_tree_view_get_cursor(treeview, &path, NULL);

	if (path)
	{
		path_prev = path;
		if (!gtk_tree_path_prev(path_prev)) {
			gtk_tree_path_free(path);
			return;
		}
		gtk_tree_view_get_cursor(treeview, &path, NULL);

		gtk_tree_model_get_iter(gtk_tree_view_get_model(treeview), &iter, path);
		gtk_tree_model_get_iter(gtk_tree_view_get_model(treeview), &iter_prev, path_prev);

		gtk_list_store_swap(GTK_LIST_STORE(gtk_tree_view_get_model(treeview)), &iter, &iter_prev);
		gtk_tree_path_free(path);
		gtk_tree_path_free(path_prev);
	}
}


void
on_down_activate                       (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
	GtkTreeIter iter;
	GtkTreeIter iter_next;
	GtkTreeView *treeview;
	GtkTreePath *path;
	GtkTreePath *path_next;

	treeview = GTK_TREE_VIEW(lookup_widget(GTK_WIDGET(g_GAria2), "treeview"));
	gtk_tree_view_get_cursor(treeview, &path, NULL);

	if (path)
	{
		path_next = path;
		gtk_tree_path_next(path_next);

		if (!gtk_tree_model_get_iter(gtk_tree_view_get_model(treeview), &iter_next, path_next)) {
			gtk_tree_path_free(path);
			return;
		}
		gtk_tree_view_get_cursor(treeview, &path, NULL);
		gtk_tree_model_get_iter(gtk_tree_view_get_model(treeview), &iter, path);

		gtk_list_store_swap(GTK_LIST_STORE(gtk_tree_view_get_model(treeview)), &iter, &iter_next);
		gtk_tree_path_free(path);
		gtk_tree_path_free(path_next);
	}

}

void
on_preferences_activate                (G_GNUC_UNUSED GtkMenuItem     *menuitem,
                                        G_GNUC_UNUSED gpointer         user_data)
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
                                        G_GNUC_UNUSED gpointer         user_data)
{
	GtkWidget *spStartTimeHour;
	GtkWidget *spStartTimeMinute;
	GtkWidget *spEndTimeHour;
	GtkWidget *spEndTimeMinute;
	gboolean schedule;

	spStartTimeHour = lookup_widget(GTK_WIDGET(togglebutton), "spStartTimeHour");
	spStartTimeMinute = lookup_widget(GTK_WIDGET(togglebutton), "spStartTimeMinute");
	spEndTimeHour = lookup_widget(GTK_WIDGET(togglebutton), "spEndTimeHour");
	spEndTimeMinute = lookup_widget(GTK_WIDGET(togglebutton), "spEndTimeMinute");

	schedule = gtk_toggle_button_get_active(togglebutton);
	gtk_widget_set_sensitive(spStartTimeHour, schedule);
	gtk_widget_set_sensitive(spStartTimeMinute, schedule);
	gtk_widget_set_sensitive(spEndTimeHour, schedule);
	gtk_widget_set_sensitive(spEndTimeMinute, schedule);
}


void
on_quit_activate                       (G_GNUC_UNUSED GtkMenuItem     *menuitem,
                                        G_GNUC_UNUSED gpointer         user_data)
{
	gtk_main_quit();
}


gboolean
on_GAria2_delete_event                 (G_GNUC_UNUSED GtkWidget       *widget,
                                        G_GNUC_UNUSED GdkEvent        *event,
                                        G_GNUC_UNUSED gpointer         user_data)
{
	gtk_main_quit();
	return FALSE;
}

