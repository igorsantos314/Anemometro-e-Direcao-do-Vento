//#include <Adafruit_Sensor.h>
//#include <Adafruit_BMP280.h>

class Anemometro{

  // -----------------------------------------------------------------

  const float pi = 3.14159265;                      // Número de pi
  const int periodoAfericaoVelocidadeVento = 30000; // Período Aferição Vento entre as medidas (ms)
  const int raioAnemometro = 65;                    // Raio do anemometro(mm)

  //extern float velocidadeVento;                   // Velocidade do vento (km/h)
  //extern boolean velocidadeDoVentoAferida;

  unsigned long dataUltimoEnvioDadosServidor;
  const int periodoAfericaoGeral = 5000;            // Período Aferição Geral entre as medidas (ms)
  
  // -----------------------------------------------------------------

  volatile byte numPulsosAnemometro;            // Contador para o sensorSi7021reed switch no anemometro
  unsigned int  rpm;                            // Rotações por minuto do anemometro
  float         velocidadeVento;                // Velocidade do vento (km/h)
  unsigned long dataUltimoAfericaoVelocidadeVento;
  boolean velocidadeDoVentoAferida;

  // -----------------------------------------------------------------#

public:
  Anemometro(){
    numPulsosAnemometro = 0;
    rpm = 0;
    velocidadeVento = 0;
    velocidadeDoVentoAferida = false;
  }

  //Função para calcular o RPM
  void calcularRpmAnemometro()
  {
    rpm = ((numPulsosAnemometro) * 60) / (periodoAfericaoVelocidadeVento / 1000);
  }

  //Função para calcular a velocidade do vento em km/h
  void calcularVelocidadeVento()
  {
    velocidadeVento = (((2 * pi * raioAnemometro * rpm) / 60) / 1000) * 3.6;
  }

  //Função para soma quantidade de Pulsos
  void somarPulsos(int quant){
    numPulsosAnemometro += 1;
  }

  //Função para resetar os contadores
  void resetarContador() {
    numPulsosAnemometro = 0;
  }

  void toString()
  {
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
