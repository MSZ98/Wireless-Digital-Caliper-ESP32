#ifndef CALIPER_H
#define CALIPER_H

#include <Arduino.h>
#include <EEPROM.h>
#include <inttypes.h>
#include <string.h>
#include <serial-readline.h>
#include <WiFi.h>
#include "defines.h"

void detected_rising_slope_clk();
void deep_sleep_measure_inactive_time(boolean);
void init_gpio();
void init_interrupts();
void deep_sleep_ready_detected();
void serial_received(char*);
void eeprom_read(eeprom_t *);
void eeprom_write(eeprom_t *);
void wifi_connect();
void wifiClient_connect();

extern int length;
extern int ready;

#endif
