#include "../include/WMInputsManager.hpp"

WM::WMInputsManager::WMInputsManager()
{
  this->pinMapping = {
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
    start : debounce(this->pinMapping.start),
    tamper : debounce(this->pinMapping.tamper),
    pressure : debounce(this->pinMapping.pressure),
    skip : debounce(this->pinMapping.skip),
    agitate2Time : analogRead(this->pinMapping.agitate2Time),
    centrifugeTime : analogRead(this->pinMapping.centrifugeTime),
    agitate3Time : analogRead(this->pinMapping.agitate3Time),
    centrifuge2Time : analogRead(this->pinMapping.centrifuge2Time),
  };
}

void WM::WMInputsManager::ajustPinMode(void) const
{
  pinMode(this->pinMapping.start, INPUT);
  pinMode(this->pinMapping.tamper, INPUT);
  pinMode(this->pinMapping.pressure, INPUT);
  pinMode(this->pinMapping.skip, INPUT);
  pinMode(this->pinMapping.agitate2Time, INPUT);
  pinMode(this->pinMapping.centrifugeTime, INPUT);
  pinMode(this->pinMapping.agitate3Time, INPUT);
  pinMode(this->pinMapping.centrifuge2Time, INPUT);
}