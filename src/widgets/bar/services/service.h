#ifndef BATTERY_H
#define BATTERY_H

// Struct to hold battery information
struct BatteryInfo {
    int percentage;
    char status[256]; // Adjust max length as needed
};

// Function prototype
struct BatteryInfo get_battery_info();

#endif
