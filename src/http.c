#include "defines.h"
#include "sim868_http.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void SIM868_HTTP_StartSession(ATTerminal* at, uint8_t identifier, uint8_t timeout)
{
	char command[MAX_COMMAND_SIZE];
	sprintf(command, "AT+HTTPINIT;+HTTPPARA=\"TIMEOUT\",%d;+HTTPPARA=\"CID\",%d", timeout, identifier);
	ATTerminal_SendCommand(at, command);
}

void SIM868_HTTP_Post(ATTerminal* at, char* url, void* data, size_t size)
{
	char command[MAX_COMMAND_SIZE];
	sprintf(command, "AT+HTTPPARA=\"URL\",\"%s\";+HTTPDATA=%ld,1000", url, size);
	ATTerminal_SendCommand(at, command);
	ATTerminal_Wait(at, "DOWNLOAD");
	ATTerminal_SendRaw(at, data, size);
	sprintf(command, "AT+HTTPACTION=%d", SIM868_HTTP_ACTION_POST);
	ATTerminal_SendCommand(at, command);
}

void SIM868_HTTP_RequestResponseData(ATTerminal* at) { ATTerminal_SendCommand(at, "AT+HTTPREAD"); }

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

size_t SIM868_HTTP_ParseReadData(char* info) { return atoi(info); }

size_t SIM868_HTTP_ReadData(ATTerminal* at, void* data, size_t size) { return ATTerminal_ReadRaw(at, data, size); }
