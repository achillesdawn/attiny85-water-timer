#include <Arduino.h>
#include <avr/iotn85.h>

void setup() {
  DDRB |= (1 << DDB0);
  PORTB = 0;
}

void loop() {

  PORTB |= (1 << PB0);
  delay(500);
  PORTB &= ~(1 << PB0);
  delay(500);
}
