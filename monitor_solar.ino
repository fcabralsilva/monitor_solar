String VERSAO = "001 - 16/10/2019";
//---------------------------------------
//    INCLUINDO BIBLIOTECAS
//---------------------------------------
#include <WiFi.h>
#include <DNSServer.h>
#include <WebServer.h>
#include <WiFiManager.h>

const int SENSOR_TENSAO = 34; //PINO ANALÓGICO EM QUE O SENSOR ESTÁ CONECTADO.
const char CABECALHO_IN[] ="<!DOCTYPE HTML><html><head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\"><link rel=\"stylesheet\" href=\"https://use.fontawesome.com/releases/v5.7.2/css/all.css\" integrity=\"sha384-fnmOCqbTlWIlj8LyTjo7mOUStjsKC4pOpQbqyi7RrhN7udi9RwhKkMHpvLbHG9Sr\" crossorigin=\"anonymous\">";
const char STYLE[] ="<style>html {font-family: Arial;display: inline-block;margin: 0px auto;text-align: center;}h2 { font-size: 3.0rem; }p { font-size: 3.0rem; }.units { font-size: 1.2rem; }.ds-labels{font-size: 1.5rem;vertical-align:middle;padding-bottom: 15px;}</style>";
const char CABECALHO_OUT[] ="</head><body>";
const char TITULO_H2[] ="<h2>Monitoramento Solar</h2>";
const char TENSAO_CORRENTE[] ="<p><i class=\"fas fa-solar-panel\" style=\"color:#059e8a;\"></i> <span class=\"ds-labels\">Tensão </span> <span id=\"\">12</span><sup class=\"units\">V</sup><span class=\"ds-labels\">Corrente </span> <span id=\"\">1000</span><sup class=\"units\">mA</sup></p>";
const char FINAL_PAGINA []="</body></html>";
WiFiServer server(80);
void setup() {
  pinMode(SENSOR_TENSAO, INPUT); //DEFINE O PINO COMO ENTRADA
  Serial.begin(115200); //INICIALIZA A SERIAL
  WiFiManager wifiManager;
  wifiManager.autoConnect("AutoConnectAP");
  Serial.println("COnectado ao WIFI :) ");
  Serial.println();
  server.begin();
}

void loop() {
  WiFiManager wifiManager;
  WiFiClient client = server.available();
  String URL, buf;
  if (client)
  {
    Serial.println("Client WEB conectado");
    URL = client.readStringUntil('\r');
  } else {
    URL = "";
  }
  if (URL != "")
  {
    buf += String(CABECALHO_IN);
    buf += String(STYLE);
    buf += String(CABECALHO_OUT);
    buf += String(TITULO_H2);
    buf += String(TENSAO_CORRENTE);
    buf += String(FINAL_PAGINA);
    client.print(buf); client.flush(); client.stop();
    Serial.println("Client WEB desconectado."); Serial.println(); 
  }
}
// FUNÇÃO QUE REALIZA LEITURA DO SENSOR DE TENSÃO DC 25V
float tensao_dc()
{
  float tensaoEntrada = 0.0; //VARIÁVEL PARA ARMAZENAR O VALOR DE TENSÃO DE ENTRADA DO SENSOR
  float tensaoMedida = 0.0; //VARIÁVEL PARA ARMAZENAR O VALOR DA TENSÃO MEDIDA PELO SENSOR
  float valorR1 = 30000; //VALOR DO RESISTOR 1 DO DIVISOR DE TENSÃO
  float valorR2 = 7500; // VALOR DO RESISTOR 2 DO DIVISOR DE TENSÃO
  int leituraSensor = 0; //VARIÁVEL PARA ARMAZENAR A LEITURA DO PINO ANALÓGICO
  leituraSensor = analogRead(SENSOR_TENSAO); //FAZ A LEITURA DO PINO ANALÓGICO E ARMAZENA NA VARIÁVEL O VALOR LIDO
  tensaoEntrada = (leituraSensor * 6) / 4024.0; //VARIÁVEL RECEBE O RESULTADO DO CÁLCULO
  tensaoMedida = tensaoEntrada / (valorR2 / (valorR1 + valorR2)); //VARIÁVEL RECEBE O VALOR DE TENSÃO DC MEDIDA PELO SENSOR
  //Serial.print("Tensão DC medida: "); //IMPRIME O TEXTO NA SERIAL
  //Serial.print(tensaoMedida, 2); //IMPRIME NA SERIAL O VALOR DE TENSÃO DC MEDIDA E LIMITA O VALOR A 2 CASAS DECIMAIS
  //Serial.println("V"); //IMPRIME O TEXTO NA SERIAL
  return tensaoMedida;
}
