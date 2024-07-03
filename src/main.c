#include "gtk4-layer-shell.h"
#include <gtk/gtk.h>
#include "./widgets/bar/bar.h"

static void
activate (GtkApplication* app, void *_data)
{
    (void)_data;

    // Create a normal GTK window however you like
    GtkWindow *gtk_window = GTK_WINDOW (gtk_application_window_new (app));

    GtkCssProvider *cssProvider = gtk_css_provider_new();
    gtk_css_provider_load_from_path(cssProvider, "theme.css");
    gtk_style_context_add_provider_for_display(gdk_display_get_default(),
                                               GTK_STYLE_PROVIDER(cssProvider),
                                               GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

    // Before the window is first realized, set it up to be a layer surface
    gtk_layer_init_for_window (gtk_window);

    // Order below normal windows
    gtk_layer_set_layer (gtk_window, GTK_LAYER_SHELL_LAYER_TOP);

    // Push other windows out of the way
    gtk_layer_auto_exclusive_zone_enable (gtk_window);

    // We don't need to get keyboard input
    // gtk_layer_set_keyboard_mode (gtk_window, GTK_LAYER_SHELL_KEYBOARD_MODE_NONE); // NONE is default
    

    
    // The margins are the gaps around the window's edges
    // Margins and anchors can be set like this...
    gtk_layer_set_margin (gtk_window, GTK_LAYER_SHELL_EDGE_LEFT, 0);
    gtk_layer_set_margin (gtk_window, GTK_LAYER_SHELL_EDGE_RIGHT, 0);
    gtk_layer_set_margin (gtk_window, GTK_LAYER_SHELL_EDGE_TOP, 0);
    gtk_layer_set_margin (gtk_window, GTK_LAYER_SHELL_EDGE_BOTTOM, 0); // 0 is default
    
    // ... or like this
    // Anchors are if the window is pinned to each edge of the output
    static const gboolean anchors[] = {TRUE, TRUE, FALSE, TRUE};                                       // [ LEFT, RIGHT, TOP, BOTTOM ]
    for (int i = 0; i < GTK_LAYER_SHELL_EDGE_ENTRY_NUMBER; i++) {
        gtk_layer_set_anchor (gtk_window, i, anchors[i]);
    }

    GtkWidget *bar = set_up_bar (gtk_window);
    
    gtk_window_set_child (GTK_WINDOW (gtk_window), bar);

    gtk_window_present (gtk_window);
}

int
main (int argc, char **argv)
{
    GtkApplication * app = gtk_application_new ("com.github.wmww.gtk4-layer-shell.example", 0);
    g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
    int status = g_application_run (G_APPLICATION (app), argc, argv);
    g_object_unref (app);


    g_info("main.c: application exited with status: %d", status);
    return status;
}
