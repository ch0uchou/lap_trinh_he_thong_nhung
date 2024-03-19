// pin dht 3
// ghi file vcc 5v, gnd, MISO 12, MOSI 11, SCK 13, CS 10
// RTC đọc thời gian vcc 5v, gnd, SDA - A4, SCL - A5
#include <SPI.h>
#include <SD.h>
#include<Wire.h>

#include "RTClib.h"

#include <DHT.h>
#define DHTPIN 3
#define DHTTYPE DHT11 

DHT dht(DHTPIN, DHTTYPE);

RTC_DS1307 RTC;

File myFile;

// change this to match your SD shield or module;
const int chipSelect = 10;
float pre_temp =0, temp =0;
void setup()
{
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
  Serial.print("Initializing SD card...");

  if (!SD.begin()) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");

  Wire.begin();

  RTC.begin(); // load the time from your computer.

  if (! RTC.isrunning())

  {

  Serial.println("RTC is NOT running!");// This will reflect the time that your sketch was compiled

  RTC.adjust(DateTime(__DATE__, __TIME__));
  }
  dht.begin();


  // SD.remove("TEST123.txt");      //uncomment nếu ghi đè
}

void writefile(String file, float temp, int Delay){
  myFile = SD.open(file, FILE_WRITE);
  // if the file opened okay, write to it:
  if (myFile) {
    String output = "";
    Serial.println("Writing to test.txt...");
    DateTime now = RTC.now();
    
    myFile.print(now.month(), DEC);
    Serial.print(now.month(), DEC);
    myFile.print('/');
    Serial.print('/');
    myFile.print(now.day(), DEC);
    Serial.print(now.day(), DEC);
    myFile.print('/');
    Serial.print('/');
    myFile.print(now.year(), DEC);
    Serial.print(now.year(), DEC);
    myFile.print(' ');
    Serial.print(' ');
    myFile.print(now.hour(), DEC);
    Serial.print(now.hour(), DEC);
    myFile.print(':');
    Serial.print(':');
    myFile.print(now.minute(), DEC);
    Serial.print(now.minute(), DEC);
    myFile.print(':');
    Serial.print(':');
    myFile.print(now.second(), DEC);
    Serial.print(now.second(), DEC);
    myFile.print(" Temperature  (C): ");
    Serial.print(" Temperature  (C): ");
    myFile.println(temp, 2);
    Serial.println(temp, 2);
    // close the file:
    myFile.close();
    Serial.println("done.");
    delay(Delay);
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }
}

void loop()
{
  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.

  // if the file opened okay, write to it:
  temp = dht.readTemperature();
  
  // writefile("TEST123.txt", temp, 10000);   //ghi nhiệt độ mỗi 10s ra file


  // ghi nhiệt độ khi nhiệt độ thay đổi
  if (temp != pre_temp){
    pre_temp = temp;
    writefile("TEST123.txt", temp, 0);
  }
}


