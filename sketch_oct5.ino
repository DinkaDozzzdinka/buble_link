#include <WiFi.h>
#include <PubSubClient.h>

// 1. Введите данные вашей точки доступа Wi-Fi (2.4 ГГц)
const char* ssid = "";
const char* password = "";

// 2. Публичный облачный MQTT-брокер
const char* mqtt_server = "broker.hivemq.com";
const int mqtt_port = 1883;


const char* outTopic = "bubblelink/team123/dev1_to_dev2";
const char* inTopic  = "bubblelink/team123/dev2_to_dev1";
const char* clientID = "BubbleLink_ESP32_Device_1";

WiFiClient espClient;
PubSubClient client(espClient);

// Обработка команд, пришедших от напарника через интернет
void callback(char* topic, byte* payload, unsigned int length) {
  String message = "";
  for (unsigned int i = 0; i < length; i++) {
    message += (char)payload[i];
  }
  Serial.print(">>> Получена команда от напарника: ");
  Serial.println(message);

  if (message == "COLOR_CHANGE") {
    Serial.println("-> Триггер: Удаленная плата просит сменить цвет светодиодов!");
  } else if (message == "BUBBLES_START") {
    Serial.println("-> Триггер: Удаленная плата просит запустить механизм пузырей!");
  }
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Подключение к MQTT брокеру...");
    if (client.connect(clientID)) {
      Serial.println(" Успешно!");
      client.subscribe(inTopic); // Слушаем сообщения от второй платы
    } else {
      Serial.print(" Ошибка подключения, код rc=");
      Serial.print(client.state());
      Serial.println(". Повтор через 5 секунд...");
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println();
  Serial.print("Подключение к Wi-Fi: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("Wi-Fi подключен успешно!");
  Serial.print("IP адрес платы: ");
  Serial.println(WiFi.localIP());

  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  // Отправка тестовых сигналов через строку Serial Monitor:
  // Введите '1' и нажмите Enter -> отправится команда смены цвета
  // Введите '2' и нажмите Enter -> отправится команда пуска пузырей
  if (Serial.available()) {
    char ch = Serial.read();
    if (ch == '1') {
      client.publish(outTopic, "COLOR_CHANGE");
      Serial.println("<<< Отправлено напарнику: COLOR_CHANGE");
    } else if (ch == '2') {
      client.publish(outTopic, "BUBBLES_START");
      Serial.println("<<< Отправлено напарнику: BUBBLES_START");
    }
  }
}
