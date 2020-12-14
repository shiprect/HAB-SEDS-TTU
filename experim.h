/*


ORIGNAL code


#ifndef __GPS_H__
#define __GPS_H__

#include <stdint.h>

extern char gps_time[7];       // HHMMSS
extern uint32_t gps_seconds;   // seconds after midnight
extern char gps_date[7];       // DDMMYY
extern float gps_lat;
extern float gps_lon;
extern char gps_aprs_lat[9];
extern char gps_aprs_lon[10];
extern float gps_course;
extern float gps_speed;
extern float gps_altitude;

void gps_setup();
bool gps_decode(char c);
void gps_reset_parser();

#endif
*/

/////////////////////////
/*
   This sample code demonstrates how to use an array of TinyGPSCustom objects
   to monitor all the visible satellites.
   Satellite numbers, elevation, azimuth, and signal-to-noise ratio are not
   normally tracked by TinyGPS++, but by using TinyGPSCustom we get around this.
   The simple code also demonstrates how to use arrays of TinyGPSCustom objects,
   each monitoring a different field of the $GPGSV sentence.
   It requires the use of SoftwareSerial, and assumes that you have a
   4800-baud serial GPS device hooked up on pins 4(RX) and 3(TX).

static const int RXPin = 4, TXPin = 3;
static const uint32_t GPSBaud = 4800;

TinyGPSPlus gps;
SoftwareSerial ss(RXPin, TXPin);

  $GPGSV

  GPS Satellites in view

  eg. $GPGSV,3,1,11,03,03,111,00,04,15,270,00,06,01,010,00,13,06,292,00*74
      $GPGSV,3,2,11,14,25,170,00,16,57,208,39,18,67,296,40,19,40,246,00*74
      $GPGSV,3,3,11,22,42,067,42,24,14,311,43,27,05,244,00,,,,*4D
  1    = Total number of messages of this type in this cycle
  2    = Message number
  3    = Total number of SVs in view
  4    = SV PRN number
  5    = Elevation in degrees, 90 maximum
  6    = Azimuth, degrees from true north, 000 to 359
  7    = SNR, 00-99 dB (null when not tracking)
  8-11 = Information about second SV, same as field 4-7
  12-15= Information about third SV, same as field 4-7
  16-19= Information about fourth SV, same as field 4-7

static const int MAX_SATELLITES = 40;

TinyGPSCustom totalGPGSVMessages(gps, "GPGSV", 1); // $GPGSV sentence, first element
TinyGPSCustom messageNumber(gps, "GPGSV", 2);      // $GPGSV sentence, second element
TinyGPSCustom satsInView(gps, "GPGSV", 3);         // $GPGSV sentence, third element
TinyGPSCustom satNumber[4]; // to be initialized later
TinyGPSCustom elevation[4];
TinyGPSCustom azimuth[4];
TinyGPSCustom snr[4];

struct
{
  bool active;
  int elevation;
  int azimuth;
  int snr;
} sats[MAX_SATELLITES];

void setup()
{
  Serial.begin(115200);
  ss.begin(GPSBaud);

  Serial.println(F("SatelliteTracker.ino"));
  Serial.println(F("Monitoring satellite location and signal strength using TinyGPSCustom"));
  Serial.print(F("Testing TinyGPS++ library v. ")); Serial.println(TinyGPSPlus::libraryVersion());
  Serial.println(F("by Mikal Hart"));
  Serial.println();

  // Initialize all the uninitialized TinyGPSCustom objects
  for (int i=0; i<4; ++i)
  {
    satNumber[i].begin(gps, "GPGSV", 4 + 4 * i); // offsets 4, 8, 12, 16
    elevation[i].begin(gps, "GPGSV", 5 + 4 * i); // offsets 5, 9, 13, 17
    azimuth[i].begin(  gps, "GPGSV", 6 + 4 * i); // offsets 6, 10, 14, 18
    snr[i].begin(      gps, "GPGSV", 7 + 4 * i); // offsets 7, 11, 15, 19
  }
}

void loop()
{
  // Dispatch incoming characters
  if (ss.available() > 0)
  {
    gps.encode(ss.read());
    if (totalGPGSVMessages.isUpdated())
    {
      for (int i=0; i<4; ++i)
      {
        int no = atoi(satNumber[i].value());
        // Serial.print(F("SatNumber is ")); Serial.println(no);
        if (no >= 1 && no <= MAX_SATELLITES)
        {
          sats[no-1].elevation = atoi(elevation[i].value());
          sats[no-1].azimuth = atoi(azimuth[i].value());
          sats[no-1].snr = atoi(snr[i].value());
          sats[no-1].active = true;
        }
      }

      int totalMessages = atoi(totalGPGSVMessages.value());
      int currentMessage = atoi(messageNumber.value());
      if (totalMessages == currentMessage)
      {
        Serial.print(F("Sats=")); Serial.print(gps.satellites.value());
        Serial.print(F(" Nums="));
        for (int i=0; i<MAX_SATELLITES; ++i)
          if (sats[i].active)
          {
            Serial.print(i+1);
            Serial.print(F(" "));
          }
        Serial.print(F(" Elevation="));
        for (int i=0; i<MAX_SATELLITES; ++i)
          if (sats[i].active)
          {
            Serial.print(sats[i].elevation);
            Serial.print(F(" "));
          }
        Serial.print(F(" Azimuth="));
        for (int i=0; i<MAX_SATELLITES; ++i)
          if (sats[i].active)
          {
            Serial.print(sats[i].azimuth);
            Serial.print(F(" "));
          }

        Serial.print(F(" SNR="));
        for (int i=0; i<MAX_SATELLITES; ++i)
          if (sats[i].active)
          {
            Serial.print(sats[i].snr);
            Serial.print(F(" "));
          }
        Serial.println();

        for (int i=0; i<MAX_SATELLITES; ++i)
          sats[i].active = false;
      }
    }
  }
}
*/


