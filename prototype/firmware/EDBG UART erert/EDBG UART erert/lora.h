/*
 * Header File for LoRa Radio.
 *
 * 
 */
#ifndef LORA_INCLUDED
#define LORA_INCLUDED

#include "RFM98W.h"

#define FREQUENCY	434000000;
#define POWER		0x88;
#define RTTY_BAUDRATE	50;


typedef enum {lmIdle, lmListening, lmSending} tLoRaMode;

struct TBinaryPacket
{
	uint8_t 	PayloadIDs;
	uint16_t	Counter;
	uint16_t	Seconds;
	float		Latitude;
	float		Longitude;
	uint16_t	Altitude;
};

struct TLoRaMode 
{
	int	ImplicitOrExplicit;
	int ErrorCoding;
	int Bandwidth;
	int SpreadingFactor;
	int LowDataRateOptimize;
	int BaudRate;
	char *Description;
};

struct TRadioConfig
{
	double	Frequency;
	int		PayloadLength;
	int		Power;
	

	int		MillisSinceLastPacket;
	int		LoraMode;
	int		LoraOpMode;
	
	int		InRTTYMode;
	int		SendingRTTY;
	int		RTTYBaudRate;
	int		RTTYShift;
	int		RTTYIndex;
	int		RTTYLength;
	int		RTTYBitLength;
	int		RTTYPreamble;
	int		RTTYMask;
	char	RTTYBuffer[256];
	int		FSKOverSample;
	unsigned int		FSKBitRate;
	
};


void SetLoraMode(uint8_t newMode);
void SetLoRaFrequency(double Frequency);
void setLoRaChannel(int LoRaChannel);
void SetLoRaParameters(int, int, int Bandwidth, int SpreadingFactor, int LowDataRateOptimize);
uint8_t  lora_init(void);
void SwitchToLoRaMode(void);
void SendLoRaData(unsigned char *buffer, int Length);
void SwitchToFSKMode(void);
int FSKPacketSent(void);
int FSKBufferLow(void);
void AddBytesToFSKBuffer(int MaxBytes);
void SendLoRaRTTY(unsigned char *buffer, int Length);
void ConfigRTTYFSK(void);
void CheckFSKBuffers(void);
int RadioState(void);


#endif // LORA_INCLUDED