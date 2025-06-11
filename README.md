# Projeto Robótica - Classificação e Manipulação de Objetos por Cor

Este é um projeto acadêmico desenvolvido para a disciplina de Robótica do curso de Engenharia da Computação na Universidade Estadual do Maranhão (UEMA).

## 👁️ Visão Geral

Sistema de automação robótica que utiliza visão computacional para classificar objetos por cor (vermelho e preto) e executar tarefas de manipulação diferenciadas através de um braço robótico com 4 graus de liberdade.

---

## 🔧 Componentes Principais

### Hardware

- **Microcontrolador:** Arduino
- **Sensor de Cor:** Adafruit TCS34725 (comunicação I2C)
- **Atuadores:** 4 servomotores VarSpeedServo
  - **Servo Base** (pino 2) – Rotação horizontal
  - **Servo Altura** (pino 4) – Movimento vertical
  - **Servo Distância** (pino 7) – Extensão/retração
  - **Servo Garra** (pino 8) – Abertura/fechamento

### Software

- **Bibliotecas:** Arduino.h, VarSpeedServo.h, Wire.h, Adafruit_TCS34725.h
- **Linguagem:** C++ para Arduino

---

## 🎯 Estratégia de Funcionamento

### 1. Inicialização

- Configuração do sensor TCS34725 (50ms de integração, ganho 4x)
- Posicionamento inicial de todos os servos em 90° (posição central)
- Verificação de conectividade do sensor

### 2. Ciclo Principal (Loop)

- Captura dos valores RGB do sensor
- Normalização dos valores para faixa 0-255
- Classificação da cor detectada
- Execução da rotina de manipulação correspondente
- Retorno à posição inicial

### 3. Algoritmo de Classificação

- **Detecção Vermelho:** R > 1, G < 100, B < 100
- **Detecção Preto:** R < 1, G < 50, B < 50
- **Normalização:** Mapeamento dos valores 16-bit (0-65535) para 8-bit (0-255)

---

## 🤖 Estratégias de Movimento

### Caso 1: Objeto Vermelho

**Objetivo:** Capturar objeto na posição frontal e depositar na caixa.

**Sequência:**
1. Abertura da garra (30°)
2. Avanço para captura (170°)
3. Fechamento da garra (90°)
4. Retorno à base (90°)
5. Elevação do braço (135°)
6. Rotação para caixa (35°)
7. Posicionamento para liberação (160°)
8. Abertura para soltar (50°)
9. Retorno à posição inicial

### Caso 2: Objeto Preto

**Objetivo:** Capturar objeto em posição lateral e depositar na caixa.

**Sequência:**
1. Rotação para alvo lateral (65°)
2. Abertura da garra (30°)
3. Avanço para captura (158°)
4. Fechamento da garra (90°)
5. Retorno à base (90°)
6. Elevação mais alta (145°)
7. Rotação para caixa (35°)
8. Posicionamento para liberação (160°)
9. Abertura para soltar (50°)
10. Retorno à posição inicial (76°)

---

## ⚙️ Características Técnicas

- **Controle de Movimento**
  - Velocidade Variável: Parâmetros ajustáveis (20-50 unidades)
  - Movimento Suave: Função `slowmove()` para transições controladas
  - Delays Estratégicos: 1000-1500ms entre movimentos para estabilização

---

## 📂 Código-Fonte

O código principal está em [`robotica.ino`](robotica.ino).

---

## 📚 Créditos

Projeto acadêmico desenvolvido por VINÍCIUS OLIVEIRA e RAFAEL JOSÉ NOGUEIRA para a disciplina de Robótica – Engenharia da Computação/UEMA.