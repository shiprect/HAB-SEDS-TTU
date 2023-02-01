#ifndef __BMP_H__
#define __BMP_H__

#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>

#include "Adafruit_BMP085_U.h"

#include "../../../Config.h"


//TODO::DEBUG_PRINT() should be reworked to use a custom DEBUG_BMP that can be macro toggled for this class
class BMP {
	private:
		Adafruit_BMP085_Unified BMPModule = Adafruit_BMP085_Unified( 10085
		); //TODO::Should be modified to work for other BMP types, type passed into constructor

		//TODO::These values should be initialized appropriately here
		bool ValidBMP;

		float BaselinePressure;
		float Pressure;
		float Temperature;
		float Altitude;
		float MaxAltitude;

	public:
		BMP() {
		};

		~BMP() {
		};


		void BMP_Setup();//TODO::should return true if successful, false otherwise
		void BMP_Update();//TODO::should return true if successful, false otherwise

		bool IsValidBMP();

		float GetBaselinePressure();
		float GetPressure();
		float GetTemperature();
		float GetAltitude();
		float GetMaxAltitude();
};

extern BMP bmp;


#endif