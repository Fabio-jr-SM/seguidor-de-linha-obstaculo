//-- Sensor ultrassonico
//Incluindo biblioteca Ultrasonic.h
#include "Ultrasonic.h"

//Criando objeto ultrasonic e definindo as portas digitais
//do Trigger - 4 - e Echo - 5
Ultrasonic SensorUltrassonico(4, 5);

long Microsegundos = 0;// Variável para armazenar o valor do tempo da reflexão do som refletido pelo objeto fornecido pela biblioteca do sensor
float DistanciaemCM = 0;// Variável para armazenar o valor da distância a ser convertido por uma função da própria bilbioteca do sensor

//---Motores Ponte H
#define MotorDireito1 8
#define MotorDireito2 9
#define MotorEsquerdo1 10
#define MotorEsquerdo2 11


void setup() {
  //Definições de entrada e saída
  pinMode(MotorDireito1, OUTPUT);
  pinMode(MotorDireito2, OUTPUT);
  pinMode(MotorEsquerdo1, OUTPUT);
  pinMode(MotorEsquerdo2, OUTPUT);

  Serial.begin(9600);// Inicia a comunicação seria com velocidade de 9600 bits por segundo

  delay(4000);// Vamos dar um tempo de 4 segundos aqui o suficiente para ligar o carrinho e colocar no chao
}

void loop() {

  //Convertendo a distância em CM e mostrando da porta serial
  DistanciaemCM = SensorUltrassonico.convert(SensorUltrassonico.timing(), Ultrasonic::CM);

  Serial.print(DistanciaemCM);
  Serial.println(" cm");

  if (DistanciaemCM <= 30) {// Se a distância lida pelo sensor for menor ou igual que 30 centimetros
    
    //Andar para trás
    
    // Motor lado esquerdo para trás
    digitalWrite(MotorEsquerdo1, HIGH);
    digitalWrite(MotorEsquerdo2, LOW);
    
    // Motor lado direito para trás
    digitalWrite(MotorDireito1, HIGH);
    digitalWrite(MotorDireito2, LOW);
    
    delay(1000);// Vá para trás durante 1 segundo

    // Após ir para tras rotacione
    
    // Motor lado esquerdo para frente
    digitalWrite(MotorEsquerdo1, HIGH);
    digitalWrite(MotorEsquerdo2, LOW);
    
    // Motor lado direito para trás
    digitalWrite(MotorDireito1, LOW);
    digitalWrite(MotorDireito2, HIGH);
    
    delay(200); //para o lado direito durante 200 milisegundos

  } else {// Se a distancia for maior que 30 centimetros o carrinho pode ir para frente ate encontrar um obstaculo

    //Ande para frente
    
    // Motor lado esquerdo para frente
    digitalWrite(MotorEsquerdo1, LOW);
    digitalWrite(MotorEsquerdo2, HIGH);

    // Motor lado direito para frente
    digitalWrite(MotorDireito1, LOW);
    digitalWrite(MotorDireito2, HIGH);
  }

}
