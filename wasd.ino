/* 
  * Aggiornato al 26/11/19 *  
  Programma da utilizzare per la taratura del trimmer dei servomotori continui
  AR-3606HB o i SM-S4303R.
  La taratura serve a sicronizzare la posizione servo 90 allo stop dei motori.
  Impostando 90 il motore non deve ruotare, in caso contrario agire delicatamente
  sul trimmer di taratura.
  Il trimmer serve soloamente a tarare lo stop e non a variare la velocitÃ  del motore!!!
*/

/******************************************************************
                             Librerie
 ******************************************************************/

#include <Servo.h>
#include <Arduino.h>

/******************************************************************
                Definizione dei pin e delle variabili
 ******************************************************************/

/* Definizione dei PIN usati sulla scheda */
#define pinruotaSinistra         13   /*  Sinistra servo Ruota       */
#define pinruotaDestra           12   /*  Destra servo Ruota         */

/* Definitione dei valori dei valori che possono assumere servo a rotazione continua */
#define ruotaStopValore 92
#define ruotaSinistraAvantiValore 0 // 180 per i servo AR-3606HB,   0 per i servo SM-S4303R
#define ruotaSinistraIndietroValore 180 //   0 per i servo AR-3606HB, 180 per i servo SM-S4303R
#define ruotaDestraAvantiValore 180     //   0 per i servo AR-3606HB, 180 per i servo SM-S4303R
#define ruotaDestraIndietroValore 0 // 180 per i servo AR-3606HB,   0 per i servo SM-S4303R

/* Test supportati */
#define TARATURA_STOP_MOTORI 1
#define TEST_MOTORI_AVANTI   2
#define TEST_MOTORI_INDIETRO 3

/* Selezionare il tipo di test da effettuare decommentando il rigo giusto*/
//int testSelected = TARATURA_STOP_MOTORI;
int testSelected = TEST_MOTORI_AVANTI;
//int testSelected = TEST_MOTORI_INDIETRO;

/* Creazione oggetti per la libreria Servo */
Servo ruotaSinistra;                    /*  Valores from 0 to 180  */
Servo ruotaDestra;                      /*  Valores from 0 to 180  */

/* Default delay */
#define defaultDelay        10

void setup() {
  /* Define dei pin degli oggetti servo */
  ruotaSinistra.attach(pinruotaSinistra);
  ruotaDestra.attach(pinruotaDestra);
  Serial.begin(9600);
}

void loop() {
  
  /*
    ruotaSinistra.write(92);
    delay(defaultDelay);
    ruotaDestra.write(ruotaStopValore);
    delay(defaultDelay);
    delay(1000); */

  if(Serial.available()){
    String s = Serial.readString();
    Serial.flush();
    char c = s[0];
    char t = s[1];
    char h = s[2];
    char d = s[3];
    char u = s[4];
    int time = int(t-'0')*1000 + int(h-'0')*100 + int(d-'0')*10 + int(u-'0');
    Serial.println(s);
    switch (c){
    case 'w':
      ruotaDestra.write(ruotaDestraAvantiValore);
      ruotaSinistra.write(ruotaSinistraAvantiValore);break;
    case 's':
      ruotaDestra.write(ruotaDestraIndietroValore);
      ruotaSinistra.write(ruotaSinistraIndietroValore);break;
    case 'a' :
      ruotaDestra.write(ruotaDestraAvantiValore);
      ruotaSinistra.write(ruotaSinistraIndietroValore);break;
    case 'd' :
      ruotaDestra.write(ruotaDestraIndietroValore);
      ruotaSinistra.write(ruotaSinistraAvantiValore);break;
    }
    delay(time);
    ruotaDestra.write(ruotaStopValore);
    ruotaSinistra.write(ruotaStopValore);
  }
    
/*
    ruotaSinistra.write(92);
    delay(defaultDelay);
    ruotaDestra.write(ruotaStopValore);
    delay(defaultDelay);
    delay(1000);

    ruotaSinistra.write(ruotaSinistraIndietroValore);
    delay(defaultDelay);
    ruotaDestra.write(ruotaDestraIndietroValore);
    delay(defaultDelay);
    delay(500);
  
*/
}
 
