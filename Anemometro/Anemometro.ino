#include "Anemometro.h"

//Headers
void IRAM_ATTR contarQtdInterrupcoesAnemometro();

//----------- Objetos -----------
Anemometro anemometro();

void setup() {
  // put your setup code here, to run once:
  attachInterrupt(digitalPinToInterrupt(2), contarQtdInterrupcoesAnemometro, RISING);
}

void loop() {
  // put your main code here, to run repeatedly:

}

void IRAM_ATTR contarQtdInterrupcoesAnemometro() {

}
