#ifndef CONFIG_H
#define CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <string.h>

//------------------------- Global define ----------------------------

//sip
extern char sip_peer_account_str[64];

//MOSQUITTO
extern char mosquitto_srv[64];

//TOPIC
extern char mosquitto_client_topic[64];
extern char mosquitto_peer_topic[64];

//Webservice
#define GLOBAL_WEBSERVICE_HOST   "139.129.94.140"
#define GLOBAL_WEBSERVICE_PORT	 80


//device baseband
#define DEVICE_PROCESS_BIND_ADDR  "127.0.0.1"
#define DEVICE_PROCESS_BIND_PORT  "1213"
#define DEVICE_UART_TO_MODEM	  "/dev/ttyS1"



//config file defination
extern char *sip_config_file_str;
#define SIPROXY_CONFIG_FILE "/siproxy_etc/pjsip_config.dat"


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif


