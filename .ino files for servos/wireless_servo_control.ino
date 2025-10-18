#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <Servo.h>

Servo myServo1, myServo2, myServo3;

int angle1 = 0, angle2 = 0, angle3 = 0;

const char* ssid = "Pussy Hunter";    
const char* password = "Jk@18.12";   

ESP8266WebServer server(80);

void handleSetAngle() {
  if (server.hasArg("Servo 1")) {
    angle1 = constrain(server.arg("Servo 1").toInt(), 0, 180);
    myServo1.write(angle1);
    Serial.print(angle1);
  }

  if (server.hasArg("Servo 2")) {
    angle2 = constrain(server.arg("Servo 2").toInt(), 0, 180);
    myServo2.write(angle2);
    Serial.print(angle2);
  }

  if (server.hasArg("Servo 3")) {
    angle3 = constrain(server.arg("Servo 3").toInt(), 0, 180);
    myServo3.write(angle3);
    Serial.print(angle3);
  }

  server.send(200, "text/plain", "OK");
}

void setup() {
  Serial.begin(115200);

  // Attach servos
  myServo1.attach(D1,500,2500);  
  myServo2.attach(D2,500,2500);  
  myServo3.attach(D4,500,2500);  

  myServo1.write(0);
  myServo2.write(0);
  myServo3.write(0);

  // WiFi connection
  Serial.print("Connecting to WiFi");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConnected to WiFi");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  // Handle "/set"
  server.on("/set", handleSetAngle);
  server.begin();
}

void loop() {
  server.handleClient();
}
