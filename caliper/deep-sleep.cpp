#include "caliper.h"


unsigned long previous_ready_time_ms;


void deep_sleep_ready_detected() {
    previous_ready_time_ms = millis();
}

void deep_sleep_measure_inactive_time(boolean normal) {
	if(millis() - previous_ready_time_ms > (normal ? deep_sleep_timeout_normal : deep_sleep_timeout_connecting)) {
    	Serial.println("Deep Sleep Enabled");
    	esp_deep_sleep_start();
    }
}
