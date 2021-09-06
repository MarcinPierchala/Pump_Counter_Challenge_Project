
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <Wire.h>

String user = "Marcin";
String pass = "*********";

#define ssid "Galaxy Note9d6fb"
#define password "************************"
#define host "192.168.43.94"
#define swPin D8  // touch button Pin
int state;
#define echoPin D7 // Echo Pin
#define trigPin D6 // Trigger Pin
#define ledPin D5 // Led indicator
int ledPinSt = LOW;
unsigned long fly = 0;
unsigned long pulse = 0; 


 
long duration, distance; // Duration used to calculate distance
int pump, up, ex;  //up & down used to count pumps
int cal = 0;
void setup()
{
Serial.begin (9600);
pinMode(trigPin, OUTPUT);
pinMode(echoPin, INPUT);
pinMode(swPin,INPUT);
pinMode(ledPin, OUTPUT);
state == 0;
pump = 0;
up = 0;
ex = 0;
digitalWrite(ledPin, LOW);


Serial.println("Witaj " + user); 
Serial.println();
Serial.println();
Serial.print("Connecting to ");
Serial.println(ssid);
WiFi.begin(ssid,password);

while (WiFi.status() != WL_CONNECTED) {
        digitalWrite(ledPin, HIGH);
        delay(500);
        Serial.print(".");
        digitalWrite(ledPin, LOW);
        delay(500);
}

Serial.println("");
Serial.println("WiFi connected");
Serial.println("IP address: ");
Serial.println(WiFi.localIP());
}
 
void loop()
{
   boolean touchState;
  touchState = digitalRead(swPin);

if (touchState == HIGH){
  state = state+1;
  delay(500);
}

digitalWrite(trigPin, LOW);
delayMicroseconds(2);
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
duration = pulseIn(echoPin, HIGH);
//Calculate the distance (in cm) based on the speed of sound.
distance = duration/58.2;
//Serial.println(distance);
//Delay 50ms before next reading.
delay(50);
if (distance > 25){  // to count next pump must go up
  up = distance;
}
if (distance <10 && up > 25){ // method to count one complete pump
  pump = pump+1;
  ex = ex+1;
  digitalWrite(ledPin, HIGH);
  delay(800);
  Serial.println("ILOSC POMPEK : " + String(pump)+ user);
  up = 0;
  digitalWrite(ledPin,LOW);
}
cal = pump*5;
if(state == 1){
digitalWrite(ledPin, HIGH);

WiFiClient client;
const int httpPort = 80;
//const char httpPort = "192.168.43.94/xampp/htdocs/moj_dzialajacy_connect.php?";
if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    digitalWrite(ledPin, HIGH);
    return;
}
    // This will send the request to the server
  client.print(String("GET http://localhost/moj_dzialajacy_connect.php?") + 
                          ("&user=") + user +
                          ("&pass=") + pass +
                          ("&pump=") + pump +
                          ("&cal=") + cal +
                          " HTTP/1.1\r\n" +
                 "Host: " + host + "\r\n" +
                 "Connection: close\r\n\r\n");
unsigned long timeout = millis();
while (client.available() == 0) {
    if (millis() - timeout > 1000) {
        Serial.println(">>> Client Timeout !");
        client.stop();
        return;
    }
}

// Read all the lines of the reply from server and print them to Serial
while(client.available()) {
    String line = client.readStringUntil('\r');
    Serial.print(line);
        
}

Serial.println();
Serial.println("closing connection");
ex = 0;
state = 2;
pump = 0;

digitalWrite(ledPin,LOW);
delay(200);
digitalWrite(ledPin,HIGH);
delay(200);
digitalWrite(ledPin,LOW);
delay(200);
digitalWrite(ledPin,HIGH);
delay(200);
digitalWrite(ledPin,LOW);
delay(200);
digitalWrite(ledPin,HIGH);
delay(200);
digitalWrite(ledPin,LOW);
delay(200);
digitalWrite(ledPin,HIGH);
delay(200);
digitalWrite(ledPin,LOW);
delay(200);
digitalWrite(ledPin,HIGH);
delay(200);
digitalWrite(ledPin,LOW);
delay(200);
}
}
