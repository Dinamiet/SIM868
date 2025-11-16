#ifndef _SIM868_BEARER_H_
#define _SIM868_BEARER_H_

#include "atterminal.h"

#include <stdint.h>

typedef enum _SIM868BearerResponse_
{
	SIM868_BEARER_RESPONSE_STATUS = 0xCF17F5DB, // SAPBR
} SIM868BearerResponse;

typedef enum _SIM868BearerConnection_
{
	SIM868_BEARER_CONNECTION_CSD,
	SIM868_BEARER_CONNECTION_GPRS
} SIM868BearerConnection;

typedef enum _SIM868BearerStatus_
{
	SIM868_BEARER_STATUS_CONNECTING,
	SIM868_BEARER_STATUS_CONNECTED,
	SIM868_BEARER_STATUS_CLOSING,
	SIM868_BEARER_STATUS_CLOSED
} SIM868BearerStatus;

typedef struct _SIM868BearerStatusInfo_
{
	uint8_t Identifier;
	SIM868BearerStatus Status;
	char IPAddress[16];
} SIM868BearerStatusInfo;

void SIM868_Bearer_SetConnectionType(ATTerminal* at, uint8_t identifier, SIM868BearerConnection type);
void SIM868_Bearer_SetAPN(ATTerminal* at, uint8_t identifier, char* apn);
void SIM868_Bearer_OpenConnection(ATTerminal* at, uint8_t identifier);
void SIM868_Bearer_CloseConnection(ATTerminal* at, uint8_t identifier);
void SIM868_Bearer_QueryConnection(ATTerminal* at, uint8_t identifier);

SIM868BearerStatusInfo SIM868_Bearer_ParseStatus(char* info);

#endif
