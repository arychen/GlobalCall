#include "config.h"



//------------------ GLOBAL PARAM -----------------------
//SIP
char device_sip_user[32];
char device_sip_passwd[32];
char client_sip_user[32];
char client_sip_passwd[32];
char sip_peer_account_str[64];


//TURN
char turn_srv[64];
char turn_user[32];
char turn_passwd[32];


//MOSQUITTO
char mosquitto_srv[64];
char turn_user[32];
char turn_passwd[32];

//TOPIC
char mosquitto_client_topic[64];
char mosquitto_peer_topic[64];



/*----------------------------------------------------
# Auto generate config file.
--id sip:DEVICE_ACCOUNT@SIP_SERVER:SIP_SRV_PORT

#
# SIP register server
#
--registrar sip:SIP_SERVER:SIP_SRV_PORT

--reg-timeout 300
--realm *
--username DEVICE_ACCOUNT
--password DEVICE_PASSWD

#
# Enable SIP Proxy
#
--proxy "<sip:SIP_SERVER:SIP_SRV_PORT;lr;transport=tcp>"

#
# ICE enable
#
--use-ice
--ice-regular

--use-turn
--turn-srv TURN_SRV_PORT
--turn-user TURN_USER
--turn-passwd TURN_PASSWD

#
# Log
#
--app-log-level 5
--log-level 5

#
# CLI and Telnet
#
--use-cli
--cli-telnet-port=CLI_TELNET_PORT
-------------------------------------------------------*/
char *sip_config_file_str=
"# Auto generate config file.\n"
"\n"
"#\n"
"# SIP register server\n"
"#\n"
"--id sip:%s@%s\n"
"--registrar sip:%s\n"
"\n"	
"--reg-timeout 300\n"
"--realm *\n"
"--username %s\n"
"--password %s\n"
"\n"
"#\n"
"# Enable SIP Proxy\n"
"#\n"
"--proxy \"<sip:%s;lr;transport=tcp>\"\n"
"\n"
"#\n"
"# ICE enable\n"
"#\n"
"--use-ice\n"
"--ice-regular\n"
"\n"
"--use-turn\n"
"--turn-srv %s\n"
"--turn-user %s\n"
"--turn-passwd %s\n"
"\n"	
"#\n"
"# Log\n"
"#\n"
"--app-log-level 5\n"
"--log-level 5\n"
"\n"	
"#\n"
"# CLI and Telnet\n"
"#\n"
"--use-cli\n"
"--cli-telnet-port=%s\n";

