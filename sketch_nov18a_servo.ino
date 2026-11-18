#include <ESP32Servo.h>

Servo servo;

void setup() {
  servo.setPeriodHertz(50);       // Частота управляющих импульсов
  servo.attach(18, 1000, 2000);   // Сигнал подключён к GPIO18
}

void loop() {
  servo.write(180);  // Перейти в положение 180°
  delay(2000);       // Подождать 2 секунды

  servo.write(100);  // Перейти в положение 100°
  delay(2000);       // Подождать 2 секунды
}