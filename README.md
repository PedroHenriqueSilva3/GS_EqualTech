# 📡 EqualTech – Plataforma IoT para Bem-Estar, Postura e Monitoramento Inteligente no Trabalho

Este repositório contém o projeto **EqualTech IoT**, parte da solução tecnológica EqualTech — uma plataforma que une **bem-estar no trabalho**, **prevenção de Burnout**, **monitoramento postural**, **gestão de estresse**, além de indicadores de **diversidade e equidade (DEI)** no ambiente corporativo.

Este módulo é focado no **sistema IoT embarcado**, responsável por coletar dados em tempo real e enviá-los via MQTT para análise.

*Alunos:*
João Marcelo Diniz Vespa RM564038
Pedro Henrique da Silva RM566235
William Queiroz de Araujo RM565032


---

## 🧩 Visão Geral da Solução

O EqualTech combina **sensores, Edge Computing e Inteligência Artificial** para ajudar colaboradores e empresas a criarem um ambiente de trabalho:

- Mais **seguro**  
- Mais **saudável**  
- Mais **sustentável**  
- Mais **inclusivo**  

## 🧩 Principais Funcionalidades do Sistema

---

### 🔵 1. Monitoramento de Postura (MPU6050)
- Detecta inclinação do corpo.  
- Classificação automática: **Boa**, **Advertência**, **Ruim**.  
- Acionamento de alerta visual/auditivo em caso crítico.  

---

### 🔴 2. Detecção de Estresse Físico (Giroscópio)
- Avalia movimentação corporal.  
- Classifica como **Baixo**, **Moderado**, **Alto**.  
- Envia alertas imediatos via MQTT.  

---

### 🟡 3. Controle Inteligente de Jornada
- Registra tempo de trabalho e de pausa.  
- Sugere pausas automáticas após **50 minutos** de trabalho contínuo.  
- Impede retomada antes do **tempo mínimo de descanso**.  

---

### 🟣 4. Análise de Ansiedade/Inquietação
- O sensor ultrassônico detecta aproximação brusca.  
- Gera alerta de possível **agitação ou estresse emocional**.  

---

### 🟢 5. Feedback em Tempo Real
- LED RGB informa estado (trabalho, alerta, pausa).  
- Buzzer emite alertas sonoros para **riscos detectados**.  

---

### 🟠 6. Envio de Dados via MQTT
Dados enviados automaticamente a cada **10 segundos**:

- `esp32/temperatura`  
- `esp32/umidade1`  
- `esp32/postura`  
- `esp32/estresse`  
- `esp32/distancia`  
- `esp32/tempo`  
- `esp32/alertas` *(mensagens urgentes)*  



---

## 🧠 Tecnologias Utilizadas

- **ESP32**  
- **DHT22** – Temperatura e Umidade  
- **MPU6050** – Acelerômetro/Giroscópio  
- **HC-SR04** – Distância  
- **LED RGB** para feedback  
- **Wi-Fi + MQTT (Mosquitto Broker)**  
- **PubSubClient**  
- **Edge Computing** no próprio ESP32  

---

## 🌐 MQTT – Tópicos Utilizados

A comunicação é feita com o broker público:
test.mosquitto.org:1883


### **Tópicos Publicados**

| Tópico | Descrição |
|-------|-----------|
| `esp32/temperatura` | Envia temperatura atual |
| `esp32/umidade1` | Envia umidade do ambiente |
| `esp32/postura` | Envia avaliação de postura (Boa, Advertência, Ruim) |
| `esp32/estresse` | Envia nível de estresse (Baixo, Moderado, Alto) |
| `esp32/distancia` | Distância captada pelo ultrassônico |
| `esp32/tempo` | Tempo trabalhado formatado |
| `esp32/alertas` | Alertas imediatos (ex: má postura, estresse alto) |
| `esp32/status` | Status do dispositivo |
| `esp32/estado` | Indica se está pausado |

### Fluxo de Funcionamento MQTT

1. O dispositivo coleta dados dos sensores  
2. Processa localmente (Edge Computing)  
3. Publica automaticamente a cada **10 segundos**  
4. Alertas críticos são enviados imediatamente  

---

## 🖥️ Instruções de Uso

### **1. Acesse o projeto no Wokwi**
**Link:** *https://wokwi.com/projects/447918959118197761*

### **2. Acesse o video explicativo**
**Link:** *https://youtu.be/53CuLuVW9N8?si=gcSL4JAkDjloyvlw*


