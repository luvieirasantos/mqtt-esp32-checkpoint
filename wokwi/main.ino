#include <WiFi.h>
#include <PubSubClient.h>

// --- Configurações da Rede Wi-Fi ---
const char* SSID = "Wokwi-GUEST";
const char* PASSWORD = "";

// --- Configurações do Broker MQTT ---
const char* BROKER_MQTT = "20.120.245.89"; // IP da sua VM Azure
const int BROKER_PORT = 1883;
const char* ID_MQTT = "esp32_mqtt";
const char* USER_MQTT = "admin";
const char* PASS_MQTT = "1234";

const char* TOPIC_SUBSCRIBE = "fiap/iot/led";
const char* TOPIC_PUBLISH = "fiap/iot/temphumi";

WiFiClient espClient;
PubSubClient client(espClient);

// --- Conectar ao Wi-Fi ---
void setup_wifi() {
  delay(10);
  Serial.println("Conectando ao WiFi...");
  WiFi.begin(SSID, PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi conectado com sucesso!");
  Serial.print("Endereço IP: ");
  Serial.println(WiFi.localIP());
}

// --- Callback (quando recebe algo do tópico inscrito) ---
void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Mensagem recebida no tópico [");
  Serial.print(topic);
  Serial.print("]: ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}

// --- Reconectar ao MQTT se cair ---
void reconnect() {
  while (!client.connected()) {
    Serial.print("Tentando conexão MQTT...");
    if (client.connect(ID_MQTT, USER_MQTT, PASS_MQTT)) {
      Serial.println("Conectado!");
      client.subscribe(TOPIC_SUBSCRIBE);
    } else {
      Serial.print("Falhou. rc=");
      Serial.print(client.state());
      Serial.println(" Tentando novamente em 5 segundos...");
      delay(5000);
    }
  }
}

// --- Setup ---
void setup() {
  Serial.begin(115200);
  setup_wifi();
  client.setServer(BROKER_MQTT, BROKER_PORT);
  client.setCallback(callback);
}

// --- Loop ---
void loop() {
  if (!client.connected()) {
    reconnect();
  }

  client.loop();

  // Simula sensores
  float temperatura = random(200, 350) / 10.0;
  float umidade = random(400, 800) / 10.0;
  float pressao = random(9800, 10500) / 10.0;
  float altitude = random(0, 500);

  // Monta JSON
  char payload[100];
  snprintf(payload, sizeof(payload),
           "{\"temp\":%.1f,\"umid\":%.1f,\"press\":%.1f,\"alt\":%.1f}",
           temperatura, umidade, pressao, altitude);

  // Publica no tópico
  client.publish(TOPIC_PUBLISH, payload);
  Serial.print("Publicado: ");
  Serial.println(payload);

  delay(5000); // Aguarda 5 segundos
}
