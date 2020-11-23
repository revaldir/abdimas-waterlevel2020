// DRUM B

#include <FirebaseArduino.h>
#include <ESP8266WiFi.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

// DEFINE LCD I2C
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2);

// DEFINE HC-SR04
#define triggerPin  D8 
#define echoPin     D7

// DEFINE FIREBASE
#define FIREBASE_HOST "abdimas2020-bd25f.firebaseio.com"
#define FIREBASE_AUTH "sRNmQjMMgPFsrhTKVKqn36VOB7RaioljJX7SxX9J"
#define WIFI_SSID "Redmi Note 9 Pro"
#define WIFI_PASSWORD "shamballa"

void setup() {
  Serial.begin(115200);
  
  // LCD I2C
  Wire.begin(D2, D1); // D2 = SDA, D1 = SCL
  
  lcd.begin();
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  // CONNECT TO WIFI
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

void loop() {
  lcd.clear();
  long duration;
  int jarakInt, persenInt;
  float jarak, persen;
  int jarTotal = 60;
  
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2); 
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10); 
  digitalWrite(triggerPin, LOW);
  duration = pulseIn(echoPin, HIGH);

  // DEFINE VARIABLES
  jarak = duration*0.034/2;
  jarakInt = int(jarak); // convert float to int
  persen = ((jarTotal-jarak)/jarTotal) * 100; // EDIT INI
  persenInt = int(persen); // convert float to int

  // UPLOAD TO FIREBASE
  Firebase.setFloat("/Jarak/drumB", jarakInt);
  Firebase.setFloat("/Persen/drumB", persenInt);

  // PRINT TO SERIAL MONITOR
  Serial.print("DRUM B | Jarak : ");
  Serial.print(jarakInt);
  Serial.println(" cm");

  // PRINT TO LCD
  lcd.setCursor(0,0);
  lcd.print("Drum B");
  lcd.setCursor(0,1);
  lcd.print("Volume : ");
  lcd.print(persenInt);
  lcd.print(" %");
  
  delay(10000);
}
