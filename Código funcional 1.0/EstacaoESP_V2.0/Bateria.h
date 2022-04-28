class Bateria{

  // ---------------- Atributos ----------------
  private: float bateryLevel = 0.0;
  private: unsigned int raw = 0;

  private: int pin = 35;                    //Pin Default
  private: float batteryCapacity = 4000.0f;    //Capacidade da Bateria
  // -------------------------------------------

public:
  Bateria(){
    
  }
  
  void aferir()
  {
    //Pega o valor em RAW
    raw = analogRead(pin);

    //Porcentagem da bateria
    bateryLevel = map(raw, 0.0f, batteryCapacity, 0, 100);
    
    //Exibir informações
    toString();
  }

  int getRaw(){
    return raw;  
  }

  float getPorcentagem(){
    return bateryLevel;
  }
  
  int getPin(){
    return pin;  
  }

  void setPin(int sPin){
    pin = sPin;
  }

  int getBatteryCapacity(){
    return batteryCapacity;  
  }

  void setBatteryCapacity(int sBatteryCapacity){
    batteryCapacity = sBatteryCapacity;
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
