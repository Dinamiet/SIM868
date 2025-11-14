#ifndef _SIM868_HTTP_H_
#define _SIM868_HTTP_H_

#include "atterminal.h"

#include <stdint.h>

typedef enum _SIM868HTTPResponse_
{
	SIM868_HTTP_RESPONSE_ACTION_STATUS = 0x6244591F, // HTTPACTION
	SIM868_HTTP_RESPONSE_RESPONSE_DATA = 0xA8048965, // HTTPREAD
} SIM868HTTPResponse;

typedef enum _SIM868HTTPAction_
{
	SIM868_HTTP_ACTION_GET,
	SIM868_HTTP_ACTION_POST,
	SIM868_HTTP_ACTION_HEAD,
	SIM868_HTTP_ACTION_DELETE
} SIM868HTTPAction;

typedef struct _SIM868HTTPActionInfo_
{
	SIM868HTTPAction Action;
	uint16_t Status;
	size_t ResponseLength;
} SIM868HTTPActionInfo;

void SIM868_HTTP_StartSession(ATTerminal* at, uint8_t identifier);
void SIM868_HTTP_Post(ATTerminal* at, char* url, void* data, size_t size);
void SIM868_HTTP_ReadResponseData(ATTerminal* at);
void SIM868_HTTP_TerminateSession(ATTerminal* at);

SIM868HTTPActionInfo SIM868_HTTP_ParseActionInfo(char* info);

#endif
