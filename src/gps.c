#include "sim868_gps.h"

#include <stdio.h>
#include <time.h>

#define MAX_COMMAND_SIZE 32

void SIM868_GPS_Power(bool powerOn)
{
	char command[MAX_COMMAND_SIZE];
	sprintf(command, "AT+CGNSPWR=%d", powerOn);
}

void SIM868_GPS_UnsolicitedFix(uint8_t period)
{
	char command[MAX_COMMAND_SIZE];
	sprintf(command, "AT+CGNSURC=%d", period);
}

void SIM868_GPS_LastFix() { char* command = "AT+CGNSINF"; }

SIM868GPSInfo SIM868_GPS_ParseFixInfo(char* info)
{
	uint8_t       reserved1, reserved2, reserved3;
	struct tm     time;
	SIM868GPSInfo gpsData;
	sscanf(info,
	       "%d,%d,%4d%2d%2d%2d%2d%2d.%3d,%f,%f,%f,%f,%f,%d,%d,%f,%f,%f,%d,%d,%d,%d,%d,%d,%f,%f",
	       &gpsData.RunningStatus,
	       &gpsData.FixStatus,
	       &time.tm_year,
	       &time.tm_mon,
		   &time.tm_mday,
	       &time.tm_hour,
	       &time.tm_min,
	       &time.tm_sec,
	       &gpsData.Millisecond,
	       &gpsData.Latitude,
	       &gpsData.Longitude,
	       &gpsData.Altitude,
	       &gpsData.GroundSpeed,
	       &gpsData.FixMode,
	       &reserved1,
	       &gpsData.HDOP,
	       &gpsData.PDOP,
	       &gpsData.VDOP,
	       &reserved2,
	       &gpsData.GPSSatellitesInView,
	       &gpsData.GNSSSatellitesUsed,
	       &gpsData.GLONASSSatellitesInView,
	       &reserved3,
	       &gpsData.CNOMax,
	       &gpsData.HPA,
	       &gpsData.VPA);

	time.tm_yday -= 1900; // Year is years from 1900
	time.tm_mon -= 1; // Month is 0 based
	time.tm_isdst = 0;

	// gpsData.UTCSeconds =timegm(
}

bool SIM868_GPS_ParsePowerInfo(char* info)
{
	bool powerOn;
	sscanf(info, "%d", &powerOn);
	return powerOn;
}
