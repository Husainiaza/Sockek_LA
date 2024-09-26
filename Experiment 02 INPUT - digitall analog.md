# **Eksperimen digital OUTPUT - Ujikaji 2 : INPUT Digital and Analog


## Ujikaji 2a: Suis sebagai **digital INPUT**

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

## Ujikaji 2b: LDR sebagai **analog INPUT**

penambahan pada header (define)
```
#define sensorLDR 34
```

kod aturcara bagi fungsi utama (loop)
```
 int dataLDR = analogRead(sensorLDR);
 Serial.println(dataLDR);
 delay(500);
```
