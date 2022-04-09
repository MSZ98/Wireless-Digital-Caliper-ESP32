#include "caliper.h"


int length = 0;
int ready = 0;


void init_gpio() {
	pinMode(io_clk, INPUT_PULLUP);
	pinMode(io_dat, INPUT_PULLUP);
	pinMode(io_button, INPUT_PULLUP);
	pinMode(io_wakeup, INPUT_PULLUP);
    ledcSetup(channel_led, 100, 16);
    ledcAttachPin(io_led, channel_led);
    esp_sleep_enable_ext0_wakeup(io_wakeup, HIGH);
}


void init_interrupts() {
    attachInterrupt(io_clk, detected_rising_slope_clk, RISING);
}
