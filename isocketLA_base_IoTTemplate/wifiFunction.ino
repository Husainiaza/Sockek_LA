void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Sambungan ke : ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  display.setTextColor(WHITE,BLACK);
  display.setCursor(0,10);
  display.print("WiFi connected");
  display.setCursor(0,20);
  display.print(WiFi.localIP());
   display.display();
  delay(5000);
}

void callback(char* topic, byte* message, unsigned int length) {
  Serial.print("Message arrived on topic: ");
  Serial.print(topic);
  Serial.print(". Message: ");
  String messageTemp;
  
  for (int i = 0; i < length; i++) {
    Serial.print((char)message[i]);
    messageTemp += (char)message[i];
  }
  Serial.println();

  // add more if statements to control more GPIOs with MQTT

  // If a message is received on the topic esp32/output, you check if the message is either "on" or "off". 
  

   if (String(topic) == "isocket/buzzer") {
    Serial.print("data diterima berubah kepada : ");
    if(messageTemp == "on"){
      Serial.println("on");
      digitalWrite(buzzer,HIGH);
     
    }
    else if(messageTemp == "off"){
      Serial.println("off");
      digitalWrite(buzzer,LOW);
      
    }
  }
  
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("sambungan ke MQTT broker...");
    // Attempt to connect
    if (client.connect("Ubah_kepada_NamaID_anda")) {
      Serial.println("sambungan berjaya");
      // Subscribe
      client.subscribe("isocket/buzzer");
    } else {
      Serial.print("sambungan gagal, rc=");
      Serial.print(client.state());
      Serial.println(" cubaan sambungan semula dalam 5 saat");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}
