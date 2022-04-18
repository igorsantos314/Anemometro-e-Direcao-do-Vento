#include "Anemoscopio.h"

static unsigned long tempoUltimaInterrupcaoCompass = 0;
Anemoscopio anemoscopio;

void setup() {
  
  Serial.begin(115200); // Define e inicializa a porta para debugar
  
  Serial.println();
  Serial.println("Starting setup...");

  anemoscopio.setDebounce(250);
  
  // Varre a lista de pinos para interrupção
  for(int i=0; i < 8; i++){
    int pin = anemoscopio.getReedPins()[i];
    
    //Código do ESP8266 está como INPUT
    pinMode(pin, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(pin), anemoscopioInterrupt, FALLING); // Falling = HIGH > LOW.
  }
  
  //Fazer a primeira aferição
  anemoscopio.enventListener();
}

void loop() {
  // put your main code here, to run repeatedly:
  anemoscopio.toString();
  delay(1000);
}

ICACHE_RAM_ATTR void anemoscopioInterrupt()
{
// <<<<<<< HEAD
  // Interrupt called (No Serial no read no wire in this function, and DEBUG disabled on PCF library)
  unsigned long tempoInterrupcao = millis();
  
  if (tempoInterrupcao - tempoUltimaInterrupcaoCompass > 200)
  { 
    //Atribui a data da ultima aferição, para processamento da função assincrona
    tempoUltimaInterrupcaoCompass = millis();
    
    //faz o debounce do reed switch
    anemoscopio.enventListener();
  }
// =======
  //faz o debounce do reed switch
  anemoscopio.enventListener();
// >>>>>>> refs/remotes/origin/master
}
