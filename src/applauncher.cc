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

static void on_activate(GtkApplication *app) 
{
    // Create a new window
    GtkWidget *window = gtk_application_window_new (app);
    // Create a new button
    GtkWidget *button = gtk_button_new_with_label ("Hello, World!");
    // When the button is clicked, close the window passed as an argument
    g_signal_connect_swapped (button, "clicked", G_CALLBACK (gtk_window_close), window);
    gtk_window_set_title(GTK_WINDOW (window), "App Launcher");
    gtk_window_present (GTK_WINDOW (window));

    const application_info brave {"/usr/share/applications/brave-browser.desktop"};
    printf("Application name: %s\n", brave.name());
    printf("Application exec: %s\n", brave.exec());
    printf("Application icon: %s\n", brave.icon());
    printf("Application type: %s\n", brave.type());
    
}

int main(int argc, char **argv)
{
    GtkApplication *app = gtk_application_new("com.example.GtkApplication", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK(on_activate), nullptr);
    return g_application_run(G_APPLICATION(app), argc, argv);
}
