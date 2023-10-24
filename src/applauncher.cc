/**
 * Copyright (C) Ramenu
 * 
 * This file is part of applauncher.
 * 
 * applauncher is free software: you can redistribute it and/or modify it under the terms of the 
 * GNU General Public License as published by the Free Software Foundation, either version 
 * 3 of the License, or (at your option) any later version.
 * 
 * applauncher is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; 
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along with applauncher. If 
 * not, see <https://www.gnu.org/licenses/>.
 */

#include <cstdio>
#include <gtk/gtk.h>
#include "application.h"
#include <string>
/*
static std::string bolden_text(const gchar *s) noexcept
{
    return std::string{"<b>"} + s + "</b>";
}*/

static void on_button_press(GtkWidget*, gpointer data) noexcept
{
    char *cmd = reinterpret_cast<char*>(data);
    printf("%s\n", cmd);
    system(cmd);
}

static void on_activate(GtkApplication *gtk_app) noexcept
{
    static constexpr gint WINDOW_DEFAULT_WIDTH = 250, WINDOW_DEFAULT_HEIGHT = 400;
    static constexpr guint GRID_ROW_SPACING = 10, GRID_COLUMN_SPACING = 5;

    // Create a new window
    GtkWidget *window = gtk_application_window_new(gtk_app);
    // Create a new button
    gtk_window_set_title(GTK_WINDOW(window), "App Launcher");
    gtk_window_set_default_size(GTK_WINDOW(window), WINDOW_DEFAULT_WIDTH, WINDOW_DEFAULT_HEIGHT);
    gtk_window_present(GTK_WINDOW(window));

    const auto global_apps {get_global_applications()};

    GtkWidget *scrolled_window = gtk_scrolled_window_new(nullptr, nullptr);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_window), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);

    GtkWidget *list_box = gtk_list_box_new();
    gtk_container_add(GTK_CONTAINER(scrolled_window), list_box);

    for (const auto &app : global_apps) {
        GtkWidget *list_item = gtk_button_new();
        GtkWidget *grid = gtk_grid_new();
        gtk_grid_set_row_spacing(GTK_GRID(grid), GRID_ROW_SPACING);
        gtk_grid_set_column_spacing(GTK_GRID(grid), GRID_COLUMN_SPACING);

        gtk_container_add(GTK_CONTAINER(list_item), grid);
        GtkWidget *label = gtk_label_new(app.name());
        GtkWidget *icon = gtk_image_new_from_icon_name(app.icon(), GTK_ICON_SIZE_MENU);

        gtk_button_set_relief(GTK_BUTTON(list_item), GTK_RELIEF_NONE);

        gtk_grid_attach(GTK_GRID(grid), icon, 0, 0, 1, 1);
        gtk_grid_attach_next_to(GTK_GRID(grid), label, icon, GTK_POS_RIGHT, 1, 1);

        g_signal_connect(G_OBJECT(list_item), "clicked", G_CALLBACK(on_button_press), reinterpret_cast<gpointer>(app.exec()));
        gtk_container_add(GTK_CONTAINER(list_box), list_item);
    }

    GtkWidget *main_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_box_pack_start(GTK_BOX(main_box), scrolled_window, TRUE, TRUE, 0);

    gtk_container_add(GTK_CONTAINER(window), main_box);

    gtk_widget_show_all(window);
    
}

int main(int argc, char **argv) noexcept
{
    GtkApplication *app = gtk_application_new("com.example.GtkApplication", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK(on_activate), nullptr);
    return g_application_run(G_APPLICATION(app), argc, argv);
}
