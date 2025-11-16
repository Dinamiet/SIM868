#ifndef _SIM868_GPS_H_
#define _SIM868_GPS_H_

#include "atterminal.h"

#include <stdbool.h>
#include <stdint.h>

typedef enum _SIM868GPSATResponses_
{
	SIM868_GPS_RESPONSE_FIX   = 0x82BE4BAD,
	SIM868_GPS_RESPONSE_POWER = 0xF0A29A35,
} SIM868GPSATResponse;

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

void SIM868_GPS_Power(ATTerminal* at, bool powerOn, uint8_t fixPeriod);
void SIM868_GPS_LastFix(ATTerminal* at);

SIM868GPSInfo SIM868_GPS_ParseFixInfo(char* info);
bool          SIM868_GPS_ParsePowerInfo(char* info);

#endif
