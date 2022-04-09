#include "caliper.h"


typedef struct {
    int value : 20;
} int20_t;


unsigned long previous_clk_rising_edge_time;
int negative = 0;
int20_t length_buffer = {0};
int bit = 0;


void detected_rising_slope_clk() {
    unsigned long now = micros();
    unsigned long dt_us = (now - previous_clk_rising_edge_time);
    previous_clk_rising_edge_time = now;
    if(dt_us > 100000) {
        length = length_buffer.value;
        if(negative) length *= -1;
        ready = 1;
        bit = 0;
        length_buffer.value = 0;
    }
    int state = !digitalRead(io_dat);
    if(bit == 0);
    else length_buffer.value |= state << (bit - 1);
    if(bit > 20) if(bit == 21) negative = state;
    bit++;
}