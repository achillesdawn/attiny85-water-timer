#!/bin/bash

# generate clang config
platformio run -t compiledb

# compile
platformio run --environment attiny85


# upload

platformio run --target upload --environment attiny85

# update platformio
platformio upgrade

# update dependencies

platformio pkg update

