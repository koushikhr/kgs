#include "./service.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to read a single line from a file
int read_line(char *filename, char *buffer, size_t max_len) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        fprintf(stderr, "Failed to open %s\n", filename);
        return 0;
    }
    if (fgets(buffer, max_len, fp) == NULL) {
        fclose(fp);
        return 0;
    }
    fclose(fp);
    // Remove newline character if it exists
    buffer[strcspn(buffer, "\n")] = 0;
    return 1;
}

// Function to get battery information
struct BatteryInfo get_battery_info() {
    struct BatteryInfo info;
    char path[256]; // Adjust max length as needed

    // Read battery percentage
    if (!read_line("/sys/class/power_supply/BAT0/capacity", path, sizeof(path))) {
        fprintf(stderr, "Failed to read battery percentage\n");
        info.percentage = -1;  // Default value if reading fails
    } else {
        sscanf(path, "%d", &info.percentage);
    }

    // Read battery status
    if (!read_line("/sys/class/power_supply/BAT0/status", info.status, sizeof(info.status))) {
        fprintf(stderr, "Failed to read battery status\n");
        strcpy(info.status, "Unknown");  // Default value if reading fails
    }

    return info;
}
