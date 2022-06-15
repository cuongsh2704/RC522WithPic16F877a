#define BLYNK_TEMPLATE_ID "TMPLu6XceyGe"
#define BLYNK_DEVICE_NAME "RIFD"
#define BLYNK_AUTH_TOKEN "gPruWrKATiWbrLBP-wsawEf5zcZINu9X"
#define RST D8 //set D8 = reset
#define SS D10 //set D10 select slaver
#define UID_True 172
#define UID_False 163




#include<MFRC522.h>
#include<SPI.h>
#include <stdint.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>



char auth[] =  BLYNK_AUTH_TOKEN;

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Master";
char pass[] = "0123456789";


char dataCard;
char data_r, data_s;
int state;
//config for CARD
 MFRC522 mfrc522(SS, RST);
 MFRC522::MIFARE_Key key;

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
 
  
  SPI.begin();
  mfrc522.PCD_Init();// khoi tao rc522
 
  
  }

void loop(){  
  // Look for new cards

  if(Serial.available() > 0)
  {
    
  
    data_r = Serial.read();
    if (data_r == UID_True){
      Blynk.virtualWrite(V0, dataCard);
      digitalWrite(LED_BUILTIN, HIGH);
      delay(1000);
      digitalWrite(LED_BUILTIN, LOW);
     
      }
    
    }
 if(!mfrc522.PICC_IsNewCardPresent())
 {
   return;
 }
 // Select one of the cards
 if(!mfrc522.PICC_ReadCardSerial())
 {
   return;
 }
 //gui UID cua the
 dataCard = mfrc522.uid.uidByte[0];
 Serial.write(dataCard);
 
 
   mfrc522.PICC_HaltA();
  
   

}
