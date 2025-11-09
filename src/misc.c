#include "defines.h"
#include "sim868_misc.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void SIM868_Misc_CommandEcho(ATTerminal* at, bool echoEnabled)
{
	char command[MAX_COMMAND_SIZE];
	sprintf(command, "ATE%d", echoEnabled);
	ATTerminal_SendCommand(at, command);
}

void SIM868_Misc_Check(ATTerminal* at) { ATTerminal_SendCommand(at, "AT"); }

void SIM868_Misc_BatteryStatus(ATTerminal* at) { ATTerminal_SendCommand(at, "AT+CBC"); }

SIM868MiscBatteryInfo SIM868_Misc_ParseBatteryInfo(char* info)
{
	SIM868MiscBatteryInfo batteryInfo = {0};
	char*                 rest        = info;
	char*                 token       = strsep(&rest, ",");

	// Charge Status
	if (token)
		batteryInfo.Status = atoi(token);

	// Charge Level
	token = strsep(&rest, ",");
	if (token)
		batteryInfo.ChargeLevel = atoi(token);

	// Voltage
	token = strsep(&rest, ",");
	if (token)
		batteryInfo.Voltage = atoi(token);

	return batteryInfo;
}
