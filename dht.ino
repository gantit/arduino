void dth() {
  char humidityBuffer[50];
  char tempBuffer[50];
  
  dtostrf(dht.readTemperature(), 5, 2, tempBuffer);
  dtostrf(dht.readHumidity(), 5, 2, humidityBuffer);
  
  //Se envian las variables
  mqttClient.publish("READ_MTQQ_EXT_TEMP", tempBuffer);
  mqttClient.publish("READ_MTQQ_EXT_HUM", humidityBuffer);
}
