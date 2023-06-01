#include <SoftwareSerial.h>
#include "VoiceRecognitionV3.h"
VR myVR(2,3);
uint8_t records[7]; 
uint8_t buf[64];
int joysBot=12;
int led=13;
int xJoystick;
int yJoystick;
String DATA; 
#define Presentar    (0)
#define Sembrar   (1) 
#define Panel    (2)
#define Auto    (3)
void printSignature(uint8_t *buf, int len)
{
  int i;
  for(i=0; i<len; i++){
    if(buf[i]>0x19 && buf[i]<0x7F){
      Serial.write(buf[i]);
    }
    else{
      Serial.print("[");
      Serial.print(buf[i], HEX);
      Serial.print("]");
    }
  }
}
void printVR(uint8_t *buf)
{
  Serial.println("VR Index\tGroup\tRecordNum\tSignature");

  Serial.print(buf[2], DEC);
  Serial.print("\t\t");

  if(buf[0] == 0xFF){
    Serial.print("NONE");
  }
  else if(buf[0]&0x80){
    Serial.print("UG ");
    Serial.print(buf[0]&(~0x80), DEC);
  }
  else{
    Serial.print("SG ");
    Serial.print(buf[0], DEC);
  }
  Serial.print("\t");

  Serial.print(buf[1], DEC);
  Serial.print("\t\t");
  if(buf[3]>0){
    printSignature(buf+4, buf[3]);
  }
  else{
    Serial.print("NONE");
  }
  Serial.println("\r\n");
}
SoftwareSerial LoRa(10,11);
void setup()
{
  LoRa.begin(9600);
  Serial.begin(9600);
  LoRa.println("Hola");
  Serial.println("Enviado Hola");
  pinMode(joysBot, INPUT);
  
  myVR.begin(9600);
  //Serial.println("Elechouse Voice Recognition V3 Module\r\nControl LED sample");
  
  pinMode(led, OUTPUT);
    
  if(myVR.clear() == 0){
    //Serial.println("Recognizer cleared.");
  }else{
    Serial.println("Not find VoiceRecognitionModule.");
    Serial.println("Please check connection and restart Arduino.");
    while(1);
  }
  
  
  if(myVR.load((uint8_t)Presentar) >= 0){
    //Serial.println("Mover Panel Ingresado");
  }
  
  if(myVR.load((uint8_t)Sembrar) >= 0){
    //Serial.println("Presentar Ingresado");
  }
  if(myVR.load((uint8_t)Panel) >= 0){
    //Serial.println("Parar Ingresado");
  }
  if(myVR.load((uint8_t)Auto) >= 0){
    //Serial.println("Parar Ingresado");
  }
  
}

void loop()
{
    
    if (LoRa.available()){
      Serial.write(LoRa.read());
    }
    xJoystick=analogRead(A1);
    yJoystick=analogRead(A0);
    if(xJoystick>=0 && xJoystick<480){
      Serial.println("Izquierda");
      //LoRa.println("Izquierda");
    }
    if(xJoystick>520 && xJoystick<=1023){
      Serial.println("Derecha");
      //LoRa.println("Derecha");
    }
    if(yJoystick>=0 && yJoystick<480){
      Serial.println("Atras");
      //LoRa.println("Atras");
    }
    if(yJoystick>520 && yJoystick<=1023){
      Serial.println("Adelante");
      //LoRa.println("Adelante");
    }

  int ret;
  ret = myVR.recognize(buf, 50);
  if(ret>0){
    switch(buf[1]){
      case Presentar:
        Serial.println("Presentar");
        //LoRa.println("Presentar");
        break;
      case Sembrar:
        Serial.println("Sembrar");
        //LoRa.println("Sembrar");
        break; 
      case Panel:
        Serial.println("Panel");
        //LoRa.println("Panel");
        break;  
       case Auto:
        Serial.println("Auto");
        //LoRa.println("Auto");
        break;      
      default:
        //Serial.println("Record function undefined");
        break;
    }
    
    //printVR(buf);
  }
}
