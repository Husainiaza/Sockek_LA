//--------------------------------------------------------------------------
//----Seksyen 1 - Senarai HEADER (Library) yang diperlukan------------- ----

#include <Wire.h>
#include <SPI.h>
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


//------------------------------Seksyen 3 - TAMAT --------------------- ----


//-----Seksyen 4 - ISTIHAR Pemboleh ubah dengan jenis Data yang digunakan---
//--------------------------------------------------------------------------

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
//------------------------------Seksyen 4 - TAMAT --------------------- ----


//-----Seksyen 6 - Fungsi Utama (LOOP) --------------------------------------------
//--------------------------------------------------------------------------
void loop() {


}
