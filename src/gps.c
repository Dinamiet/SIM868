#include "sim868_gps.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_COMMAND_SIZE 32

void SIM868_GPS_Power(ATTerminal* at, bool powerOn)
{
	char command[MAX_COMMAND_SIZE];
	sprintf(command, "AT+CGNSPWR=%d", powerOn);
	ATTerminal_SendCommand(at, command);
}

void SIM868_GPS_UnsolicitedFix(ATTerminal* at, uint8_t period)
{
	char command[MAX_COMMAND_SIZE];
	sprintf(command, "AT+CGNSURC=%d", period);
	ATTerminal_SendCommand(at, command);
}

void SIM868_GPS_LastFix(ATTerminal* at)
{
	char* command = "AT+CGNSINF";
	ATTerminal_SendCommand(at, command);
}

SIM868GPSInfo SIM868_GPS_ParseFixInfo(char* info)
{
	// uint8_t       reserved1, reserved2, reserved3;
	struct tm     time    = {0};
	SIM868GPSInfo gpsData = {0};

	char* rest  = info;
	char* token = strsep(&rest, ",");

	// Running Status
	if (token)
		gpsData.RunningStatus = atoi(token);

	// Fix status
	token = strsep(&rest, ",");
	if (token)
		gpsData.FixStatus = atoi(token);

	// UTC Date and time
	token = strsep(&rest, ".");
	if (token)
	{
		sscanf(token, "%4d%2d%2d%2d%2d%2d", &time.tm_year, &time.tm_mon, &time.tm_mday, &time.tm_hour, &time.tm_min, &time.tm_sec);
		time.tm_year -= 1900; // Year is years from 1900
		time.tm_mon -= 1;     // Month is 0 based
		time.tm_isdst      = 0;
		gpsData.UTCSeconds = mktime(&time);
	}

	// Milliseconds
	token = strsep(&rest, ",");
	if (token)
		gpsData.Millisecond = atoi(token);

	// Latitude
	token = strsep(&rest, ",");
	if (token)
		gpsData.Latitude = atof(token);

	// Longitude
	token = strsep(&rest, ",");
	if (token)
		gpsData.Longitude = atof(token);

	// Altitude
	token = strsep(&rest, ",");
	if (token)
		gpsData.Altitude = atof(token);

	// Ground speed
	token = strsep(&rest, ",");
	if (token)
		gpsData.GroundSpeed = atof(token);

	// Heading
	token = strsep(&rest, ",");
	if (token)
		gpsData.Heading = atof(token);

	// Fix Mode
	token = strsep(&rest, ",");
	if (token)
		gpsData.FixMode = atoi(token);

	// Reserved1
	token = strsep(&rest, ",");

	// HDOP
	token = strsep(&rest, ",");
	if (token)
		gpsData.HDOP = atof(token);

	// PDOP
	token = strsep(&rest, ",");
	if (token)
		gpsData.PDOP = atof(token);

	// VDOP
	token = strsep(&rest, ",");
	if (token)
		gpsData.VDOP = atof(token);

	// Reserved2
	token = strsep(&rest, ",");

	// GPS Satellites in view
	token = strsep(&rest, ",");
	if (token)
		gpsData.GPSSatellitesInView = atoi(token);

	// GNSS Satellites used
	token = strsep(&rest, ",");
	if (token)
		gpsData.GNSSSatellitesUsed = atoi(token);

	// GLONASS Satellites in view
	token = strsep(&rest, ",");
	if (token)
		gpsData.GLONASSSatellitesInView = atoi(token);

	// Reserved3
	token = strsep(&rest, ",");

	// CNO Max
	token = strsep(&rest, ",");
	if (token)
		gpsData.CNOMax = atoi(token);

	// HPA
	token = strsep(&rest, ",");
	if (token)
		gpsData.HPA = atof(token);

	// VPA
	token = strsep(&rest, ",");
	if (token)
		gpsData.VPA = atof(token);

	return gpsData;
}

bool SIM868_GPS_ParsePowerInfo(char* info)
{
	int powerOn = atoi(info);
	return powerOn;
}
