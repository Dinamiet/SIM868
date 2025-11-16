#include "defines.h"
#include "sim868_http.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void SIM868_HTTP_StartSession(ATTerminal* at) { ATTerminal_SendCommand(at, "AT+HTTPINIT"); }

void SIM868_HTTP_SetBearerProfile(ATTerminal* at, uint8_t identifier)
{
	char command[MAX_COMMAND_SIZE];
	sprintf(command, "AT+HTTPPARA=\"CID\",%d", identifier);
	ATTerminal_SendCommand(at, command);
}

void SIM868_HTTP_SetURL(ATTerminal* at, char* url)
{
	char command[MAX_COMMAND_SIZE];
	sprintf(command, "AT+HTTPPARA=\"URL\",\"%s\"", url);
	ATTerminal_SendCommand(at, command);
}

void SIM868_HTTP_SetRequestBody(ATTerminal* at, void* data, size_t size)
{
	char command[MAX_COMMAND_SIZE];
	sprintf(command, "AT+HTTPDATA=%ld,60000", size);
	ATTerminal_SendCommand(at, command);
	ATTerminal_Wait(at, "DOWNLOAD");
	ATTerminal_SendRaw(at, data, size);
}

void SIM868_HTTP_ExecuteAction(ATTerminal* at, SIM868HTTPAction action)
{
	char command[MAX_COMMAND_SIZE];
	sprintf(command, "AT+HTTPACTION=%d", action);
	ATTerminal_SendCommand(at, command);
}

void SIM868_HTTP_ReadResponseData(ATTerminal* at) { ATTerminal_SendCommand(at, "AT+HTTPREAD"); }

void SIM868_HTTP_TerminateSession(ATTerminal* at) { ATTerminal_SendCommand(at, "AT+HTTPTERM"); }

SIM868HTTPActionInfo SIM868_HTTP_ParseActionInfo(char* info)
{
	SIM868HTTPActionInfo actionInfo= {0};

	char* rest = info;
	char* token = strsep(&rest, ",");

	// Action
	if (token)
		actionInfo.Action = atoi(token);

	// Response Code
	token = strsep(&rest, ",");
	if (token)
		actionInfo.Status = atoi(token);

	// Response length
	token = strsep(&rest, ",");
	if (token)
		actionInfo.ResponseLength= atoi(token);

	return actionInfo;
}
