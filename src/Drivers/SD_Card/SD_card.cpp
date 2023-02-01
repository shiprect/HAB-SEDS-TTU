#include "SD_card.hpp"

///order
//bmp
//gps
//status


void SD_card::SD_Setup() {

	if ( !SD.begin( ChipSelectPin )) {
		ValidSD = 0;
	}
	else {
		ValidSD = 1;
	}

	//dataFile = SD.open("data.csv",FILE_WRITE);
	if ( dataFile ) {
		//dataFile.print(F("BMP Sea Level Pressure: "));
		//dataFile.print(bmp.GetBaselinePressure());
		//dataFile.print(F("\n"));

		//BMP Temp(#1), Pressure(#2), Altitude(#3), MaxAltitude(#4)
		// dataFile.print(F("Temperature(C), Pressure(Pa), Altitude(m), MaxAltitude(m), "));

		//Accel x(#5), y(#6), z(#7), Orientation(#8)
		//dataFile.print(F("x, y, z(m/s^2), Orientation, "));

		////Lat(#9), Long(#10), gpsAlt(#11), Course(#12), Speed(#13), Satellites(#14), Full_Lat(#16), Full_lon(#17), Date(#18), Time(#19), Day(#20)
		//dataFile.print(F("Latitude, Longitude, gpsAltitude, Course, Speed, Satellites, Full_Latitude, Full_Longitude, Date, Day, Hour, Minute, Second, "));

		//Status Liftoff(#21), Burnout(#22), Falling(#23), ValidBMP(#24), ValidSD(#25)
		//dataFile.print(F("ValidBMP, ValidSD, IsRising, IsFalling, IsLanded, IsServerOn\n"));

		dataFile.close();
	}
	else {
		ValidSD = 0;
	}

}


void SD_card::SD_Record() {
	static unsigned long sd_timer = 0;

	if (( int32_t )( millis() - sd_timer ) >= 0 ) {
		sd_timer += 1000;

		dataFile = SD.open( "data.csv", FILE_WRITE ); //opens file to write too
		if ( dataFile ) {
			dataFile.println( F( "" ));

			/*
            //Bmp Data Group
            //Print #1
            dataFile.print(bmp.GetTemperature());
            dataFile.print(",");
            //Print #2
            dataFile.print(bmp.GetPressure());
            dataFile.print(",");
            //Print #3
            dataFile.print(bmp.GetAltitude());
            dataFile.print(",");
            //Print #4
            dataFile.print(bmp.GetMaxAltitude());
            dataFile.print(",");*/

			/*//Accelerometer Data Group
			//Print #5
			dataFile.print(x);
			dataFile.print(",");
			//Print #6
			dataFile.print(y);
			dataFile.print(",");
			//Print #7
			dataFile.print(z);
			dataFile.print(",");
			//Print #8
			dataFile.print(Orientation);
			dataFile.print(",");
			*/

			/*
            //GPS Data Group
            //Print #9
            dataFile.print(gps.GetLatitude());
            dataFile.print(",");
            //Print #10
            dataFile.print(gps.GetLongitude());
            dataFile.print(",");
            //Print #11
            dataFile.print(gps.GetAltitude());
            dataFile.print(",");
            //Print #12
            dataFile.print(gps.GetCourse());
            dataFile.print(",");
            //Print #13
            dataFile.print(gps.GetSpeed());
            dataFile.print(",");
            //Print #14
            dataFile.print(gps.GetSatellites());
            dataFile.print(",");
            //Print #16
            dataFile.print(gps.GetFull_Latitude());
            dataFile.print(",");
            //Print #17
            dataFile.print(gps.GetFull_Longitude());
            dataFile.print(",");
            //Print #18
            dataFile.print(gps.GetDate());
            dataFile.print(",");
            //Print #19
            dataFile.print(gps.GetDay());
            dataFile.print(",");
            //Print #20
            dataFile.print(gps.GetHour());
            dataFile.print(",");
			dataFile.print(gps.GetMinute());
            dataFile.print(",");
			dataFile.print(gps.GetSecond());
            dataFile.print(",");


            //Status Data Group
            //Print #21
            dataFile.print(status.IsValidBMP());
            dataFile.print(",");
            //Print #22
            dataFile.print(status.IsValidSD());
            dataFile.print(",");
            //Print #23
            dataFile.print(status.IsRising());
            dataFile.print(",");
            //Print #24
            dataFile.print(status.IsFalling());
            dataFile.print(",");
            //Print #25
            dataFile.print(status.IsLanded());
            dataFile.print(",");

            dataFile.print("\n");*/


			// //////////////////////////////////
			// dataFile.println(F(""));
			// dataFile.print(pins.GetsensorValue());
			// dataFile.print(F(","));
			// dataFile.print(F("\n"));
			//
			// DEBUG_PRINT(F(""));
			// DEBUG_PRINT(pins.GetsensorValue());
			// DEBUG_PRINT(F(","));
			// DEBUG_PRINT(F("\n"));
			// ///////////////////////////

			dataFile.close(); //Close the file to save
			dataFile.close(); //Close the file to save
			ValidSD = 1;
		}
		else {
			ValidSD = 0;
		}
	}
}

void SD_card::SD_arrayPass() {


}


bool SD_card::IsValidSD() {
	return ValidSD;
}