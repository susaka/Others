//Libraries
#include <DHT.h>
#include <Ethernet.h>
#include <SPI.h>
#include <Wire.h>
#include "RTClib.h"

//Constants
#define DHTPIN 2     // what pin we're connected to
#define DHTTYPE DHT22   // DHT 22  (AM2302)
DHT dht(DHTPIN, DHTTYPE); // Initialize DHT sensor for normal 16mhz Arduino

//Variables
int chk;
int hum;  //Stores humidity value
int temp; //Stores temperature value
long t;

//Constants
byte mac[] = {0x90, 0xA2, 0xDA, 0x0F, 0x6B, 0x6A}; //reserved MAC address
byte ip[] = {192, 168, 127, 159}; //statisk IP
byte dnsServer[] = {192, 168, 10, 250};
byte gateway[] = {192, 168, 127, 129};
byte subnet[] = {255, 255, 255, 128};

//IP adresse på Web-serveren
IPAddress dthServer(192, 168, 127, 166);

//initializere Ethernet Client library
EthernetClient client;

RTC_DS1307 RTC;

/*RTC uses pins
PIN A5 for SCL
PIN A4 for SDA
*/

void setup()
{
//Seriel kommunikation
  Serial.begin(9600);
  
//temperatur sensor start
  dht.begin();
  
//Ethernet start
  Ethernet.begin(mac, ip, dnsServer, gateway, subnet);

//I2C startes
  Wire.begin();

//Real time clock startes
  RTC.begin();

//RTC indstilles til tidspunktet for compiling af dette program
  if (! RTC.isrunning()) {
    Serial.println("RTC is NOT running!");
  // following line sets the RTC to the date & time this sketch was compiled
    RTC.adjust(DateTime(__DATE__, __TIME__));
  }  
}

void loop()
{
//Read data and store it to variables hum and temp
  hum = dht.readHumidity();
  temp = dht.readTemperature();
//Print temp and humidity values to serial monitor
  Serial.print("Humidity: ");
  Serial.print(hum);
  Serial.print(" %, Temp: ");
  Serial.print(temp);
  Serial.println(" Celsius");

//Get RTC time
  DateTime now = RTC.now();
    
  Serial.print(now.year(), DEC);
  Serial.print('/');
  Serial.print(now.month(), DEC);
  Serial.print('/');
  Serial.print(now.day(), DEC);
  Serial.print(' ');
  Serial.print(now.hour(), DEC);
  Serial.print(':');
  Serial.print(now.minute(), DEC);
  Serial.print(':');
  Serial.print(now.second(), DEC);
  Serial.println();
    
  Serial.print(" since midnight 1/1/1970 = ");
  Serial.print(now.unixtime());
  t = now.unixtime();
  Serial.print("s");
  Serial.println();

//Send data to the webserver
  if (client.connect(dthServer, 80)) {
  Serial.println("connected");
//Make a HTTP request
  client.print("POST /save_data.php?");
  client.print("time=");
  client.print(t);
  client.print("&t=");
  client.print(temp);
  client.print("&h=");
  client.print(hum);
  client.println(" HTTP/1.1");
  client.print("Host: "); //server address again
  client.println(dthServer);
  client.println("Connection: close");
  client.println();
  client.println();
  client.stop();
  }
  else
  {
//couldn't connect to server
  Serial.println(" --> connection failed/n ");
  }    

//wait until next sending
//waiting 60 seconds
delay(60000);
Serial.println();

}
