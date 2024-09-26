//--------------------------------------------------------------------------
//----Seksyen 1 - Senarai HEADER (Library) yang diperlukan------------- ----

#include <Wire.h>
#include <SPI.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

//------------------------------Seksyen 1 - TAMAT --------------------- ----

//--------------------------------------------------------------------------
//-----Seksyen 2 - ISTIHAR Sambungan nama Pin dengan Nombor Fizikal PIN ----
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

//------------------------------Seksyen 2 - TAMAT --------------------- ----


//-----Seksyen 3 - Cipta Objek dari Librari berkaitan------------------ ----
//--------------------------------------------------------------------------
// Istihar Module OLED Display - SSD1306 
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Istihar Module Sersor Suhu Dallas 18B20
OneWire oneWire(SensorSuhu);
DallasTemperature DS18B20(&oneWire);

//------------------------------Seksyen 3 - TAMAT --------------------- ----


//-----Seksyen 4 - ISTIHAR Pemboleh ubah dengan jenis Data yang digunaka ---
//--------------------------------------------------------------------------
float dataSuhuC; // suhu dalam Celsius
int dataLDR;
//------------------------------Seksyen 4 - TAMAT --------------------- ----


//-----Seksyen 5 - Fungsi Setup --------------------------------------------
//--------------------------------------------------------------------------
void setup() {
  pinMode(relay01,OUTPUT);
  pinMode(relay02,OUTPUT);
  pinMode(buzzer,OUTPUT);

  Serial.begin(115200); // initialize serial

if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }

 DS18B20.begin();    // initialize the DS18B20 sensor
  
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
//------------------------------Seksyen 4 - TAMAT --------------------- ----


//-----Seksyen 6 - Fungsi Utama (LOOP) --------------------------------------------
//--------------------------------------------------------------------------
void loop() {

//------sensor suhu -------------------------------------------------------
  DS18B20.requestTemperatures();       // arahan baca suhu
  dataSuhuC = DS18B20.getTempCByIndex(0);  // nilai suhu disimpan dalam pembolehubah tempC
 
  Serial.print("Temperature: ");
  Serial.print(dataSuhuC);    
  Serial.print("°C");


//------sensor LDR -------------------------------------------------------
  dataLDR = analogRead(sensorLDR);
  Serial.print("Cahaya: ");
  Serial.println(dataLDR);   

//------Kawalan relay -------------------------------------------------------  
  digitalWrite(relay02,HIGH);
  digitalWrite(relay01,LOW);
  delay (300);
  digitalWrite(relay02,LOW);
  digitalWrite(relay01,HIGH);
  delay (300);
  digitalWrite(relay02,LOW);
  digitalWrite(relay01,LOW);
  delay (300);
  digitalWrite(relay02,HIGH);
  digitalWrite(relay01,HIGH);
  delay (300);
  digitalWrite(buzzer,HIGH);
  delay (500);
  digitalWrite(buzzer,LOW);
  delay (100);

//------Paparan di OLED Display--------------------------------------------------  
  display.clearDisplay();
  display.setCursor(0,0);
  display.println("---  iSocket LA  ---");
  display.setCursor(0,10);
  display.println("K. Komuniti Sbg Jaya");
  display.setCursor(10,20);
  display.println("--------------------");
  display.setCursor(0,30);
  display.print("BACAAN SUHU :");
  display.print(dataSuhuC,1);
  display.setCursor(0,40);
  display.print("BACAAN LDR  :");
  display.print(dataLDR);
  display.setCursor(0, 60);
  display.display();  
}
