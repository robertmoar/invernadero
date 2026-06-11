//
// Created by robert mora on 24/05/2026.
//
#include <cstdio>
#include <esp_log.h>
#include "soc/gpio_periph.h"
#include "driver/gpio.h"
#include "../hal/gpio.h"

/**
 * Because we implement our own error handling and to
 * make it coherent with HAL implementation plus digital twin
 * we need to translate from native build to esp32
 * that's the reason for this switch to be
 * helper translator
 */
static GpioError_t from_esp_err(esp_err_t err) {
    switch (err) {
        case ESP_OK:                    return GpioError_t::OK;
        case ESP_ERR_INVALID_ARG:       return GpioError_t::INVALID_ARG;
        case ESP_ERR_INVALID_STATE:     return GpioError_t::INVALID_STATE;
        default:                        return GpioError_t::FAIL;
    }
}

GpioError_t gpio_init(GpioPin_t pin, GpioMode_t mode) {
    gpio_mode_t esp_mode;
    switch (mode) {
        case GpioMode_t::OUTPUT: esp_mode = GPIO_MODE_OUTPUT; break;
        case GpioMode_t::INPUT: esp_mode = GPIO_MODE_INPUT; break;
        default: return GpioError_t::INVALID_ARG;
    }
    gpio_config_t gpio_num  = {};
    gpio_num.pin_bit_mask   = (1ULL << static_cast<int>(pin));
    gpio_num.mode           = esp_mode;
    gpio_num.pull_up_en     = GPIO_PULLUP_DISABLE;
    gpio_num.pull_down_en   = GPIO_PULLDOWN_DISABLE;
    gpio_num.intr_type      = GPIO_INTR_DISABLE;
    esp_err_t err = gpio_config(&gpio_num);
    if (err != ESP_OK) {
        std::printf("gpio_init pin %d err: %s\n", static_cast<int>(pin), esp_err_to_name(err));
        return from_esp_err(err);
    }
    return from_esp_err(err);
}

void gpio_set(GpioPin_t pin, GpioLevel_t level) {
    esp_err_t err = gpio_set_level(static_cast<gpio_num_t>(pin), static_cast<uint32_t>(level));
    if (err != ESP_OK) {
        std::printf("gpio_set pin %d level %d err: %s\n", static_cast<int>(pin),
                                                            static_cast<int>(level),
                                                              esp_err_to_name(err));
    return;
    }
    std::printf("gpio_set has success on pin %d level %d\n", static_cast<int>(pin), static_cast<int>(level));
}


GpioError_t gpio_get(GpioPin_t pin, GpioLevel_t *out_level) {
    // first we validate the pointer if it's not we return an error and a string
    if (out_level == nullptr) {
        std::printf("gpio_get: NULL pointer\n");
        return GpioError_t::INVALID_ARG;
    }
    /*
    #define GPIO_IS_VALID_GPIO(gpio_num)        ((gpio_num >= 0) && \
    ((1ULL << (gpio_num)) & SOC_GPIO_VALID_GPIO_MASK) != 0))
    from the header file driver/gpio.h
    this checks if pin is a valid gpio_pin if not return an error and a string
     */
    gpio_num_t gpio_num = static_cast<gpio_num_t>(pin);
    if (!GPIO_IS_VALID_GPIO(gpio_num)) {
    std::printf("gpio_get: invalid gpio pin; %d\n", pin);
        return GpioError_t::INVALID_ARG;
    }

    int pin_level = gpio_get_level(gpio_num);
    if (pin_level < 0) {
        std::printf("gpio_get: read failed on pin %d\n value: %d", static_cast<int>(pin), pin_level);
        return GpioError_t::FAIL;
    }
    *out_level = (pin_level == 1) ? GpioLevel_t::HIGH : GpioLevel_t::LOW;
return GpioError_t::OK;
}
