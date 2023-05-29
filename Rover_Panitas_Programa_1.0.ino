#include <SoftwareSerial.h>
#include <TinyGPS.h> 
#include <DHT.h>
#define LoraRx 2
#define LoraTx 3
#define pinDHT 4
#define GPSNeo6mRx 10
#define GPSNeo6mTx 11
SoftwareSerial LoRa(LoraRx, LoraTx);
SoftwareSerial GPSNeo6m(GPSNeo6mRx , GPSNeo6mTx);
int temperatura;
int humedad;
float lat=0;
float lon=0;
String datos;
String latitud;
String longitud;
TinyGPS gps; 
DHT sensorDHT(pinDHT, DHT22);
void setup() {
  Serial.begin(9600);
  LoRa.begin(9600);
  GPSNeo6m.begin(9600);
  sensorDHT.begin();
}

void loop() {
  LeerGPS();
  LecturaDHT();
  UnionDatos();
  EnvioLoRa();
}
void LeerGPS(){
  while(GPSNeo6m.available()) {
    if(gps.encode(GPSNeo6m.read()))
    {  
    gps.f_get_position(&lat,&lon); 
    latitud=String(lat,6);
    longitud=String(lon,6);
    }  
  } 
}
void EnvioLoRa(){
  if (LoRa.available()) {
    LoRa.println(datos);
  }
}
void LecturaDHT(){
  temperatura = sensorDHT.readTemperature();
  humedad = sensorDHT.readHumidity();
}
void UnionDatos(){
  datos=latitud+longitud+String(temperatura)+String(humedad);
}
