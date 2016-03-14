#include "http_util.h"

#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <time.h>
#include <errno.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "cJSON.h"
#include "config.h"


#define HTTP_PARAM_STR_ASSERT(PARAM, ERRCODE)  \
	if(PARAM==NULL)    return ERRCODE;



int http_static_content_str(char *buf, char *user, char *passwd)
{
	char http_body_str[256];
	char tmp_buf[256];

	HTTP_PARAM_STR_ASSERT(buf, -1);
	HTTP_PARAM_STR_ASSERT(user, -1);
	HTTP_PARAM_STR_ASSERT(passwd, -1);

	//HTTP BODY
	memset(http_body_str, 0x00, sizeof(http_body_str));
	sprintf(http_body_str, "username=%s&password=%s", user, passwd);

	memset(tmp_buf, 0x00, sizeof(tmp_buf));

	//HTTP STATIC HEAD
	strcat(buf, "POST /opensips/Home/Api/login.html HTTP/1.1\r\n");
	sprintf(tmp_buf, "Host: %s\r\n", GLOBAL_WEBSERVICE_HOST);
	strcat(buf, tmp_buf);
	strcat(buf, "Content-Type: application/x-www-form-urlencoded; charset=UTF-8\r\n");

	memset(tmp_buf, 0x00, sizeof(tmp_buf));
	sprintf(tmp_buf, "Content-Length: %d\r\n", strlen(http_body_str));
	strcat(buf, tmp_buf);

	strcat(buf, "\r\n");

	//ADD CONTENT LENGTH
	strcat(buf, http_body_str);

	return 0;
}



