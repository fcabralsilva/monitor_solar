void sensor_tensão(int pin){
	//VARIÁVEL PARA ARMAZENAR O VALOR DE TENSÃO DE ENTRADA DO SENSOR
	float TENSAO_ENTRADA_DC = 0.0;
	//VARIÁVEL PARA ARMAZENAR O VALOR DA TENSÃO MEDIDA PELO SENSOR
	float TENSAO_MEDIA_DC = 0.0; 
	//VALOR DO RESISTOR 1 DO DIVISOR DE TENSÃO
	float VALOR_R1 = 30000.0; 
	// VALOR DO RESISTOR 2 DO DIVISOR DE TENSÃO
	float VALOR_R2 = 7500.0; 
	//VARIÁVEL PARA ARMAZENAR A LEITURA DO PINO ANALÓGICO
	int LEITURA_SENSOR = 0; 
	//FAZ A LEITURA DO PINO ANALÓGICO E ARMAZENA NA VARIÁVEL O VALOR LIDO
	LEITURA_SENSOR = analogRead(PINO_SENSOR_T); 
	//VARIÁVEL RECEBE O RESULTADO DO CÁLCULO
	TENSAO_ENTRADA_DC = (LEITURA_SENSOR * 5.0) / 1024.0; 
	//VARIÁVEL RECEBE O VALOR DE TENSÃO DC MEDIDA PELO SENSOR
	TENSAO_MEDIA_DC = TENSAO_ENTRADA_DC / (VALOR_R2/(VALOR_R1+VALOR_R2)); 
  //IMPRIME O TEXTO NA SERIAL
	Serial.print("Tensão DC medida: "); 
	//IMPRIME NA SERIAL O VALOR DE TENSÃO DC MEDIDA E LIMITA O VALOR A 2 CASAS DECIMAIS
	Serial.print(TENSAO_MEDIA_DC,2); 
	//IMPRIME O TEXTO NA SERIAL
	Serial.println("V"); 
}
String readDSTemperatureC() {
  // Call sensors.requestTemperatures() to issue a global temperature and Requests to all devices on the bus
  sensors.requestTemperatures(); 
  float tempC = sensors.getTempCByIndex(0);

  if(tempC == -127.00) {
    Serial.println("Falha na leitura do sensor DS18B20");
    return "--";
  } else {
    Serial.print("Temperatura: ");
    Serial.println(tempC); 
  }
  return String(tempC);
}

