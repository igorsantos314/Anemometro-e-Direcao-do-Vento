#include "Anemometro.h"

//Headers
void IRAM_ATTR contarQtdInterrupcoesAnemometro();

//----------- Objetos -----------
Anemometro anemometro;

void setup() {
  Serial.begin(115200); // Define e inicializa a porta para debugar
  Serial.println();
  Serial.println("Starting setup...");
  
  // Anemometro
  pinMode(anemometro.getPin(), INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(anemometro.getPin()), contarQtdInterrupcoesAnemometro, RISING); // interrupção 0 está ligado ao pino 2 do arduino. Falling = HIGH > LOW.
  
}

void loop() {
  // Aferir Velocicade do Vento
  anemometro.aferir();
  delay(1000);
  Serial.print(".");
}

void IRAM_ATTR contarQtdInterrupcoesAnemometro() {
  static unsigned long tempoUltimaInterrupcaoAnem = 0;
  unsigned long tempoInterrupcao = millis();
  
  if (tempoInterrupcao - tempoUltimaInterrupcaoAnem > 200)
  { 
    //faz o debounce do reed switch
    anemometro.somarPulsos(1);
  }
  
}
