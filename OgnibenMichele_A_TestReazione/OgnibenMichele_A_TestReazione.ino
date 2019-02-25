            //  librerie
#include <LiquidCrystal.h>;
#include "pitches.h";
LiquidCrystal lcd(13, 12, 11, 10, 9, 8);
            
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
int ris1;
int ris2;
int prova1;
int prova2;

void setup() {
                    //  inizio dello schermo lcd
  lcd.begin(16, 2);
                    //  assegnazione variabili
  buttonStart   = 7;
  buttonLed     = 6;
  buttonBuzzer  = 5;
  ledTest       = 4;
  esitoRosso    = 3;
  esitoVerde    = 2;
  buzzer        = 1;
  prova1        = 500;
  prova2        = 500;
                              //  input
  pinMode(buttonStart,  INPUT);
  pinMode(buttonLed,    INPUT);
  pinMode(buttonBuzzer, INPUT);
                              //  output
  pinMode(ledTest,    OUTPUT);
  pinMode(esitoRosso, OUTPUT);
  pinMode(esitoVerde, OUTPUT);
  pinMode(buzzer,     OUTPUT);
}

void loop() {
  //  button 1                                           
  while (digitalRead(buttonStart) == LOW) {};
  lcd.clear();
  digitalWrite(esitoVerde && esitoRosso, LOW);       
  
  //  button 2                              
  ris1 = conteggioTempo(ledTest, buttonLed, 0, ledTest);  
  
  //  button 3         
  ris2 = conteggioTempo(buzzer, buttonBuzzer, 1, buzzer);
  
  //  led RGB
  if (ris1 <= prova1 && ris2 <= prova2){
    digitalWrite(esitoVerde, HIGH);
  }else{
    digitalWrite(esitoRosso, HIGH);
  }
}

int conteggioTempo(int pinAcceso, int button, int linea, int pinSpento){
  //  aspetto il tempo random ed accendo il led / buzzer
  delay(random(1000, 5000));
  digitalWrite(pinAcceso, HIGH);
  //  while che calcola il tempo di reazione
  int ris = 0;
  while (digitalRead(button) == LOW){
    ris++;
    delay(1);
  }
  //  stampo il risultato e spengo il led / buzzer
  digitalWrite(pinSpento, LOW);
  lcd.setCursor(0, linea);
  String stampo = ris + " millisec.";
  lcd.print(stampo);
  return ris;
}
