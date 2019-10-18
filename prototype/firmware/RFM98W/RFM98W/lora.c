/*
 * Drivers for RFM98W chip
 *
 * 
 */
#include <stdio.h>
#include <string.h>
#include "driver_init.h"
#include "RFM98W.h"
#include "lora.h"

// RFM98
uint8_t currentMode = 0x81;
struct TRadioConfig		RadioConfig;

struct TLoRaProfile LoRaProfiles[] =
{
	{EXPLICIT_MODE, ERROR_CODING_4_8, BANDWIDTH_20K8, SPREADING_11, 8,    60, "Telemetry"},			// 0: Normal mode for telemetry
	{IMPLICIT_MODE, ERROR_CODING_4_5, BANDWIDTH_20K8, SPREADING_6,  0,  1400, "SSDV"},				// 1: Normal mode for SSDV
	{EXPLICIT_MODE, ERROR_CODING_4_8, BANDWIDTH_62K5, SPREADING_8,  0,  2000, "Repeater"},			// 2: Normal mode for repeater network
	{EXPLICIT_MODE, ERROR_CODING_4_6, BANDWIDTH_250K, SPREADING_7,  0,  8000, "Turbo"},				// 3: Normal mode for high speed images in 868MHz band
	{IMPLICIT_MODE, ERROR_CODING_4_5, BANDWIDTH_250K, SPREADING_6,  0, 16828, "TurboX"},			// Fastest mode within IR2030 in 868MHz band
	{EXPLICIT_MODE, ERROR_CODING_4_8, BANDWIDTH_41K7, SPREADING_11, 0,   200, "Calling"},			// Calling mode
	{IMPLICIT_MODE, ERROR_CODING_4_5, BANDWIDTH_41K7, SPREADING_6,  0,  2800, "Uplink"},			// Uplink mode for 868
	{EXPLICIT_MODE, ERROR_CODING_4_5, BANDWIDTH_20K8, SPREADING_7,  0,  2800, "Telnet"},			// 7: Telnet-style comms with HAB on 434
	{IMPLICIT_MODE, ERROR_CODING_4_5, BANDWIDTH_62K5, SPREADING_6,  0,  4500, "SSDV Repeater"},		// 8: SSDV Repeater Network
};



void SetLoraMode(uint8_t newMode)
{
	if(newMode == currentMode)
	return;
	
	switch (newMode)
	{
		case RF98_MODE_FSK_TX:
		write_RFM98W_Register(REG_LNA, LNA_OFF_GAIN);  // TURN LNA OFF FOR TRANSMIT
		write_RFM98W_Register(REG_PA_CONFIG, RadioConfig.Power);
		write_RFM98W_Register(REG_OPMODE, newMode);
		currentMode = newMode;
		break;
		
		case RF98_MODE_RX_CONTINUOUS:
		write_RFM98W_Register(REG_PA_CONFIG, PA_OFF_BOOST);  // TURN PA OFF FOR RECIEVE??
		write_RFM98W_Register(REG_LNA, LNA_MAX_GAIN);  // LNA_MAX_GAIN);  // MAX GAIN FOR RECIEVE
		write_RFM98W_Register( REG_OPMODE, newMode);
		currentMode = newMode;
		break;
		
		case RF98_MODE_SLEEP:
		write_RFM98W_Register(REG_OPMODE, newMode);
		currentMode = newMode;
		break;
		
		case RF98_MODE_STANDBY:
		write_RFM98W_Register(REG_OPMODE, newMode);
		currentMode = newMode;
		break;
		
		default: return;
	}
	
	if(newMode != RF98_MODE_SLEEP)
	{
		
		while(ModeReady() == false) ;// DIO5 has the mode_ready signal
		
		
	}
	else
	{
			delay_ms(10);
	}
}


