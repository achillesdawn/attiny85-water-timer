#include <Arduino.h>
#include <avr/iotn85.h>
#include <stdint.h>

constexpr uint32_t DELAY_MS = 500;

void setup() {
  DDRB |= (1 << DDB1) | (1 << DDB4);
  PORTB = 0;
}

inline void activate_pin(int pin, uint32_t time, bool active) {
  if (active) {
    PORTB |= (1 << pin);
  } else {
    PORTB &= ~(1 << pin);
  }

  delay(time);
}

void loop() {

  for (uint8_t i = 0; i < 2; i++) {
    activate_pin(PB1, DELAY_MS, true);
    activate_pin(PB1, DELAY_MS, false);
  }

  activate_pin(PB1, DELAY_MS, true);

  activate_pin(PB4, 2000, true);
  activate_pin(PB4, 0, false);

  activate_pin(PB1, DELAY_MS, false);
}
