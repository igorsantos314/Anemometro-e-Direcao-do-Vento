/*
 * Classe Anemoscópio
 * 
 * 
 */
class Anemoscopio{
  
  //Pontos cardiais, colaterais e subcolaterais
  private: const String compass[17] = { "N  ", "NNE", "NE ", "NEE",
                                        "E  ", "SEE", "SE ", "SSE",
                                        "S  ", "SSW", "SW ", "SWW",
                                        "W  ", "NWW", "NW ", "NNW", "???"};
  
  //Pins do ESP32
  private: int reedPins[8] = {16, 17, 18, 19, 21, 22, 23, 27};
              
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
      //Serial.print(i);
      //Incrementa no byte
      sDirect = sDirect | ( convert(digitalRead(reedPins[7-i])) << i);
    }
    
    //Envia a direção para ser tratada
    setDirecaoDoVento(sDirect);
  }
  
  int convert(int sinal){
    if(sinal == LOW)
      return HIGH;
    return LOW;
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
    //toString();
  }
  
  //Retorna o vetor de ReedPins na memória
  int *getReedPins(){
    return reedPins;
  }
  
  /*
   * Função que modifica um pino do vetor, com base na posição,
   * verificando que a posição seja menor que o tamanho do vetor reedPins
   * 
   * @param int posicao, posição do vetor
   * @param int pin, pino do dispositivo
   * 
   * @return void
   */
  void setPin(int posicao, int pin){
    if(posicao < sizeof(reedPins))
      reedPins[posicao] = pin;
  }
  
  /*
   * Função que retorna o pino, com base na posição do vetor,
   * verificando que a posição seja menor que o tamanho do vetor reedPins
   * 
   * @param int posicao, posição do vetor
   * 
   * @return int
   */
  int getPin(int posicao){
    if(posicao < sizeof(reedPins))
      return reedPins[posicao];
  }

  /*
   * Função que exibe as informações de direção do vento,
   * pointer e a direção do compass
   * 
   * Não recebe parâmetros
   * 
   * @return void
   */
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