/*
   This sample code tracks satellite elevations using TinyGPSCustom objects.
   Satellite numbers and elevations are not normally tracked by TinyGPS++, but
   by using TinyGPSCustom we get around this.
   It requires the use of SoftwareSerial and assumes that you have a
   4800-baud serial GPS device hooked up on pins 4(RX) and 3(TX).

static const int RXPin = 4, TXPin = 3;
static const uint32_t GPSBaud = 4800;
static const int MAX_SATELLITES = 40;
static const int PAGE_LENGTH = 40;

TinyGPSPlus gps;
SoftwareSerial ss(RXPin, TXPin);

TinyGPSCustom totalGPGSVMessages(gps, "GPGSV", 1); // $GPGSV sentence, first element
TinyGPSCustom messageNumber(gps, "GPGSV", 2);      // $GPGSV sentence, second element
TinyGPSCustom satNumber[4]; // to be initialized later
TinyGPSCustom elevation[4];
bool anyChanges = false;
unsigned long linecount = 0;

struct
{
  int elevation;
  bool active;
} sats[MAX_SATELLITES];

void setup()
{
  // Initialize all the uninitialized TinyGPSCustom objects
  for (int i=0; i<4; ++i)
  {
    satNumber[i].begin(gps, "GPGSV", 4 + 4 * i); // offsets 4, 8, 12, 16
    elevation[i].begin(gps, "GPGSV", 5 + 4 * i); // offsets 5, 9, 13, 17
  }
}

void loop()
{
  // Dispatch incoming characters
  if (ss.available() > 0)
  {
    gps.encode(ss.read());

    if (totalGPGSVMessages.isUpdated())
    {
      for (int i=0; i<4; ++i)
      {
        int no = atoi(satNumber[i].value());
        if (no >= 1 && no <= MAX_SATELLITES)
        {
          int elev = atoi(elevation[i].value());
          sats[no-1].active = true;
          if (sats[no-1].elevation != elev)
          {
            sats[no-1].elevation = elev;
            anyChanges = true;
          }
        }
      }

      int totalMessages = atoi(totalGPGSVMessages.value());
      int currentMessage = atoi(messageNumber.value());
      if (totalMessages == currentMessage && anyChanges)
      {
        if (linecount++ % PAGE_LENGTH == 0)
          printHeader();
        TimePrint();
        for (int i=0; i<MAX_SATELLITES; ++i)
        {
          Serial.print(F(" "));
          if (sats[i].active)
            IntPrint(sats[i].elevation, 2);
          else
            Serial.print(F("   "));
          sats[i].active = false;
        }
        Serial.println();
        anyChanges = false;
      }
    }
  }
}

void IntPrint(int n, int len)
{
  int digs = n < 0 ? 2 : 1;
  for (int i=10; i<=abs(n); i*=10)
    ++digs;
  while (digs++ < len)
    Serial.print(F(" "));
  Serial.print(n);
  Serial.print(F(" "));
}

void TimePrint()
{
  if (gps.time.isValid())
  {
    if (gps.time.hour() < 10)
      Serial.print(F("0"));
    Serial.print(gps.time.hour());
    Serial.print(F(":"));
    if (gps.time.minute() < 10)
      Serial.print(F("0"));
    Serial.print(gps.time.minute());
    Serial.print(F(":"));
    if (gps.time.second() < 10)
      Serial.print(F("0"));
    Serial.print(gps.time.second());
    Serial.print(F(" "));
  }
  else
  {
    Serial.print(F("(unknown)"));
  }
}

void printHeader()
{
  Serial.println();
  Serial.print(F("Time     "));
  for (int i=0; i<MAX_SATELLITES; ++i)
  {
    Serial.print(F(" "));
    IntPrint(i+1, 2);
  }
  Serial.println();
  Serial.print(F("---------"));
  for (int i=0; i<MAX_SATELLITES; ++i)
    Serial.print(F("----"));
  Serial.println();
}
*/

