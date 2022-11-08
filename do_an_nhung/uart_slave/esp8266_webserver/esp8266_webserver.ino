#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
ESP8266WebServer server(80);

#include "web.h"

const char *ssid = "LAI THE DAN";
const char *pass = "12345678";


// config dia chi esp co dinh
IPAddress local_IP(192, 168, 0, 21) ;
IPAddress gateway(192, 168, 0, 1) ;
IPAddress subnet(255, 255, 255, 0) ;
IPAddress primaryDNS(8, 8, 8, 8) ;
IPAddress secondaryDNS(8, 8, 4, 4) ;

String ChuoiSendWebJason ="";
float nhietdo1 ;
float nhietdo2 ;
int doam;
void ConnectWifi();
void SendWebPage();
//void chuongtrinhcambien();
long last =0 ;
void SendUpdate() ;
void Button_Onclick();
void XulyONOFF(String button);
int RELAY = 1;
byte Data[4];
void setup() {
  
  Serial.begin(9600) ;
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(RELAY, OUTPUT); 
  ConnectWifi();

server.on("/", []
{
  SendWebPage();
});

server.on("/Update", []
{
 SendUpdate();
});


server.on("/Button", []
{
 Button_Onclick();
});

server.begin(); // bat dau server
Serial.println("Server start");


   last= millis() ;
}
void loop() {
  
server.handleClient();// duy tri server

if (millis() - last >= 1000)
{
  last = millis();
}  
  if (Serial.available()>3)
  {
    Data[0]=Serial.read();
    if(Data[0]=='A')
    {
      Data[1]=Serial.read() -48;
      Data[2]=Serial.read() -48;
      Data[3]=Serial.read() -48;
      nhietdo1 =((Data[1] * 100)+(Data[2]*10)+Data[3])/10;
      }
     if(Data[0]=='B')
    {
      Data[1]=Serial.read() -48;
      Data[2]=Serial.read() -48;
      Data[3]=Serial.read() -48;
      nhietdo2 =((Data[1] * 100)+(Data[2]*10)+Data[3])/10;
      } 
  } 


//chuongtrinhcambien();

//ledblynk();
Button_Onclick();
}
void SendWebPage()
{
  server.send(200, "text/html", webpage );
}

void ConnectWifi()
{
  WiFi.disconnect(); delay(1000);
  if (!  WiFi.config(local_IP, gateway, subnet, primaryDNS, secondaryDNS))
  {
    Serial.println("ERROR configure");
  }
  delay(1000); WiFi.begin(ssid, pass);
  while (WiFi.status() !=WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
    
  }
  Serial.println();
  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());


  
}
void SendUpdate()
{
  DataJson(String (nhietdo1), String (nhietdo2),String (doam) );
  server.send(200, "text/html", String(ChuoiSendWebJason));
  
}

void DataJson( String sensor1 , String sensor2, String sensor3)

{
  ChuoiSendWebJason = "{\"ND1\":\"" + String(sensor1) +"\"," +
                      "\"ND2\":\"" + String(sensor2) +"\"," +
                      "\"DA\":\"" + String(sensor3) + "\"}" ;
}

//void chuongtrinhcambien()
//{
//  int a = analogRead(A0) ;
//  float volt = a*3.3/1024.0 ;
//
//  nhietdo = volt*100.0;
//  delay(1000);
  
  
//}
//void ledblynk()
//{
//  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
//  delay(1000);                       // wait for a second
//  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
//  delay(1000);                       // wait for a second
//}
void Button_Onclick()
{
//  Serial.println(">>>ONCLICK bUTTON");
//  Serial.println(server.arg("Button"));
  String button = ""; 
  button = server.arg("Button");
  XulyONOFF(String (button) );
  server.send(200, "text/html", webpage );
  
}
void XulyONOFF(String button )
{
  if(button.indexOf("A0B") >=0)
  {
    Serial.println("OFF DEN");
    //digitalWrite(RELAY, LOW);
    digitalWrite(LED_BUILTIN, LOW);
    doam =0;
  }
  else if(button.indexOf("A1B") >=0)
  {
    Serial.println("ON DEN");
    //digitalWrite(RELAY, HIGH);
    digitalWrite(LED_BUILTIN, HIGH);
    doam =1;
  }
}
