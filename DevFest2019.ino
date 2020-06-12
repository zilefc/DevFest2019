// d1  d2  d5

#include <ESP8266WiFi.h>
#include<FirebaseArduino.h>
#define FIREBASE_HOST "myroom-b3273.firebaseio.com/"
#define FIREBASE_AUTH "tDLFJNprBAPi8mBwhA4pbEllJTnUVykDxMsMjVMy"
#define WIFI_SSID "Frederico Zile"
#define WIFI_PASSWORD "1234mzhd"
#define Relay1 12 //D6
int val1;
#define Relay2 14 //D2
int val2;
#define Relay3 4  //D1
int val3;
#define Relay4 5 //D5
int val4;
void setup()
{
  Serial.begin(115200);
  
  pinMode(Relay2, OUTPUT);
  pinMode(Relay3, OUTPUT);
  pinMode(Relay4, OUTPUT);

  
  digitalWrite(Relay2, HIGH);
  digitalWrite(Relay3, HIGH);
  digitalWrite(Relay4, HIGH);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connectando");
  
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connectado:");
  Serial.println(WiFi.localIP());

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  
  Firebase.setInt("S2", 0);
  Firebase.setInt("S3", 0);
  Firebase.setInt("S4", 0);
}
void firebasereconnect()
{
  Serial.println("Tentando acessar a base de dados");
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}
void loop()
{
  if (Firebase.failed())
  {
    Serial.print("setting number failed:");
    Serial.println(Firebase.error());
    firebasereconnect();
    return;
  }

  
  val2 = Firebase.getString("S2").toInt();
  if (val2 == 1)
  {
    digitalWrite(Relay2, LOW);
    Serial.println("light 2 ON");
  }
  else if (val2 == 0)         {
    digitalWrite(Relay2, HIGH);
    Serial.println("light 2 OFF");
  }

  val3 = Firebase.getString("S3").toInt();
  if (val3 == 1)
  {
    digitalWrite(Relay3, LOW);
    Serial.println("light 3 ON");
  }
  else if (val3 == 0)  {
    digitalWrite(Relay3, HIGH);
    Serial.println("light 3 OFF");
  }

  val4 = Firebase.getString("S4").toInt();
  if (val4 == 1)
  {
    digitalWrite(Relay4, LOW);
    Serial.println("light 4 ON");
  }
  else if (val4 == 0)
  {
    digitalWrite(Relay4, HIGH);
    Serial.println("light 4 OFF");
  }
}
