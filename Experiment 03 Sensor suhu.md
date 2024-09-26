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




 pinMode(sensorSuis,INPUT);
```
kod aturcara bagi fungsi utama (loop)
```
int dataSuis = digitalRead(sensorSuis);
Serial.println(dataSuis);
delay(500);
```
