//
// Created by robert mora on 24/05/2026.
//

#include "../hal/gpio.h"
#include <cstdio>


constexpr size_t STATE_TABLE_SIZE = 23;
static GpioLevel_t gpio_state_table[STATE_TABLE_SIZE] = {};

void gpio_set(GpioPin_t pin, GpioLevel_t level) {
    if (static_cast<size_t>(pin) >= STATE_TABLE_SIZE) {
        std::printf("Atempted to set invalid pin: %d\n", static_cast<int>(pin));
        return;
    }
    gpio_state_table[static_cast<size_t>(pin)] = level;
    std::printf("Set pin %d to %d\n", static_cast<int>(pin), static_cast<int>(level));
}

GpioError_t gpio_get(GpioPin_t pin, GpioLevel_t *out_level) {
    if (out_level == nullptr) {
        std::printf("gpio_get: NULL pointer on digital twin\n");
        return GpioError_t::INVALID_ARG;
    }
    if (static_cast<size_t>(pin) >= STATE_TABLE_SIZE) {
        std::printf("gpio_get: invalid gpio pin on digital twin; %d\n", static_cast<uint8_t>(pin));
        return GpioError_t::INVALID_ARG;
    }
    GpioLevel_t twin_level = gpio_state_table[static_cast<size_t>(pin)];
    *out_level = twin_level;
    return GpioError_t::OK;
}

GpioError_t gpio_init(GpioPin_t pin, GpioMode_t mode) {
    if (static_cast<size_t>(pin) >= STATE_TABLE_SIZE) {
        return GpioError_t::INVALID_ARG;
    }
    std::printf("gpio_init pin %d mode %d\n",
                static_cast<int>(pin),
                static_cast<int>(mode));
    return GpioError_t::OK;
}