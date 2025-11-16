#include "defines.h"
#include "sim868_bearer.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void SIM868_Bearer_OpenConnection(ATTerminal* at, uint8_t identifier, char* apn, SIM868BearerConnection type)
{
	char command[MAX_COMMAND_SIZE];
	sprintf(command,
	        "AT+SAPBR=3,%d,\"Contype\",\"%s\";"
	        "+SAPBR=3,%d,\"APN\",\"%s\";"
	        "+SAPBR=1,%d",
	        identifier,
	        type == SIM868_BEARER_CONNECTION_GPRS ? "GPRS" : "CSD",
	        identifier,
	        apn,
	        identifier);
	ATTerminal_SendCommand(at, command);
}

void SIM868_Bearer_CloseConnection(ATTerminal* at, uint8_t identifier)
{
	char command[MAX_COMMAND_SIZE];
	sprintf(command, "AT+SAPBR=0,%d", identifier);
	ATTerminal_SendCommand(at, command);
}

void SIM868_Bearer_QueryConnection(ATTerminal* at, uint8_t identifier)
{
	char command[MAX_COMMAND_SIZE];
	sprintf(command, "AT+SAPBR=2,%d", identifier);
	ATTerminal_SendCommand(at, command);
}

SIM868BearerStatusInfo SIM868_Bearer_ParseStatus(char* info)
{
	SIM868BearerStatusInfo statusInfo = {0};

	char* rest  = info;
	char* token = strsep(&rest, ",");

	// Identifier
	if (token)
		statusInfo.Identifier = atoi(token);

	// Status
	token = strsep(&rest, ",");
	if (token)
		statusInfo.Status = atoi(token);

	// IP address
	token = strsep(&rest, ",");
	strsep(&token, "\"");
	token = strsep(&token, "\"");
	if (token)
		strncpy(statusInfo.IPAddress, token, sizeof(statusInfo.IPAddress) - 1);

	return statusInfo;
}
