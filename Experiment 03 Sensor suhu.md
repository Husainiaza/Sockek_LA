# **Eksperimen digital OUTPUT - Ujikaji 3 : Sensor suhu 18b20


## Ujikaji 3: Membaca suhu 18B20 **

penambahan pada header (define)
```
//----- Library yang perlu dimaksudkan ---
#include <OneWire.h>
#include <DallasTemperature.h>
```
//----ISTIHAR SENSOR SUHU DS18B20 --------
```
OneWire oneWire(SensorSuhu);
DallasTemperature sensors(&oneWire);
penambahan pada fungsi setup()
```
penambahan pada fungsi setup()
```
sensors.begin();
```
kod aturcara bagi fungsi utama (loop)
```
sensors.requestTemperatures(); 
float temperatureC = sensors.getTempCByIndex(0);
  
Serial.println("---------------- socket LA -------------");  
Serial.print(temperatureC);
Serial.println(" ºC");
```
