//#include <Adafruit_Sensor.h>
//#include <Adafruit_BMP280.h>

class Anemometro{

  // -----------------------------------------------------------------
  public: const int pin = 18;
  
  const float pi = 3.14159265;                      // Número de pi
  const int periodoAfericaoVelocidadeVento = 30000; // Período Aferição Vento entre as medidas (ms) 30000
  const int raioAnemometro = 65;                    // Raio do anemometro(mm) 

  //extern float velocidadeVento;                   // Velocidade do vento (km/h)
  //extern boolean isVelocidadeAferida;

  unsigned long dataUltimoEnvioDadosServidor;
  const int periodoAfericaoGeral = 5000;            // Período Aferição Geral entre as medidas (ms)
  
  // -----------------------------------------------------------------

  volatile byte numPulsosAnemometro;            // Contador para o sensorSi7021reed switch no anemometro
  unsigned int  rpm;                            // Rotações por minuto do anemometro
  float         velocidadeVento;                // Velocidade do vento (km/h)
  unsigned long dataUltimoAfericaoVelocidadeVento;
  boolean isVelocidadeAferida;

  // -----------------------------------------------------------------

public:
  Anemometro(){
    numPulsosAnemometro = 0;
    rpm = 0;
    velocidadeVento = 0;
    isVelocidadeAferida = false;
    dataUltimoAfericaoVelocidadeVento = millis();
  }

  //Função para calcular o RPM
  void calcularRpmAnemometro()
  {
    //Calcular Rotações por minuto (RPM)
    rpm = ((numPulsosAnemometro) * 60) / (periodoAfericaoVelocidadeVento / 1000);
  }

  //Função para calcular a velocidade do vento em km/h
  void calcularVelocidadeVento()
  {
    //Calcular velocidade do vento em km/h
    velocidadeVento = (((2 * pi * raioAnemometro * rpm) / 60) / 1000) * 3.6;
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
    if (millis() > dataUltimoAfericaoVelocidadeVento + periodoAfericaoVelocidadeVento)
    {
      //Calcular RPM
      calcularRpmAnemometro();

      //Calcular Velocidade
      calcularVelocidadeVento();    
      
      dataUltimoAfericaoVelocidadeVento = millis();
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
