/*
 * Classe Anemoscopio
 * 
 * 
 */
class Anemoscopio{
  
  //Pontos cardiais
  private: const String compass[17] = { "N  ", "NNE", "NE ", "NEE",
                                        "E  ", "SEE", "SE ", "SSE",
                                        "S  ", "SSW", "SW ", "SWW",
                                        "W  ", "NWW", "NW ", "NNW", "???"};
  
  //Pins do ESP32
  private: int reedPins[8] = {16, 17, 18, 19, 21, 22, 23, 25};
              
  // Variáveis auxiliáres
  private: byte direct = 1; //Inicia com a posição Norte
  private: int pointer = 0;
  
public:
  Anemoscopio(){
        
  }
  
  void enventListener(){
    //Caso Default
    byte sDirect = 0;
    
    //Varre as 8 posições
    for(int i=7; i > 0; i--){
      //Incrementa no byte
      sDirect = sDirect | (digitalRead(reedPins[7-i]) << i);
    }
    
    //Envia a direção para ser tratada
    setDirecaoDoVento(sDirect);
  }
  
  void setDirecaoDoVento(byte sDirect)
  {
    //Ponto não encontrado
    pointer = -1;

    //Pino de Direção
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
    toString();
  }
  
  //Retorna o vetor de ReedPins na memória
  int *getReedPins(){
    return reedPins;
  }
  
  void toString()
  {
    Serial.print("Direção do Vento: ");
    Serial.print(direct);
    Serial.print("\t . ");
    Serial.print(pointer);
    Serial.print("\t . ");
    Serial.print(compass[pointer]);
    //Serial.println(direct, BIN);
    Serial.println();
  }

};