int http_request_post(char *http_str, char *http_responst_str)
{
	int ret,num;
	int socketfd;
	struct sockaddr_in servaddr;
	fd_set t_set;
	struct timeval tv;

	HTTP_PARAM_STR_ASSERT(http_str, -1);
	HTTP_PARAM_STR_ASSERT(http_responst_str, -1);

	socketfd = socket(AF_INET, SOCK_STREAM, 0);
	if(socketfd < 0)
		return -2;

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(GLOBAL_WEBSERVICE_PORT);
	ret = inet_pton(AF_INET, GLOBAL_WEBSERVICE_HOST, &servaddr.sin_addr);
	if(ret <= 0)
	{
		close(socketfd);
		return -3;
	}

	ret = connect(socketfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
	if(ret < 0)
	{
		close(socketfd);
		return -4;
	}

	ret = write(socketfd, http_str, strlen(http_str));
	if(ret <= 0)
	{
		close(socketfd);
		return -5;
	}

	FD_ZERO(&t_set);
	FD_SET(socketfd, &t_set);

	while(1)
	{
		tv.tv_sec = 0;
		tv.tv_usec = 0;

		sleep(2);

		ret = select(socketfd+1, &t_set, NULL, NULL, &tv);
printf("select =%d\n", ret);
		if(ret == 0)
			continue;
		else if(ret < 0)
		{
			close(socketfd);
			return -6;
		}
		else
		{
			num = read(socketfd, http_responst_str, 2048);
			close(socketfd);

			if(num <= 0)
				return -10;
			else
				return num;
		}
	}

	close(socketfd);
	return 0;
}



/*--------------------------------- PARSE JASON STRING -------------------------------------*/
static char * str_get_line(char *buf)
{
	HTTP_PARAM_STR_ASSERT(buf, NULL);

	while(((*buf)!= '\n') && ((*buf)!= '\0'))
		buf++;

	if((*buf) == '\n')
	{
		*buf = '\0';
		return buf+1;
	}
	else
	{
		(*buf) = '\0';
		return NULL;
	}

	return NULL;
}

static char* find_str_jason(char *buf)
{
	int content_len;
	char *postion = NULL;
	char *tmp_point = NULL;

	HTTP_PARAM_STR_ASSERT(buf, NULL);

	//Get Content Length
	postion = strstr(buf, "Content-Length");
	if(postion == NULL)
		return NULL;
	tmp_point = postion + 15;
	postion = str_get_line(tmp_point);
	content_len = atoi(tmp_point);
printf("Check postion = %s\n   %d\n", tmp_point, content_len);
printf("-------------------------------------------------------\n");
printf("last string = %s\n", postion);
	//Find Jason
	postion = strstr(postion, "{\"status\"");
	if(postion == NULL)
		return NULL;

printf("Find status postion: %s\n", postion);
	//Check the last character '}'
	if(*(postion+content_len-1) == '}')
	{
		*(postion+content_len) = '\0';
		return postion;
	}

	return NULL;
}


/*-----------------------------------------------------------------------------------------*/
static int http_user_authentication(char *jason)
{
	cJSON * root; 
	char * status_str;

	HTTP_PARAM_STR_ASSERT(jason, -1);

	root = cJSON_Parse(jason);	
	status_str = cJSON_GetObjectItem(root,"status")->valuestring;

	if(status_str == NULL)
	{
		cJSON_Delete(root);
		return -2;
	}

	if(strcmp(status_str, "OK") == 0)
	{
		cJSON_Delete(root);
		return 1;
	}

	if(strcmp(status_str, "NG") == 0)
	{
		cJSON_Delete(root);
		return 0;
	}

	cJSON_Delete(root);
	return -3;
}


static int siproxy_config_generate_jason(char *jason)
{
	cJSON * root; 
	cJSON * jason_data; 
	char config_file_str[2048];

	FILE *fp = NULL;
	int file_size = 0;

	HTTP_PARAM_STR_ASSERT(jason, -1);

	root = cJSON_Parse(jason);
	jason_data = cJSON_GetObjectItem(root,"data");

	if(jason_data == NULL)
	{
		cJSON_Delete(root);
		return -2;
	}
	
	//MQTT SRV
	memset(mosquitto_srv, 0x00, sizeof(mosquitto_srv));
	strcpy(mosquitto_srv, cJSON_GetObjectItem(jason_data,"mosquitto_server")->valuestring);	
	//TOPIC
	memset(mosquitto_client_topic, 0x00, sizeof(mosquitto_client_topic));
	memset(mosquitto_peer_topic,   0x00, sizeof(mosquitto_peer_topic));
	//use the contrast topic
	strcpy(mosquitto_client_topic, cJSON_GetObjectItem(jason_data,"mosquitto_peer_topic")->valuestring);
	strcpy(mosquitto_peer_topic,   cJSON_GetObjectItem(jason_data,"mosquitto_client_topic")->valuestring);

	//SIP PEER ACCOUNT 
	memset(sip_peer_account_str, 0x00, sizeof(sip_peer_account_str));
	sprintf(sip_peer_account_str, "%s@%s", cJSON_GetObjectItem(jason_data,"sip_account_client")->valuestring, cJSON_GetObjectItem(jason_data,"sip_server")->valuestring);

	//PJSIP CONFIG FILE
	memset(config_file_str, 0x00, sizeof(config_file_str));
	sprintf(config_file_str, sip_config_file_str,
		//--id sip:DEVICE_ACCOUNT@SIP_SERVER:SIP_SRV_PORT
		cJSON_GetObjectItem(jason_data,"sip_account_device")->valuestring, cJSON_GetObjectItem(jason_data,"sip_server")->valuestring,
		//--registrar sip:SIP_SERVER:SIP_SRV_PORT
		cJSON_GetObjectItem(jason_data,"sip_server")->valuestring,
		//device sip user
		cJSON_GetObjectItem(jason_data,"sip_account_device")->valuestring,
		//device sip passwd
		cJSON_GetObjectItem(jason_data,"sip_password_device")->valuestring,
		//--proxy "<sip:%s:%s;lr;transport=tcp>"
		cJSON_GetObjectItem(jason_data,"sip_server")->valuestring,
		//--turn-srv %s
		cJSON_GetObjectItem(jason_data,"trun_server")->valuestring,
		//--turn-user %s
		cJSON_GetObjectItem(jason_data,"trun_username")->valuestring,
		//--turn-passwd %s
		cJSON_GetObjectItem(jason_data,"trun_password")->valuestring,
		//--cli-telnet-port=%s
		DEVICE_PROCESS_BIND_PORT
		);

	//create the config file
	printf("CLD pjsip_config_generate_jason=%s\n", config_file_str);
	fp = fopen(SIPROXY_CONFIG_FILE, "wb");
	if(fp == NULL)
	{
		cJSON_Delete(root);
		return -3;		
	}

	file_size = fputs(config_file_str, fp);
	if(file_size != strlen(config_file_str))
	{
		cJSON_Delete(root);
		fclose(fp);
		return -4;				
	}

	fclose(fp);
	cJSON_Delete(root);
	return 0;
}




/*-----------------------------------------------------------------------------------------*/


int http_param_confirm_proc(char *user, char *passwd)
{
	char *str1;
	char *str2;
	int ret;

	cJSON * root;  
	cJSON * format;  
	int value_int;	
	char * value_string;  
	char * username;
	  
	char *jason_str;

	str1 = (char *)malloc(1024*sizeof(char));
	str2 = (char *)malloc(1536*sizeof(char));

	memset(str1, 0x00, 1024);
	memset(str2, 0x00, 1536);
	
	//HTTP REQUEST CONTENT
	http_static_content_str(str1, user, passwd);

	ret = http_request_post(str1, str2);
	if(ret <= 0)
	{
		free(str1);
		free(str2);
		printf("CLD http_request_post = %d\n", ret);
		return -101;
	}

	//find jason body string
	jason_str = find_str_jason(str2);
	if(jason_str == NULL)
	{
		free(str1);
		free(str2);
		return -102;
	}

	//CREATE CONFIG FILE & GLOBAL PARAM
	ret = siproxy_config_generate_jason(jason_str);
	if(ret != 0)
	{
		free(str1);
		free(str2);
		return -103;
	}

	free(str1);
	free(str2);

	return 0;
}
