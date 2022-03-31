/**
 * Classe Anemometro
 * 
 * Calcula a velocidade do vento com base em interrupções aferidas
 * em um intervalo de 30 segundos.
 * 
 */
class Anemometro{

  // -----------------------------------------------------------------
  
  const float pi = 3.14159265;                      // Número de pi
  
  private: int pin = 18;
  private: int periodoAfericao = 30000;             // (Default) Período Aferição Vento em milésimos de segundo (ms)
  private: int raio = 65;                           // (Default) Raio do anemometro em milímetros (mm) 
  
  unsigned long dataUltimoEnvio;                    
  const int periodoAfericaoGeral = 5000;            // Período Aferição Geral entre as medidas (ms)
  
  // -----------------------------------------------------------------

  volatile byte numPulsosAnemometro = 0;            // Contador para o sensor Si7021 reed switch no anemômetro
  unsigned int  rpm                 = 0;            // Rotações por minuto do anemômetro
  float         velocidadeVento     = 0;            // Velocidade do vento em Km/h
  unsigned long dataUltimaAfericao  = millis();     // Data da ultima aferição -- ?
  boolean isVelocidadeAferida       = false;        // Status da aferição da Velocidade em boolean

  // -----------------------------------------------------------------
  
public:
  /**
   * Construtor da Classe Anemometro
   * 
   * Ao ser chamado, o construtor vazio,
   * os atributos pin, o periodoAfericao e o raio 
   * teram valores atribuidos com dados pré determinados/setados.
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
   * @return void
   */
  Anemometro(int sPin, int sPeriodoAfericao, int sRaio){
    pin = sPin;
    periodoAfericao = sPeriodoAfericao;
    raio = sRaio;
  }

  /*
  * Função de cálculo do RPM
  * 
  * Função deve calcular o rpm do anemômetro
  * 
  * Não contém parâmetros
  * 
  * @return void
  */
  void calcularRpm()
  {
    rpm = ((numPulsosAnemometro) * 60) / (periodoAfericao / 1000);
  }
   
  /*
  * Função de cálculo da velocidade do vento em Km/h
  * 
  * Função deve calcular a velocidade do vento daquele momento do anemômetro
  * 
  * Não contém parâmetros
  * 
  * @return void
  */
  void calcularVelocidadeVento()
  {
    velocidadeVento = (((2 * pi * raio * rpm) / 60) / 1000) * 3.6;
  }

  /*
  * Função de soma de quantidade de Pulsos do anemômetro
  * 
  * Função deve calcular a quantidade de pulsos do anemômetro, somando mais um a cada pulso
  * 
  * @param int quant, deve receber a quantidade de pulsos
  * 
  * @return void
  */
  void somarPulsos(int quant){
    numPulsosAnemometro += 1;
  }

  /*
  * Função para resetar contador
  * 
  * Função deve resetar um contador do anemômetro se a velocidade do vento já tenha sido aferida
  * 
  * Não contém parâmetros
  * 
  * @return void
  */
  void resetarContador() {
    if(isVelocidadeAferida){
      
      isVelocidadeAferida = false;

      numPulsosAnemometro = 0;
    }
  }

  /*
  * Função de aferição da velocidade do vento
  * 
  * Função realizar o calculo do RPM, após calcula a velocidade do vento com base no RPM calculado,
  * salva a data da ultima aferição, exibe a velocidade do vento em KM/h e reseta o contador.
  *
  * Não contém parâmetros
  * 
  * @return void
  */
  void aferir(){
    if (millis() > dataUltimaAfericao + periodoAfericao)
    {
      calcularRpm();

      calcularVelocidadeVento();    
      
      dataUltimaAfericao = millis();
      isVelocidadeAferida = true;

      toString(); //Exibir aferição
      
      resetarContador();
    }
  }

  /*
  * Função para pegar a velocidade do vento
  * 
  * Função deve retornar o resultado do cálculo da velocidade do vento em Km/h
  * 
  * Não contém parâmetros
  * 
  * @return float
  */
  float getWinSpeed(){
    return velocidadeVento;
  }

  /*
  * Função para setar o pin do anemômetro
  * 
  * Não contém parâmetros
  * 
  * @return void
  */
  void setPin(int sPin){
    pin = sPin;
  }

  /*
  * Função irá retornar o pino de conexão do anemometro
  * 
  * Não contém parâmetros
  * 
  * @return pin
  */
  int getPin(){
    return pin;
  }

  /*
  * Função para setar o Período de Aferição
  * 
  * Função deve setar o valor do período de aferição
  * 
  * @params int sPeriodoAfericao
  * 
  * @return void
  */
  void setPeriodoAfericao(int sPeriodoAfericao){
    periodoAfericao = sPeriodoAfericao;
  }

  /*
   * Função que retorna o perído de aferição setado
   * 
   * @return int 
   */
  int getPeriodoAfericao(){
    return periodoAfericao;
  }

  /*
   * Função para setar o raio do anemômetro
   * @param int sRaio, raio em milimetros
   * 
   * @return void
   */
  void setRaio(int sRaio){
    raio = sRaio;
  }

  /*
   * Função para retornar o raio do anemômetro em milimetros
   * 
   * Não contém parâmetros
   * 
   * @return int
   */
  int getRaio(){
    return raio;
  }

  /*
   * Exibe as informações aferidas:
   *  - Número de pulsos do anemômetro
   *  - Rotações por minuto(RPM)
   *  - Velocidade do vento KM/h
   */
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
