#include "sleep.h"
#include <Arduino.h>
#include <avr/wdt.h>

bool done = false;
uint64_t count = 0;
uint8_t blink_pin = PB0;

ISR(INT0_vect) {
    PORTB |= (1 << PB0);
    sleep(WDTO_60MS);
    PORTB &= ~(1 << PB0);
    sleep();
}

void setup_interrupt() {
    // The External Interrupt Control Register A 
    // contains control bits for interrupt sense control.
    // The rising edge of INT0 generates an interrupt request.
    MCUCR |= (1 << ISC01) | (1 << ISC00);

    // General Interrupt Mask Register
    // enabling external interrupt flag
    GIMSK |= (1 << INT0);

    PCMSK |= (1 << PB1);
}

void setup() {

    pins_as_input();
    
    // set pints as output
    DDRB |= (1 << DDB0) | (1 << DDB4)| (1 << DDB3);

    PORTB = 0;

    setup_interrupt();

    // global interrupt enable
    sei();
}

void blink(uint8_t pin) {
    PORTB |= (1 << pin);
    sleep(WDTO_60MS);
    PORTB &= ~(1 << pin);
    sleep();
    sleep();
}

void loop() {

    while (!done) {

        blink(blink_pin);

        count += 2;

        if (count > 20) {
            blink_pin = PB3;
        } else if (count > 10) {
            blink_pin = PB4;
        }
    }
}