/*
void loop()
{
  // Dispatch incoming characters
  while (ss.available() > 0)
    gps.encode(ss.read());


  else if (millis() - last > 5000)
  {
    Serial.println();
    if (gps.location.isValid())
    {
      static const double LONDON_LAT = 51.508131, LONDON_LON = -0.128002;
      double distanceToLondon =
        TinyGPSPlus::distanceBetween(
          gps.location.lat(),
          gps.location.lng(),
          LONDON_LAT,
          LONDON_LON);
      double courseToLondon =
        TinyGPSPlus::courseTo(
          gps.location.lat(),
          gps.location.lng(),
          LONDON_LAT,
          LONDON_LON);

      Serial.print(F("LONDON     Distance="));
      Serial.print(distanceToLondon/1000, 6);
      Serial.print(F(" km Course-to="));
      Serial.print(courseToLondon, 6);
      Serial.print(F(" degrees ["));
      Serial.print(TinyGPSPlus::cardinal(courseToLondon));
      Serial.println(F("]"));
    }

    Serial.print(F("DIAGS      Chars="));
    Serial.print(gps.charsProcessed());
    Serial.print(F(" Sentences-with-Fix="));
    Serial.print(gps.sentencesWithFix());
    Serial.print(F(" Failed-checksum="));
    Serial.print(gps.failedChecksum());
    Serial.print(F(" Passed-checksum="));
    Serial.println(gps.passedChecksum());

    if (gps.charsProcessed() < 10)
      Serial.println(F("WARNING: No GPS data.  Check wiring."));

    last = millis();
    Serial.println();
  }
}
 */

 /*
void loop()
{
  static const double LONDON_LAT = 51.508131, LONDON_LON = -0.128002;



  unsigned long distanceKmToLondon =
    (unsigned long)TinyGPSPlus::distanceBetween(
      gps.location.lat(),
      gps.location.lng(),
      LONDON_LAT,
      LONDON_LON) / 1000;
  printInt(distanceKmToLondon, gps.location.isValid(), 9);

  double courseToLondon =
    TinyGPSPlus::courseTo(
      gps.location.lat(),
      gps.location.lng(),
      LONDON_LAT,
      LONDON_LON);

  printFloat(courseToLondon, gps.location.isValid(), 7, 2);

  const char *cardinalToLondon = TinyGPSPlus::cardinal(courseToLondon);

  printStr(gps.location.isValid() ? cardinalToLondon : "*** ", 6);

  printInt(gps.charsProcessed(), true, 6);
  printInt(gps.sentencesWithFix(), true, 10);
  printInt(gps.failedChecksum(), true, 9);
  Serial.println();

  smartDelay(1000);

  if (millis() > 5000 && gps.charsProcessed() < 10)
    Serial.println(F("No GPS data received: check wiring"));
}








/*
void setup() {
    declarations();

    //for the LED requirements
    elapsedMillis T_ledTrack;
    bool led_status = 1;

    //the preflight loop, runs until liftoff
    elapsedMillis T_preLiftoff;
    elapsedMillis T_sinceLiftoff;
    while(!status.liftoff) {
        bmp_get_data();
        imu_get_data();
        //Serial.println("liftoff");
        data_log(T_preLiftoff, T_sinceStart);
        status_liftoff(T_sinceLiftoff);
        if(T_ledTrack >= 200) {
            led_status = !led_status;
            T_ledTrack = 0;
        }
    }

    //launch has occured, runs until burnout
    elapsedMillis T_sinceBurnout;
    while(!status.burnout) {
        bmp_get_data();
        imu_get_data();
        //Serial.println("burnout");
        data_log(T_sinceLiftoff, T_sinceStart);
        status_burnout(T_sinceBurnout);
    }

    //wait for two seconds before moving on to the main control loop(contest rules)
    elapsedMillis T_waiting;
    while(T_waiting < wait_time) {
        bmp_get_data();
        imu_get_data();
        //Serial.println("waiting");
        data_log(T_sinceBurnout, T_sinceStart);
    }

    //do these to setup for control functions after the burnout wait period
    T_sinceControl = 0;
    T_sincePulsed = Control_period;
    T_sinceHold = 0;
    T_lastTime = 0;
    T_sinceApogee = 0;
    T_sinceFalling = 0;
    T_sinceLoop = 0;
    current_command = 0;
}


void loop() {
    bmp_get_data();
    imu_get_data();
    data_log(T_sinceControl, T_sinceStart);

    control();
    valveWrite();

    checkApogee();
}

void checkApogee() {
    //CHANGE THE NUMBER FOR APOGEE TIMING//
    if(T_sinceLoop >= 20000) {
        elapsedMillis T_ledTrack;
        bool led_status = 1;
        while(1) {
            bmp_get_data();
            imu_get_data();
            data_log(T_sinceApogee, T_sinceStart);

            if(T_ledTrack >= 500) {
                led_status = !led_status;
            }

            if(dumpTime >= 12000) {
                digitalWrite(valve_dump, LOW);
            }
        }
    } else {
        T_sinceApogee = 0;
    }
}

void data_log(elapsedMillis current_time, elapsedMillis global_time) {
    if(T_sinceLogged >= log_period_T) {

        sd_write(current_time, global_time);
        //print_stuff(current_time, global_time);

        T_sinceLogged = 0;
    }
}

    pinMode(SD_chipSelect, OUTPUT);
    if(!SD.begin(SD_chipSelect)) {
        Serial.println("initialization failed");
        delay(500);
    }
    sd_setup();
*/



