# **Eksperimen digital OUTPUT - Ujikaji 2 : INPUT Digital and Analog


## Ujikaji 1a: Suis sebagai **digital INPUT**

penambahan pada header (define)
```
#define sensorSuis 18
```
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

