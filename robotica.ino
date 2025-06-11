#include <Arduino.h>
#include <VarSpeedServo.h>
#include <Wire.h>
#include "Adafruit_TCS34725.h"

// **Definição dos pinos dos servos**
#define SERVO_GARRA 8
#define SERVO_DISTANCIA 7
#define SERVO_ALTURA 4
#define SERVO_BASE 2

// **Inicialização do sensor TCS34725**
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);

// **Objetos dos servos**
VarSpeedServo servo_distancia;
VarSpeedServo servo_garra;
VarSpeedServo servo_altura;
VarSpeedServo servo_base;

// **Função para detectar vermelho (R alto, G e B baixos)**
bool isRed(uint8_t r, uint8_t g, uint8_t b) {
  return (r > 1 && g < 100 && b < 100 /*&& r > g * 1.5 && r > b * 1.5*/);
}

// **Função para detectar preto (todos os valores baixos)**
bool isBlack(uint8_t r, uint8_t g, uint8_t b) {
  return (r < 1 && g < 50 && b < 50);
}

void setup() {
  Serial.begin(9600);
  
  // **Inicializa o sensor de cor**0202
  if (!tcs.begin()) {
    Serial.println("Erro: Sensor TCS34725 não encontrado!");
    while (1); // **Para o programa se o sensor não for detectado**
  }
  
  // **Anexa os servos aos pinos**
  servo_garra.attach(SERVO_GARRA);
  servo_distancia.attach(SERVO_DISTANCIA);
  servo_altura.attach(SERVO_ALTURA);
  servo_base.attach(SERVO_BASE);

  // **Nova posição inicial com base na centralização mecânica (90 como centro)**
  servo_distancia.write(90);
  servo_garra.write(90);
  servo_altura.write(90);
  servo_base.write(90);
}

void loop() {
  // **Lê os valores RGB do sensor**
  uint16_t r, g, b, c;
  tcs.getRawData(&r, &g, &b, &c);
  
  // **Normaliza os valores para 0-255**
  uint8_t red = map(r, 0, 65535, 0, 255);
  uint8_t green = map(g, 0, 65535, 0, 255);
  uint8_t blue = map(b, 0, 65535, 0, 255);
  
  // **Exibe os valores no Serial Monitor (opcional)**
  Serial.print("R: "); Serial.print(red);
  Serial.print(" G: "); Serial.print(green);
  Serial.print(" B: "); Serial.println(blue);
  
  // **Verifica a cor e executa o movimento correspondente**
  if (isRed(red, green, blue)) {
    Serial.println("Cor detectada: VERMELHO → Executando Caso 1");
    caso1();
  } else if (isBlack(red, green, blue)) {
    Serial.println("Cor detectada: PRETO → Executando Caso 2");
    caso2();
  } else {
    Serial.println("Cor indefinida! Aguardando nova leitura...");
    delay(1000);
  }

  final(); // **Retorna à posição inicial**
}

// **Movimento para objetos VERMELHOS (Caso 1)**
void caso1() {
  delay(1000);
  servo_garra.slowmove(30, 20);          // Abre a garra
  delay(1500);
  servo_distancia.slowmove(170, 20);     // Avança até o alvo
  delay(1000);
  servo_garra.slowmove(90, 30);          // Fecha a garra
  delay(1500);
  servo_distancia.slowmove(90, 30);      // Retorna à posição inicial
  delay(1000);
  servo_altura.slowmove(135, 30);        // Levanta o braço
  delay(1000);
  servo_base.slowmove(35, 30);           // Gira para a posição da caixa
  delay(1000);
  servo_distancia.slowmove(160, 30);     // Posiciona para soltar
  delay(1000);
  servo_garra.slowmove(50, 30);          // Abre a garra para soltar
  delay(1500);
  servo_garra.slowmove(90, 30);          // Fecha a garra novamente
  delay(1500);
  servo_distancia.slowmove(90, 30);      // Retorna à base
  delay(1000);
  servo_base.slowmove(90, 30);           // Volta à posição inicial
  delay(1000);
  servo_altura.slowmove(90, 30);         // Abaixa o braço
  delay(1000);
}

// **Movimento para objetos PRETOS (Caso 2)**
void caso2() {
  delay(1000);
  servo_base.slowmove(65, 30);           // Gira para o alvo
  delay(1000);
  servo_garra.slowmove(30, 50);          // Abre a garra
  delay(1500);
  servo_distancia.slowmove(158, 30);     // Avança até o alvo
  delay(1000);
  servo_garra.slowmove(90, 30);          // Fecha a garra
  delay(1500);
  servo_distancia.slowmove(90, 40);      // Retorna à posição inicial
  delay(1000);
  servo_altura.slowmove(145, 40);        // Levanta o braço
  delay(1000);
  servo_base.slowmove(35, 30);           // Gira para a caixa
  delay(1000);
  servo_distancia.slowmove(160, 30);     // Posiciona para soltar
  delay(1000);
  servo_garra.slowmove(50, 50);          // Abre a garra para soltar
  delay(1500);
  servo_garra.slowmove(90, 30);          // Fecha a garra novamente
  delay(1500);
  servo_distancia.slowmove(90, 30);      // Retorna à base
  delay(1000);
  servo_base.slowmove(76, 30);           // Volta à posição inicial
  delay(1000);
  servo_altura.slowmove(90, 30);         // Abaixa o braço
  delay(1000);
}

// **Função para retornar à posição inicial**
void final() {
  servo_distancia.slowmove(90, 30);
  delay(1000);
  servo_garra.slowmove(90, 30);
  delay(1500);
  servo_altura.slowmove(90, 30);
  delay(1500);
  servo_base.slowmove(90, 30);
  delay(1500);
}
