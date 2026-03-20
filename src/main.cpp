#include <Arduino.h>
#include <avr/iotn85.h>
#include <stdint.h>

constexpr uint32_t DELAY_MS = 500;
constexpr uint16_t SECONDS_PER_ACTIVATION = 60 * 60 * 8;
constexpr uint32_t ACTIVATION_TIME = 8000;

uint16_t seconds = 0;

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

inline void activate_sequence() {

  activate_pin(PB1, 0, true);

  activate_pin(PB4, ACTIVATION_TIME, true);

  activate_pin(PB4, 0, false);

  activate_pin(PB1, 0, false);
}

void loop() {

  activate_sequence();

  while (true) {

    activate_pin(PB1, DELAY_MS, true);
    activate_pin(PB1, DELAY_MS, false);

    seconds += 1;

    if (seconds > SECONDS_PER_ACTIVATION) {
      seconds = 0;

      activate_sequence();
    }
  }
}
