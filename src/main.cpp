#include "sleep.h"
#include <Arduino.h>
#include <avr/wdt.h>

bool done = false;
uint64_t count = 0;
uint8_t blink_pin = PB0;

ISR(PCINT0_vect) {
    // disable interrupts
    PCMSK &= ~(1 << PB3);

    PORTB |= (1 << PB4);
    sleep(WDTO_60MS);
    PORTB &= ~(1 << PB4);
    sleep(WDTO_2S);

    // re-enable interrupts
    PCMSK |= (1 << PB3);
}

void setup_interrupt() {
    // The External Interrupt Control Register A: ref page 51
    // contains control bits for interrupt sense control.

    // The rising edge of INT0 generates an interrupt request.
    // MCUCR |= (1 << ISC01) | (1 << ISC00);

    // // The falling edge of INT0 generates an interrupt request.
    // MCUCR |= (0 << ISC01) | (1 << ISC00);

    // The low level of INT0 generates an interrupt request.
    MCUCR |= (0 << ISC01) | (0 << ISC00);

    // General Interrupt Mask Register

    // enabling external interrupt flag
    // GIMSK |= (1 << INT0);

    // enabling pin change interrupt flag
    GIMSK |= (1 << PCIE);

    // enable mask on PB3
    PCMSK |= (1 << PB3);
}

void setup() {

    pins_as_input();

    // set pins
    // 0 = input
    // 1 = output
    DDRB |= (1 << DDB0) | (1 << DDB4);
    DDRB &= ~(1 << DDB3);

    PORTB = 0;
    // if input, 1 = pullup
    PORTB |= (1 << PORTB3);

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
    }
}