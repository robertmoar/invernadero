//
// Created by robert mora on 27/05/2026.
//
#include <gtest/gtest.h>
#include "../lib/hal/gpio.h"

class GpioTest : public testing::Test {
protected:
    void SetUp() override {
        gpio_set(GpioPin::LED_BUILTIN,  GpioLevel_t::LOW);
        gpio_set(GpioPin::RELAY_1,      GpioLevel_t::LOW);
        gpio_set(GpioPin::RELAY_2,      GpioLevel_t::LOW);
        gpio_set(GpioPin::RELAY_3,      GpioLevel_t::LOW);
        gpio_set(GpioPin::RELAY_4,      GpioLevel_t::LOW);
    }
};

TEST_F(GpioTest, SetHighGetHigh) {
    gpio_set(GpioPin::RELAY_1,  GpioLevel_t::HIGH);
    GpioLevel_t result;
    GpioError_t err = gpio_get(GpioPin::RELAY_1, &result);
    ASSERT_EQ(err, GpioError_t::OK);
    EXPECT_EQ(result, GpioLevel_t::HIGH);
}

TEST_F(GpioTest, PinsAreIndependent) {
    gpio_set(GpioPin::RELAY_1,  GpioLevel_t::HIGH);
    gpio_set(GpioPin::RELAY_2,  GpioLevel_t::LOW);
    GpioLevel_t result_1;
    GpioLevel_t result_2;
    GpioError_t err_1 = gpio_get(GpioPin::RELAY_1, &result_1);
    GpioError_t err_2 = gpio_get(GpioPin::RELAY_2, &result_2);
    ASSERT_EQ(err_1, GpioError_t::OK);
    ASSERT_EQ(err_2, GpioError_t::OK);
    EXPECT_EQ(result_1, GpioLevel_t::HIGH);
    EXPECT_EQ(result_2, GpioLevel_t::LOW);
}

TEST_F(GpioTest, GetWithNullPointer) {
    ASSERT_EQ(gpio_get(GpioPin::RELAY_1, nullptr), GpioError_t::INVALID_ARG);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}