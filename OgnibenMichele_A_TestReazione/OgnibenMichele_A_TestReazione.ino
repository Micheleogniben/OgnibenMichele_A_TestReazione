            //  librerie
#include <LiquidCrystal.h>;
#include "pitches.h";
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);            
            
            //  input
int buttonStart;
int buttonLed;
int buttonBuzzer;
            //  output
int ledTest;
int esitoRosso;
int esitoVerde;
int buzzer;
            //  variabili
int tRandom1;
int tRandom2;
int ris1;
int ris2;
int prova1;
int prova2;

void setup() {
                    //  inizio dello schermo lcd
  lcd.begin(16, 2);
                    //  assegnazione variabili
  buttonStart   = 8;
  buttonLed     = 9;
  buttonBuzzer  = 10;
  ledTest       = 6;
  esitoRosso    = 1;
  esitoVerde    = 0;
  buzzer        = 13;
  prova1        = 500;
  prova2        = 500;
                              //  input
  pinMode(buttonStart,  INPUT);
  pinMode(buttonLed,    INPUT);
  pinMode(buttonBuzzer, INPUT);
                              //  output
  pinMode(ledTest,  OUTPUT);
  pinMode(esitoRosso, OUTPUT);
  pinMode(esitoVerde, OUTPUT);
  pinMode(buzzer,   OUTPUT);
}

void loop() {
  //  estraggo i nuovi tempi
  tRandom1 = random(1000, 5000);
  tRandom2 = random(1000, 5000);
  
  //  button 1                                           
  while (digitalRead(buttonStart) == LOW) {};
  lcd.clear();
  
  //  button 2         
  digitalWrite(esitoVerde && esitoRosso, LOW);                            
  ris1 = conteggioTempo(tRandom1, ledTest, buttonLed, 0, ledTest);  
  
  //  button 3         
  ris2 = conteggioTempo(tRandom2, buzzer, buttonBuzzer, 1, buzzer);
  
  //  led RGB
  if (ris1 <= prova1 && ris2 <= prova2){
    digitalWrite(esitoVerde, HIGH);
  }else{
    digitalWrite(esitoRosso, HIGH);
  }
}

int conteggioTempo(int led, int tempo, int ledDaAccendere, int button, int linea){
  //  aspetto il tempo random ed accendo il led / buzzer
  delay(tempo);
  digitalWrite(ledDaAccendere, HIGH);
  //  while che calcola il tempo di reazione
  int ris = 0;
  while (digitalRead(button) == LOW){
    ris++;
    delay(1);
  }
  //  stampo il risultato e spengo il led / buzzer
  digitalWrite(led, LOW);
  lcd.setCursor(0, linea);
  String stampo = ris + " millisec.";
  lcd.print(stampo);
  return ris;
}
