#ifdef ESP32
  #include <WiFi.h>
  #include <ESPAsyncWebServer.h>
#else
  #include <Arduino.h>
  #include <ESP8266WiFi.h>
  #include <Hash.h>
  #include <ESPAsyncTCP.h>
  #include <ESPAsyncWebServer.h>
#endif
#include <OneWire.h>
#include <DallasTemperature.h>

// Data wire is connected to GPIO 4
#define ONE_WIRE_BUS 4

// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature sensor 
DallasTemperature sensors(&oneWire);

//PINO ANALÓGICO EM QUE O SENSOR ESTÁ CONECTADO
const int PINO_SENSOR_T = A2; 

// DAS CONEXÃO WIFI
const char* ssid = "redea";
const char* password = "!g@t0pret0203154121";

// PORTA SERVIDOR WEB
AsyncWebServer server(80);

// Replaces placeholder with DHT values
String processor(const String& var){
  Serial.println(var);
  if(var == "TEMPERATUREC"){
    return readDSTemperatureC();
  }
  return String();
}

void setup(){
	//DEFINE O PINO COMO ENTRADA
	pinMode(PINO_SENSOR_T, INPUT); 

  Serial.begin(115200);
  Serial.println();
  
  // INICIA A LIB DO SENSOR DS18B20
  sensors.begin();
  
  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  Serial.println("Conectando ao WIFI ");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
	
  Serial.println();
  
  // EXIBE IP OBTIDO DO ROTEADOR
  Serial.println(WiFi.localIP());

  // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html, processor);
  });
  server.on("/temperaturec", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", readDSTemperatureC().c_str());
  });
	sensor_tensão(PINO_SENSOR_T);
  server.begin();
}
 
void loop(){
  
}
