# **Eksperimen digital OUTPUT - Ujikaji 1 : LED**

## Ujikaji 1a: LED - ON
```
digitalWrite(relay01,HIGH);
```

## Ujikaji 1b: kawal LED - ON dan OFF
```
  digitalWrite(relay01,HIGH);
  delay(1000);
  digitalWrite(relay01,LOW);
  delay(1000);
```
## Ujikaji 1c: kawal 2 LED
```
  digitalWrite(relay01,HIGH);
  digitalWrite(relay02,HIGH);
  delay(1000);
  digitalWrite(relay01,LOW);
  digitalWrite(relay02,LOW);
  delay(1000);
```
## Ujikaji 1d: kawal 2 LED - Kelip kelap
```
 digitalWrite(relay01,HIGH);
  digitalWrite(relay02,LOW);
  delay(1000);
  digitalWrite(relay01,LOW);
  digitalWrite(relay02,HIGH);
  delay(1000);
```
https://markdownlivepreview.com/
