#include "../include/WMInputsManager.hpp"

WM::WMInputsManager::WMInputsManager()
{
  pinMapping = {
    start : WM_INPUTS_DEFAULT_START_PIN,
    tamper : WM_INPUTS_DEFAULT_TAMPER_PIN,
    pressure : WM_INPUTS_DEFAULT_PRESSURE_PIN,
    skip : WM_INPUTS_DEFAULT_SKIP_PIN,
    agitate2Time : WM_INPUTS_DEFAULT_AGITATE2_TIME_PIN,
    centrifugeTime : WM_INPUTS_DEFAULT_CENTRIFUGE_TIME_PIN,
    agitate3Time : WM_INPUTS_DEFAULT_AGITATE3_TIME_PIN,
    centrifuge2Time : WM_INPUTS_DEFAULT_CENTRIFUGE2_TIME_PIN,
  };
}

WM::WMInputsManager::WMInputsManager(const WMInputsPinMapping &pinMapping)
{
  this->pinMapping = pinMapping;
}

WM::WMInputs WM::WMInputsManager::read(void) const
{
  return {
    start : debounce(pinMapping.start),
    tamper : debounce(pinMapping.tamper),
    pressure : debounce(pinMapping.pressure),
    skip : debounce(pinMapping.skip),
    agitate2Time : analogRead(pinMapping.agitate2Time),
    centrifugeTime : analogRead(pinMapping.centrifugeTime),
    agitate3Time : analogRead(pinMapping.agitate3Time),
    centrifuge2Time : analogRead(pinMapping.centrifuge2Time),
  };
}

void WM::WMInputsManager::ajustPinMode(void) const
{
  pinMode(pinMapping.start, INPUT);
  pinMode(pinMapping.tamper, INPUT);
  pinMode(pinMapping.pressure, INPUT);
  pinMode(pinMapping.skip, INPUT);
  pinMode(pinMapping.agitate2Time, INPUT);
  pinMode(pinMapping.centrifugeTime, INPUT);
  pinMode(pinMapping.agitate3Time, INPUT);
  pinMode(pinMapping.centrifuge2Time, INPUT);
}