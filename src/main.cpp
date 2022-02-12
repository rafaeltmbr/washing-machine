#include <Arduino.h>
#include <ArduinoSTL.h>
#include "WMController.hpp"
#include "WMInputsManager.hpp"
#include "./include/convertWMStepToString.hpp"

#define DELAY 250

WM::WMController controller;
WM::WMInputsManager inputsManager;

void setup()
{
  Serial.begin(115200);
  inputsManager.ajustPinMode();
}

void loop()
{
  auto inputs = inputsManager.read();
  std::cout << std::endl
            << "================================================" << std::endl;

  std::cout << std::endl
            << "  INPUTS" << std::endl;
  std::cout << "start    : " << inputs.start << std::endl;
  std::cout << "tamper   : " << inputs.tamper << std::endl;
  std::cout << "pressure : " << inputs.pressure << std::endl;
  std::cout << "skip     : " << inputs.skip << std::endl;
  std::cout << "agitate2Time    : " << inputs.agitate2Time << std::endl;
  std::cout << "centrifugeTime  : " << inputs.centrifugeTime << std::endl;
  std::cout << "agitate3Time    : " << inputs.agitate3Time << std::endl;
  std::cout << "centrifuge2Time : " << inputs.centrifuge2Time << std::endl;

  auto resp = controller.exec(inputs);

  std::cout << std::endl
            << "  OUTPUTS" << std::endl;
  std::cout << "Motor      : " << resp.motor << std::endl;
  std::cout << "Agitate    : " << resp.agitate << std::endl;
  std::cout << "Centrifuge : " << resp.centrifuge << std::endl;
  std::cout << "Valve      : " << resp.valve << std::endl;

  auto stats = controller.stats();

  std::cout << std::endl
            << "  STATS" << std::endl;
  std::cout << "step : " << convertWMStepToString(stats.currentStep) << std::endl;
  std::cout << "time : " << stats.currentStepTime << std::endl;

  delay(DELAY);
}