/*
static elapsedMillis T_sinceApogee;
static elapsedMillis T_sinceFalling;

static elapsedMillis T_sinceLogged;
static elapsedMillis T_statuscheck;
static elapsedMillis T_sinceStart;
static elapsedMillis T_sinceEmergency;


struct status_set {
    bool liftoff = 0;
    bool burnout = 0;
    bool falling = 0;
    bool emergency = 0;
    bool active_valves = 0;
    bool IMU_connected = 0;
    bool BMP_connected = 0;
};
extern struct status_set status; //the struct holding the status of all systems


#define lift_check_T 50
#define burn_check_T 50
#define apo_check_T 50
#define fall_check_T 50
#define liftoff_Gforce_check 6
#define burnout_Gforce_check 3
//#define apogee_velocity_check 2.5 //check should be about 2.5 m/s


//perform status check and update flags, will disbale control and trigger landing loop code when apogee has been reached, will activate emergency dump valve if given signal by ground, etc.
void status_liftoff(elapsedMillis T_sinceLiftoff);
void status_burnout(elapsedMillis T_sinceBurnout);
void status_falling(elapsedMillis T_sinceFalling);


void status_liftoff(elapsedMillis T_sinceLiftoff) {
    if(((abs(imu_data.aSqrt)) <= liftoff_Gforce_check)) {
        T_sinceLiftoff = 0;
        imu_data.theta_roll = 0;
        imu_data.omega_roll_last = 0;
        //data.setNorth();
    } else {
        if(T_sinceLiftoff >= lift_check_T)
            status.liftoff = true;
    }
}

void status_burnout(elapsedMillis T_sinceBurnout) {
    if((abs(imu_data.aSqrt)) >= burnout_Gforce_check){
      T_sinceBurnout = 0;
    } else {
      if(T_sinceBurnout >= burn_check_T)
        status.burnout = true;
    }
}

void status_falling(elapsedMillis T_sinceFalling) {
    if(bmp.altitude < (bmp.max_altitude-100)) {
        T_sinceFalling = 0;
    } else {
        if (T_sinceFalling > fall_check_T) {
            status.falling = true;
        }
    }
}

*/




