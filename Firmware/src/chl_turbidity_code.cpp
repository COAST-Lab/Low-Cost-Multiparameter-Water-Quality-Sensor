/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "/Users/jessiewynne/chl_turbidity_code/src/chl_turbidity_code.ino"
#include <Adafruit_AS7341.h>
#include <Adafruit_AW9523.h>
#include "RTClibrary.h"
#include <SdFat.h>

void setup();
void loop();
void fileprintresults(SdFat &sd, RTC_PCF8523 &rtc);
void serialprintresults(RTC_PCF8523 &rtc);
#line 6 "/Users/jessiewynne/chl_turbidity_code/src/chl_turbidity_code.ino"
Adafruit_AS7341 as7341;
Adafruit_AW9523 aw;
RTC_PCF8523 rtc;
File myFile;

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
const int SD_CHIP_SELECT = D5;

// Define an array of pin numbers for each LED
const uint8_t LedPins[] = {0, 10}; // Define LedPin 10 as LedPins[0] and LedPin 0 as LedPins[1]

const int NumLEDs = sizeof(LedPins) / sizeof(LedPins[0]);

int LEDbright = 255;
int LEDdim = 0;

SdFat SD;

SYSTEM_THREAD(ENABLED);
SYSTEM_MODE(SEMI_AUTOMATIC);

void setup() {
  Serial.begin(9600);

  // Wait for communication with the host computer serial monitor
  while (!Serial) {
    delay(1);
  }

  if (!as7341.begin(0x39)){
    Serial.println("Could not find AS7341");
    while (1) { delay(10); }
  }

  as7341.setATIME(255);      
  as7341.setASTEP(999);
  as7341.setGain(AS7341_GAIN_128X);

  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }

  if (! rtc.initialized()) {
    Serial.println("RTC is NOT running!");
  }

  if (! aw.begin(0x58)) {
    Serial.println("AW9523 not found? Check wiring!");
    while (1) delay(10);  // halt forever
  }

  Serial.println("AW9523 found!");

  for (int i = 0; i < NumLEDs; i++) {
    aw.pinMode(LedPins[i], AW9523_LED_MODE);
  }

  SD.begin(SD_CHIP_SELECT);

  File file = SD.open("2_15_24_700ms_128x_through_hole_dilutions.csv", FILE_WRITE);

  if (file) {
    file.println("Date and Time,ASTEP,ATIME,GAIN,LED Status,LED Intensity,Test,Seconds,Milliseconds,Type,F1 (Basic),F2 (Basic),F3 (Basic),F4 (Basic),F5 (Basic),F6 (Basic),F7 (Basic),F8 (Basic),Clear (Basic),NIR (Basic),Type,F1 (Raw),F2 (Raw),F3 (Raw),F4 (Raw),F5 (Raw),F6 (Raw),F7 (Raw),F8 (Raw),Clear (Raw),NIR (Raw)"); // Headers
    file.close();
  } else {
    Serial.println(F("Error opening file!"));
  }
}

void loop() {
  unsigned long ledDuration1 = 6000; // Set the duration for LED 0 in milliseconds
  unsigned long ledDuration2 = 6000; // Set the duration for LED 10 in milliseconds

  // Turn on LED 0 for a specified duration
  unsigned long startTime1 = millis();
  while (millis() - startTime1 < ledDuration1) {
    aw.analogWrite(LedPins[0], 255); // Turn on LED 0
    aw.analogWrite(LedPins[1], 0);    // Turn off LED 10
    fileprintresults(SD, rtc); // Take measurements and write to file
    serialprintresults(rtc);
    aw.analogWrite(LedPins[0], 0);

  Serial.print("LED 0 off");
  
  // Delay before turning on LED 10
  delay(1000); // Adjust delay as needed

  // Turn on LED 10 for a specified duration
  unsigned long startTime2 = millis();
  while (millis() - startTime2 < ledDuration2) {
    aw.analogWrite(LedPins[0], 0);    // Turn off LED 0
    aw.analogWrite(LedPins[1], 255); // Turn on LED 10
    fileprintresults(SD, rtc); // Take measurements and write to file
    serialprintresults(rtc);
  }

  // Turn off LED 10
  aw.analogWrite(LedPins[1], 0);
  Serial.println("LED 10 off");

  // Halt forever
  while (1) {
    delay(1);
  }
}

}


