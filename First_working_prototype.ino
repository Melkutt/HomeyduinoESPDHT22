#include <ArduinoSort.h>
#include <dhtnew.h>
#include <WiFiClient.h>
#include <Homey.h>
#include <ESP8266WiFi.h>

DHTNEW dht(D5); //Signera pinne D5 till DHT givaren

float tempArray[5];
float humiArray[5];

int i = 0;
int j = 0;


void setup() {
  
  Serial.begin(115200); //För debugging
  Serial.println("Test");

}

void loop() {

 DHTtemp(2);
 
 DHThumi(2);
  
 medianValue();
 
  Serial.println(tempArray[0]);
  delay(10);
  Serial.println(tempArray[1]);
  delay(10);
  Serial.println(tempArray[2]);
  delay(10);
  Serial.println(tempArray[3]);
  delay(10);
  Serial.println(tempArray[4]);
  
  Serial.println(humiArray[0]);
  delay(10);
  Serial.println(humiArray[1]);
  delay(10);
  Serial.println(humiArray[2]);
  delay(10);
  Serial.println(humiArray[3]);
  delay(10);
  Serial.println(humiArray[4]);  
  

}

/*
 * 
 */
void DHTtemp(float pin)
{
  for (byte i = 0; i < 4;){
    delay(2000);
    dht.read();
    tempArray[i] = dht.getTemperature();
   // Serial.print(dht.getTemperature());
    //Serial.println("c");
    ++i;
    }
  
}

void DHThumi(float pin)
{
  for (byte j = 0; j < 4;) {
    dht.read();
    delay(2000);
    humiArray[j] = dht.getHumidity();
    //Serial.print(dht.getHumidity());
    //Serial.println("%");
    ++j;
  }
}

/*
 * Här kommer arrayen som skall sorteras och medianvärdet skall sorteras fram
 */

 void medianValue(){

  sortArray(tempArray, 5);
  delay(10);
  Serial.println(tempArray[2]);
  delay(10);
  
  sortArray(humiArray, 5);
  delay(10);
  Serial.println(humiArray[2]);
  delay(10);
   zero();
 }

 
 void zero(){

 Serial.println("Zeroing dah shit now!");
  i = 0;
  j = 0;
 }

 /*
  *
  */
