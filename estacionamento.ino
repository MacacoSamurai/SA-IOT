#include <Servo.h>

const int TRIG = 12;
const int ECHO = 13;
const int SERVO_PIN = 11;

Servo cancela;
int vagas = 9;

long lerDistanciaCm() {
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);
  long d = pulseIn(ECHO, HIGH);
  return d * 0.034 / 2;
}

void setup() {
  Serial.begin(9600);
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  cancela.attach(SERVO_PIN);
  cancela.write(0);                 // fechada
  Serial.println("Sistema iniciado");
}

void loop() {
  long dist = lerDistanciaCm();
  Serial.println(dist);

  if (dist < 20 && vagas > 0) {
    cancela.write(90);              // abre
    vagas--;
    Serial.print("Vagas: ");
    Serial.println(vagas);
    delay(3000);                    // espera o carro passar (chute)
    cancela.write(0);               // fecha
    delay(1000);
  }

  delay(100);
}