/*
 *      tree.c
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

#include <gtk/gtk.h>

typedef struct
{
	const gchar *url;
	const guint downloaded;
	const guint total;
	const guint ratio;
	const gchar *protocol;
}
Download;

enum
{
  COLUMN_URL,
  COLUMN_DOWNLOADED,
  COLUMN_TOTAL,
  COLUMN_RATIO,
  COLUMN_PROTOCOL,
  NUM_COLUMNS
};

static Download data[] =
{
	{"a.txt", 1, 2, 1, "torrent"},
	{"b.txt", 2, 3, 4, "http"},
};

static GtkTreeModel *
create_model (void)
{
	gint i = 0;
	GtkListStore *store;
	GtkTreeIter iter;

	/* create list store */
	store = gtk_list_store_new (NUM_COLUMNS,
				G_TYPE_STRING,
				G_TYPE_UINT,
				G_TYPE_UINT,
				G_TYPE_UINT,
				G_TYPE_STRING);

	/* add data to the list store */
	for (i = 0; i < G_N_ELEMENTS (data); i++) {
		gtk_list_store_append (store, &iter);
		gtk_list_store_set (store, &iter,
			COLUMN_URL, data[i].url,
			COLUMN_DOWNLOADED, data[i].downloaded,
			COLUMN_TOTAL, data[i].total,
			COLUMN_RATIO, data[i].ratio,
			COLUMN_PROTOCOL, data[i].protocol,
			-1);
    }
	return GTK_TREE_MODEL (store);
}

static void
add_columns (GtkTreeView *treeview)
{
	GtkCellRenderer *renderer;
	GtkTreeViewColumn *column;
	GtkTreeModel *model = gtk_tree_view_get_model (treeview);

	renderer = gtk_cell_renderer_text_new ();
	column = gtk_tree_view_column_new_with_attributes ("Url",
						     renderer,
						     "text",
						     COLUMN_URL,
						     NULL);
	gtk_tree_view_column_set_sort_column_id (column, COLUMN_URL);
	gtk_tree_view_append_column (treeview, column);

	renderer = gtk_cell_renderer_text_new ();
	column = gtk_tree_view_column_new_with_attributes ("Downloaded",
						     renderer,
						     "text",
						     COLUMN_DOWNLOADED,
						     NULL);
	gtk_tree_view_column_set_sort_column_id (column, COLUMN_DOWNLOADED);
	gtk_tree_view_append_column (treeview, column);

	renderer = gtk_cell_renderer_text_new ();
	column = gtk_tree_view_column_new_with_attributes ("Total",
						     renderer,
						     "text",
						     COLUMN_TOTAL,
						     NULL);
	gtk_tree_view_column_set_sort_column_id (column, COLUMN_TOTAL);
	gtk_tree_view_append_column (treeview, column);

	renderer = gtk_cell_renderer_text_new ();
	column = gtk_tree_view_column_new_with_attributes ("Ratio",
						     renderer,
						     "text",
						     COLUMN_RATIO,
						     NULL);
	gtk_tree_view_column_set_sort_column_id (column, COLUMN_RATIO);
	gtk_tree_view_append_column (treeview, column);

	renderer = gtk_cell_renderer_text_new ();
	column = gtk_tree_view_column_new_with_attributes ("Protocol",
						     renderer,
						     "text",
						     COLUMN_PROTOCOL,
						     NULL);
	gtk_tree_view_column_set_sort_column_id (column, COLUMN_PROTOCOL);
	gtk_tree_view_append_column (treeview, column);
}

void init_tree(GtkTreeView *treeview)
{
	/* create tree model */
	GtkTreeModel *model = create_model();

	/* create tree view */
	gtk_tree_view_set_model(treeview, model);

	gtk_tree_view_set_rules_hint (GTK_TREE_VIEW (treeview), TRUE);
	gtk_tree_view_set_search_column (GTK_TREE_VIEW (treeview),
		COLUMN_URL);
//	g_object_unref (model);

	/* add columns to the tree view */
	add_columns (GTK_TREE_VIEW (treeview));
}
