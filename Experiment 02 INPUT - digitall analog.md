# **Eksperimen digital OUTPUT - Ujikaji 2 : INPUT Digital and Analog

## Ujikaji 1a: Suis as digital INPUT
penambahan pada header (define)
```
#define sensorSuis 18
```
penambahan pada fungsi setup()
```
 pinMode(sensorSuis,INPUT);
```
```
int dataSuis = digitalRead(sensorSuis);
Serial.println(dataSuis);
delay(500);
```

