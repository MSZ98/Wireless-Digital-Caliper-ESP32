#include "caliper.h"

void eeprom_read(eeprom_t *eeprom) {
	void *eeprom_p = eeprom;
	for(int i = 0;i < sizeof(eeprom_t);i++) {
		uint8_t x = EEPROM.read(i);
		Serial.printf("%p / %p\n", eeprom, eeprom_p + i);
		memcpy(eeprom_p + i, &x, 1);
	}
}

void eeprom_write(eeprom_t *eeprom) {
	void *eeprom_p = eeprom;
	for(int i = 0;i < sizeof(eeprom_t);i++) {
		uint8_t x = 0;
		memcpy(&x, eeprom_p + i, 1);
		EEPROM.write(x, i);
	}
}
