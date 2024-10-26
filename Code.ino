// Cài đặt ID, NAME, link Blynk của bạn
#define BLYNK_TEMPLATE_ID "TMPL6f3tAGb5T"
#define BLYNK_TEMPLATE_NAME "HCSR04"
#define BLYNK_AUTH_TOKEN "yLy_p9AHfWb1aKvSQxKTiB0EdP7uUlg7"

#define DHTPIN 33     // what digital pin the DHT sensor is connected to
#define DHTTYPE DHT11   // there are multiple kinds of DHT11 sensors

//define sound speed in cm/uS
#define SOUND_SPEED 0.034  // HC-SR04 sensor

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <string.h>
#include "DHT.h"
#include <PZEM004Tv30.h>

PZEM004Tv30 pzem(Serial2 , 16,17);// Signal Pin Installation pzem004t sensor

DHT dht(DHTPIN, DHTTYPE);
// // Signal Pin Installation pzem004t sensor
const int trigPin = 26;const int echoPin = 25;

char auth[] = BLYNK_AUTH_TOKEN;
// Địa chỉ Wifi 
char ssid[] = "Huong";char pass[] = "huong123";

long duration;float distanceCm;

void setup() {
  Serial.begin(9600); // Starts the serial communication
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  pinMode(4, OUTPUT);
  pinMode(2, OUTPUT);
  dht.begin();
  Blynk.begin(auth, ssid, pass);
}

void loop() {
  Blynk.run();
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);distanceCm = duration * SOUND_SPEED/2;
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  float voltage = pzem.voltage();
  float current = pzem.current();
  // float power = pzem.power();
  // float energy = pzem.energy();
  // float frequency = pzem.frequency();
  // float pf = pzem.pf();
  if (isnan(h) || isnan(t) || isnan(distanceCm)) {
    Serial.println("Failed to read");
    return;
  }
    Serial.print(h);

  if(t < 37){
      digitalWrite(4, HIGH);  // ON or OFF RELAY
  } else {
    digitalWrite(4, LOW);  // ON or OFF RELAY
  }
  if(h < 75){
      digitalWrite(2 , HIGH);  // ON or OFF RELAY
  } else {
    digitalWrite(2, LOW);  // ON or OFF RELAY
  }
  // Send Parameters to Pins Installed on Blynk
  Blynk.virtualWrite(V0, h);
  Blynk.virtualWrite(V1, t);
  Blynk.virtualWrite(V2, distanceCm);

  // if(distanceCm > 3 && distanceCm < 20)
  // {
  //   digitalWrite(4, HIGH);  // ON or OFF RELAY
  // } else {digitalWrite(4, LOW);}

  Blynk.virtualWrite(V3, voltage);
  Blynk.virtualWrite(V4, current);
  delay(1000);
}