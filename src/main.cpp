#include <Arduino.h>
#include <avr/iotn85.h>
#include <stdint.h>

uint32_t elapsed_seconds = 0;

void setup() {
  DDRB |= (1 << DDB0) | (1 << DDB4);
  PORTB = 0;
}

void loop() {

  PORTB |= (1 << PB0);
  delay(250);
  PORTB &= ~(1 << PB0);
  delay(250);
  PORTB |= (1 << PB0);
  delay(250);
  PORTB &= ~(1 << PB0);
  delay(250);

  elapsed_seconds += 1;

  if (elapsed_seconds > 5) {
    PORTB ^= (1 << PB4);
    elapsed_seconds = 0;
  }
}
