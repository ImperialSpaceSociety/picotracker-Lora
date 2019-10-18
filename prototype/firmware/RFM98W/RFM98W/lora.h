/*
 * Header File for LoRa Radio.
 *
 * 
 */
#ifndef LORA_INCLUDED
#define LORA_INCLUDED

#include "RFM98W.h"

#define FREQUENCY	144600000
#define POWER		0x88
#define RTTY_BAUDRATE	1200
#define RTTY_SHIFT		976 // this is quantised in 122Hz steps


typedef enum {radioIdle, radioListening, radioSending} tRadioState;


struct TLoRaProfile 
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
	tRadioState		radioState;
	int		current_Profile;
	
	
	int		InRTTYMode; // Are we in LoRa or RTTY FSK Mode ?
	bool	RTTYSending;  // Busy sending RTTY
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
bool FSKPacketSent(void);
bool FSKBufferLow(void);
bool ModeReady(void);
void AddBytesToFSKBuffer(int MaxBytes);
void SendLoRaRTTY(unsigned char *buffer, int Length);
void ConfigRTTYFSK(void);
void CheckFSKBuffers(void);
bool RTTYSending(void);


#endif // LORA_INCLUDED