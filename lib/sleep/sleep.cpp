#include <Arduino.h>
#include <avr/power.h>
#include <avr/sleep.h>
#include <avr/wdt.h>

#include "sleep.h"

ISR(WDT_vect) {}

void pins_as_input() {
    // set all pins as inputs pullup for power saving
    for (uint8_t i = 0; i < 6; i++) {
        pinMode(i, INPUT_PULLUP);
    }
}


void watch_dog_enable(uint8_t wdto) {
    wdt_reset();

    // WDTO_4S == 4 seconds
    wdt_enable(wdto);

    // WDIE enables interrupt mode instead of reset when watchdog timer reaches
    // threshold WDIE is cleared after a timeout, next timeout will generate a
    // reset to avoid reset, WDIE must be set after each interrupt
    WDTCR |= (1 << WDIE);
}

void sleep_setup() {
    power_adc_disable();
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
}

void sleep_wake() {
    power_adc_enable();
    set_sleep_mode(SLEEP_MODE_IDLE);

    wdt_disable();
}

void sleep(uint8_t wdto = WDTO_1S) {

    sleep_setup();
    watch_dog_enable(wdto);

    sleep_bod_disable();
    sleep_enable();
    sei();
    sleep_cpu();

    // === ATtiny85 sleeps here  ===

    sleep_disable();
    sleep_wake();
}