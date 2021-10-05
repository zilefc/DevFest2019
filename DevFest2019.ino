#include <ESP8266WiFi.h>
#include<FirebaseArduino.h>

#define FIREBASE_HOST "cursoiot-02-default-rtdb.firebaseio.com/"
#define FIREBASE_AUTH "nwEuF0XUCr7igrFFu9G0VHxYCXtUWlTOHjRVVLdw"

#define WIFI_SSID "TME Education"
#define WIFI_PASSWORD "mz1234@mzm"

#define Relay 0
int val1;

void setup()
{
  Serial.begin(115200);
  
  pinMode(Relay, OUTPUT);

  
  digitalWrite(Relay, HIGH);

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
  
  Firebase.setInt("S1", 0);
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

  
  val1 = Firebase.getString("S1").toInt();
  if (val1 == 1)
  {
    digitalWrite(Relay, LOW);
    Serial.println("light ON");
  }
  else if (val1 == 0)         {
    digitalWrite(Relay, HIGH);
    Serial.println("light OFF");
  }

}
