#ifndef _SIM868_MISC_H_
#define _SIM868_MISC_H_

/**
 * \file
 * SIM868 miscellaneous management
 *
 * This file provides functions to manage miscellaneous features of the SIM868 module, including command echo, checking module readiness, and retrieving battery status information.
 * It also defines the necessary data structures and enumerations for handling miscellaneous responses and parsing battery information.
 */

#include "atterminal.h"

#include <stdbool.h>
#include <stdint.h>

/**
 * Miscellaneous AT response identifiers
 */
typedef enum _SIM868MiscResponse_
{
	SIM868_MISC_RDY            = 0xBCD1304E, // RDY
	SIM868_MISC_BATTERY_STATUS = 0x4647B2A9, // CBC
} SIM868MiscResponse;

/**
 * Battery status types
 */
typedef enum _SIM868MiscBatteryStatus_
{
	SIM868_MISC_BATTERY_STATUS_DISCHARGING,
	SIM868_MISC_BATTERY_STATUS_CHARGING,
	SIM868_MISC_BATTERY_STATUS_FINISHED
} SIM868MiscBatteryStatus;

/**
 * Battery information structure
 */
typedef struct _SIM868MiscBatteryInfo_
{
	SIM868MiscBatteryStatus Status;
	uint8_t                 ChargeLevel;
	uint16_t                Voltage;
} SIM868MiscBatteryInfo;

/**
 * Enable or disable command echo on the SIM868 module.
 * \param at ATTerminal instance to send the command through
 * \param echoEnabled True to enable command echo, false to disable it
 */
void SIM868_Misc_CommandEcho(ATTerminal* at, bool echoEnabled);

/**
 * Check if the SIM868 module is ready by sending an AT command.
 * \param at ATTerminal instance to send the command through
 */
void SIM868_Misc_Check(ATTerminal* at);

/**
 * Retrieve the battery status from the SIM868 module.
 * \param at ATTerminal instance to send the command through
 */
void SIM868_Misc_BatteryStatus(ATTerminal* at);

/**
 * Parse the battery information from a response string.
 * \param info Response string containing the battery information
 * \return Parsed battery information
 */
SIM868MiscBatteryInfo SIM868_Misc_ParseBatteryInfo(char* info);

#endif
