/*
 * Melker Hult, or "Melkutt" on GitHub, and every else online
 * SA1CKW
 * 
 * You have found this sketch here --> https://github.com/Melkutt/HomeyduinoESPDHT22
 * 
 * This i just a working prototype, only tested with a LoLin/NodMCU board
 * 
 * DHT22 -> ESP
 * Pin 1 -> VCC, Pin 2 -> D5, Pin 3 -> NC, Pin 4 -> GND
 * A 4.7k resistor between Pin 1 -> Pin 2
 * 
 * 
 * To-Do-List:
 * A lot =)
 * 
 * 
 * Firse beta release dec 2021
 * 
 * For more info, check out this GitHub links
 * Homeys arduino lib, or "Homeyduino" --> https://github.com/athombv/homey-arduino-library
 * emilv and his ArduSorting lib --> https://github.com/emilv/ArduinoSort
 * RobTillaart's DTHNew lib --> https://github.com/RobTillaart/DHTNew
 * 
 */

#include <ArduinoSort.h>
#include <dhtnew.h>
#include <Homey.h>
#include <ESP8266WiFi.h>

DHTNEW dht (D4);                                //Data pin to sensor

float tempArray[5];
float humiArray[5];


void setup() {
  
  Serial.begin(115200);                        //Just for debuging
  Serial.println("I'm alive!");                //Firest "debugging" stage

 
  Homey.begin("DHT22");                     //Your nod/sensor name
  Homey.setClass("sensor");
  Homey.addCapability("measure_humidity");
  Homey.addCapability("measure_temperature");

}

void loop() {

  wifi();

 updateSensorArray(2);
  
  medianValue(2);

  Homey.loop();{                             
  updateSensor(2);
 }
 
 zero();
}

/*
 *  Collecting sensor reading and updates array
 */
 
void updateSensorArray(float)
{
  int i = 0;
  int j = 0;
  for (byte i = 0; i < 4;){
    delay(2000);
    dht.read();
    tempArray[i] = dht.getTemperature();
    humiArray[j] = dht.getHumidity();
    ++i;
    ++j;
  } 
}


/*
 * This part sorts the array from low to high so updateSensor just report the median value.
 * Pretty smart and very easy way to sort out any error from the sensor!
 */

 void medianValue(float){

    sortArray(tempArray, 5);
    sortArray(humiArray, 5);
 
 }

 /*
  * This part zeros both arrays so the can be filld again with out overflows
  */
  
 void zero(){

     Serial.println("Zeroing dah shit now!");
      memset(tempArray,0,sizeof(tempArray));
      memset(humiArray,0,sizeof(humiArray));
 }

 /*
  * Update sensor value to Homey
  */

  void updateSensor(float) {
    
  float temperature = tempArray[2];
  float humidity = humiArray[2];

  
  Serial.print((float)temperature); Serial.println(" *C, ");
  Serial.print((float)humidity); Serial.println(" H");

  Homey.setCapabilityValue("measure_temperature", (float) temperature);
  Homey.setCapabilityValue("measure_humidity", (float) humidity);

  }
 
  
  /*
   * Wifi connection
   */
   
  void wifi() {
    
  if (WiFi.status() != WL_CONNECTED) {
    WiFi.begin("SSID", "PASSWORD");
    uint8_t timeout = 30;
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      
      Serial.print(".");
      if (timeout<1) break;
    }
    
    if (WiFi.status() == WL_CONNECTED) {
      //Print IP address
      Serial.print("Connected to WiFi! (");
      Serial.print(WiFi.localIP());
      Serial.println(")");
    }
  }
}   
