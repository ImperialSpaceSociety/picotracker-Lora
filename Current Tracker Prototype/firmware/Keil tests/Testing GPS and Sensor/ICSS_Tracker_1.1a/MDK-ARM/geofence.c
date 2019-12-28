///*
// * GEOFENCE.c
// *
// * Created: 5.11.2016 22:04:58
// *  Author: Tomy2
// * Modified by Medad Newman 27/12/19
// */ 

// 
#include "geofence.h"
#include <stdio.h>




/*
 * dummy function to force the compiler to compile all the polygons
 * to see their memory footprint. MUST NEVER BE CALLED!
 */
void doit(void){
	EU863870_1[1] = 1;
	EU863870_2[1] = 1;
	EU863870_3[1] = 1;
	EU863870_4[1] = 1;
	EU863870_5[1] = 1;

	
	AU915928_1[1] =1;
	AU915928_2[1] = 1;
	AU915928_3[1] = 1;

	US902928_1[1] = 1;
	KR920923_1[1] = 1;
	IN865867_1[1] = 1;
	
	AS920923_2[1] = 1;
	AS920923_1[1] = 1;

	CN470510_1[1] = 1;
	
	AS923925_4[1] = 1;
	AS923925_3[1] = 1;
	AS923925_2[1] = 1;
	AS923925_1[1] = 1;

}



// Strategy: check if GPS coordinate is in any of the polygons. If so, look up what transmit frequency it uses.

/*
	Adapted version of pointInPolygon() function from:	http://alienryderflex.com/polygon/
	
	Returns '0' if the point is outside of the polygon and '1' if it's inside.
	
	Expects input DEGREES * 100000 for latitude and longitude. Eg 4961070 for 49.61070 N.
	The reason is to make sure all calculations fit inside int32_t.
	
	However, this function is not very accurate due to rounding within the computation.
*/
int32_t pointInPolygon(int32_t polyCorners, int32_t * polygon, int32_t latitude, int32_t longitude)
{
	int32_t i;
	int32_t j = polyCorners * 2 - 2;
	int32_t oddNodes = 0;

	for(i = 0; i < polyCorners * 2; i += 2)
	{
		if((polygon[i + 1] < latitude && polygon[j + 1] >= latitude
			|| polygon[j + 1] < latitude && polygon[i + 1] >= latitude)
			&& (polygon[i] <= longitude || polygon[j] <= longitude))
		{
			oddNodes ^= (polygon[i] + (latitude - polygon[i + 1])
			/ (polygon[j + 1] - polygon[i + 1]) * (polygon[j] - polygon[i]) < longitude);
		}

		j = i;
	}

	return oddNodes;
}


/*
	Adapted version of pointInPolygon() function from:	http://alienryderflex.com/polygon/
	
	Returns '0' if the point is outside of the polygon and '1' if it's inside.
	
	Uses FLOAT input for better accuracy.
*/
int32_t pointInPolygonF(int32_t polyCorners, float * polygon, float latitude, float longitude)
{
	int32_t i;
	int32_t j = polyCorners * 2 - 2;
	int32_t oddNodes = 0;

	for(i = 0; i < polyCorners * 2; i += 2)
	{
		if((polygon[i + 1] < latitude && polygon[j + 1] >= latitude
		|| polygon[j + 1] < latitude && polygon[i + 1] >= latitude)
		&& (polygon[i] <= longitude || polygon[j] <= longitude))
		{
			oddNodes ^= (polygon[i] + (latitude - polygon[i + 1])
			/ (polygon[j + 1] - polygon[i + 1]) * (polygon[j] - polygon[i]) < longitude);
		}

		j = i;
	}

	return oddNodes;
}


typedef enum
{
  EU863870    = 0x00U,
  AU915928    = 0x01U,
  US902928    = 0x02U,
  KR920923    = 0x03U,
	IN865867    = 0x03U,
	AS920923		= 0x03U,
	CN470510		= 0x03U,
	AS923925		= 0x03U,
	
} LoRa_FREQUENCIES;

///*
//	Changes GEOFENCE_LoRA_frequency and GEOFENCE_no_tx global variables based on the input coordinates.
//	TODO: documentation must be updated for LoRa frequencies
//	FREQUENCIES:
//						Africa				144.800
//						Europe				144.800
//						Russia				144.800
//	Expected input FLOAT for latitude and longitude as in GPS_UBX_latitude_Float and GPS_UBX_longitude_Float.
//*/
void GEOFENCE_position(float latitude, float longitude)
{
	EU863870_1[1] = 1;
	EU863870_2[1] = 1;
	EU863870_3[1] = 1;
	EU863870_4[1] = 1;
	EU863870_5[1] = 1;

	
	AU915928_1[1] =1;
	AU915928_2[1] = 1;
	AU915928_3[1] = 1;

	US902928_1[1] = 1;
	KR920923_1[1] = 1;
	IN865867_1[1] = 1;
	
	AS920923_2[1] = 1;
	AS920923_1[1] = 1;

	CN470510_1[1] = 1;
	
	AS923925_4[1] = 1;
	AS923925_3[1] = 1;
	AS923925_2[1] = 1;
	AS923925_1[1] = 1;
		

	if(pointInPolygonF(sizeof(EU863870_1)/2, EU863870_1, latitude, longitude) == 1)		{GEOFENCE_no_tx = 0; GEOFENCE_LoRa_frequency = 144930000;}
	else if(pointInPolygonF(sizeof(EU863870_2)/2, EU863870_2, latitude, longitude) == 1)		{GEOFENCE_no_tx = 0; GEOFENCE_LoRa_frequency = 145570000;}
	else if(pointInPolygonF(sizeof(EU863870_3)/2, EU863870_3, latitude, longitude) == 1)	{GEOFENCE_no_tx = 0; GEOFENCE_LoRa_frequency = 145010000;}
	else if(pointInPolygonF(sizeof(EU863870_4)/2, EU863870_4, latitude, longitude) == 1)	{GEOFENCE_no_tx = 0; GEOFENCE_LoRa_frequency = 145010000;}
	
	// Over the sea or areas where there is no frequency declared

	else																{GEOFENCE_no_tx = 0; GEOFENCE_LoRa_frequency = 144390000;}
}
	
	



