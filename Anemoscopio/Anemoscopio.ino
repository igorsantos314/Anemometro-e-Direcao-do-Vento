#include "Anemoscopio.h"

Anemoscopio anemoscopio;

void setup() {
  // Varre a lista de pinos para interrupção
  for(int i=0; i < 8; i++){
    int pin = anemoscopio.getReedPins()[i];

    //Código do ESP8266 está como INPUT
    pinMode(pin, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(pin), anemoscopioInterrupt, RISING); // Falling = HIGH > LOW.
  }

}

void loop() {
  // put your main code here, to run repeatedly:
  
}

ICACHE_RAM_ATTR void anemoscopioInterrupt()
{
  // Interrupt called (No Serial no read no wire in this function, and DEBUG disabled on PCF library)
  static unsigned long tempoUltimaInterrupcaoCompass = 0;
  unsigned long tempoInterrupcao = millis();
  if (tempoInterrupcao - tempoUltimaInterrupcaoCompass > 200)
  { 
    //faz o debounce do reed switch
    anemoscopio.enventListener();
  }
}
