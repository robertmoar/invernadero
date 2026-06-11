//
// Created by robert mora sanchez on 23/5/26.
//
#pragma once

#include <cstdint>

#ifdef __cplusplus
/**
 * We only include the pins we actually use
 */
enum class GpioPin : uint8_t {
    LED_BUILTIN = 4,    ///< Built-in LED (GPIO 4)
    RELAY_1 = 16,       ///< Relay channel 1 (GPIO 16)
    RELAY_2 = 17,       ///< Relay channel 2 (GPIO 17)
    RELAY_3 = 21,       ///< Relay channel 3 (GPIO 21)
    RELAY_4 = 22        ///< Relay channel 4 (GPIO 22)
};

/**
 * We make an enum class prevent esp32 only implementations to
 * leak into shared header
 */
enum class GpioMode : uint8_t {
    INPUT = 0,
    OUTPUT = 1
};

/**
 * Logic level for a GPIO pin.
 * LOW = 0V, HIGH = 3.3V on ESP32 hardware.
 * On native builds this is simulated software.
 */
enum class GpioLevel : uint8_t {
    LOW = 0,
    HIGH = 1
};

/**
 * Here we define our own error handling,
 * done in that way to work with Gtest
 */

enum class GpioError : int32_t { //we sign error types
    OK = 0,
    INVALID_ARG = 1,
    FAIL = 2,
    INVALID_STATE = 3
};
/**
 * Our bridge to C++ --> C
 */
typedef GpioPin GpioPin_t;      ///< C++ alias; resolves to uint8_t in C (no enum safety in C)
typedef GpioLevel GpioLevel_t;  ///< C++ alias; resolves to uint8_t in C
typedef GpioMode GpioMode_t;
typedef GpioError GpioError_t;
#else
typedef uint8_t GpioPin_t;
typedef uint8_t GpioLevel_t;
typedef uint8_t GpioMode_t;
typedef int32_t GpioError_t;
#endif

#ifdef __cplusplus
extern "C" {
#endif
    //one function to set the pin, another to get its lvl
void gpio_set(GpioPin_t pin, GpioLevel_t level);
GpioError_t gpio_get(GpioPin_t pin, GpioLevel_t *out_level);
GpioError_t gpio_init(GpioPin_t pin, GpioMode_t mode);

#ifdef __cplusplus
}
#endif