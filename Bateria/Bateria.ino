#include "Bateria.h";

Bateria bateria;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200); // Define e inicializa a porta para debugar
  
  Serial.println();
  Serial.println("Starting setup...");
  
  bateria.setPin(35);
  pinMode(bateria.getPin(), INPUT);  
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(1000);
  bateria.aferir();
  bateria.toString();
}
