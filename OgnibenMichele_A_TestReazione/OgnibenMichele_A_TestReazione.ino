            //  librerie
#include <LiquidCrystal.h>;
#include "pitches.h";
LiquidCrystal lcd(8, 9, 10, 11, 12, 13);
            
            //  input
int btn_start;
int btn_led;
int btn_buzzer;
            //  output
int led_blu;
int led_rosso;
int led_verde;
int buzzer;
            //  variabili
int ris1;
int ris2;
int prova1;
int prova2;

void setup() {
                    //  inizio dello schermo lcd
  lcd.begin(16, 2);
                    //  assegnazione variabili
  btn_start   = 7;
  btn_led     = 6;
  btn_buzzer  = 5;
  buzzer        = 4;
  led_blu       = 3;
  led_rosso    = 2;
  led_verde    = 1;
  prova1        = 500;
  prova2        = 500;
                              //  input
  pinMode(btn_start,  INPUT);
  pinMode(btn_led,    INPUT);
  pinMode(btn_buzzer, INPUT);
                              //  output
  pinMode(led_blu,    OUTPUT);
  pinMode(led_rosso,  OUTPUT);
  pinMode(led_verde,  OUTPUT);
  pinMode(buzzer,     OUTPUT);
}

void loop() {
  //  button 1                                           
  while (digitalRead(btn_start) == LOW) {};
  lcd.clear();
  digitalWrite(led_verde, LOW);
  digitalWrite(led_rosso, LOW);       
                           
  ris1 = conteggioTempo(led_blu, btn_led, 0, led_blu);  
     
  ris2 = conteggioTempo(buzzer, btn_buzzer, 1, buzzer);
  
  if (ris1 <= prova1 && ris2 <= prova2){
    digitalWrite(led_verde, HIGH);
  }else{
    digitalWrite(led_rosso, HIGH);
  }
}

int conteggioTempo(int pinAcceso, int button, int linea, int pinSpento){
  delay(random(1000, 5000));                                                    //  aspetto il tempo random ed accendo il led / buzzer
  digitalWrite(pinAcceso, HIGH);
  int ris = 0;
  while (digitalRead(button) == LOW){                                           //  while che calcola il tempo di reazione aumentando di 1 ogni millisecondo
    ris++;
    delay(1);
  }
  digitalWrite(pinSpento, LOW);                                                 //  stampo il risultato e spengo il led / buzzer
  lcd.setCursor(0, linea);
  lcd.print(ris);
  return ris;
}
