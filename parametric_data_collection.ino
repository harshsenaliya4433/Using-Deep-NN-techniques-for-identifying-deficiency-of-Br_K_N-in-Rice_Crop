#include <SPI.h>
#include <SD.h>
#include <dht.h>
#define dht_apin A0 // Analog Pin sensor is connected to

int sensorPin = A1; 
int sensorValue;  
int limit = 300; 

dht DHT;

File myFile;

void setup() {

Serial.begin(9600);
 //pinMode(13, OUTPUT);
 pinMode(8, OUTPUT);
while (!Serial) {
 ; // wait for serial port to connect. Needed for native USB port only
}
Serial.print("Initializing SD card...");
if (!SD.begin(10)) {
 Serial.println("initialization failed!");
 while (1);
}
Serial.println("initialization done.");


}

int writedata(String value) {
myFile = SD.open("test.txt", FILE_WRITE);
 if (myFile) {
  myFile.seek(EOF);
  myFile.println(value); 
 myFile.close();
 Serial.println("done.");
 } else {
  Serial.println("error opening test.txt");
 }
 return 0;
}

void loop() { 
  sensorValue = analogRead(sensorPin);
 if (sensorValue<limit) {
 digitalWrite(13, HIGH); 
 }
 else {
 digitalWrite(13, LOW); 
 }
  DHT.read11(dht_apin);
   Serial.print("Current humidity = ");
    Serial.print(DHT.humidity);
    Serial.print("%  ");
    Serial.print("temperature = ");
    Serial.print(DHT.temperature); 
    Serial.println("C  ");
    Serial.println(sensorValue);
    String stringOne = String("Current humidity =") +DHT.humidity;
    writedata(stringOne);
    stringOne = String("Current Temperature =") +DHT.temperature;
     writedata(stringOne);
     float moisture_percentage = sensorValue;
     stringOne = String("Current moisture =") +moisture_percentage +String("%");
      writedata(stringOne);
    //writedata("Current temperature = "+DHT.temperature);
 delay(600000);
}
