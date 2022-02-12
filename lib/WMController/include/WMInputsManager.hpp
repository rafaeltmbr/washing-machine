#ifndef WM_INPUTS_MANAGER_HPP
#define WM_INPUTS_MANAGER_HPP

#include <Arduino.h>
#include <cstdint>
#include <debounce.hpp>
#include "WMInputs.hpp"

#ifndef WM_INPUTS_DEFAULT_START_PIN
#define WM_INPUTS_DEFAULT_START_PIN 2
#endif

#ifndef WM_INPUTS_DEFAULT_TAMPER_PIN
#define WM_INPUTS_DEFAULT_TAMPER_PIN 3
#endif

#ifndef WM_INPUTS_DEFAULT_PRESSURE_PIN
#define WM_INPUTS_DEFAULT_PRESSURE_PIN 4
#endif

#ifndef WM_INPUTS_DEFAULT_SKIP_PIN
#define WM_INPUTS_DEFAULT_SKIP_PIN 5
#endif

#ifndef WM_INPUTS_DEFAULT_AGITATE2_TIME_PIN
#define WM_INPUTS_DEFAULT_AGITATE2_TIME_PIN A0
#endif

#ifndef WM_INPUTS_DEFAULT_CENTRIFUGE_TIME_PIN
#define WM_INPUTS_DEFAULT_CENTRIFUGE_TIME_PIN A1
#endif

#ifndef WM_INPUTS_DEFAULT_AGITATE3_TIME_PIN
#define WM_INPUTS_DEFAULT_AGITATE3_TIME_PIN A2
#endif

#ifndef WM_INPUTS_DEFAULT_CENTRIFUGE2_TIME_PIN
#define WM_INPUTS_DEFAULT_CENTRIFUGE2_TIME_PIN A3
#endif

namespace WM
{
  typedef std::uint8_t InputPin;

  class WMInputsPinMapping
  {
  public:
    InputPin start;
    InputPin tamper;
    InputPin pressure;
    InputPin skip;
    InputPin agitate2Time;
    InputPin centrifugeTime;
    InputPin agitate3Time;
    InputPin centrifuge2Time;
  };

  class WMInputsManager
  {
  protected:
    WMInputsPinMapping pinMapping;

  public:
    WMInputsManager();
    WMInputsManager(const WMInputsPinMapping &);
    void ajustPinMode(void) const;
    WMInputs read(void) const;
  };
}

#endif // WM_PINS_MANAGER_HPP