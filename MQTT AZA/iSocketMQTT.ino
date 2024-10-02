//--------------------------------------------------------------------------
//----Seksyen 1 - Senarai HEADER (Library) yang diperlukan------------- ----
#include <WiFi.h>
#include <MQTT.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DallasTemperature.h>

//---Actuator and Relay  pin connection---
#define relay01 27 
#define relay02 26
#define buzzer 25
#define SensorSuhu  4 // pin sambungan ke DS18B20 (ONEWIRE)
#define sensorLDR 34
//---Analog Sensor  pin connection---

//---Tentukan nama yg diumpukkan kepada satu nilai awal yg ditetapkan --
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

//-------Istihar constant --------------------- ----



const char ssid[] = "IoT";
const char pass[] = "iot@kksj2023";


//------ Cipta Objek dari Librari berkaitan---------------------------------
//--------------------------------------------------------------------------
WiFiClient net;
MQTTClient client;

// Istihar Module OLED Display - SSD1306 
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Istihar Module Sersor Suhu Dallas 18B20
OneWire oneWire(SensorSuhu);
DallasTemperature DS18B20(&oneWire);


//------ ISTIHAR Pemboleh ubah dengan jenis Data yang digunakan---
//--------------------------------------------------------------------------

unsigned long lastMillis = 0;

float dataSuhuC; // suhu dalam Celsius
int dataLDR;
//------------------------------Seksyen 1 - TAMAT --------------------- ----

void connect() {
  Serial.print("checking wifi...");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }

  Serial.print("\nconnecting...");
  while (!client.connect("arduino47557636656")) {
    Serial.print(".");
    delay(1000);
  }

  Serial.println("\nconnected!");

  client.subscribe("/hello");
  client.subscribe("socketLA01/buzzer");
  client.subscribe("socketLA01/socket1");
  client.subscribe("socketLA01/socket2");
 
}

void messageReceived(String &topic, String &payload) {
  //Serial.println("incoming: " + topic + " - " + payload);
   Serial.println(payload);
  
  //==============================================================
  if(String(topic) == "socketLA01/buzzer") 
  {
      if(payload =="on")
      {
      Serial.println(payload);
      digitalWrite(buzzer,HIGH);
      Serial.println("Buzzer ON");
      client.publish("socketLA01/buzzer/status", "Buzzer ON");
      }
      
      else if(payload =="off")
      {
        Serial.println(payload);
        digitalWrite(buzzer,LOW);
        Serial.println("Buzzer OFF");
        client.publish("socketLA01/buzzer/status", "Buzzer OFF");
      }
  } 


  if(String(topic) == "socketLA01/socket1") 
  {
      if(payload =="on")
      {
      Serial.println(payload);
      digitalWrite(relay01,HIGH);
      Serial.println("socket1 ON");
      client.publish("socketLA01/socket1/status", "socket1 ON");
      }
      
      else if(payload =="off")
      {
        Serial.println(payload);
        digitalWrite(relay01,LOW);
        Serial.println("socket1 OFF");
        client.publish("socketLA01/socket1/status", "socket1 OFF");
      }
  }

   if(String(topic) == "socketLA01/socket2") 
  {
      if(payload =="on")
      {
      Serial.println(payload);
      digitalWrite(relay02,HIGH);
      Serial.println("socket2 ON");
      client.publish("socketLA01/socket2/status", "socket2 ON");

      }
      
      else if(payload =="off")
      {
        Serial.println(payload);
        digitalWrite(relay02,LOW);
        Serial.println("Buzzer OFF");
         client.publish("socketLA01/socket2/status", "socket2 OFF");
      }
  }

  //==============================================================
  // Note: Do not use the client in the callback to publish, subscribe or
  // unsubscribe as it may cause deadlocks when other things arrive while
  // sending and receiving acknowledgments. Instead, change a global variable,
  // or push to a queue and handle it in the loop after calling `client.loop()`.
}

void setup() {
  pinMode(relay01,OUTPUT);
  pinMode(relay02,OUTPUT);
  pinMode(buzzer,OUTPUT);

  Serial.begin(115200);

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }

  WiFi.begin(ssid, pass);

  

  // Note: Local domain names (e.g. "Computer.local" on OSX) are not supported
  // by Arduino. You need to set the IP address directly.
  client.begin("broker.hivemq.com", net);
  client.onMessage(messageReceived);

 

  DS18B20.begin();    // initialize the DS18B20 sensor
  
  connect();
  
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("---  iSocket LA  ---");
  display.setCursor(0,10);
  display.println("K. Komuniti Sbg Jaya");
  display.setCursor(10,20);
  display.println("--------------------");
  display.display();
  delay(5000);



}

void loop() {
  client.loop();
  delay(10);  // <- fixes some issues with WiFi stability

  if (!client.connected()) {
    connect();
  }

  // publish a message roughly every second.
  if (millis() - lastMillis > 1000) {
    lastMillis = millis();
    client.publish("/hello", "world");

//===========================================================================================
//------sensor Suhu-----------------
  DS18B20.requestTemperatures();       // arahan baca suhu
  dataSuhuC = DS18B20.getTempCByIndex(0);  // nilai suhu disimpan dalam pembolehubah tempC
 
  Serial.print("Temperature: ");
  Serial.print(dataSuhuC);    
  Serial.println("°C");

  client.publish("socketLA01/suhu", String(dataSuhuC));

//------sensor LDR -----------------
  dataLDR = analogRead(sensorLDR);
  Serial.print("Cahaya: ");
  Serial.println(dataLDR);  

  client.publish("socketLA01/ldr", String(dataLDR)); 

//------Paparan di OLED Display--------------------------------------------------  
  display.clearDisplay();
  display.setCursor(0,0);
  display.print("---  iSocket LA  ---");
  display.setCursor(0,10);
  display.print("K. Komuniti Sbg Jaya");
  display.setCursor(10,20);
  display.print("--------------------");
  display.setCursor(0,30);
  display.print("BACAAN SUHU :");
  display.print(dataSuhuC,1);
  display.setCursor(0,40);
  display.print("BACAAN LDR  :");
  display.print(dataLDR);
  display.display();  
//=============================================================================================


  }
}
