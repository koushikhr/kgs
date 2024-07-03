
#include "gtk4-layer-shell.h"
#include <gtk/gtk.h>
#include "./bar.h"

GtkWidget
*set_up_bar (GtkWindow *window)
{

    GtkWidget *box, *appLaunchBtn, *colorPickerIconBtn, *batteryLevelBar;

    box = gtk_box_new (0, 0);

    appLaunchBtn = gtk_button_new_with_label ("Applications");
    gtk_widget_set_name(appLaunchBtn, "appLaunchBtn");
    gtk_widget_add_css_class (appLaunchBtn, "app-launch-btn");
    gtk_box_append (GTK_BOX (box), appLaunchBtn);

    colorPickerIconBtn = gtk_button_new_from_icon_name ("color-select");
    gtk_widget_add_css_class (colorPickerIconBtn, "color-picker-icon-btn");
    gtk_box_append (GTK_BOX (box), colorPickerIconBtn);

    set_up_battery (window, box);


    return (box);
}

