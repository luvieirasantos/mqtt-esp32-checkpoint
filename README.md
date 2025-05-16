# 📡 Checkpoint 03 – IoT com MQTT, ESP32 e Node-RED

**Disciplina:** Disruptive Architectures: IoT, IoB & Generative AI  
**Professor:** André Tritiack  
**Grupo:** Melissa Pereira 555656 Lu Vieira (Luis Henrique) 558935 Diego Furigo 558755

---

## ✅ Objetivo do Projeto

O objetivo deste projeto foi implementar um sistema IoT completo utilizando o protocolo MQTT. A aplicação conecta um ESP32 (simulado no Wokwi) a um broker Mosquitto hospedado em uma máquina virtual da Azure, enviando dados para o Node-RED, onde são visualizados em tempo real por meio de um dashboard.

---

## 🔧 Tecnologias Utilizadas

- 🟠 ESP32 (simulado no [Wokwi](https://wokwi.com))
- 🔵 Protocolo MQTT (via Mosquitto Broker)
- 🟣 Node-RED (dashboard e fluxo visual)
- ☁️ Azure (máquina virtual com Ubuntu 20.04)
- 🌐 GitHub

---

## 🔁 Fluxo da Aplicação

1. O ESP32 se conecta ao Wi-Fi simulado do Wokwi
2. Ele envia dados de sensores simulados (temperatura, umidade, pressão e altitude) a cada 5 segundos para o tópico MQTT `fiap/iot/temphumi`
3. O broker Mosquitto, na VM da Azure, recebe os dados
4. O Node-RED, também rodando na VM, processa os dados e exibe em medidores (gauges) via dashboard

---

## 📊 Exemplo de Dados Publicados

```json
{"temp": 26.4, "umid": 58.1, "press": 1002.5, "alt": 242.0}
