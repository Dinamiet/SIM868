#include "defines.h"
#include "sim868_gsm.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void SIM868_GSM_Functionality(ATTerminal* at, SIM868GSMFunctionality func)
{
	char command[MAX_COMMAND_SIZE];
	sprintf(command, "AT+CFUN=%d", func);
	ATTerminal_SendCommand(at, command);
}

void SIM868_GSM_EnterPin(ATTerminal* at, char* pin)
{
	char command[MAX_COMMAND_SIZE];
	sprintf(command, "AT+CPIN=%s", pin);
	ATTerminal_SendCommand(at, command);
}

void SIM868_GSM_SignalCheck(ATTerminal* at) { ATTerminal_SendCommand(at, "AT+CSQ"); }

void SIM868_GSM_NetworkRegistrationStatus(ATTerminal* at, SIM868GSMNetworkNotify notify)
{
	char command[MAX_COMMAND_SIZE];
	sprintf(command, "AT+CGREG=%d", notify);
	ATTerminal_SendCommand(at, command);
}

void SIM868_GSM_SetAPN(ATTerminal* at, char* apn, char* user, char* pass)
{
	char command[MAX_COMMAND_SIZE];
	if (pass)
		sprintf(command, "AT+CSTT=\"%s\",\"%s\",\"%s\"", apn, user, pass);
	else if (user)
		sprintf(command, "AT+CSTT=\"%s\",\"%s\"", apn, user);
	else
		sprintf(command, "AT+CSTT=\"%s\"", apn);

	ATTerminal_SendCommand(at, command);
}

void SIM868_GSM_ConnectData(ATTerminal* at) { ATTerminal_SendCommand(at, "AT+CIICR"); }

void SIM868_GSM_IPAddress(ATTerminal* at) { ATTerminal_SendCommand(at, "AT+CIFSR"); }

SIM868GSMNetworkInfo SIM868_GSM_ParseNetworkInfo(char* info)
{
	SIM868GSMNetworkInfo networkData = {0};

	char* rest  = info;
	char* token = strsep(&rest, ",");

	// Stat field
	if (token)
		networkData.Status = atoi(token);

	// Location Code field
	token = strsep(&rest, ",");
	strsep(&token, "\"");
	token = strsep(&token, "\"");
	if (token)
		networkData.LocationCode = strtoul(token, NULL, 16);

	// Cell ID field
	token = strsep(&rest, ",");
	strsep(&token, "\"");
	token = strsep(&token, "\"");
	if (token)
		networkData.CellID = strtoul(token, NULL, 16);

	return networkData;
}

SIM868GSMSignalInfo SIM868_GSM_ParseSignalInfo(char* info)
{
	SIM868GSMSignalInfo signalInfo = {0};

	char* rest  = info;
	char* token = strsep(&rest, ",");

	// RSSI field
	if (token)
		signalInfo.RSSI = atoi(token);

	token = strsep(&rest, ",");
	if (token)
		signalInfo.BER = atoi(token);

	return signalInfo;
}
