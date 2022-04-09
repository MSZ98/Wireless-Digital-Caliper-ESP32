#ifndef DEFS_H
#define DEFS_H

#define io_led 2
#define io_clk 23
#define io_dat 22
#define io_wakeup GPIO_NUM_4
#define io_button 13

#define channel_led 0

#define deep_sleep_timeout_normal 3000
#define deep_sleep_timeout_connecting 10000

#define ssid_command 		"ssid "
#define pass_command 		"pass "
#define ip_command 			"ip "
#define port_command 		"port "
#define handshake_command 	"areyouok??"
#define stats_command 		"stats??"
#define ack_command 		"ok.."

typedef struct {
	char ssid[100];
	char pass[100];
	char ip[20];
	int port;
} eeprom_t;

#endif
