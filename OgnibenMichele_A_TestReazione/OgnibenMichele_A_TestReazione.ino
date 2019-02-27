            //  librerie
#include <LiquidCrystal.h>;
LiquidCrystal lcd(8, 9, 10, 11, 12, 13);
            //  input
int btn_start;
int btn_led;
int btn_beep;
            //  output
int led_blu;
int led_rosso;
int led_verde;
int beep;
            //  variabili
int ris1;
int ris2;
int prova1;
int prova2;

void setup() {
  lcd.begin(16, 2);

  btn_start  = 7;
  btn_led    = 6;
  btn_beep   = 5;
  beep       = 4;
  led_blu    = 3;
  led_rosso  = 2;
  led_verde  = 1;
  prova1     = 500;
  prova2     = 500;

  pinMode(btn_start,  INPUT);
  pinMode(btn_led,    INPUT);
  pinMode(btn_beep,   INPUT);

  pinMode(led_blu,    OUTPUT);
  pinMode(led_rosso,  OUTPUT);
  pinMode(led_verde,  OUTPUT);
  pinMode(beep,       OUTPUT);
}

void loop() {
  while (digitalRead(btn_start) == LOW) {};
  lcd.clear();
  digitalWrite(led_verde, LOW);
  digitalWrite(led_rosso, LOW);       
                           
  ris1 = conteggioTempo(led_blu, btn_led, 0);  
     
  ris2 = conteggioTempo(beep, btn_beep, 1);
  
  if (ris1 <= prova1 && ris2 <= prova2){
    digitalWrite(led_verde, HIGH);
  }else{
    digitalWrite(led_rosso, HIGH);
  }
}

int conteggioTempo(int pin, int button, int linea){
  delay(random(1000, 5000));                                                    //  aspetto il tempo random ed accendo il led / buzzer
  digitalWrite(pin, HIGH);
  int ris = 0;
  while (digitalRead(button) == LOW){                                           //  while che calcola il tempo di reazione aumentando di 1 ogni millisecondo
    ris++;
    delay(1);
  }
  digitalWrite(pin, LOW);                                                       //  stampo il risultato e spengo il led / buzzer
  lcd.setCursor(0, linea);
  lcd.print(ris);
  return ris;
}