void SetLoRaFrequency(double Frequency)
{
	uint64_t FrequencyValue;

	SetLoraMode(RF98_MODE_STANDBY);
	SetLoraMode(RF98_MODE_SLEEP);
	write_RFM98W_Register(REG_OPMODE, 0x80);
	SetLoraMode(RF98_MODE_SLEEP);

	FrequencyValue = ((uint64_t) Frequency << 19)/32000000;
	
	
	write_RFM98W_Register(REG_FRF_MSB, (FrequencyValue >> 16) & 0xFF);		// Set frequency
	write_RFM98W_Register(REG_FRF_MID, (FrequencyValue >> 8) & 0xFF);
	write_RFM98W_Register(REG_FRF_LSB, FrequencyValue & 0xFF);
}

void UpdateLoRaFrequency(void)
{
	
	SetLoRaFrequency(RadioConfig.Frequency);
	
}
	
void SetLoRaParameters(int ImplicitOrExplicit, int ErrorCoding, int Bandwidth, int SpreadingFactor, int LowDataRateOptimize)
{
	write_RFM98W_Register(REG_MODEM_CONFIG, ImplicitOrExplicit | ErrorCoding | Bandwidth);
	write_RFM98W_Register(REG_MODEM_CONFIG2, SpreadingFactor | CRC_ON);
	write_RFM98W_Register(REG_MODEM_CONFIG3, 0x04 | LowDataRateOptimize);									// 0x04: AGC sets LNA gain
	write_RFM98W_Register(REG_DETECT_OPT, (read_RFM98W_Register(REG_DETECT_OPT) & 0xF8) | ((SpreadingFactor == SPREADING_6) ? 0x05 : 0x03));	// 0x05 For SF6; 0x03 otherwise
	write_RFM98W_Register(REG_DETECTION_THRESHOLD, (SpreadingFactor == SPREADING_6) ? 0x0C : 0x0A);		// 0x0C for SF6, 0x0A otherwise
	
	RadioConfig.PayloadLength = ImplicitOrExplicit == IMPLICIT_MODE ? 255 : 0;
	
	write_RFM98W_Register(REG_PAYLOAD_LENGTH, RadioConfig.PayloadLength);
	write_RFM98W_Register(REG_RX_NB_BYTES, RadioConfig.PayloadLength);
}	

uint8_t lora_init(void)

{
	RFM98W_Setup();
	
	reset_RFM98W();
	
	if (read_RFM98W_Register(REG_VERSION) != 0x12) return 0;
	
	
	RadioConfig.Frequency = FREQUENCY;
	RadioConfig.Power	= PA_MAX_UK;
	
	
	
	RadioConfig.RTTYBaudRate = RTTY_BAUDRATE;
	
	ConfigRTTYFSK();
		
		
	UpdateLoRaFrequency();

	SetLoRaParameters(
	LoRaProfiles[0].ImplicitOrExplicit,
	LoRaProfiles[0].ErrorCoding,
	LoRaProfiles[0].Bandwidth,
	LoRaProfiles[0]. SpreadingFactor,
	LoRaProfiles[0].LowDataRateOptimize);
		
	write_RFM98W_Register(REG_FIFO_ADDR_PTR, 0);

	write_RFM98W_Register(REG_DIO_MAPPING_2,0x00); // Mapping for DIO5 is 0
		
	return 1;
}

void SwitchToLoRaMode(void)
{
	UpdateLoRaFrequency();

	SetLoRaParameters(
	LoRaProfiles[RadioConfig.current_Profile].ImplicitOrExplicit,
	LoRaProfiles[RadioConfig.current_Profile].ErrorCoding,
	LoRaProfiles[RadioConfig.current_Profile].Bandwidth,
	LoRaProfiles[RadioConfig.current_Profile]. SpreadingFactor,
	LoRaProfiles[RadioConfig.current_Profile].LowDataRateOptimize);
	
	
}



