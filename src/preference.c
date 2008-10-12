/*
 *      preference.c
 *      
 *      Copyright 2008 Yura Siamashka <yurand2@gmail.com>
 *      
 *      This program is free software; you can redistribute it and/or modify
 *      it under the terms of the GNU General Public License as published by
 *      the Free Software Foundation; either version 3 of the License, or
 *      (at your option) any later version.
 *      
 *      This program is distributed in the hope that it will be useful,
 *      but WITHOUT ANY WARRANTY; without even the implied warranty of
 *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *      GNU General Public License for more details.
 */

#include <string.h>

#include "preference.h"
#include "garia2.h"
#include "support.h"

void gui_to_preference(GtkWidget *dlg, Preferences *pref)
{
	GtkWidget *enDownloadDir;
	GtkWidget *spMaxConcurrentDownloads;
	GtkWidget *cbBackend;
	GtkWidget *checkUseScheduler;
	GtkWidget *spStartTimeHour;
	GtkWidget *spStartTimeMinute;
	GtkWidget *spEndTimeHour;
	GtkWidget *spEndTimeMinute;

	enDownloadDir = lookup_widget(dlg, "enDownloadDir");
	spMaxConcurrentDownloads = lookup_widget(dlg, "spMaxConcurrentDownloads");
	cbBackend = lookup_widget(dlg, "cbBackend");
	checkUseScheduler = lookup_widget(dlg, "checkUseScheduler");
	spStartTimeHour = lookup_widget(dlg, "spStartTimeHour");
	spStartTimeMinute = lookup_widget(dlg, "spStartTimeMinute");
	spEndTimeHour = lookup_widget(dlg, "spEndTimeHour");
	spEndTimeMinute = lookup_widget(dlg, "spEndTimeMinute");
	
	pref->backend = gtk_combo_box_get_active(GTK_COMBO_BOX(cbBackend));
	pref->download_dir = g_strdup(gtk_entry_get_text(GTK_ENTRY(enDownloadDir)));
	pref->max_concurrent_downloads = gtk_spin_button_get_value(GTK_SPIN_BUTTON(spMaxConcurrentDownloads));
	pref->use_schedule = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(checkUseScheduler));
	pref->start_time_hour = gtk_spin_button_get_value(GTK_SPIN_BUTTON(spStartTimeHour));
	pref->start_time_minute = gtk_spin_button_get_value(GTK_SPIN_BUTTON(spStartTimeMinute));
	pref->end_time_hour = gtk_spin_button_get_value(GTK_SPIN_BUTTON(spEndTimeHour));
	pref->end_time_minute = gtk_spin_button_get_value(GTK_SPIN_BUTTON(spEndTimeMinute));
}

void preference_to_gui(GtkWidget *dlg, Preferences *pref)
{
	GtkWidget *enDownloadDir;
	GtkWidget *spMaxConcurrentDownloads;
	GtkWidget *cbBackend;
	GtkWidget *checkUseScheduler;
	GtkWidget *spStartTimeHour;
	GtkWidget *spStartTimeMinute;
	GtkWidget *spEndTimeHour;
	GtkWidget *spEndTimeMinute;

	enDownloadDir = lookup_widget(dlg, "enDownloadDir");
	spMaxConcurrentDownloads = lookup_widget(dlg, "spMaxConcurrentDownloads");
	cbBackend = lookup_widget(dlg, "cbBackend");
	checkUseScheduler = lookup_widget(dlg, "checkUseScheduler");
	spStartTimeHour = lookup_widget(dlg, "spStartTimeHour");
	spStartTimeMinute = lookup_widget(dlg, "spStartTimeMinute");
	spEndTimeHour = lookup_widget(dlg, "spEndTimeHour");
	spEndTimeMinute = lookup_widget(dlg, "spEndTimeMinute");	
	
	gtk_combo_box_set_active(GTK_COMBO_BOX(cbBackend), pref->backend); 
	gtk_entry_set_text(GTK_ENTRY(enDownloadDir), pref->download_dir);
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(spMaxConcurrentDownloads), pref->max_concurrent_downloads);
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(checkUseScheduler), pref->use_schedule);
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(spStartTimeHour), pref->start_time_hour);
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(spStartTimeMinute), pref->start_time_minute);
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(spEndTimeHour), pref->end_time_hour);
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(spEndTimeMinute), pref->end_time_minute);
}

