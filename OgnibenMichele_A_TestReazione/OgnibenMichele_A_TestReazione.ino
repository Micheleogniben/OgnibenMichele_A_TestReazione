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
int tempo_max;
int led_esito;

void setup() {
  lcd.begin(16, 2); 
  lcd.print("Inizia");
                    //  pin
  led_blu    = 1;
  beep       = 2;
  led_rosso  = 3;   //  porta analogica per l'effetto dissolvenza
  btn_start  = 4;
  led_verde  = 5;   //  porta analogica per l'effetto dissolvenza
  btn_led    = 6;
  btn_beep   = 7;
                    //  variabili
  tempo_max  = 500;
  ris1       = -1;
  ris2       = -1;
  
  pinMode(btn_start,  INPUT);
  pinMode(btn_led,    INPUT);
  pinMode(btn_beep,   INPUT);

  pinMode(led_blu,    OUTPUT);
  pinMode(led_rosso,  OUTPUT);
  pinMode(led_verde,  OUTPUT);
  pinMode(beep,       OUTPUT);
}

void loop() {
  
  while (digitalRead(btn_start) == LOW) {};     //  non inizierà nulla fino a che non verrà premuto il bottone
                                                //  metodi per il calcolo del tempo di reazione per led e buzzer
  digitalWrite(led_verde, LOW);
  digitalWrite(led_rosso, LOW);
  lcd.clear();
  
  ris1 = conteggioTempo(led_blu, btn_led,  0, "Led: ");
  
  if (ris1 < 100){                              //  primo test non valido perchè l'utente ha "barato"
    lcd.clear();
    lcd.print("Test non valido");
    led_esito = led_rosso;
  }else{
    ris2 = conteggioTempo(beep, btn_beep, 1, "Suono: ");
    if (ris2 < 100){                            //  secondo test non valido perchè l'utente ha "barato"
      lcd.clear();
      lcd.print("Test non valido");
      led_esito = led_rosso;
    }else{
      if (ris1 <= tempo_max && ris2 <= tempo_max){
        led_esito = led_verde;                                //  test passato     => Led Verde
      }else{
        led_esito = led_rosso;                                //  test non passato => Led Rosso
      }
    }
  }
  
  while(digitalRead(btn_start) == LOW){                 //  effetto dissolvenza del led
    for (int i = 0; i <= 255; i++){                     //  accensione
      if (digitalRead(btn_start) == HIGH){
        break;
      }
      analogWrite(led_esito, i);
      delay(6);
    }
    for (int i = 255; i >= 0; i--){                     //  spegnimento
      if (digitalRead(btn_start) == HIGH){
        break;
      }
      analogWrite(led_esito, i);
      delay(6);
    }
  }
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
