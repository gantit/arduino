void readWifiData() {
  if ( W.indexOf("D=[") > 0 ) {
    int pinI = W.indexOf("D=[") + 3; // Obtener el 1er el numero de la cadena
    int pinF = W.indexOf("]") - 1; // Obtener el 2do el numero de la cadena
    if (pinI != pinF ) { // Si son Diferentes quiere decir que es un pin superio a 10 y tiene 2 digitos
      ouput_str = "D=[" + String(W[pinI]) + String(W[pinF]) + "]"; //concatenamos los dos digitos
    } else {
      ouput_str = "D=[" + String(W[pinI]) + "]";
    }
    ouput_str.toCharArray(ouput, ouput_str.length() + 1); //packaging up the data to publish to mqtt whoa...

    mqttClient.publish("READ_MTQQ_Digital", ouput);
    Serial.print(ouput);
  }

  if ( W.indexOf("A=[") > 0 ) {
    int pinI = W.indexOf("A=[") + 3; // Obtener el 1er el numero de la cadena
    int pinF = W.indexOf("]") - 1; // Obtener el 2do el numero de la cadena
    if (pinI != pinF ) { // Si son Diferentes quiere decir que es un pin superio a 10 y tiene 2 digitos
      ouput_str = "A=[" + String(W[pinI]) + String(W[pinF]) + "]";//concatenamos los dos digitos
    } else {
      ouput_str = "A=[" + String(W[pinI]) + "]";
    }
    ouput_str.toCharArray(ouput, ouput_str.length() + 1); //packaging up the data to publish to mqtt whoa...

    mqttClient.publish("READ_MTQQ_Analogic", ouput);
    Serial.print(ouput);
  }

  if ( W.indexOf("V=[") > 0 ) {
    bool value = W.indexOf("ON") > 0; // Obtener el 1er el numero de la cadena
    if (value) { // Si son Diferentes quiere decir que es un pin superio a 10 y tiene 2 digitos
      ouput_str = " V=[ON]";//concatenamos los dos digitos
    } else {
      ouput_str = " V=[OFF]";
    }
    ouput_str.toCharArray(ouput, ouput_str.length() + 1); //packaging up the data to publish to mqtt whoa...

    mqttClient.publish("READ_MTQQ_Value", ouput);
    Serial.println(ouput);
  }
  Serial.println();
  W = ' ';
}

