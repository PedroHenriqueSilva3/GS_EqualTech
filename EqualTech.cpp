#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <WiFi.h>
#include <PubSubClient.h>

unsigned long inicioTrabalho = 0; 
unsigned long inicioPausado = 0; 
unsigned long tempoTrabalhado = 0;
unsigned long tempoPausado = 0;
unsigned long totalPausado = 0;
unsigned long totalTrabalho = 0;
unsigned long tempoMinimo = 10;

const unsigned long LIMITE_TRABALHO = 50UL * 60UL * 1000UL; // 50 minutos
bool trabalhoPausado = false;

// ----------------------- DHT22 -----------------------
#define DHTPIN 4
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

// ----------------------- HC-SR04 ---------------------
#define TRIG_PIN 13
#define ECHO_PIN 12

// ----------------------- LED RGB ----------------------
#define LED_R 14
#define LED_G 15
#define LED_B 2

// ----------------------- Buzzer -----------------------
#define BUZZER 17

// ----------------------- Botões -----------------------
#define BTN_PAUSA 26
#define BTN_RETORNA 25

// ----------------------- MPU6050 -----------------------
Adafruit_MPU6050 mpu;

// -------------------- WIFI --------------------
const char* ssid = "Wokwi-GUEST";
const char* password = "";

// -------------------- MQTT --------------------
const char* mqttServer = "test.mosquitto.org";  
const int mqttPort = 1883;

WiFiClient espClient;
PubSubClient client(espClient);

unsigned long lastMQTTSend = 0;

// ======================================================
// Funções auxiliares
// ======================================================

String formatarTempo(unsigned long ms) {
  unsigned long totalSeg = ms / 1000;
  int horas = totalSeg / 3600;
  int minutos = (totalSeg % 3600) / 60;
  int segundos = totalSeg % 60;

  char buffer[20];
  sprintf(buffer, "%02dh:%02dm:%02ds", horas, minutos, segundos);
  return String(buffer);
}


String avaliarPostura(sensors_event_t accel) {
  float inclinacao = abs(accel.acceleration.x) + abs(accel.acceleration.y);

  if (inclinacao > 8) {
    return "Ruim";
  } else if (inclinacao > 4) {
    return "Advertência";
  } else {
    return "Boa";
  }
}

String avaliarEstresse(sensors_event_t gyro) {
  float movimento = abs(gyro.gyro.x) + abs(gyro.gyro.y) + abs(gyro.gyro.z);

  if (movimento > 4) return "Alto";
  if (movimento > 2) return "Moderado";
  return "Baixo";
}

float medirDistancia() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  float duracao = pulseIn(ECHO_PIN, HIGH);
  float distancia = duracao * 0.034 / 2;

  return distancia;
}

void setRGB(bool r, bool g, bool b) {
  digitalWrite(LED_R, r);
  digitalWrite(LED_G, g);
  digitalWrite(LED_B, b);
}

void tocarAlerta() {
  tone(BUZZER, 1000, 300);
}

void conectarWiFi() {
  Serial.print("Conectando ao WiFi ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi conectado!");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
}

void conectarMQTT() {
  while (!client.connected()) {
    Serial.print("Conectando ao MQTT... ");

    if (client.connect("ESP32_Postura")) {
      Serial.println("Conectado!");
      client.publish("esp32/status", "ESP32 online");
    } else {
      Serial.print("Falhou, rc=");
      Serial.print(client.state());
      Serial.println(" Tentando novamente...");
      delay(2000);
    }
  }
}

// ======================================================
// SETUP
// ======================================================
void setup() {
  Serial.begin(115200);

  // DHT
  dht.begin();

  // HC-SR04
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  // LEDs
  pinMode(LED_R, OUTPUT);
  pinMode(LED_G, OUTPUT);
  pinMode(LED_B, OUTPUT);

  // Buzzer
  pinMode(BUZZER, OUTPUT);

  // Botões
  pinMode(BTN_PAUSA, INPUT_PULLUP);
  pinMode(BTN_RETORNA, INPUT_PULLUP);

  // MPU6050
  Wire.begin(21, 22);

  if (!mpu.begin()) {
    Serial.println("ERRO: MPU6050 não encontrado!");
    while (1) delay(10);
  }

  Serial.println("MPU6050 pronto!");

  conectarWiFi();
  client.setServer(mqttServer, mqttPort);
  conectarMQTT();

  inicioTrabalho = millis();

}

