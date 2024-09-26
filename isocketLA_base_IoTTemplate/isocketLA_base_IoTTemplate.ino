/*-------------------------------------------------------*
  IoT Kod Template bagi IoT
 --------------------------------------------------------* */
//--------------------------------------------------------------------------
//===================== Seksyen 1 - Senarai HEADER (Library) ==============

#include <Wire.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
//-- Library MQTT dan Sambungan Wifi
#include <WiFi.h>
#include <PubSubClient.h>
//--- Library bagi One wire dan sensor DS18B20
#include <OneWire.h>
#include <DallasTemperature.h>

//----- ISTIHAR Sambungan nama Pin dengan Nombor Fizikal PIN ----
//--------------------------------------------------------------------------

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

//-----ISTIHAR Pemboleh ubah dengan jenis Data yang digunakan---

//---- pemboleh ubah bagi PENETAPAN WIFI --
const char* ssid = "IoT";
const char* password = "iot@kksj2023";

// --- data pembolehubah
char varPotString[8];
float dataMoisture;
long lastMsg = 0;
char msg[50];
int value = 0;


//-----Istihar Cipta Objek dari Librari berkaitan------------------ ----
//--------------------------------------------------------------------------
// Istihar Module OLED Display - SSD1306 
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

//----ISTIHAR SENSOR SUHU DS18B20 -----
OneWire oneWire(SensorSuhu);
DallasTemperature sensors(&oneWire);

//----ISTIHAR Wifi dan Mqtt -----
WiFiClient espClient;                                                                          
PubSubClient client(espClient); //MQTT
const char* mqtt_server = "broker.hivemq.com";


//===================== Seksyen 2 - Fungsi Setup ===========================
//--------------------------------------------------------------------------

void setup() {

  pinMode(relay01,OUTPUT);
  pinMode(relay02,OUTPUT);
  pinMode(buzzer,OUTPUT);

Serial.begin(115200);

    if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  delay(100);  

  sensors.begin();

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("----  iSocket LA  ---");
  display.setCursor(0,10);
  display.println("---------------------");
  display.display();
  delay(5000);
    
}

//===================== Seksyen 2 - Fungsi Setup ===========================
//--------------------------------------------------------------------------
void loop() {
if (!client.connected()) {
    reconnect(); }
client.loop();
long now = millis();

if (now - lastMsg > 1000) {  
  lastMsg = now;

//----------- Tulis Kod anda disini ----------------------------------

  int dataLDR = analogRead(sensorLDR);  
    Serial.print("LDR Value : ");
    Serial.println(dataLDR);
    // Convert the value to a char array
    dtostrf(dataLDR, 1, 2, varPotString);
    client.publish("isocket/ldr", varPotString);
    
  //-------------------Tammat ------------------------------------------------

  }

}

 