static gchar* get_config_path()
{
	gchar *path = g_build_filename(g_get_user_config_dir(), "garia2", "config.ini", NULL);
	return path;
}

void load_settings(Preferences *pref)
{
	gchar *path;
	GKeyFile* key;
	GError *err = NULL;

	path = get_config_path();
	key = g_key_file_new();
	memset(pref, 0, sizeof(*pref));
	g_key_file_load_from_file(key, path, G_KEY_FILE_KEEP_COMMENTS|G_KEY_FILE_KEEP_TRANSLATIONS, NULL);
	
	pref->backend = g_key_file_get_integer(key, "core", "backend", &err);
	if (err) {
		g_error_free(err);
		err = NULL;
		pref->backend = BACKEND_AUTODETECT;
	}
	
	pref->download_dir = g_key_file_get_string(key, "core", "download_dir", &err);
	if (err) {
		g_error_free(err);
		err = NULL;
		pref->download_dir = g_strdup(g_get_home_dir());
	}

	pref->max_concurrent_downloads = g_key_file_get_integer(key, "core", "max_concurrent_downloads", &err);
	if (err) {
		g_error_free(err);
		err = NULL;
		pref->max_concurrent_downloads = 1;
	}

	pref->use_schedule = g_key_file_get_boolean(key, "core", "use_schedule", &err);
	if (err) {
		g_error_free(err);
		err = NULL;
		pref->use_schedule = FALSE;
	}

	pref->start_time_hour = g_key_file_get_integer(key, "core", "start_time_hour", &err);
	if (err) {
		g_error_free(err);
		err = NULL;
		pref->start_time_hour = 0;
	}
	
	pref->start_time_minute = g_key_file_get_integer(key, "core", "start_time_minute", &err);
	if (err) {
		g_error_free(err);
		err = NULL;
		pref->start_time_minute = 0;
	}
	
	pref->end_time_hour = g_key_file_get_integer(key, "core", "end_time_hour", &err);
	if (err) {
		g_error_free(err);
		err = NULL;
		pref->end_time_hour = 23;
	}
	
	pref->end_time_minute = g_key_file_get_integer(key, "core", "end_time_minute", &err);
	if (err) {
		g_error_free(err);
		err = NULL;
		pref->end_time_minute = 59;
	}
	g_key_file_free(key);
	g_free(path);
}

void save_settings(Preferences *pref)
{
	gchar *path;
	gchar *dir;
	GKeyFile* key;
	GError *err = NULL;
	gchar *data;
	gsize data_len = 0;
	GtkWidget *dialog;

	path = get_config_path();
	dir = g_dirname(path);
	
	key = g_key_file_new();
	g_key_file_load_from_file(key, path, G_KEY_FILE_KEEP_COMMENTS|G_KEY_FILE_KEEP_TRANSLATIONS, NULL);
	
	g_key_file_set_integer(key, "core", "backend", pref->backend);
	g_key_file_set_string(key, "core", "download_dir", pref->download_dir);
	g_key_file_set_integer(key, "core", "max_concurrent_downloads", pref->max_concurrent_downloads);
	g_key_file_set_boolean(key, "core", "use_schedule", pref->use_schedule);
	g_key_file_set_integer(key, "core", "start_time_hour", pref->start_time_hour);
	g_key_file_set_integer(key, "core", "start_time_minute", pref->start_time_minute);
	g_key_file_set_integer(key, "core", "end_time_hour", pref->end_time_hour);
	g_key_file_set_integer(key, "core", "end_time_minute", pref->end_time_minute);
	
	data = g_key_file_to_data(key, &data_len, &err);
	if (err) {
		dialog = gtk_message_dialog_new (GTK_WINDOW(g_GAria2),
                                  GTK_DIALOG_DESTROY_WITH_PARENT,
                                  GTK_MESSAGE_ERROR,
                                  GTK_BUTTONS_CLOSE,
                                  "Error: %s", err->message);
 		gtk_dialog_run (GTK_DIALOG (dialog));
 		gtk_widget_destroy (dialog);
		g_error_free(err);
	}
	
	if (!g_file_test(dir, G_FILE_TEST_EXISTS)) {
		g_mkdir_with_parents(dir, 0700);
	}
	g_file_set_contents(path, data, data_len, NULL);
	
	g_free(data);
	g_free(path);
	g_free(dir);
	g_key_file_free(key);
}
