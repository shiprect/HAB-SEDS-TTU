/*



/////
//#define DEBUGPRINT(_fmt, ...)  fprintf(stderr, "[file %s, line %d]: " _fmt, __FILE__, __LINE__, __VA_ARGS__)

//  DEBUGPRINT("hey, x=%d\n", x);


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
*/

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

/*// include the SD library:
#include <SPI.h>
#include <SD.h>

// set up variables using the SD utility library functions:
Sd2Card card;
SdVolume volume;
SdFile root;

// change this to match your SD shield or module;
// Arduino Ethernet shield: pin 4
// Adafruit SD shields and modules: pin 10
// Sparkfun SD shield: pin 8
// MKRZero SD: SDCARD_SS_PIN
// VELLEMAN I/O VMA304: SD shield: pin 10 
const int chipSelect = 10;

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }


  Serial.print("\nInitializing SD card...");

  // we'll use the initialization code from the utility libraries
  // since we're just testing if the card is working!
  if (!card.init(SPI_HALF_SPEED, chipSelect)) {
    Serial.println("initialization failed. Things to check:");
    Serial.println("* is a card inserted?");
    Serial.println("* is your wiring correct?");
    Serial.println("* did you change the chipSelect pin to match your shield or module?");
    return;
  } else {
    Serial.println("Wiring is correct and a card is present.");
  }

  // print the type of card
  Serial.print("\nCard type: ");
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
    return;
  }


  // print the type and size of the first FAT-type volume
  uint32_t volumesize;
  Serial.print("\nVolume type is FAT");
  Serial.println(volume.fatType(), DEC);
  Serial.println();

  volumesize = volume.blocksPerCluster();    // clusters are collections of blocks
  volumesize *= volume.clusterCount();       // we'll have a lot of clusters
  volumesize *= 512;                            // SD card blocks are always 512 bytes
  Serial.print("Volume size (bytes): ");
  Serial.println(volumesize);
  Serial.print("Volume size (Kbytes): ");
  volumesize /= 1024;
  Serial.println(volumesize);
  Serial.print("Volume size (Mbytes): ");
  volumesize /= 1024;
  Serial.println(volumesize);


  Serial.println("\nFiles found on the card (name, date and size in bytes): ");
  root.openRoot(volume);

  // list all files in the card with date and size
  root.ls(LS_R | LS_DATE | LS_SIZE);
}

void printFilenames(void ) { // function printFilenames
  ////find files in SD card
  root = SD.open("/");
  while (true) {
    File entry =  root.openNextFile();
    if (! entry) {
      break;// no more files
    }
    Serial.println(entry.name());
    entry.close();
  }
}
*/