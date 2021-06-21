B. Code For NODEMCU

//#include <Blynk.h>
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "g3E-o14rpcr8IJyo_FX9xcGiKDLrLJmj";
// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Pooja";
char pass[] = "12345678";
#define ACmot D0
#define DCmot1 D1
#define DCmot2 D2
//#define m1 D3
//#define m2 D4
void setup()
{
  // Debug console
  Serial.begin(115200);
// pinMode(light,OUTPUT);
// pinMode(fan,OUTPUT);
 pinMode(DCmot1,OUTPUT);
 pinMode(DCmot2,OUTPUT);
// pinMode(m2,OUTPUT);
  digitalWrite(DCmot1,LOW);
   digitalWrite(DCmot2,LOW);
 digitalWrite(ACmot,LOW);
  Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 80);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);
}
void loop()
{
  Blynk.run();
  // You can inject your own code or combine it with other sketches.
  // Check other examples on how to communicate with Blynk. Remember
  // to avoid delay() function!
}
