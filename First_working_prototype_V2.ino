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
  Serial.println("Test"); //Så vi vet att de har brumme igång

  /*
   * WiFi mojjen
   */
  WiFi.begin("SSID", "PASW");

  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());

  /*
   * Hail Homey
   */
   Homey.begin("Homey");

}

void loop() {

 DHTtemp(2);
 
 DHThumi(2);
  
 medianValue();

 Homey.loop();

 delay(10000);

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
    ++i;
    }
  
}

void DHThumi(float pin)
{
  for (byte j = 0; j < 4;) {
    dht.read();
    delay(2000);
    humiArray[j] = dht.getHumidity();
    ++j;
  }
}

/*
 * Här kommer arrayen som skall sorteras och medianvärdet skall sorteras fram
 */

 void medianValue(){

  sortArray(tempArray, 5);
  Serial.println(tempArray[2]);
  
  sortArray(humiArray, 5);
  Serial.println(humiArray[2]);
   zero();
 }

 
 void zero(){

 Serial.println("Zeroing dah shit now!");
  i = 0;
  j = 0;
 }

 /*
  * Homeyn skall tillkallas också!
  */



  /*
   * ESP Shit
   */
