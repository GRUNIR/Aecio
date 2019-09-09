#define TRIGGER 13
#define ECHO 12

#define sensorDir A1
#define sensorEsq A5
#define sensorEsqVERDE A3
#define sensorDirVERDE A4

#define POTENCIOMETRO A2

#define IN1 5
#define IN2 4
#define IN3 3
#define IN4 2

#define IN5 11
#define IN6 10
#define IN7 12
#define IN8 8

#define VELOD 6
#define VELOE 9

const int Stay = 0;
int Speed;
int ESQUERDA, ESQUERDAVERDE;
int DIREITA, DIREITAVERDE;
int cont = 0, flag = 0;
int INTERVALOVERDE;
int INTERVALOBLACK;
int INTERVALOSENSORPRETO;


//Robô movimento para frente
void Frente() {
  analogWrite(VELOD, Speed);
  analogWrite(VELOE, Speed);

  //MOTOR FRENTE ESQ
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);

  //MOTOR TRASEIRO ESQ
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);

  //MOTOR FRENTE DIR
  digitalWrite(IN5, LOW);
  digitalWrite(IN6, HIGH);

  //MOTOR TRASEIRO DIR
  digitalWrite(IN7, LOW);
  digitalWrite(IN8, HIGH);
}

void Atras() {
  analogWrite(VELOD, Speed);
  analogWrite(VELOE, Speed);

  //MOTOR FRENTE ESQ
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  //MOTOR TRASEIRO ESQ
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

  //MOTOR FRENTE DIR
  digitalWrite(IN5, HIGH);
  digitalWrite(IN6, LOW);

  //MOTOR TRASEIRO DIR
  digitalWrite(IN7, HIGH);
  digitalWrite(IN8, LOW);
}

//Robô movimento no sentido antihorário
void Antihorario() {
  analogWrite(VELOE, 175);
  analogWrite(VELOD, 200);

  //MOTOR FRENTE ESQ
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);

  //MOTOR TRASEIRO ESQ
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);

  //MOTOR FRENTE DIR
  digitalWrite(IN5, HIGH);
  digitalWrite(IN6, LOW);

  //MOTOR TRASEIRO DIR
  digitalWrite(IN7, HIGH);
  digitalWrite(IN8, LOW);
}

//Robô movimento no sentido horário
void Horario() {
  analogWrite(VELOE, 200); //155
  analogWrite(VELOD, 175); //255

  //MOTOR FRENTE ESQ
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  //MOTOR TRASEIRO ESQ
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

  //MOTOR FRENTE DIR
  digitalWrite(IN5, LOW);
  digitalWrite(IN6, HIGH);

  //MOTOR TRASEIRO DIR
  digitalWrite(IN7, LOW);
  digitalWrite(IN8, HIGH);
}

//Robô permanece em repouso
void Parar() {
  analogWrite(VELOE, 200);
  analogWrite(VELOD, 145);

  //MOTOR FRENTE ESQ
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);

  //MOTOR TRASEIRO ESQ
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);

  //MOTOR FRENTE DIR
  digitalWrite(IN5, LOW);
  digitalWrite(IN6, LOW);

  //MOTOR TRASEIRO DIR
  digitalWrite(IN7, LOW);
  digitalWrite(IN8, LOW);
}

//Função para calculo de distancia
//float Distance() {
//  digitalWrite(TRIGGER, HIGH);
//  delayMicroseconds(10);
//  digitalWrite(TRIGGER, LOW);
//  tempo = pulseIn(ECHO, HIGH);
//  distancia = tempo / 29.4 / 4;
//  return distancia;
//}
//
////Função para contorno do obstáculo
//void contorna() {
//  Horario();
//  delay(250);
//  Frente();
//  delay(350);
//  Antihorario();
//  delay(100);
//  Frente();
//}

void Calibragem() {

  //Serial.print(range);
  // Serial.println(" SENSOR DISTANCIA");
  //Serial.println("----------------------------");
  Serial.print(DIREITA);
  Serial.print(" : ");
  Serial.print(ESQUERDA);
  Serial.println(" SENSOR FAIXA PRETA");
  Serial.println("----------------------------");
  Serial.print(DIREITAVERDE);
  Serial.print(" : ");
  Serial.print(ESQUERDAVERDE);
  Serial.println(" SENSOR FAIXA VERDE");
  Serial.println("----------------------------");
  delay(1000);

}

void Leitura() {

  ESQUERDA = analogRead(sensorEsq);
  DIREITA = analogRead(sensorDir);
  ESQUERDAVERDE = analogRead(sensorEsqVERDE);
  DIREITAVERDE = analogRead(sensorDirVERDE);
}


void Velocidade(){
  Speed = map(analogRead(POTENCIOMETRO), 0, 1024, 0, 255); 
}

void configuracoes() {
  Serial.begin(9600);
  pinMode(VELOD, OUTPUT);
  pinMode(VELOE, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(IN5, OUTPUT);
  pinMode(IN6, OUTPUT);
  pinMode(IN7, OUTPUT);
  pinMode(IN8, OUTPUT);
}

void Linhapreta() {
  //vira verde

  if (((DIREITAVERDE > INTERVALOVERDE) && (DIREITAVERDE < INTERVALOBLACK)) || ((ESQUERDAVERDE > INTERVALOVERDE) && (ESQUERDAVERDE < INTERVALOBLACK))) ++cont;
  if (cont > 60) {
    cont = 0;
    
    if ((DIREITAVERDE > INTERVALOVERDE) && (DIREITAVERDE < INTERVALOBLACK)) {
      Antihorario();
      delay(350);
      while (1) {
        Leitura();
        if (ESQUERDA > INTERVALOSENSORPRETO)
          break;
      }
      Frente();
      delay(350);
    }
    else {
      Horario();
      delay(350);
      while (1) {
        Leitura();
        if (DIREITA > INTERVALOSENSORPRETO)
          break;
      }
      Frente();
      delay(350);
    }
  }
  

  if (((DIREITA > INTERVALOSENSORPRETO) && (ESQUERDA > INTERVALOSENSORPRETO)) || ((DIREITA < INTERVALOSENSORPRETO) && (ESQUERDA < INTERVALOSENSORPRETO))) {
    Frente();
  }

  else if (DIREITA < INTERVALOSENSORPRETO) {
    Horario();
    while (1) {
      Leitura();
      if (DIREITA > INTERVALOSENSORPRETO) break;
      if (ESQUERDA < INTERVALOSENSORPRETO && DIREITA < INTERVALOSENSORPRETO) {
        Frente();
        break;
      }

    }
  }


  else if (ESQUERDA < INTERVALOSENSORPRETO) {
    Antihorario();
    while (1) {
      Leitura();
      if (ESQUERDA > INTERVALOSENSORPRETO) break;
      if (ESQUERDA < INTERVALOSENSORPRETO && DIREITA < INTERVALOSENSORPRETO) {
        Frente();
        break;
      }
    }
  }

  if (ESQUERDAVERDE > INTERVALOBLACK || DIREITAVERDE > INTERVALOBLACK) {
    
    if (ESQUERDAVERDE > INTERVALOBLACK) {
      Horario();
      while (1) {
        Leitura();
        if (DIREITA > INTERVALOSENSORPRETO) break;
      }
    }
    else {
      Antihorario();
      while (1) {
        Leitura();

        if (ESQUERDA > INTERVALOSENSORPRETO) break;
      }
    }
  }
  
}
