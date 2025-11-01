#ifndef _SIM868_GPS_H_
#define _SIM868_GPS_H_

#include <stdbool.h>
#include <stdint.h>

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

void SIM868_GPS_Power(bool powerOn);
void SIM868_GPS_UnsolicitedFix(uint8_t period);
void SIM868_GPS_LastFix();

SIM868GPSInfo SIM868_GPS_ParseFixInfo(char* info);
bool          SIM868_GPS_ParsePowerInfo(char* info);

#endif
