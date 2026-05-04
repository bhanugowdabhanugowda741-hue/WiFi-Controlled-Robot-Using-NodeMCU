#include <ESP8266WiFi.h>

const char* ssid = "YourWiFiName";
const char* password = "YourWiFiPassword";

WiFiServer server(80);

int motor1Pin1 = D1;
int motor1Pin2 = D2;
int motor2Pin1 = D3;
int motor2Pin2 = D4;

void setup() {
pinMode(motor1Pin1, OUTPUT);
pinMode(motor1Pin2, OUTPUT);
pinMode(motor2Pin1, OUTPUT);
pinMode(motor2Pin2, OUTPUT);

WiFi.begin(ssid, password);

while (WiFi.status() != WL_CONNECTED) {
delay(500);
}

server.begin();
}

void loop() {
WiFiClient client = server.available();
if (!client) return;

String request = client.readStringUntil('\r');
client.flush();

if (request.indexOf("/FORWARD") != -1) forward();
if (request.indexOf("/BACK") != -1) backward();
if (request.indexOf("/LEFT") != -1) left();
if (request.indexOf("/RIGHT") != -1) right();
if (request.indexOf("/STOP") != -1) stopRobot();

client.println("HTTP/1.1 200 OK");
client.println("Content-Type: text/html");
client.println("");
}

void forward() {
digitalWrite(motor1Pin1, HIGH);
digitalWrite(motor1Pin2, LOW);
digitalWrite(motor2Pin1, HIGH);
digitalWrite(motor2Pin2, LOW);
}

void backward() {
digitalWrite(motor1Pin1, LOW);
digitalWrite(motor1Pin2, HIGH);
digitalWrite(motor2Pin1, LOW);
digitalWrite(motor2Pin2, HIGH);
}

void left() {
digitalWrite(motor1Pin1, LOW);
digitalWrite(motor1Pin2, HIGH);
digitalWrite(motor2Pin1, HIGH);
digitalWrite(motor2Pin2, LOW);
}

void right() {
digitalWrite(motor1Pin1, HIGH);
digitalWrite(motor1Pin2, LOW);
digitalWrite(motor2Pin1, LOW);
digitalWrite(motor2Pin2, HIGH);
}

void stopRobot() {
digitalWrite(motor1Pin1, LOW);
digitalWrite(motor1Pin2, LOW);
digitalWrite(motor2Pin1, LOW);
digitalWrite(motor2Pin2, LOW);
}