// #ifndef H_h
// #define H_h
 // struct globe
  // {
    // float x;
    // float y;
    // float z;
    // float accx;
    // float accy;
    // float accz;
  // };
// void SPI_SETUP();
// void Accelerometer_Setup();
// void accel();
// void readVal();



/*

//#include "SparkFunLIS3DH.h"
#include "Wire.h"
#include "SPI.h"
#include "H.h"

LIS3DH myIMU; //Default constructor is I2C, addr 0x19.
void setup() {
Serial.begin(9600);
  delay(1000); //relax...
  Serial.println("Processor came out of reset.\n");

  //Call .begin() to configure the IMU
  myIMU.begin();
}

void loop() {
   #include "H.h"
 
//*************************************************************************************************************
//Writes gyro to serial print  
  Serial.print("\nAccelerometer:\n");
  Serial.print(" X = ");
  Serial.println(myIMU.readFloatAccelX(), 4);
  Serial.print(" Y = ");
  Serial.println(myIMU.readFloatAccelY(), 4);
  Serial.print(" Z = ");
  Serial.println(myIMU.readFloatAccelZ(), 4);

  delay(500);
//**************************************************************************************************************   
void SPI_SETUP();
void Accelerometer_Setup();
void accel();
void readVal();

globe AC;
Serial.print("Accel X = ");
  Serial.print(AC.accx);
  Serial.print(" Accel Y = ");
  Serial.print(AC.accy);
  Serial.print(" Accel Z = ");
  Serial.println(AC.accz);
delay(100);
}


*/


