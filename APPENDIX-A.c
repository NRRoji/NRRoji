APPENDIX-A
CODE

A.Code for IOT and GSM

include<LiquidCrystal.h>
#include "DHT.h"
#define DHTPIN 10
#define DHTTYPE DHT11
DHT dht(DHTPIN,DHTTYPE);
LiquidCrystal lcd(7,6,5,4,3,2);
int gas=12;
int FIRE=11;
int magsen=9;
void setup() {
  Serial.begin(9600);
  lcd.begin(16,2);
  lcd.setCursor(0,0);
  lcd.print("Smartpoultryfarm");
  lcd.setCursor(0,1);
  lcd.print("using IOT");
  pinMode(gas,INPUT);
  pinMode(FIRE,INPUT);
  pinMode(magsen,INPUT);
  digitalWrite(magsen,LOW);
  dht.begin();
  // put your setup code here, to run once:
}
void loop() 
{
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float f = dht.readTemperature(true);
  if (isnan(h) || isnan(t) || isnan(f)) 
  {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  else
  {
    Serial.println("Humidity:");
    Serial.println(h);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("hum:");
    lcd.setCursor(4,0);
    lcd.print(h);
    Serial.println("Temperature:");
    Serial.println(t);
    lcd.setCursor(0,1);
    lcd.print("Temp:");
    lcd.setCursor(5,1);
    lcd.print(t);
    delay(1000);
    Serial.println("Temperature in F:");
    Serial.println(f);
  }
 int gasv=digitalRead(gas);
  if(gasv==LOW)
  {
    Serial.println("gas is detected");
    lcd.clear();
    lcd.print("gas detected");
    delay(1000);
    msg("gas is detected");
   int send_data_to_server(gas);
    delay(1000);
  }
  else
  {
    Serial.println("gas is not detected");
  }
  Serial.print("fire:");
  Serial.println(digitalRead(FIRE));
int  firev=digitalRead(FIRE);
  if(firev==LOW)
  {
   Serial.println("fire is detected");
    lcd.clear();
    lcd.print("fire detected");
    delay(1000);
    msg("fire is detected");
    int send_data_to_server(FIRE);
    delay(1000);
  }
  else
  {
    Serial.println("fire is not detected");
  }
  Serial.print("mag sen:");
  Serial.println(digitalRead(magsen));
  if(digitalRead(magsen)==LOW)
  {
    Serial.println("door is opened");
    lcd.clear();
    lcd.print("door opened");
    delay(1000);
    msg("door is opened");
int   send_data_to_server(magsen);
    delay(1000);
  }
  else
  {
    Serial.println("door close");
  }
  if(h>40 && t>35)
  {
    Serial.println("Temperature is exceeded");
    lcd.clear();
    lcd.print("Temp exceeded");
    msg("Temperature is exceeded");
  int send_data_to_server(h,t);
   //int send_data_to_server(h);
    delay(1000);
  }
  else
  {
    Serial.println("Temperature is not exceeded");
  } 
}
void msg(String data)
{
  lcd.clear();
  Serial.println("AT");
  delay(1000);
  Serial.println("ATE0");
  delay(1000);
  Serial.println("AT+CMGF=1");
  delay(1000);
  lcd.print("message sending");
  Serial.println("AT+CMGS=\"+919014243237\"");
  delay(1000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("message sent");
  Serial.print(data);
  Serial.write(26);
  delay(500);
}
void send_data_to_server(int gas, int fire, int magsen, int h, int t)
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("data");
  lcd.setCursor(0,1);
  lcd.print("uploading ");
  Serial.println("AT");      // Atention for  test
  delay(1000);
  Serial.println("AT+CPIN?");//This is to check if SIM is unlocked
  delay(1000);
  Serial.println("AT+CREG?"); //This checks if SIM is registered or not
  delay(1000);
  Serial.println("AT+CGATT?");//Check if Serial is attached or not
  delay(1000);
  Serial.println("AT+CIPSHUT");//Reset the IP session if any
  delay(1000);
  Serial.println("AT+CIPSTATUS");//Check if the IP stack is initialized
  delay(2000);
  Serial.println("AT+CIPMUX=0");//To keep things simple, I’m setting up a single connection mode
  delay(2000);
  Serial.println("AT+CSTT=\"Airtel Internet\"");//start task and setting the APN,
  delay(1000);
  Serial.println("AT+CIICR");//Now bring up the wireless. Please note, the response to this might take some time
  delay(3000);
  Serial.println("AT+CIFSR");//get local IP adress
  delay(1000);
  Serial.println("AT+CIPSPRT=0");
  delay(3000);
  Serial.println("AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",\"80\"");//start up the connection
  delay(5000);
  Serial.println("AT+CIPSEND");//begin send data to remote server
  delay(5000);                                                   /////////////////////https://thingspeak.com/channels/722496
  String str="GET https://api.thingspeak.com/update?api_key=3N1UTALOXDM4VMBL&field1=" + String(gas)+ "&field2="+ String(FIRE)+ "&field3="+ String(magsen)+ "&field4="+ String(h)+ "&field5="+ String(t);
  Serial.println(str);//begin send data to remote server   
  delay(3000);
  Serial.write(26);//sending
  delay(1000);//waitting for reply, important! the time is base on the condition of internet 
  Serial.println();
  Serial.println("AT+CIPSHUT");//close the connection
  delay(1000);
//https://thingspeak.com/channels/938763
}
