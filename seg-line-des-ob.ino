//-- Sensor ultrassonico
//Incluindo biblioteca Ultrasonic.h
#include "Ultrasonic.h"

//Criando objeto ultrasonic e definindo as portas digitais
//do Trigger - 4 - e Echo - 5
Ultrasonic SensorUltrassonico(4, 5);

long Microsegundos = 0;
/* Variável para armazenar o valor do 
tempo da reflexão do som refletido 
pelo objeto fornecido pela biblioteca do sensor*/
float DistanciaemCM = 0;

//---Motores Ponte H
#define MotorDireita 9 // Pino_Velocidade 1º Motor ( 0 a 255)_ Porta IN2 ponte H;
#define MotorEsquerda 11 //Pino_Velocidade 2º Motor ( 0 a 255) _ Porta IN4 ponte H;
#define dirDir 8 //Pino_Direção do 1º Motor: Para frente / Para trás (HIGH ou LOW)_ porta IN1 ponte H;
#define dirEsq 10 //Pino_Direção do 2º Motor: Para frente / Para trás (HIGH ou LOW)_ porta IN3 ponte H;

//Definição dos pinos dos sensores
#define pin_SDireita 7
#define pin_SEsquerda 6
bool SensorDireita = 0;
bool SensorEsquerda = 0;

int velocidade = 150;

void setup(){
  //Setamos os pinos de controle dos motores como saída 
  pinMode(MotorDireita, OUTPUT);
  pinMode(MotorEsquerda, OUTPUT);
  pinMode(dirDir, OUTPUT);
  pinMode(dirEsq, OUTPUT);
  
  //Setamos os pinos dos sensores como entrada
  pinMode(pin_SDireita, INPUT);
  pinMode(pin_SEsquerda, INPUT);

  //Setamos a direção inicial do motor como 0, isso fará com que ambos os motores girem para frente
  //Nesse caso o LOW vai para frente, pois depende de cada circuito, como o LOW vai para frente o
  //HIGH vai na direção oposta.
  digitalWrite(dirDir, LOW);
  digitalWrite(dirEsq, LOW);

  // Inicia a comunicação seria com velocidade de 9600 bits por segundo
  Serial.begin(9600);
}


void loop(){
  //Neste processo armazenamos o valor lido pelo sensor na variável que armazena tais dados.
  SensorDireita = digitalRead(pin_S1);
  SensorEsquerda = digitalRead(pin_S2);

  //Convertendo a distância em CM e mostrando da porta serial
  DistanciaemCM = SensorUltrassonico.convert(SensorUltrassonico.timing(), Ultrasonic::CM);

  Serial.print(DistanciaemCM);
  Serial.println(" cm");

  if (DistanciaemCM <= 15){
    objectDetected();
  } else {
    lineFollower();
  }
}

void lineFollower(){
  //Aqui está toda a lógica de comportamento do robô: Para a cor branca atribuímos o valor 0 e, para a cor preta, o valor 1.
  if((SensorDireita == 0) && (SensorEsquerda == 0)){ // Se detectar na extremidade das faixas duas cores brancas
    analogWrite(MotorDireita, velocidade); // Ambos motores ligam na mesma velocidade
    analogWrite(MotorEsquerda, velocidade);
  }
  
  if((SensorDireita == 1) && (SensorEsquerda == 0)){ // Se detectar um lado preto e o outro branco
    analogWrite(MotorDireita, 0); // O motor 1 desliga
    analogWrite(MotorEsquerda, velocidade); // O motor 2 fica ligado, fazendo assim o carrinho virar
  }
  
  if((SensorDireita == 0) && (SensorEsquerda == 1)){ // Se detectar um lado branco e o outro preto
    analogWrite(MotorDireita, velocidade); //O motor 1 fica ligado
    analogWrite(MotorEsquerda, 0); // O motor 2 desliga, fazendo assim o carrinho virar no outro sentido
  }
}

void objectDetected(){
  analogWrite(MotorDireita, 0); // Ambos motores desligam e esperam por 2 segundos
  analogWrite(MotorEsquerda, 0);
  delay(2000);

  analogWrite(MotorDireita, -velocidade); // Os motores fazem uma rotação para a direita e esperam por 2 segundos
  analogWrite(MotorEsquerda, velocidade);
  delay(2000);

  analogWrite(MotorDireita, velocidade); // Os vão para frente por 2,5 segundos
  analogWrite(MotorEsquerda, velocidade);
  delay(2500);

  analogWrite(MotorDireita, velocidade); // fazem a rotação para a esquerda por 2 segundos
  analogWrite(MotorEsquerda, -velocidade);
  delay(2000);

  analogWrite(MotorDireita, velocidade); // Os vão para frente por 2,5 segundos
  analogWrite(MotorEsquerda, velocidade);
  delay(2500);

  analogWrite(MotorDireita, velocidade); // fazem a rotação ao contraria por 2 segundos
  analogWrite(MotorEsquerda, -velocidade);
  delay(2000);

  SensorDireita = 1;
  while(SensorDireita != 1){
    analogWrite(MotorDireita, velocidade); // Os vão para frente por 2,5 segundos
    analogWrite(MotorEsquerda, velocidade);
  }
  lineFollower();
}
