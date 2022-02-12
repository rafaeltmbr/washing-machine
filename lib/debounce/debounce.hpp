#ifndef DEBOUNCE_HPP
#define DEBOUNCE_HPP

#include <cstdint>
#include <Arduino.h>

int debounce(const std::uint8_t pin, const std::uint16_t timeout = 25, const std::uint16_t maxCount = 50);

#endif // DEBOUNCE_HPP