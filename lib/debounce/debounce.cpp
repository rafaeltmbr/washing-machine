#include "debounce.hpp"

int debounce(const std::uint8_t pin, const std::uint16_t timeout, const std::uint16_t maxCount)
{
  auto startTime = millis();
  auto lastRead = digitalRead(pin);
  unsigned count = 0;

  while ((count < maxCount) || (startTime - millis() < timeout))
  {
    auto read = digitalRead(pin);

    count = read != lastRead ? 0 : count + 1;
    lastRead = read;
  }

  return lastRead;
}