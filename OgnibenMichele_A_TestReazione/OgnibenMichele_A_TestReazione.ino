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
  
  lcd.print("Inizia test");
  digitalWrite(led_verde, LOW);
  digitalWrite(led_rosso, LOW);
  
  while (digitalRead(btn_start) == LOW) {};     //  non inizierà nulla fino a che non verrà premuto il bottone
                                                //  metodi per il calcolo del tempo di reazione per led e buzzer
  lcd.clear();
  ris1 = conteggioTempo(led_blu, btn_led,  0, "Led: ");
  ris2 = conteggioTempo(beep,    btn_beep, 1, "Suono: ");
                                                //  led esito positivo/negativo
  if (ris1 <= prova1 && ris2 <= prova2){
    digitalWrite(led_verde, HIGH);
  }else{
    digitalWrite(led_rosso, HIGH);
  }

  delay(3000);
  lcd.clear();
}

int conteggioTempo(int pin, int button, int linea, String test){
  delay(random(1000, 5000));                    //  aspetto il tempo random ed accendo il led / buzzer
  digitalWrite(pin, HIGH);
  int ris = 0;
  while (digitalRead(button) == LOW){           //  while che calcola il tempo di reazione aumentando di 1 ogni millisecondo
    ris++;
    delay(1);
  }
  lcd.setCursor(0, linea);
  lcd.print(test + String(ris) + "ms");
  digitalWrite(pin, LOW);                       //  stampo il risultato e spengo il led / buzzer
  return ris;
}