void SendLoRaData(unsigned char *buffer, int Length)
{
	

	if (RadioConfig.InRTTYMode != 0)
	{
		// Set LoRa mode
		SwitchToLoRaMode();
		RadioConfig.InRTTYMode = 0;
	}

	RadioConfig.MillisSinceLastPacket = 0;

	SetLoraMode(RF98_MODE_STANDBY);
	
	write_RFM98W_Register(REG_DIO_MAPPING_1, 0x40);		// 01 00 00 00 maps DIO0 to TxDone

	write_RFM98W_Register(REG_FIFO_TX_BASE_AD, 0x00);  // Update the address ptr to the current tx base address
	write_RFM98W_Register(REG_FIFO_ADDR_PTR, 0x00);
	
	write_RFM98W_FIFO(buffer, Length);
	 
	// Set the length. For implicit mode, since the length needs to match what the receiver expects, we have to set a value which is 255 for an SSDV packet
	write_RFM98W_Register(REG_PAYLOAD_LENGTH, Length);

	// go into transmit mode
	SetLoraMode(RF98_MODE_LORA_TX);
	
	RadioConfig.radioState = radioSending;
	RadioConfig.RTTYSending = false;
}

void SwitchToFSKMode(void)
{
	
	
	uint8_t mode = read_RFM98W_Register(REG_OPMODE);
	mode |= (1<<3); 													//set LF range

	if (mode & (1<<7))  //if in lora mode
	{
		write_RFM98W_Register(REG_OPMODE,(mode & ~(uint8_t)7));		//set to sleep mode so fsk bit can be written
	}
	else
	{
		write_RFM98W_Register(REG_OPMODE,(mode & ~(uint8_t)7) | 1);	//set to standby mode so various settings can be written
	}

	mode = read_RFM98W_Register(REG_OPMODE);
	write_RFM98W_Register(REG_OPMODE, mode & ~(uint8_t)(7<<5));         //set to FSK

	write_RFM98W_Register(REG_LNA, LNA_OFF_GAIN);  // TURN LNA OFF FOR TRANSMIT
	write_RFM98W_Register(REG_PA_CONFIG, RadioConfig.Power);
	
	
	
	//write modem config
	write_RFM98W_Register(REG_BITRATE_LSB, RadioConfig.FSKBitRate & 0xFF);
	write_RFM98W_Register(REG_BITRATE_MSB, (RadioConfig.FSKBitRate >> 8) & 0xFF);
	write_RFM98W_Register(REG_FDEV_LSB, (RadioConfig.RTTYShift / 122) & 0xFF);
	write_RFM98W_Register(REG_FDEV_MSB, 0);
	write_RFM98W_Register(REG_PREAMBLE_LSB_FSK, 0);		// Preamble
	write_RFM98W_Register(REG_PREAMBLE_MSB_FSK, 0);
	
	// writeRegister(LoRaChannel, REG_PACKET_CONFIG1, 0x80);		// variable length, no DC fix, no CRC, no addressing
	write_RFM98W_Register(REG_PACKET_CONFIG1, 0x00);		// fixed length, no DC fix, no CRC, no addressing
	write_RFM98W_Register(REG_PAYLOAD_LENGTH_FSK, 0);

}

bool FSKPacketSent(void)
{
	return ((read_RFM98W_Register(REG_IRQ_FLAGS2) & 0x08) != 0);
}

bool FSKBufferLow(void)
{
	return ((read_RFM98W_Register(REG_IRQ_FLAGS2) & 0x20) == 0);
}

bool ModeReady(void)
{
	return ((read_RFM98W_Register(REG_IRQ_FLAGS1) & 0x80) != 0);
	
}

bool RTTYSending(void)
{
	return RadioConfig.RTTYSending;
}

void AddBytesToFSKBuffer(int MaxBytes)
/* Send FSK RTTY Data using the FSK channel of the RFM98W

 * The RFM98 bitrate is 800 bps for 50 baud and 2400 bps for 300 baud.
 * The oversample is 2 for 50 baud and 1 for 300 baud
 * So at 50 baud we send two full bytes of either 0x00 or 0xff for each data bit
 * or at 300 baud we send a full byte of either 0x00 or 0xff for each data bit
 */

