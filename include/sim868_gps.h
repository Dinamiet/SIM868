#ifndef _SIM868_GPS_H_
#define _SIM868_GPS_H_

/**
 * \file
 * SIM868 GPS management
 *
 * This file provides functions to manage the GPS functionality of the SIM868 module, including powering on/off the GPS and retrieving the last GPS fix information.
 * It also defines the necessary data structures and enumerations for handling GPS responses and parsing GPS information
 */

#include "atterminal.h"

#include <stdbool.h>
#include <stdint.h>

/**
 * GPS AT response identifiers
 */
typedef enum _SIM868GPSATResponses_
{
	SIM868_GPS_RESPONSE_FIX   = 0x82BE4BAD,
	SIM868_GPS_RESPONSE_POWER = 0xF0A29A35,
} SIM868GPSATResponse;

/**
 * GPS information structure
 */
typedef struct _SIM868GPSInfo_
{
	bool     RunningStatus;
	bool     FixStatus;
	uint8_t  FixMode;
	uint32_t UTCSeconds;
	uint16_t Millisecond;
	float    Latitude;
	float    Longitude;
	float    Altitude;
	float    GroundSpeed;
	float    Heading;
	float    HDOP;
	float    PDOP;
	float    VDOP;
	uint8_t  GPSSatellitesInView;
	uint8_t  GNSSSatellitesUsed;
	uint8_t  GLONASSSatellitesInView;
	uint8_t  CNOMax;
	float    HPA;
	float    VPA;
} SIM868GPSInfo;

/**
 * Power on/off the GPS and set the fix period.
 * \param at ATTerminal instance to send the command through
 * \param powerOn True to power on the GPS, false to power it off
 * \param fixPeriod Fix period in seconds (0 for continuous updates)
 */
void SIM868_GPS_Power(ATTerminal* at, bool powerOn, uint8_t fixPeriod);

/**
 * Retrieve the last GPS fix information.
 * \param at ATTerminal instance to send the command through
 */
void SIM868_GPS_LastFix(ATTerminal* at);

/**
 * Parse the GPS fix information from a response string.
 * \param info Response string containing the GPS fix information
 * \return Parsed GPS fix information
 */
SIM868GPSInfo SIM868_GPS_ParseFixInfo(char* info);

/**
 * Parse the GPS power information from a response string.
 * \param info Response string containing the GPS power information
 * \return True if the power information was parsed successfully, false otherwise
 */
bool          SIM868_GPS_ParsePowerInfo(char* info);

#endif
