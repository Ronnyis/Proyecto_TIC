#include <WiFi.h>
#include <PubSubClient.h>
#define TOPIC_STAFF "dron/senales"

const char* ssid = "Ronny";
const char* password = "12345678";
const char* mqttServer = "172.29.25.114";
const int mqttPort = 1883;
const int motor1 = 16;
const int motor2 = 27;
const int motor3 = 17;
const int motor4 = 26;

void callback(char*, byte*, unsigned int);

WiFiClient espClient;
PubSubClient client(espClient);
void setup() {
  pinMode(motor1, OUTPUT);
  pinMode(motor2, OUTPUT);
  pinMode(motor3, OUTPUT);
  pinMode(motor4, OUTPUT);
  // Conexión WiFi
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  // Conexión WiFi
   while (true) { // Bucle infinito
    if (WiFi.status() == WL_CONNECTED) {
      Serial.println("Conectado a WiFi!");
      break; // Sale del bucle cuando se conecta
    }
    Serial.println(".");
    delay(200);
   }

  
  // Conexión MQTT
  client.setServer(mqttServer, mqttPort);
  client.setCallback(callback);

  while (!client.connected()) {
    Serial.println("Conectando a MQTT...");

    if (client.connect("ESP32")) {
      Serial.println("Conectado");
    } else {
      Serial.print("Error de conexión: ");
      Serial.print(client.state());
      delay(2000);
    }
  }

  Serial.println("Suscripción a tópicos");
  // Se suscribe al tópico
  client.subscribe(TOPIC_STAFF);
  analogWrite(motor1, 40);
  analogWrite(motor2, 40);
  analogWrite(motor3, 40);
  analogWrite(motor4, 40);
  
}
  // put your setup code here, to run once:

void callback(char* topic, byte* payload, unsigned int length) {
  String payloadStr = "";

  Serial.println("mensaje recibido");

  // Convierte los bytes del payload a String
  for (int i = 0; i < length; i++) {
    payloadStr += (char)payload[i];
  }
  if(payloadStr == "arriba"){
      // fade in from min to max in increments of 5 points:
      // sets the value (range from 0 to 255):
      analogWrite(motor1, 255);
      analogWrite(motor2, 255);
      analogWrite(motor3, 255);
      analogWrite(motor4, 255);
      // wait for 30 milliseconds to see the dimming effect
      delay(30);
    
    
    
  }else if(payloadStr == "abajo"){
    
      // sets the value (range from 0 to 255):
      analogWrite(motor1, 100);
      analogWrite(motor2, 100);
      analogWrite(motor3, 100);
      analogWrite(motor4, 100);
      // wait for 30 milliseconds to see the dimming effect
      delay(30);
      
  }else if(payloadStr == "izquierda"){
    
      // sets the value (range from 0 to 255):
      analogWrite(motor1, 255);
      analogWrite(motor2, 100);
      analogWrite(motor3, 255);
      analogWrite(motor4, 100);
      // wait for 30 milliseconds to see the dimming effect
      delay(30);
     
  }else if(payloadStr == "derecha"){
    
      // sets the value (range from 0 to 255):
      analogWrite(motor1, 100);
      analogWrite(motor2, 255);
      analogWrite(motor3, 100);
      analogWrite(motor4, 255);
      // wait for 30 milliseconds to see the dimming effect
      delay(30);
         
  }
  else if(payloadStr == "off"){
    analogWrite(motor1, 0);
    analogWrite(motor2, 0);
    analogWrite(motor3, 0);
    analogWrite(motor4, 0);

  }
  Serial.println(payloadStr);

}

void loop() {
  client.loop();
}

