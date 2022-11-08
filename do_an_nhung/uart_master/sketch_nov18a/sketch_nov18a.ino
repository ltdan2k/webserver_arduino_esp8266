#include <DallasTemperature.h>
#include <OneWire.h>
// Data wire is plugged into pin D3 on the ESP8266
#define ONE_WIRE_BUS 3

// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature.
DallasTemperature DS18B20(&oneWire);



long last =0 ;
float nhietdo1 ;
float nhietdo2 ;
void chuongtrinhcambien();
void setup() 
{
 
 Serial.begin(9600) ;
 pinMode(A0 ,INPUT);
 last= millis() ;

}

void loop() 
{
  if (millis() - last >= 1000)
{
  getTemperature();
  
  chuongtrinhcambien();
  Serial.print('A');
  Serial.print(nhietdo1);

  delay(100);
  Serial.print('B');
  Serial.print(nhietdo2);
  last = millis();
}
  

}

void chuongtrinhcambien()
{
  int a = analogRead(A0) ;
  float volt1 = a*5/1024.0 ;

  nhietdo1 = volt1*1000;
//nhietdo1 = nhietdo1 +1;
  delay(100);

  
}
void getTemperature() {
  do {
    DS18B20.requestTemperatures();
    nhietdo2 = DS18B20.getTempCByIndex(0);
    nhietdo2 = nhietdo2 * 10 ;
    if (nhietdo2 == (-127)) {
      delay(100);
    }
  } while (nhietdo2 == (-127.0));
}
