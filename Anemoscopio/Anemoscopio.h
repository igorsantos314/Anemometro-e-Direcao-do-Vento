class Anemoscopio{

  //Pontos cardiais
  private: const String compass[17] = { "N  ", "NNE", "NE ", "NEE",
                                        "E  ", "SEE", "SE ", "SSE",
                                        "S  ", "SSW", "SW ", "SWW",
                                        "W  ", "NWW", "NW ", "NNW", "???"};
              
  // Variáveis auxiliáres utilizadas para definir a direção do Vento.
  private: byte direct = 1; //Inicia com a posição Norte
  private: int pointer = 0;
  
public:
  Anemoscopio(){
        
  }
  
  void enventListened(int direct){
    //Seta a direção do vento
    setDirecaoDoVento(direct);

    //Exibir
    toString();
  }
  
  void setDirecaoDoVento(int sDirect)
  {
    //Ponto não encontrado
    pointer = -1;

    //Pino de Direção
    direct = sDirect;
      
    switch (direct)
    {
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
      default:
        pointer = 16;
        // if nothing else matches, do the default
        // default 16, "???" mainly for debugging
        break;
    }
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
