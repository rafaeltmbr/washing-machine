#include "../include/WMController.hpp"
#include "../util/createStepConditionMapping.cpp"

WM::WMController::WMController()
{
  this->currentStep = WMSteps::standby;
  this->stepTime = 0;
  this->lastStepTime = millis();
  this->stepConditionMapping = createStepConditionMapping();
}

WM::WMController::WMController(WMControllerConfig &config)
{
  WM::WMController();
  this->intermittentTime = config.intermittentTime;
}

WM::WMOutputs WM::WMController::exec(WMInputs inputs)
{
  auto action = this->stepConditionMapping[this->currentStep];

  this->updateCurrentStepTime(inputs);
  this->updateNextStep(action, inputs);

  return this->computeOutputs(action, inputs);
}

void WM::WMController::updateCurrentStepTime(WMInputs inputs)
{
  if (!inputs.tamper)
    this->stepTime += millis() - this->lastStepTime;

  this->lastStepTime = millis();
}

void WM::WMController::updateNextStep(WMStepAction action, WMInputs inputs)
{
  if (this->gotoNextStep(action, inputs))
  {
    this->stepTime = 0;
    this->currentStep = action.nextStep;
  }
}

WM::WMOutputs WM::WMController::computeOutputs(WMStepAction action, WMInputs inputs)
{
  return {
    motor : computeOutput(action.motor, inputs, this->stepTime),
    agitate : computeOutput(action.agitate, inputs, this->stepTime),
    centrifuge : computeOutput(action.centrifuge, inputs, this->stepTime),
    valve : computeOutput(action.valve, inputs, this->stepTime),
  };
}

bool WM::WMController::computeOutput(
    WMOutputCondition condition,
    WMInputs inputs,
    WMTime time)
{
  switch (condition)
  {
  case WM::WMOutputCondition::forceLow:
    return false;
  case WM::WMOutputCondition::forceHigh:
    return true;
  case WM::WMOutputCondition::pressure:
    return inputs.pressure;
  case WM::WMOutputCondition::tamper:
    return inputs.tamper;
  case WM::WMOutputCondition::pressureAndTamper:
    return inputs.pressure && inputs.tamper;
  case WM::WMOutputCondition::intermittent:
  default:
    return (time / this->intermittentTime) % 2;
  }
}

bool WM::WMController::gotoNextStep(WMStepAction action, WMInputs inputs)
{
  switch (action.nextStepCondition)
  {
  case WMNextStepCondition::pressure:
    return inputs.pressure;
  case WMNextStepCondition::startButton:
    return inputs.start;
  case WMNextStepCondition::time:
  default:
    return this->stepTime >= action.duration;
  }
}
