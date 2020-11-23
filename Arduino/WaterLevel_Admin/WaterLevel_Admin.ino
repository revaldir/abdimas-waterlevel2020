#include <FirebaseArduino.h>
#include <ESP8266WiFi.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

// DEFINE LCD I2C
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2);

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
  int drumAInt, drumBInt;
  float drumA, drumB;
  String path = "/";

  // FETCH ALL
  FirebaseObject object = Firebase.get(path);

  // EXTRACT FROM ALL
  drumA = object.getFloat("Persen/drumA");
  drumB = object.getFloat("Persen/drumB");

  // CONVERT
  drumAInt = int(drumA);
  drumBInt = int(drumB);

  // PRINT TO LCD
  lcd.setCursor(0,0);
  lcd.print("Drum A : ");
  lcd.print(drumAInt);
  lcd.print(" %");
  lcd.setCursor(0,1);
  lcd.print("Drum B : ");
  lcd.print(drumBInt);
  lcd.print(" %");
  
  delay(10000);
}
