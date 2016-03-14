#ifndef HTTP_H
#define HTTP_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <string.h>

int http_static_content_str(char *buf, char *user, char *passwd);

int http_request_post(char *http_str, char *http_responst_str);


int http_param_confirm_proc(char *user, char *passwd);



#ifdef __cplusplus
} /* extern "C" */
#endif

#endif