void fileprintresults(SdFat &sd, RTC_PCF8523 &rtc) {
  File file = sd.open("2_15_24_700ms_128x_through_hole_dilutions.csv", FILE_WRITE);
  DateTime now = rtc.now();

  uint16_t readings[12];
  float counts[12];

  if (!as7341.readAllChannels(readings)){
    Serial.println("Error reading all channels!");
    return;
  }

  for(uint8_t i = 0; i < 12; i++) {
    if(i == 4 || i == 5) continue;
    counts[i] = as7341.toBasicCounts(readings[i]);
  }

  if (file) {
    unsigned long currentTime = millis();
    unsigned long onTime = 60000;
    unsigned long offTime = 0;

    unsigned long elapsedTime = currentTime % (onTime + offTime);

    bool isLedOn = (elapsedTime < onTime);
    aw.analogWrite(LedPins[0], isLedOn ? LEDbright : LEDdim);
    
    // Write data to file
    file.print(now.year(), DEC);
    file.print('/');
    file.print(now.month(), DEC);
    file.print('/');
    file.print(now.day(), DEC);
    file.print(" (");
    file.print(daysOfTheWeek[now.dayOfTheWeek()]);
    file.print(") ");
    file.print(now.hour(), DEC);
    file.print(':');
    file.print(now.minute(), DEC);
    file.print(':');
    file.print(now.second(), DEC);
    file.print(',');
    file.print(as7341.getASTEP());
    file.print(',');
    file.print(as7341.getATIME());
    file.print(',');
    file.print(as7341.getGain());
    file.print(',');
    file.print(isLedOn ? "LED ON" : "LED OFF");
    file.print(',');
    file.print(isLedOn ? "255" : "0"); // Record the LED intensity (100 when on, 0 when off)
    file.print(',');
    file.print("6.0");
    file.print(',');
    file.print(millis() / 1000);
    file.print(','); 
    file.print(millis());
    file.print(',');
    file.print("BASIC COUNTS");
    file.print(',');
    file.print(counts[0]);
    file.print(',');
    file.print(counts[1]);
    file.print(',');
    file.print(counts[2]);
    file.print(',');
    file.print(counts[3]);
    file.print(',');
    file.print(counts[6]);
    file.print(',');
    file.print(counts[7]);
    file.print(',');
    file.print(counts[8]);
    file.print(',');
    file.print(counts[9]);
    file.print(',');
    file.print(counts[10]);
    file.print(',');
    file.print(counts[11]);
    file.print(',');
    file.print("RAW VALUES");
    file.print(',');
    file.print(readings[0]);
    file.print(',');
    file.print(readings[1]);
    file.print(',');
    file.print(readings[2]);
    file.print(',');
    file.print(readings[3]);
    file.print(',');
    file.print(readings[6]);
    file.print(',');
    file.print(readings[7]);
    file.print(',');
    file.print(readings[8]);
    file.print(',');
    file.print(readings[9]);
    file.print(',');
    file.print(readings[10]);
    file.print(',');
    file.println(readings[11]);
    
    file.close();
  }
  else {
    Serial.println(F("Error opening file!"));
  }
}

void serialprintresults(RTC_PCF8523 &rtc) {
  DateTime now = rtc.now();

  uint16_t readings[12];
  float counts[12];

  if (!as7341.readAllChannels(readings)){
    Serial.println("Error reading all channels!");
    return;
  }

  for(uint8_t i = 0; i < 12; i++) {
    if(i == 4 || i == 5) continue;
    counts[i] = as7341.toBasicCounts(readings[i]);
  }

  Serial.print(',');
  Serial.println(millis() / 1000);
  Serial.print("F1 415nm : ");
  Serial.print(counts[0]);
  Serial.print("  ");
  Serial.print("Raw Value : ");
  Serial.println(readings[0]);
  Serial.print("F2 445nm : ");
  Serial.print(counts[1]);
  Serial.print("  ");
  Serial.print("Raw Value : ");
  Serial.println(readings[1]);
  Serial.print("F3 480nm : ");
  Serial.print(counts[2]);
  Serial.print("  ");
  Serial.print("Raw Value : ");
  Serial.println(readings[2]);
  Serial.print("F4 515nm : ");
  Serial.print(counts[3]);
  Serial.print("  ");
  Serial.print("Raw Value : ");
  Serial.println(readings[3]);
  Serial.print("F5 555nm : ");

  // again, we skip the duplicates  

  Serial.print(counts[6]);
  Serial.print("  ");
  Serial.print("Raw Value : ");
  Serial.println(readings[6]);
  Serial.print("F6 590nm : ");
  Serial.print(counts[7]);
  Serial.print("  ");
  Serial.print("Raw Value : ");
  Serial.println(readings[7]);
  Serial.print("F7 630nm : ");
  Serial.print(counts[8]);
  Serial.print("  ");
  Serial.print("Raw Value : ");
  Serial.println(readings[8]);
  Serial.print("F8 680nm : ");
  Serial.print(counts[9]);
  Serial.print("  ");
  Serial.print("Raw Value : ");
  Serial.println(readings[9]);
  Serial.print("Clear    : ");
  Serial.print(counts[10]);
  Serial.print("  ");
  Serial.print("Raw Value : ");
  Serial.println(readings[10]);
  Serial.print("NIR      : ");
  Serial.print(counts[11]);
  Serial.print("  ");
  Serial.print("Raw Value : ");
  Serial.println(readings[11]);
  Serial.print("  ");
  Serial.println();
}
