#include "caliper.h"

SerialLineReader reader(Serial, serial_received);
eeprom_t eeprom;
WiFiClient client;
int bt = 0;

void setup() {
	init_gpio();
	init_interrupts();
	EEPROM.begin(sizeof(eeprom_t));
	EEPROM.get(0, eeprom);
	Serial.begin(115200);
	ledcWrite(channel_led, 100);
}

void serial_received(char *data) {
	
	if(strstr(data, handshake_command) != NULL) Serial.println("ok..");
	else if(strstr(data, stats_command) != NULL) {
		Serial.printf("ssid %s\npass %s\nip %s\nport %d\n", eeprom.ssid, eeprom.pass, eeprom.ip, eeprom.port);
	}
	else if(strstr(data, ssid_command) != NULL) {
		strcpy(eeprom.ssid, data + strlen(ssid_command));
		EEPROM.put(0, eeprom);
		EEPROM.commit();
		Serial.printf("ok.. new ssid: %s\n", eeprom.ssid);
		WiFi.disconnect();
	}
	else if(strstr(data, pass_command) != NULL) {
		strcpy(eeprom.pass, data + strlen(pass_command));
		EEPROM.put(0, eeprom);
		EEPROM.commit();
		Serial.printf("ok.. new pass: %s\n", eeprom.pass);
		WiFi.disconnect();
	}
	else if(strstr(data, ip_command) != NULL) {
		strcpy(eeprom.ip, data + strlen(ip_command));
		EEPROM.put(0, eeprom);
		EEPROM.commit();
		Serial.printf("ok.. new ip: %s\n", eeprom.ip);
		client.stop();
	}
	else if(strstr(data, port_command) != NULL) {
		sscanf(data + strlen(port_command), "%d", &eeprom.port);
		EEPROM.put(0, eeprom);
		EEPROM.commit();
		Serial.printf("ok.. new port: %d\n", eeprom.port);
		client.stop();
	}
	
}

int prev_led_state = 0;

void loop() {
	
	reader.poll();

	if(WiFi.status() != WL_CONNECTED) {
		WiFi.begin(eeprom.ssid, eeprom.pass);
		while(WiFi.status() != WL_CONNECTED) {
			reader.poll();
			if(prev_led_state == 0) ledcWrite(channel_led, 100 + (int) (100 + 65535 * 0.2));
			else ledcWrite(channel_led, 100);
			prev_led_state = !prev_led_state;
			deep_sleep_measure_inactive_time(false);
			delay(200);
		}
	}

	while(!client.connected()) {
		reader.poll();
		int result = client.connect(eeprom.ip, eeprom.port, 100);
		if(result) Serial.println("Connected to server");
		if(prev_led_state == 0) ledcWrite(channel_led, 100 + (int) (100 + 65535 * 0.2));
		else ledcWrite(channel_led, 100);
		prev_led_state = !prev_led_state;
		deep_sleep_measure_inactive_time(false);
	}
	
	if(ready) {
		ledcWrite(channel_led, (int) (100 + abs(length) / 15500.0 * 65535 * 0.3));
//		Serial.println(length);
		deep_sleep_ready_detected();
		ready = 0;
	}

	deep_sleep_measure_inactive_time(true);

	if(digitalRead(io_button) == 0) {
		if(bt == 1000) if(client.connected()) client.printf("%.2f\n", length / 100.0);
		bt = 0;
	}
	if(bt < 1000) bt++;
	
}
