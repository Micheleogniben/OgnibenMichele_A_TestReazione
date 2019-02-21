            //  input
int buttonStart;
int buttonLed;
int buttonBuzzer;
            //  output
int ledTest;
int ledEsito;
int buzzer;
            //  variabili
int tRandom1;
int tRandom2;
int ris1;
int ris2;
int prova1;
int prova2;


void setup() {
                    //  assegnazione variabili
  buttonStart   = 1;
  buttonLed     = 2;
  buttonBuzzer  = 3;
  ledTest       = 4;
  ledEsito      = 5;
  buzzer        = 6;
                              //  input
  pinMode(buttonStart,  INPUT);
  pinMode(buttonLed,    INPUT);
  pinMode(buttonBuzzer, INPUT);
                              //  output
  pinMode(ledTest,  OUTPUT);
  pinMode(ledEsito, OUTPUT);
  pinMode(buzzer,   OUTPUT);
}


void loop() {
                                //  estraggo i tempi ed azzero i risultati dell'utente
  tRandom1 = random(1000, 5000);
  tRandom2 = random(1000, 5000);
  
                                            //  button 1
  while (digitalRead(buttonStart) == LOW) {};
  
  delay(tRandom1);
  digitalWrite(ledTest, HIGH);              
                                            //  button 2
  ris1 = conteggioTempo(buttonLed, ris2);
  
  digitalWrite(ledTest, LOW);
  
  delay(tRandom2);
  
  //ACCENDO IL BUZZER  
                                            //  button 3
  conteggioTempo(buttonBuzzer, ris1);

  //  SPENGO IL BUZZER

  if (ris1 <= prova1 && ris2 <= prova2){
    digitalWrite(ledEsito, HIGH); //VERDE;
  }
  else{
    digitalWrite(ledEsito, HIGH); //ROSSO;
  }
  
}


int conteggioTempo(int button, int ris){
  
  ris = 0;
  while (digitalRead(button) == LOW){
    ris++;
    delay(1);
  }
  
  //  STAMPO RIS SULLO SCHERMO LCD
}
