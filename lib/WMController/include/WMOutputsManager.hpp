#ifndef WM_OUTPUTS_MANAGER_HPP
#define WM_OUTPUTS_MANAGER_HPP

#include <Arduino.h>
#include <cstdint>
#include "WMOutputs.hpp"

#ifndef WM_OUTPUTS_DEFAULT_MOTOR_PIN
#define WM_OUTPUTS_DEFAULT_MOTOR_PIN 6
#endif

#ifndef WM_OUTPUTS_DEFAULT_AGITATE_PIN
#define WM_OUTPUTS_DEFAULT_AGITATE_PIN 7
#endif

#ifndef WM_OUTPUTS_DEFAULT_CENTRIFUGE_PIN
#define WM_OUTPUTS_DEFAULT_CENTRIFUGE_PIN 8
#endif

#ifndef WM_OUTPUTS_DEFAULT_VALVE_PIN
#define WM_OUTPUTS_DEFAULT_VALVE_PIN 9
#endif

namespace WM
{
  typedef std::uint8_t WMOutputPin;

  class WMOutputsPinMap
  {
  public:
    WMOutputPin motor;
    WMOutputPin agitate;
    WMOutputPin centrifuge;
    WMOutputPin valve;
  };

  class WMOutputsManager
  {
  private:
    WMOutputsPinMap pinMap;

  public:
    WMOutputsManager();
    WMOutputsManager(const WMOutputsPinMap &);
    void ajustPinMode(void) const;
    void write(const WMOutputs &) const;
  };
}

#endif // WM_OUTPUTS_MANAGER_HPP