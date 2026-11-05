const int BUTTON_PIN = 12;  // GPIO, к которому подключён OUT кнопки
const int MOSFET_PIN = 17;  // D17 → PWM модуля

const unsigned long TOUCH_MS = 180;
const unsigned long RUN_MS = 2000;

bool lastReading = LOW;
bool stableReading = HIGH;  // Сначала ждём, пока кнопка будет отпущена
bool motorRunning = false;

unsigned long changedAt = 0;
unsigned long motorStartedAt = 0;

void setup() {
  pinMode(MOSFET_PIN, OUTPUT);
  digitalWrite(MOSFET_PIN, LOW);
  pinMode(BUTTON_PIN, INPUT_PULLDOWN);

  Serial.begin(115200);
  Serial.println("Готово. Коснись кнопки для запуска.");
}

void loop() {
  const unsigned long now = millis();

  if (motorRunning && now - motorStartedAt >= RUN_MS) {
    digitalWrite(MOSFET_PIN, LOW);
    motorRunning = false;
    Serial.println("Генератор выключен");
  }

  const bool reading = digitalRead(BUTTON_PIN);

  if (reading != lastReading) {
    lastReading = reading;
    changedAt = now;
  }

  if (reading != stableReading && now - changedAt >= TOUCH_MS) {
    stableReading = reading;

    if (stableReading == HIGH && !motorRunning) {
      digitalWrite(MOSFET_PIN, HIGH);
      motorStartedAt = now;
      motorRunning = true;
      Serial.println("Генератор включён на 2 секунды");
    }
  }
}