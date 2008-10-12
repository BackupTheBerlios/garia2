/*
 *      preference.h
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
 *      
 */

#ifndef __GARIA2_PREFERENCE_H__
#define __GARIA2_PREFERENCE_H__

#include <gtk/gtk.h>

enum {
	BACKEND_AUTODETECT,
	BACKEND_ARIA2,
	BACKEND_WGET
};

typedef struct _Preferences
{
	gint backend;
	gchar *download_dir;
	gint  max_concurrent_downloads;
	gboolean use_schedule;
	gint start_time_hour;
	gint start_time_minute;
	gint end_time_hour;
	gint end_time_minute;	
} Preferences;

void gui_to_preference(GtkWidget *dlg, Preferences *pref);
void preference_to_gui(GtkWidget *dlg, Preferences *pref);

void load_settings(Preferences *pref);
void save_settings(Preferences *pref);

#endif
