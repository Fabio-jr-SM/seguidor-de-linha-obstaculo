// Definição dos pinos de controle do motor
#define M1 9 // Pino_Velocidade 1º Motor (0 a 255)_ Porta IN2 ponte H;
#define M2 11 // Pino_Velocidade 2º Motor (0 a 255) _ Porta IN4 ponte H;
#define dir1 8 // Pino_Direção do 1º Motor: Para frente / Para trás (HIGH ou LOW)_ porta IN1 ponte H;
#define dir2 10 // Pino_Direção do 2º Motor: Para frente / Para trás (HIGH ou LOW)_ porta IN3 ponte H;

// Definição dos pinos dos sensores
#define pin_S1 A0
#define pin_S2 A1

// Variáveis dos sensores
bool Sensor1 = 0;
bool Sensor2 = 0;

// Variáveis de controle
int velocidade = 150;
bool obstaculo = false;

void setup() {
  // Setamos os pinos de controle dos motores como saída
  pinMode(M1, OUTPUT);
  pinMode(M2, OUTPUT);
  pinMode(dir1, OUTPUT);
  pinMode(dir2, OUTPUT);

  // Setamos os pinos dos sensores como entrada
  pinMode(pin_S1, INPUT);
  pinMode(pin_S2, INPUT);

  // Setamos a direção inicial do motor como 0, isso fará com que ambos os motores girem para frente
  digitalWrite(dir1, LOW);
  digitalWrite(dir2, LOW);
}

void loop() {
  // Neste processo armazenamos o valor lido pelo sensor na variável que armazena tais dados
  Sensor1 = digitalRead(pin_S1);
  Sensor2 = digitalRead(pin_S2);

  // Verifica se há obstáculo
  if (Sensor1 == 1 && Sensor2 == 1) {
    obstaculo = true;
  }

  // Lógica de comportamento do robô
  if (!obstaculo) {
    if (Sensor1 == 0 && Sensor2 == 0) { // Se detectar na extremidade das faixas duas cores brancas
      analogWrite(M1, velocidade); // Ambos motores ligam na mesma velocidade
      analogWrite(M2, velocidade);
    } else if (Sensor1 == 1 && Sensor2 == 0) { // Se detectar um lado preto e o outro branco
      analogWrite(M1, 0); // O motor 1 desliga
      analogWrite(M2, velocidade); // O motor 2 fica ligado, fazendo assim o carrinho virar
    } else if (Sensor1 == 0 && Sensor2 == 1) { // Se detectar um lado branco e o outro preto
      analogWrite(M1, velocidade); // O motor 1 fica ligado
      analogWrite(M2, 0); // O motor 2 desliga, fazendo assim o carrinho virar no outro sentido
    }
  } else {
    // Desvio de obstáculo
    analogWrite(M1, velocidade); // Ambos os motores ligam na mesma velocidade
    analogWrite(M2, velocidade);

    // Vira para a direita por um tempo
    digitalWrite(dir1, HIGH);
    digitalWrite(dir2, LOW);
    delay(1000); // Tempo para virar

    // Volta a seguir a linha
    digitalWrite(dir1, LOW);
    digitalWrite(dir2, LOW);
    delay(500); // Tempo para retomar a linha

    obstaculo = false; // Reseta a flag de obstáculo
  }
}
