📘 EqualTech — Sistema IoT de Monitoramento de Bem-Estar, Postura e Estresse no Trabalho

📌 Descrição Geral do Projeto

O EqualTech é uma solução inovadora desenvolvida para promover bem-estar, saúde mental e ambientes de trabalho mais seguros e inclusivos.
Esta parte do projeto implementa um sistema IoT com ESP32, responsável por monitorar indicadores físicos e emocionais do colaborador, enviando dados em tempo real via MQTT para um dashboard corporativo.

O objetivo é permitir que empresas acompanhem tendências de estresse, postura, temperatura, umidade e sinais de burnout de forma anônima e integrada, apoiando tomadas de decisão baseadas em dados — sem violar a privacidade do colaborador.

Este módulo IoT se conecta à plataforma EqualTech, que também oferece dashboards de diversidade, equidade salarial, acessibilidade e inclusão.
No conjunto, o sistema auxilia empresas a criarem ambientes mais saudáveis, justos e sustentáveis.

🧠 Problema

Estresse, burnout, jornadas exaustivas, má postura e sobrecarga emocional são problemas crescentes no ambiente de trabalho. Paralelamente, muitas empresas enfrentam desafios profundos em equidade salarial, diversidade e inclusão.

O módulo IoT do EqualTech atua no pilar de bem-estar, monitorando fatores críticos como:

Postura inadequada

Agitação corporal (indicador de estresse)

Temperatura/umidade (conforto térmico)

Longos períodos de trabalho sem pausas

Proximidade excessiva ao sensor (indicador de ansiedade)

Todos os dados são enviados de forma segura via MQTT para análise pela plataforma.

🚀 Solução IoT — Como Funciona

O ESP32 monitora continuamente sensores físicos e envia informações para o broker MQTT. A plataforma EqualTech utiliza esses dados para gerar alertas, recomendações automáticas e indicadores agregados para o RH.

Sensores Utilizados
Componente	Função
DHT22	Mede temperatura e umidade do ambiente.
MPU6050 (Acelerômetro/Giroscópio)	Avalia postura, movimentos bruscos e nível de estresse.
HC-SR04 (Ultrassônico)	Detecta proximidade → indicador de inquietação ou ansiedade.
LED RGB + Buzzer	Feedback imediato para o colaborador.
Botões físicos	Registrar pausas e retomadas de trabalho.
🧩 Principais Funcionalidades do Sistema
🔵 1. Monitoramento de Postura (MPU6050)

Detecta inclinação do corpo.

Classificação automática: Boa, Advertência, Ruim.

Acionamento de alerta visual/auditivo em caso crítico.

🔴 2. Detecção de Estresse Físico (Giroscópio)

Avalia movimentação corporal.

Classifica como Baixo, Moderado, Alto.

Envia alertas imediatos via MQTT.

🟡 3. Controle Inteligente de Jornada

Registra tempo de trabalho e de pausa.

Sugere pausas automáticas após 50 minutos de trabalho contínuo.

Impede retomada antes do tempo mínimo de descanso.

🟣 4. Análise de Ansiedade/Inquietação

O sensor ultrassônico detecta aproximação brusca.

Gera alerta de possível agitação ou estresse emocional.

🟢 5. Feedback em Tempo Real

LED RGB informa estado (trabalho, alerta, pausa).

Buzzer emite alertas sonoros para riscos detectados.

🟠 6. Envio de Dados via MQTT

Dados enviados a cada 10 segundos:

esp32/temperatura

esp32/umidade1

esp32/postura

esp32/estresse

esp32/distancia

esp32/tempo

esp32/alertas (mensagens urgentes)

🌐 MQTT — Tópicos Utilizados
Broker Público
test.mosquitto.org
Porta: 1883

Tópicos
Tópico	Descrição
esp32/status	Informa que o dispositivo está online.
esp32/temperatura	Temperatura do ambiente.
esp32/umidade1	Umidade do ambiente.
esp32/postura	Classificação da postura (Boa/Advertência/Ruim).
esp32/estresse	Nível de estresse físico.
esp32/distancia	Proximidade da pessoa ao sensor.
esp32/tempo	Tempo contínuo de trabalho.
esp32/alertas	Alertas críticos enviados imediatamente.
esp32/estado	Indica se o usuário está em pausa.

Esses dados são consumidos pelo backend da EqualTech para gerar indicadores agregados e insights.

🛠️ Arquitetura do Sistema
[Sensores IoT] → [ESP32] → (MQTT Publish) → [Broker Mosquitto]
→ [EqualTech Platform] → Dashboards e Insights de Saúde & Bem-Estar

🔧 Dependências do Código

Bibliotecas utilizadas:

WiFi.h (Conexão Wi-Fi)

PubSubClient.h (MQTT)

Wire.h

Adafruit_MPU6050.h

Adafruit_Sensor.h

DHT.h

💻 Como Executar o Projeto
1. Abra o código no Arduino IDE

Certifique-se de ter selecionado a placa:

ESP32 Dev Module

2. Instale as bibliotecas

Via Gerenciador de Bibliotecas:

Adafruit MPU6050

Adafruit Unified Sensor

DHT Sensor Library

PubSubClient

3. Conecte à rede Wi-Fi Wokwi (se estiver usando simulação)

SSID: Wokwi-GUEST
Senha: (vazia)

4. Inicie o broker MQTT

Usamos:

test.mosquitto.org:1883

5. Teste os tópicos

Você pode usar:

MQTT Explorer

HiveMQ Console

MQTT Dashboard

🔗 Link do Projeto no Wokwi

https://wokwi.com/projects/447918959118197761
Exemplo:

https://wokwi.com/projects/XXXXXX
