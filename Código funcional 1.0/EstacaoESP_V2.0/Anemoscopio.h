/**
 * Classe Anemoscopio
 * 
 * 
 */
class Anemoscopio{
  
  //Pontos cardiais, colaterais e subcolaterais
  private: const String compass[17] = { "N  ", "NNE", "NE ", "NEE",
                                        "E  ", "SEE", "SE ", "SSE",
                                        "S  ", "SSW", "SW ", "SWW",
                                        "W  ", "NWW", "NW ", "NNW", "???"};
  
  //Data da ultima interrupção
  private: unsigned long tempoUltimaInterrupcao = 0;
  
  //Tempo de debouncing
  private: int debounce = 250;
  
  //Pins do ESP32
  private: int reedPins[8] = {16, 17, 18, 19, 21, 22, 23, 27};
              
  // Variáveis auxiliáres
  private: byte direct = 0; //Inicia com a posição Norte
  private: int pointer = 0;
  
public:
  Anemoscopio(){
        
  }
  
  void enventListener(){

    // Interrupt called (No Serial no read no wire in this function, and DEBUG disabled on PCF library)
    unsigned long tempoInterrupcao = millis();
    
    if (tempoInterrupcao - tempoUltimaInterrupcao > debounce)
    { 
      //Caso Default
      byte sDirect = 0;
      
      //Varre as 8 posições
      for(int i=7; i >= 0; i--){
        //Serial.print(i);
        //Incrementa no byte
        sDirect = sDirect | ( convert(digitalRead(reedPins[7-i])) << i);
      }
      
      //Envia a direção para ser tratada
      setDirecaoDoVento(sDirect);

      //Atualiza a variável de debounce
      tempoUltimaInterrupcao = tempoInterrupcao;
    }
  }
  
  int convert(int sinal){
    if(sinal == LOW)
      return HIGH;
    return LOW;
  }
  
  void setDirecaoDoVento(byte sDirect)
  {
    //Serial.println(sDirect, BIN);
    
    //Ponto não encontrado
    pointer = -1;

    //Pino de Direção
    direct = 0;
    direct = sDirect;
      
    switch (direct)
    {
      // ---- Casos N, NNE, NE, NEE ----
      case 1:
        pointer = 0;
        break;
      case 3:
        pointer = 1;
        break;
      case 2:
        pointer = 2;
        break;
      case 6:
        pointer = 3;
        break;

      // ---- Casos E, SEE, SE, SSE ----  
      case 4:
        pointer = 4;
        break;
      case 12:
        pointer = 5;
        break;
      case 8:
        pointer = 6;
        break;
      case 24:
        pointer = 7;
        break;

      // ---- Casos S, SSW, SW, SWW ----   
      case 16:
        pointer = 8;
        break;
      case 48:
        pointer = 9;
        break;
      case 32:
        pointer = 10;
        break;
      case 96:
        pointer = 11;
        break;

      // ---- Casos W, NWW, NW, NNW ----    
      case 64:
        pointer = 12;
        break;
      case 192:
        pointer = 13;
        break;
      case 128:
        pointer = 14;
        break;
      case 129:
        pointer = 15;
        break;

      //---- Nenhum dos Casos ----        
      default:
        pointer = 16;
        // if nothing else matches, do the default
        // default 16, "???" mainly for debugging
        break;
    }
    
    //Exibir informações
    //toString();
  }
  
  //Retorna o vetor de ReedPins na memória
  int *getReedPins(){
    return reedPins;
  }

  //Seta o tempo de espera entre as aferições
  void setDebounce(int sDebounce){
    debounce = sDebounce;  
  }
  
  //Retorna o tempo de espera entre as aferições
  int getDebounce(){
    return debounce;  
  }

  //Retorna a direção do vento
  public: int getPointer(){
    return pointer;  
  }
  
  void toString()
  {
    Serial.print("Direção do Vento: ");
    Serial.print(direct);
    Serial.print("\t Pointer: ");
    Serial.print(pointer);
    Serial.print("\t Compass: ");
    Serial.print(compass[pointer]);
    //Serial.println(direct, BIN);
    Serial.println();
  }

};
