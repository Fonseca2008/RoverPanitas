#include <SoftwareSerial.h>
#include <TinyGPS.h> 
#include <DHT.h>
#define LoraRx 13
#define LoraTx 12
#define pinDHT 25
#define GPSNeo6mRx 64
#define GPSNeo6mTx 63
SoftwareSerial LoRa(LoraRx, LoraTx);
SoftwareSerial GPSNeo6m(GPSNeo6mRx , GPSNeo6mTx);
int temperaturaDHT;
int humedadDHT;
int Higro;
const int seco=456;
const int moja=234;
float lat=0;
float lon=0;
String datos;
String latitud;
String longitud;
String lectura;
String buffer = "";
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
  HumSuelo();
  UnionDatos();
  EnvioLoRa();
  LeerLoRa();
}
void LeerGPS(){
  while(GPSNeo6m.available()) {
    if(gps.encode(GPSNeo6m.read()))
    {  
    gps.f_get_position(&lat,&lon); 
    latitud=String(lat,6);
    longitud=String(lon,6);
    } 
    else{
      latitud=String(0);
      longitud=String(0); 
    }
  }
}
void EnvioLoRa(){
  if (LoRa.available()) {
    LoRa.println(datos);
  }
}
void LecturaDHT(){
  temperaturaDHT = sensorDHT.readTemperature();
  humedadDHT = sensorDHT.readHumidity();
}
void UnionDatos(){
  datos=latitud+","+longitud+","+String(temperaturaDHT)+","+String(humedadDHT)+","+String(Higro);
  Serial.println(datos);
}
void HumSuelo(){
  int ValorHigro=analogRead(A0);
  Higro = map(ValorHigro, moja, seco, 100, 0);
}
void LeerLoRa(){
  if (LoRa.available()) {
    char lec= LoRa.read();// ignorar el Carriage Return y el Line Feed
    lectura.concat(lec);
  if (buffer.length() > 0) {
  lectura += buffer;
  buffer = "";
}

if (lectura.endsWith("Adelante")) {
  //Adelante
}

if (lectura.endsWith("Atras")) {
  //Atras
}
if (lectura.endsWith("Izquierda")) {
  //Izquierda
}
if (lectura.endsWith("Derecha")) {
  //Derecha
}
if (lectura.endsWith("Presentar")) {
  //Presentar
}
if (lectura.endsWith("Parar")) {
  //Parar
}
if (lectura.endsWith("Panel")) {
  //Panel
}

if (lectura.endsWith("\n")) { // imprimir solo cuando se recibe un salto de línea
  Serial.println(lectura);
  lectura = ""; // reiniciar la variable lectura
}
  }
}
