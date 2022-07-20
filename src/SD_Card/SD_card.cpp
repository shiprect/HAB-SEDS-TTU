#include "SD_card.hpp"
#include <Arduino.h>
#include <SD.h>
#include <SPI.h>
///order
//bmp
//gps
//status


void SD_card::SD_Setup() {

    if (!SD.begin(CS)) {
        ValidSD = 0;
    } else {
        ValidSD = 1;
    }

    dataFile = SD.open("data.csv",FILE_WRITE);
    if(dataFile) {
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
	else{
		ValidSD = 0;
	}

}


void SD_card::SD_Record() {
    static unsigned long sd_timer = 0;

    if ((int32_t) (millis() - sd_timer) >= 0) {
        sd_timer += 1000;

        
    }
}

void SD_card::SD_arrayPass(int *x, int array_Size) {   // Add stuff about passing to the array here 
		
		dataFile = SD.open("data.csv", FILE_WRITE); //opens file to write too
        if(dataFile){
			
			for (int ii = 0; ii < numberofSamples; ii++){ // FIXME:: formatting issue when outputted to DATA.csv 
			dataFile.println(x[ii]); // Prints out a singular one 
			dataFile.print(F(","));
		}

		dataFile.println("");
		
	    // dataFile.print(pins.GetsensorValue());  
	   //  dataFile.print(F(","));

            dataFile.close(); //Close the file to save
            ValidSD = 1;
        } else {
            ValidSD = 0;
        }
		
}


bool SD_card::IsValidSD() {
	
  Serial.print("\nInitializing SD card...");

  // we'll use the initialization code from the utility libraries
  // since we're just testing if the card is working!
  if (!card.init(SPI_HALF_SPEED, CS)) {  // CS is chipSelect
    Serial.println("initialization failed. Things to check:");
    Serial.println("* is a card inserted?");
    Serial.println("* is your wiring correct?");
    Serial.println("* did you change the chipSelect pin to match your shield or module?");
    while (1);
  } else {
    Serial.println("Wiring is correct and a card is present.");
  }

  // print the type of card
  Serial.println();
  Serial.print("Card type:         ");
  switch (card.type()) {
    case SD_CARD_TYPE_SD1:
      Serial.println("SD1");
      break;
    case SD_CARD_TYPE_SD2:
      Serial.println("SD2");
      break;
    case SD_CARD_TYPE_SDHC:
      Serial.println("SDHC");
      break;
    default:
      Serial.println("Unknown");
  }

  // Now we will try to open the 'volume'/'partition' - it should be FAT16 or FAT32
  if (!volume.init(card)) {
    Serial.println("Could not find FAT16/FAT32 partition.\nMake sure you've formatted the card");
    while (1);
  }

  Serial.print("Clusters:          ");
  Serial.println(volume.clusterCount());
  Serial.print("Blocks x Cluster:  ");
  Serial.println(volume.blocksPerCluster());

  Serial.print("Total Blocks:      ");
  Serial.println(volume.blocksPerCluster() * volume.clusterCount());
  Serial.println();

  // print the type and size of the first FAT-type volume
  uint32_t volumesize;
  Serial.print("Volume type is:    FAT");
  Serial.println(volume.fatType(), DEC);

  volumesize = volume.blocksPerCluster();    // clusters are collections of blocks
  volumesize *= volume.clusterCount();       // we'll have a lot of clusters
  volumesize /= 2;                           // SD card blocks are always 512 bytes (2 blocks are 1KB)
  Serial.print("Volume size (Kb):  ");
  Serial.println(volumesize);
  Serial.print("Volume size (Mb):  ");
  volumesize /= 1024;
  Serial.println(volumesize);
  Serial.print("Volume size (Gb):  ");
  Serial.println((float)volumesize / 1024.0);

  Serial.println("\nFiles found on the card (name, date and size in bytes): ");
  //root.openRoot(volume);

  // list all files in the card with date and size
  //root.ls(LS_R | LS_DATE | LS_SIZE);
	
    return ValidSD;
}