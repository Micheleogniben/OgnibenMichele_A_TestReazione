            //  richiamazione della libreria per utilizzare lo schermo lcd
#include <LiquidCrystal.h>;
LiquidCrystal lcd(8, 9, 10, 11, 12, 13);

            //  variabili di input
int btn_start;              //  pin del bottone utilizzato per l'inizio del test
int btn_led;                //  pin del bottone utilizzato per spegnere il led
int btn_beep;               //  pin del bottone utilizzato per spegnere il buzzer

            //  variabili di output
int beep;                   //  pin del buzzer che si accende durante il test di reazione uditivo
int led_blu;                //  pin del led che si accende durante il test di reazione visivo
int led_rosso;              //  pin del led rosso del led rgb (si accende se il test non è valido o è fallito)
int led_verde;              //  pin del led verde del led rgb (si accende se il test viene superato)

            //  variabili numeriche
int ris1;                   //  risultato del primo test di reazione (visivo)
int ris2;                   //  risultato del secondo test di reazione (uditivo)
int tempo_max;              //  tempo entro il quale l'utente deve completare il test
int led;                    //  variabile che indica se il led rgb si dovrà accendere rosso o verde in base al risultato dei due test


int conteggioTempo(int pin, int button, int linea, String test){
    delay(random(1000, 5000));                    //  aspetto il tempo random ed accendo il led / buzzer
    digitalWrite(pin, HIGH);
    int ris = 0;
    while (digitalRead(button) == LOW){           //  while che calcola il tempo di reazione aumentando di 1 ogni millisecondo
      ris++;
      delay(1);
    }
    lcd.setCursor(0, linea);
    lcd.print(test + String(ris) + "ms       ");
    digitalWrite(pin, LOW);                       //  stampo il risultato e spengo il led / buzzer
    if (ris <= tempo_max){led = led_verde;}
    else{led = led_rosso;}
    return ris;
}


void setup() {      //  inizializzazione dello schermo lcd di dimensioni 16x2
  lcd.begin(16, 2); 
                    //  pin
  led_blu    = 1;
  beep       = 2;
  led_rosso  = 3;   //  porta PWM per l'effetto dissolvenza
  btn_start  = 4;
  led_verde  = 5;   //  porta PWM per l'effetto dissolvenza
  btn_led    = 6;
  btn_beep   = 7;
                    //  variabili
  tempo_max  = 500;
  
  pinMode(btn_start,  INPUT);
  pinMode(btn_led,    INPUT);
  pinMode(btn_beep,   INPUT);

  pinMode(led_blu,    OUTPUT);
  pinMode(led_rosso,  OUTPUT);
  pinMode(led_verde,  OUTPUT);
  pinMode(beep,       OUTPUT);
}


void loop() {
  lcd.clear();
  lcd.print("Inizia");
  delay(300);
  while (digitalRead(btn_start) == LOW) {};       //  non inizierà nulla fino a che non verrà premuto il bottone
  lcd.clear();
  lcd.print("Test iniziato");
  led = led_rosso;
                                                  //  metodo per il calcolo del tempo di reazione al led
  ris1 = conteggioTempo(led_blu, btn_led,  0, "Led: ");
  
  if (ris1 < 100){                                //  se il risultato del primo test è minore di 100 l'utente ha "barato" e il test viene annullato
    lcd.clear();
    lcd.print("Test non valido");
  }else{                                          //  metodo per il calcolo del tempo di reazione al buzzer
    ris2 = conteggioTempo(beep, btn_beep, 1, "Suono: ");
    if (ris2 < 100){                              //  se il risultato del secondo test è minore di 100 l'utente ha "barato" e il test viene annullato
      lcd.clear();
      lcd.print("Test non valido");
    }
  }
  
  while(digitalRead(btn_start) == LOW){           //  ciclo per l'effetto dissolvenza del led
    for (int i = 0; i <= 255; i++){
      if (digitalRead(btn_start) == HIGH){ break; }
      analogWrite(led, i);
      delay(6);
    }
    for (int i = 255; i >= 0; i--){
      if (digitalRead(btn_start) == HIGH){ break; }
      analogWrite(led, i);
      delay(6);
    }
  }
                                                  //  il bottone deve essere premuto per cancellare tutto
  while (digitalRead(btn_start) == LOW) {};
  digitalWrite(led, LOW);
}