// ======================================================
// LOOP
// ======================================================
void loop() {

  if (!client.connected()) {
    conectarMQTT();
  }
  client.loop();
  
  if (digitalRead(BTN_PAUSA) == LOW && !trabalhoPausado) {
    trabalhoPausado = true;
    totalTrabalho += tempoTrabalhado;
    tempoTrabalhado = 0;
    inicioPausado = millis();
    setRGB(1, 1, 0);  // Amarelo = pausa
    Serial.println("🟡 Trabalho pausado. Contador zerado.");
    delay(1000);
  }

  // ---------------- BOTÃO RETOMAR ----------------
  if (digitalRead(BTN_RETORNA) == LOW && trabalhoPausado && tempoPausado/1000 > tempoMinimo) {
    trabalhoPausado = false;
    tempoMinimo = 10;
    totalPausado += tempoPausado;
    tempoPausado = 0;
    inicioTrabalho = millis();
    Serial.println("🟢 Trabalho retomado.");
    delay(1000);
  }

  if (trabalhoPausado) {
    client.publish("esp32/estado", "Trabalho pausado");
  }

  // ------ Se estiver pausado, só mostrar status ------
  if (trabalhoPausado) {
    Serial.print("Pausado...");
    tempoPausado = millis() - inicioPausado;
    String tempoStop = formatarTempo(tempoPausado);
    Serial.println("Tempo Pausado: "); Serial.println(tempoStop);
    delay(1000);
    return;
  }
  
  // --- Tempo de trabalho ---
  tempoTrabalhado = millis() - inicioTrabalho;
  String tempoStr = formatarTempo(tempoTrabalhado);

  // ---------- Ler DHT22 ----------
  float temperatura = dht.readTemperature();
  float umidade = dht.readHumidity();

  // ---------- Ler MPU6050 ----------
  sensors_event_t accel, gyro, temp;
  mpu.getEvent(&accel, &gyro, &temp);

  String postura = avaliarPostura(accel);
  String estresse = avaliarEstresse(gyro);

  // ---------- Distância ----------
  float distancia = medirDistancia();

  // ---------- Feedback com LED e buzzer ----------
  if (postura == "Ruim" || estresse == "Alto") {
    setRGB(0, 1, 1);
    tocarAlerta();
  } else if (postura == "Advertência" || estresse == "Moderado") {
    setRGB(0, 0, 1);
  } else {
    setRGB(1, 0, 1);
  }

  if (distancia < 20) {
    Serial.println("Alerta: Funcionário muito próximo do sensor → possível ansiedade/agitação.");
    setRGB(0, 1, 1);
    tocarAlerta();
  }

  // ---------- Controle de pausa ----------
  if (tempoTrabalhado > LIMITE_TRABALHO) {
    Serial.println("⚠️ Recomenda-se uma pausa breve para descanso mental de 5 minutos.");
    tempoMinimo = 300;
    setRGB(0, 1, 1);
    tocarAlerta();
  }

  // ---------- Print geral ----------
  Serial.println("----- STATUS -----");
  Serial.print("Temperatura: "); Serial.println(temperatura);
  Serial.print("Umidade: "); Serial.println(umidade);
  Serial.print("Postura: "); Serial.println(postura);
  Serial.print("Estresse: "); Serial.println(estresse);
  Serial.print("Distância: "); Serial.println(distancia);
  Serial.print("Tempo Trabalhado: "); Serial.println(tempoStr);
  Serial.println("------------------\n");

  

  // Envio periódico dos sensores (a cada 5 segundos)
  if (millis() - lastMQTTSend > 10000) {
    lastMQTTSend = millis();

    client.publish("esp32/temperatura", String(temperatura).c_str());
    client.publish("esp32/umidade1", String(umidade).c_str());
    client.publish("esp32/postura", postura.c_str());
    client.publish("esp32/estresse", estresse.c_str());
    client.publish("esp32/distancia", String(distancia).c_str());
    client.publish("esp32/tempo", tempoStr.c_str());
  }

  // Avisos imediatos
  if (postura == "Ruim") {
    client.publish("esp32/alertas", "Alerta: Má postura detectada!");
  }

  if (estresse == "Alto") {
    client.publish("esp32/alertas", "Alerta: Estresse elevado detectado!");
  }

  if (tempoTrabalhado > LIMITE_TRABALHO) {
    client.publish("esp32/alertas", "Tempo de trabalho excedido! Recomende pausa!");
  }

  if (distancia < 20) {
    client.publish("esp32/alertas", "Pessoa muito próxima do sensor!");
  }

  
  delay(1000);
}

