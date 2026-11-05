const int BUTTON_PIN = 12;
const int LED_PIN = 2; 

bool previousPressed = false;
bool ledState = LOW;
unsigned long lastBlink = 0;

void setup() {
  Serial.begin(115200);

  pinMode(BUTTON_PIN, INPUT_PULLDOWN);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  Serial.println("Коснись сенсорной кнопки");
}

void loop() {
  bool pressed = digitalRead(BUTTON_PIN) == HIGH;

  if (pressed != previousPressed) {
    previousPressed = pressed;
    Serial.println(pressed ? "Кнопка нажата" : "Кнопка отпущена");
  }

  if (pressed) {
    if (millis() - lastBlink >= 200) {
      lastBlink = millis();
      ledState = !ledState;
      digitalWrite(LED_PIN, ledState);
    }
  } else {
    ledState = LOW;
    digitalWrite(LED_PIN, LOW);
  }
}