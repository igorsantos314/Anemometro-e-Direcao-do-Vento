class Bateria{

  // ---------------- Atributos ----------------
  private: float bateryLevel = 0.0;
  private: unsigned int raw = 0;

  private: int pin = 33;
  // -------------------------------------------

public:
  Bateria(){
    
  }
  
  void aferir()
  {
    //Pega o valor em RAW
    raw = analogRead(pin);

    //Porcentagem da bateria
    bateryLevel = map(analogRead(pin), 0.0f, 4000.00f, 0, 100);
  }

  int getRaw(){
    return raw;  
  }

  int getPorcentagem(){
    return bateryLevel;
  }
  
  int getPin(){
    return pin;  
  }

  void setPin(int sPin){
    pin = sPin;
  }
  
  void toString()
  {
    Serial.print("Carga Bateria: Raw = ");
    Serial.print(raw);
    Serial.print("; Porcentagem = ");
    Serial.print(bateryLevel);
    Serial.print(" [%]");
    Serial.println();
  }
};