{
	unsigned char data[64], temp;
	
	uint8_t BytesWritten = 0;

	if (RadioConfig.RTTYIndex < RadioConfig.RTTYLength)
	{
				
		while((BytesWritten <= (MaxBytes - RadioConfig.FSKOverSample)) &&
			  (RadioConfig.RTTYIndex < RadioConfig.RTTYLength))
		{
			if (RadioConfig.RTTYMask < 0)  //start bit
			{
				temp = 0xFF;
				RadioConfig.RTTYMask++;
			}
			else if (RadioConfig.RTTYMask == 0)  //start bit
			{
				temp = 0;
				RadioConfig.RTTYMask = 1;
			}
			else if (RadioConfig.RTTYMask >= (1<<RadioConfig.RTTYBitLength))  //stop bits
			{
				RadioConfig.RTTYMask <<= 1;
				temp = 0xFF;
				if (RadioConfig.RTTYMask >= (1<<(RadioConfig.RTTYBitLength+2)))
				{
					RadioConfig.RTTYMask = 0;
					RadioConfig.RTTYIndex++;
				}
			}
			else  //data bits
			{
				if (RadioConfig.RTTYBuffer[RadioConfig.RTTYIndex] & RadioConfig.RTTYMask)
				{
					temp = 0xFF;
				}
				else
				{
					temp = 0x0;
				}
				RadioConfig.RTTYMask <<= 1;
			}

			for (uint8_t i = 0; i < RadioConfig.FSKOverSample; i++)
			{
				data[BytesWritten++] = temp;
			}
		}
		
		write_RFM98W_FIFO(data, BytesWritten);

		
	}
}


void SendLoRaRTTY(unsigned char *buffer, int Length) // send up to 256 bytes of data
{
	

	if (RadioConfig.InRTTYMode != 1)
	{
		// Set RTTY mode
		SwitchToFSKMode();
		RadioConfig.InRTTYMode = 1;
	}

	RadioConfig.MillisSinceLastPacket = 0;
	
	// Fill in RTTY buffer
	memcpy(RadioConfig.RTTYBuffer, buffer, Length);
	RadioConfig.RTTYLength = Length;
	RadioConfig.RTTYIndex = 0;
	RadioConfig.RTTYMask = RadioConfig.RTTYPreamble;
	
	// Set FIFO threshold
	uint8_t r = read_RFM98W_Register( REG_FIFO_THRESH);
	write_RFM98W_Register(REG_FIFO_THRESH,(r&(~0x3F)) | 20);			// 20 = FIFO threshold
	
	write_RFM98W_Register(REG_OPMODE, RF98_MODE_FSK_TX);		// Tx mode

	// Populate FIFO
	AddBytesToFSKBuffer(64);
	
	// Set channel state
	RadioConfig.radioState = radioSending;
	RadioConfig.RTTYSending = true;
}


void ConfigRTTYFSK(void)
{
	
	
	RadioConfig.RTTYShift = RTTY_SHIFT;
	RadioConfig.RTTYPreamble = 8;
	if (RadioConfig.RTTYBaudRate == 50)
	{
		RadioConfig.FSKBitRate = 40000;
		RadioConfig.FSKOverSample = 2;
		RadioConfig.RTTYBitLength = 8;
	}
	else if (RadioConfig.RTTYBaudRate == 1200)
	{
		RadioConfig.FSKBitRate = 3333
		;
		RadioConfig.FSKOverSample = 1;
		RadioConfig.RTTYBitLength = 8;
	}
	else
	{
		// 300 baud
		RadioConfig.FSKBitRate = 13333;
		RadioConfig.FSKOverSample = 1;
		RadioConfig.RTTYBitLength = 8;
	}
	
}





void CheckFSKBuffers(void)
{
	
	
	if ((RadioConfig.radioState == radioSending) && RadioConfig.RTTYSending)
	{
		// Check if packet sent
		if (FSKPacketSent())
		{
			

			RadioConfig.radioState = radioIdle;
			RadioConfig.RTTYSending = false;
			SetLoraMode(RF98_MODE_STANDBY);
			//			SetLoraMode(RF98_MODE_SLEEP);
		}
		else if (FSKBufferLow())
		{
			AddBytesToFSKBuffer(64 - 20);
		}
	}
	
}