/*
#include <Adafruit_Sensor.h>
#include <Wire.h>

const long interval = 1000;   // interval at which to call the function (milliseconds)

unsigned long previousMillis = 0;



void loop() {

        unsigned long currentMillis = millis();
        int Time = currentMillis * .001;


        if (currentMillis - previousMillis >= interval) {
                previousMillis = currentMillis;
                Serial.print(F("Time = ")); Serial.print(Time);
                Serial.println(F(""));

                dataFile = SD.open(F("data.txt"),FILE_WRITE);
                dataFile.print(Time);
                dataFile.print(F(","));
                dataFile.close();
        }

}

// void gpsData() {

        // float Latitude = tinyGPS.location.lat(), Longitude = tinyGPS.location.lng();
        // double gpsAltitude = tinyGPS.altitude.feet(), Course = tinyGPS.course.deg(), Speed = tinyGPS.speed.mph();
        // int Satellites = tinyGPS.satellites.value();

        // Serial.print(F("Lat: ")); Serial.println(Latitude, 6);
        // Serial.print(F("Long: ")); Serial.println(Longitude, 6);
        // Serial.print(F("Alt: ")); Serial.println(gpsAltitude);
        // Serial.print(F("Course: ")); Serial.println(Course);
        // Serial.print(F("Speed: ")); Serial.println(Speed);
        // Serial.print(F("Satillites: ")); Serial.println(Satellites);
        // Serial.println();

        // dataFile = SD.open(F("data.txt"),FILE_WRITE);
        // dataFile.print(Latitude, 6);
        // dataFile.print(F(","));
        // dataFile.print(Longitude, 6);
        // dataFile.print(F(","));
        // dataFile.print(gpsAltitude);
        // dataFile.print(F(","));
        // dataFile.print(Course);
        // dataFile.print(F(","));
        // dataFile.print(Speed);
        // dataFile.print(F(","));
        // dataFile.print(Satellites);
        // dataFile.println(F(""));
        // dataFile.close();

// }

/////////////////////////////////////////////////////////////////////////////////////////////
// struct bmp_data bmp;


// #include <Status.h>
// struct status_set status; //the struct holding the status of all systems

// void setup() {
    // elapsedMillis T_preLiftoff;
    // elapsedMillis T_sinceLiftoff;
    // while(!status.liftoff) {
        // bmp_get_data();
        // imu_get_data();
        // data_log(T_preLiftoff, T_sinceStart);
        // status_liftoff(T_sinceLiftoff);
        // if(T_ledTrack >= 200) {
            // led_status = !led_status;
            // T_ledTrack = 0;
        // }
    // }

    // elapsedMillis T_sinceBurnout;
    // while(!status.burnout) {
        // bmp_get_data();
        // imu_get_data();
        // data_log(T_sinceLiftoff, T_sinceStart);
        // status_burnout(T_sinceBurnout);
    // }

    // elapsedMillis T_waiting;
    // while(T_waiting < wait_time) {
        // bmp_get_data();
        // imu_get_data();
        // data_log(T_sinceBurnout, T_sinceStart);
    // }

    // T_sinceControl = 0;
    // T_sincePulsed = Control_period;
    // T_sinceHold = 0;
    // T_lastTime = 0;
    // T_sinceApogee = 0;
    // T_sinceFalling = 0;
    // T_sinceLoop = 0;
    // current_command = 0;
// }


// void loop() {
    // bmp_get_data();
    // imu_get_data();
    // data_log(T_sinceControl, T_sinceStart);

    // control();
    // valveWrite();

    // checkApogee();

    // /*
    // T_sinceEmergency = 0;
    // while(status.emergency) {
        // bmp_get_data();
        // imu_get_data();
        // digitalWrite(valve_dump, HIGH);
        // data_log(T_sinceEmergency, T_sinceStart);
    // }
    // */
// }


// void checkApogee() {
    // if(T_sinceLoop >= 20000) {
        // elapsedMillis T_ledTrack;
        // bool led_status = 1;
        // while(1) {
            // bmp_get_data();
            // imu_get_data();
            // data_log(T_sinceApogee, T_sinceStart);

            // if(T_ledTrack >= 500) {
                // led_status = !led_status;
            // }
        // }
    // } else {
        // T_sinceApogee = 0;
    // }
// }

// void data_log(elapsedMillis current_time, elapsedMillis global_time) {
    // if(T_sinceLogged >= log_period_T) {

        // sd_write(current_time, global_time);

        // T_sinceLogged = 0;
    // }
// }

// void declarations() {
    // pinMode(SD_chipSelect, OUTPUT);
    // if(!SD.begin(SD_chipSelect)) {
        // Serial.println("initialization failed");
        // delay(500);
    // }
    // sd_setup();
// }
/////////////////////////////////////////////////////////////////////////////////////////////
// const int ChipSelectPin = BUILTIN_SDCARD;
// #define SD_chipSelect BUILTIN_SDCARD
// extern File myFile;


// void status_liftoff(elapsedMillis T_sinceLiftoff) {
    // if(((abs(imu_data.aSqrt)) <= liftoff_Gforce_check)) {
        // T_sinceLiftoff = 0;
        // imu_data.theta_roll = 0;
        // imu_data.omega_roll_last = 0;
    // } else {
        // if(T_sinceLiftoff >= lift_check_T)
            // status.liftoff = true;
    // }
// }

// void status_burnout(elapsedMillis T_sinceBurnout) {
    // if((abs(imu_data.aSqrt)) >= burnout_Gforce_check){
      // T_sinceBurnout = 0;
    // } else {
      // if(T_sinceBurnout >= burn_check_T)
        // status.burnout = true;
    // }
// }

