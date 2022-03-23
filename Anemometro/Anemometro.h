/**
 * Classe Anemometro
 * 
 * Transforma interrupções aferidas em um intervalo de 30 segundos
 * em velocidade do vento
 */
class Anemometro{

  // -----------------------------------------------------------------
  
  const float pi = 3.14159265;                      // Número de pi
  
  private: int pin = 18;
  private: int periodoAfericao = 30000;             // (Default) Período Aferição Vento entre as medidas (ms) 30000
  private: int raio = 65;                           // (Default) Raio do anemometro(mm) 
  
  unsigned long dataUltimoEnvio;
  const int periodoAfericaoGeral = 5000;            // Período Aferição Geral entre as medidas (ms)
  
  // -----------------------------------------------------------------

  volatile byte numPulsosAnemometro = 0;            // Contador para o sensor Si7021 reed switch no anemometro
  unsigned int  rpm                 = 0;            // Rotações por minuto do anemometro
  float         velocidadeVento     = 0;            // Velocidade do vento (km/h)
  unsigned long dataUltimaAfericao  = millis();     // Data da Ultima Afericao
  boolean isVelocidadeAferida       = false;        // Status da aferição da Velocidade

  // -----------------------------------------------------------------
  
public:
  /**
   * Construtor da Classe Anemometro
   * 
   * Ao ser invocado o construtor vazio,
   * os atributos pin, periodoAfericao e raio 
   * serão atribuidos os valores pré setados.
   * 
   * return void
   */
  Anemometro(){
    
  }

  /**
   * Construtor da Classe Anemometro
   * 
   * @param int sPin, define o pino de aferição
   * @param int sPeriodoAfericao, define o período entre aferições
   * @param int sRaio, define o raio do anemometro
   * 
   * return void
   */
  Anemometro(int sPin, int sPeriodoAfericao, int sRaio){
    pin = sPin;
    periodoAfericao = sPeriodoAfericao;
    raio = sRaio;
  }

  //Função para calcular o RPM
  void calcularRpm()
  {
    //Calcular Rotações por minuto (RPM)
    rpm = ((numPulsosAnemometro) * 60) / (periodoAfericao / 1000);
  }
  
  //Função para calcular a velocidade do vento em km/h
  void calcularVelocidadeVento()
  {
    //Calcular velocidade do vento em km/h
    velocidadeVento = (((2 * pi * raio * rpm) / 60) / 1000) * 3.6;
  }
  
  //Função para soma quantidade de Pulsos
  void somarPulsos(int quant){
    numPulsosAnemometro += 1;
  }

  //Função para resetar os contadores
  void resetarContador() {
    if(isVelocidadeAferida){
      //Velocidade do Vento
      isVelocidadeAferida = false;

      //Resetar pulsos do anemometro
      numPulsosAnemometro = 0;
    }
  }

  //Função para Aferir a velocidade do Vento
  void aferir(){
    if (millis() > dataUltimaAfericao + periodoAfericao)
    {
      //Calcular RPM
      calcularRpm();

      //Calcular Velocidade
      calcularVelocidadeVento();    
      
      dataUltimaAfericao = millis();
      isVelocidadeAferida = true;

      //Exibir aferição
      toString();
      
      //Resetar o contador
      resetarContador();
    }
  }

  float getWinSpeed(){
    //Retorna a velocidade do vento
    return velocidadeVento;
  }

  //--- Pino do Anemometro ---
  void setPin(int sPin){
    pin = sPin;
  }

  int getPin(){
    return pin;
  }

  //--- Periodo de Afericao de Velocidade do Vento Milisegundos ---
  void setPeriodoAfericao(int sPeriodoAfericao){
    periodoAfericao = sPeriodoAfericao;
  }
  
  int getPeriodoAfericao(){
    return periodoAfericao;
  }

  //--- Raio do Anemometro em Milimetros ---
  void setRaio(int sRaio){
    raio = sRaio;
  }
  
  int getRaio(){
    return raio;
  }
  
  void toString()
  {
    Serial.println("");
    Serial.print("Pulsos anemômetro: ");
    Serial.print(numPulsosAnemometro);
    Serial.print(";  RPM: ");
    Serial.print(rpm);
    Serial.print(";  Vel. Vento: ");
    Serial.print(velocidadeVento);
    Serial.print(" [km/h] ");
    Serial.println();
  }

};
