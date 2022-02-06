#include <Arduino.h>
#include <ArduinoSTL.h>
#include "WMController.hpp"

#define LED 13
#define DELAY 250

WM::WMController controller;

void setup()
{
  pinMode(LED, OUTPUT);
  Serial.begin(115200);
}

void loop()
{
  const bool state = digitalRead(LED);
  digitalWrite(LED, !state);
  delay(DELAY);

  std::cout << "State: " << (state ? "ON" : "OFF") << std::endl;

  auto resp = controller.exec(WM::WMInputs{
    start : state,
    tamper : false,
    pressure : true,
  });

  std::cout << "Motor     : " << resp.motor << std::endl;
  std::cout << "Agitate   : " << resp.agitate << std::endl;
  std::cout << "Centrifuge: " << resp.centrifuge << std::endl;
  std::cout << "Valve     : " << resp.valve << std::endl;
}