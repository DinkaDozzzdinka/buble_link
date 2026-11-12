#include <Adafruit_NeoPixel.h>

constexpr int LED_PIN = 23;
constexpr int LED_COUNT = 8;

Adafruit_NeoPixel ring(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  ring.begin();
  ring.setBrightness(25);  // Небольшая яркость для первого теста
  ring.clear();
  ring.show();
}

void loop() {
  ring.fill(ring.Color(255, 0, 0));  // Красный
  ring.show();
  delay(1000);

  ring.fill(ring.Color(0, 255, 0));  // Зелёный
  ring.show();
  delay(1000);

  ring.fill(ring.Color(0, 0, 255));  // Синий
  ring.show();
  delay(1000);
}