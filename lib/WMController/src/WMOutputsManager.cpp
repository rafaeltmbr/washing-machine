#include "WMOutputsManager.hpp"

WM::WMOutputsManager::WMOutputsManager()
{
  pinMap = {
    motor : WM_OUTPUTS_DEFAULT_MOTOR_PIN,
    agitate : WM_OUTPUTS_DEFAULT_AGITATE_PIN,
    centrifuge : WM_OUTPUTS_DEFAULT_CENTRIFUGE_PIN,
    valve : WM_OUTPUTS_DEFAULT_VALVE_PIN,
  };
}

WM::WMOutputsManager::WMOutputsManager(const WMOutputsPinMap &pinMap)
{
  this->pinMap = pinMap;
}

void WM::WMOutputsManager::ajustPinMode(void) const
{
  pinMode(pinMap.motor, OUTPUT);
  pinMode(pinMap.agitate, OUTPUT);
  pinMode(pinMap.centrifuge, OUTPUT);
  pinMode(pinMap.valve, OUTPUT);
}

void WM::WMOutputsManager::write(const WMOutputs &outputs) const
{
  digitalWrite(pinMap.motor, outputs.motor);
  digitalWrite(pinMap.agitate, outputs.agitate);
  digitalWrite(pinMap.centrifuge, outputs.centrifuge);
  digitalWrite(pinMap.valve, outputs.valve);
}