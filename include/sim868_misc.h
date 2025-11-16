#ifndef _SIM868_MISC_H_
#define _SIM868_MISC_H_

#include "atterminal.h"

#include <stdbool.h>
#include <stdint.h>

typedef enum _SIM868MiscResponse_
{
	SIM868_MISC_RDY            = 0xBCD1304E, // RDY
	SIM868_MISC_BATTERY_STATUS = 0x4647B2A9, // CBC
} SIM868MiscResponse;

typedef enum _SIM868MiscBatteryStatus_
{
	SIM868_MISC_BATTERY_STATUS_DISCHARGING,
	SIM868_MISC_BATTERY_STATUS_CHARGING,
	SIM868_MISC_BATTERY_STATUS_FINISHED
} SIM868MiscBatteryStatus;

typedef struct _SIM868MiscBatteryInfo_
{
	SIM868MiscBatteryStatus Status;
	uint8_t                 ChargeLevel;
	uint16_t                Voltage;
} SIM868MiscBatteryInfo;

void SIM868_Misc_CommandEcho(ATTerminal* at, bool echoEnabled);
void SIM868_Misc_Check(ATTerminal* at);
void SIM868_Misc_BatteryStatus(ATTerminal* at);

SIM868MiscBatteryInfo SIM868_Misc_ParseBatteryInfo(char* info);

#endif
