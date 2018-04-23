void phValue() {
  int ph_pin = A0; // A0 -> Po
  const int analogInPin = A0; 
int sensorValue = 0; 
unsigned long int avgValue; 
float b;
int buf[10],temp;
  int m_4 = 573; // ph4
  int m_7 = 536; // ph7

  int measure = 0;
  float prom = 0;

  for (int i = 0; i < 20; i++) {
    measure = analogRead(ph_pin);
    prom = prom + measure;
  }
  
  prom = (float)prom / 20;

  //calibracion
  float Po = 7 + ((prom - m_7 ) * 3 / ( m_7 - m_4 ));
  Serial.print("Po = ");
  Serial.println(Po);

  char phBuffer[18];
  dtostrf(pHValue, 4, 2, phBuffer);

  envio de ph
  mqttClient.publish("READ_MTQQ_PH", phBuffer);
}