// void status_falling(elapsedMillis T_sinceFalling) {
    // if(bmp.altitude < (bmp.max_altitude-100)) {
        // T_sinceFalling = 0;
    // } else {
        // if (T_sinceFalling > fall_check_T) {
            // status.falling = true;
        // }
    // }
// }

// #ifndef _STATUS_H_
// #define _STATUS_H_

// #include "Global.h"
// #include <IMU.h>
// #include <BMP085.h>


// struct status_set {
    // bool liftoff = 0;
    // bool burnout = 0;
    // bool falling = 0;
    // bool emergency = 0;
    // bool active_valves = 0;
    // bool IMU_connected = 0;
    // bool BMP_connected = 0;
// };
// extern struct status_set status; //the struct holding the status of all systems


// #define lift_check_T 50
// #define burn_check_T 50
// #define apo_check_T 50
// #define fall_check_T 50
// #define liftoff_Gforce_check 6
// #define burnout_Gforce_check 3

// void status_liftoff(elapsedMillis T_sinceLiftoff);
// void status_burnout(elapsedMillis T_sinceBurnout);
// void status_falling(elapsedMillis T_sinceFalling);
// void flight_plan();


// /*    //GROUP 1 DATA
    // float setpoint = 0.0;
    // float last_setpoint = 0.0;
    // int hold_time = 0;
    // int global_time = 0; //the synced timing
    // int local_time = 0; //timing of the current system state

    // double pressure;
    // double temperature;
    // double altitude;
    // double max_altitude;
// */
// /*    //GROUP 2 DATA
    // float aX;
    // float aY;
    // float aZ;
    // float aSqrt;
    // float gX;
    // float gY;
    // float gZ;
    // float mDirection;
    // float mX;
    // float mY;
    // float mZ;
// */
// /*  //GROUP 3 DATA
    // int current_command;

    // float error;
    // float d_error;
    // float d_error_sum;
    // float d_error_cnt;

    // float omega_roll;
    // float theta_roll;

    // bool liftoff = 0;
    // bool burnout = 0;
    // bool falling = 0;
    // bool emergency = 0;
    // bool is_done = 0;
    // bool roll_direction = 0;
    // bool active_valves = 0;

    // bool IMU_connected = 0;
    // bool BMP_connected = 0;
// */





/*************************************

*************************************/

/*
void printFloat(double number, int digits)
{
  // Handle negative numbers
  if (number < 0.0) {
     Serial.print('-');
     number = -number;
  }

  // Round correctly so that print(1.999, 2) prints as "2.00"
  double rounding = 0.5;
  for (uint8_t i=0; i<digits; ++i)
    rounding /= 10.0;
  
  number += rounding;

  // Extract the integer part of the number and print it
  unsigned long int_part = (unsigned long)number;
  double remainder = number - (double)int_part;
  Serial.print(int_part);

  // Print the decimal point, but only if there are digits beyond
  if (digits > 0)
    Serial.print("."); 

  // Extract digits from the remainder one at a time
  while (digits-- > 0) {
    remainder *= 10.0;
    int toPrint = int(remainder);
    Serial.print(toPrint);
    remainder -= toPrint;
  }
}
*/


/* 
void CheckLEDs(void)
{
  if (millis() >= NextLEDs)
  {
    static byte Flash=0;
    
    // This would normally be the only LED for status (i.e. no OK or WARN LEDs)
    if (GPS.Altitude > 1000)
    {
      // All off
      ControlLEDs(0,0,0);
    }
    else if ((GPS.FixType == 3) && (GPS.Satellites >= 4))
    {
      ControlLEDs(Flash, Flash, 0);
    }
    else
    {
      ControlLEDs(1, 0, Flash);
    }       
    
    NextLEDs = millis() + 500L;
    Flash = 1-Flash;
  }
}
*/



    /*if (APRS_SLOT >= 0) {
        //transmission_timer = millis() //+ 1000 * (APRS_PERIOD - (gps_seconds + APRS_PERIOD - APRS_SLOT) % APRS_PERIOD);
        transmission_timer = millis() + (1000L * APRS_SLOT);
    } else {
        transmission_timer = millis();
    }*/