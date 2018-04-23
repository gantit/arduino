void temp() {
  sensors.requestTemperatures();
  float temP1 = sensors.getTempCByIndex(0);
  float temP2 = sensors.getTempCByIndex(1);
  
  Serial.print("[WATER_TEMP1]: ");
  Serial.print(temP1);
  Serial.println(":[WATER_TEMP1]");
  Serial.print("[WATER_TEMP2]: ");
  Serial.print(temP2);
  Serial.println(":[WATER_TEMP2]");
}
