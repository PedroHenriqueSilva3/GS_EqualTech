# 📡 EqualTech – Plataforma IoT para Bem-Estar, Postura e Monitoramento Inteligente no Trabalho

Este repositório contém o projeto **EqualTech IoT**, parte da solução tecnológica EqualTech — uma plataforma que une **bem-estar no trabalho**, **prevenção de Burnout**, **monitoramento postural**, **gestão de estresse**, além de indicadores de **diversidade e equidade (DEI)** no ambiente corporativo.

Este módulo é focado no **sistema IoT embarcado**, responsável por coletar dados em tempo real e enviá-los via MQTT para análise.

---

## 🧩 Visão Geral da Solução

O EqualTech combina **sensores, Edge Computing e Inteligência Artificial** para ajudar colaboradores e empresas a criarem um ambiente de trabalho:

- Mais **seguro**  
- Mais **saudável**  
- Mais **sustentável**  
- Mais **inclusivo**  

O dispositivo IoT desenvolvido monitora:

- **Postura corporal** (MPU6050 – acelerômetro/giroscópio)  
- **Níveis de estresse** (variações de movimento e tremor do corpo)  
- **Temperatura e umidade do ambiente** (DHT22)  
- **Comportamentos de ansiedade/agitação** (sensor ultrassônico HC-SR04)  
- **Tempo efetivo de trabalho e tempo de pausa**  
- Recomenda **pausas inteligentes** com base em métricas ergonômicas e comportamentais  

Os dados são enviados via **MQTT**, processados em dashboards e integrados ao ecossistema EqualTech.

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


