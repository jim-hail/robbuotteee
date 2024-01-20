#include <Arduino.h>

#define MAXCOUNT 100

const int trigPin = 9;
const int echoPin = 8;
long duration;
int cm;
int conteggio = 0;
int rec;
float perclost;


void setup() {
Serial.begin(115200);
pinMode(trigPin, OUTPUT);
pinMode(echoPin, INPUT);
}

long microsecondsToCentimeters(long microseconds)
{return microseconds / 29 / 2;}

void loop(){
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
digitalWrite(trigPin, HIGH);
conteggio++;
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
duration = pulseIn(echoPin, HIGH);
cm = microsecondsToCentimeters(duration);
if(cm < 400){
Serial.print(cm);
Serial.print(" cm");
Serial.println();
rec++;
}
if(conteggio < MAXCOUNT){
perclost = (rec*100)/conteggio;
}else{
  conteggio = 0;
  rec = 0;
  Serial.print(perclost);
  Serial.println("%");

}
delay(100);
}

