#!/bin/bash

# compile
platformio run --environment attiny85


# upload

platformio run --target upload --environment attiny85

# update platformio
platformio upgrade

# update dependencies

platformio pkg update
