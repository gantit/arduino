void loop(void) {
  //readData();
  if (!mqttClient.connected()) {
    reconnect();
  }
  mqttClient.loop();
  dth();
  phValue();
  delay(3000);
}
