#include <gtk/gtk.h>
#include "./bar.h"
#include "./services/service.h"

void
set_up_battery (GtkWindow *window, GtkWidget *box)
{
    GtkWidget *batteryBox, *bar, *batteryLabel, *batteryLabelOverlay;

    batteryBox = gtk_box_new (0, 0);

    // Get battery information
    struct BatteryInfo batteryInfo = get_battery_info();

    double batteryPercentage = round (batteryInfo.percentage * 10) /100;
    // Output battery percentage and status
    printf("Battery Percentage: %f\n", batteryPercentage);
    printf("Battery Status: %s\n", batteryInfo.status);
    
    
    bar = gtk_level_bar_new ();
    gtk_level_bar_set_min_value (GTK_LEVEL_BAR (bar), 0.0);
    gtk_level_bar_set_max_value (GTK_LEVEL_BAR (bar), 7.0);

    gtk_level_bar_add_offset_value (GTK_LEVEL_BAR (bar), GTK_LEVEL_BAR_OFFSET_LOW, 1.0);
    gtk_level_bar_add_offset_value (GTK_LEVEL_BAR (bar), GTK_LEVEL_BAR_OFFSET_HIGH, 6.0);

    // gtk_level_bar_add_offset_value (GTK_LEVEL_BAR (bar), "full", 10.0);
    // gtk_level_bar_add_offset_value (GTK_LEVEL_BAR (bar), "my-offset", 5.0);

    char batteryPercentageStr[20];
    sprintf(batteryPercentageStr, "%d%%", batteryInfo.percentage);
    
    batteryLabel = gtk_label_new (batteryPercentageStr);
    batteryLabelOverlay = gtk_overlay_new ();
    gtk_overlay_add_overlay (GTK_OVERLAY (batteryLabelOverlay), bar);
    gtk_overlay_add_overlay (GTK_OVERLAY (batteryLabelOverlay), batteryLabel);
    
    g_object_set (batteryLabel, "halign", GTK_ALIGN_START, NULL);
    g_object_set (batteryLabel, "valign", GTK_ALIGN_START, NULL);
    gtk_widget_add_css_class (batteryLabel, "battery-label-style");

    gtk_box_append (GTK_BOX (batteryBox), batteryLabelOverlay);
    gtk_box_append (GTK_BOX (batteryBox), bar);

    gtk_box_append (GTK_BOX (box), batteryBox);
    gtk_level_bar_set_mode (GTK_LEVEL_BAR (bar), GTK_LEVEL_BAR_MODE_DISCRETE);

    gtk_level_bar_set_value (GTK_LEVEL_BAR (bar), batteryPercentage);
}

