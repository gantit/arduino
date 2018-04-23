void waterValue() {
  int measureHigh = 0;
  measureHigh = digitalRead(highLvl_pin);
  int measureLow = 0;
  measureLow = digitalRead(lowLvl_pin);

  Serial.print("[WATER_LVL_HIGH]: ");
  Serial.print(measureHigh);
  Serial.println(":[WATER_LVL_HIGH]");

  Serial.print("[WATER_LVL_LOW]: ");
  Serial.print(measureLow);
  Serial.println(":[WATER_LVL_LOW]");
}
