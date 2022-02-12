#include "../include/WMController.hpp"
#include "../util/createStepConditionMapping.cpp"

WM::WMController::WMController()
{
  this->currentStep = WMSteps::standby;
  this->stepTime = 0;
  this->lastStepTime = millis();
  this->stepConditionMapping = createStepConditionMapping();
}

WM::WMController::WMController(const WMControllerConfig &config)
{
  WM::WMController();
  this->intermittentTime = config.intermittentTime;
}

WM::WMOutputs WM::WMController::exec(const WMInputs &inputs)
{
  auto action = this->stepConditionMapping[this->currentStep];

  this->updateCurrentStepTime(inputs);
  this->updateNextStep(action, inputs);

  return this->computeOutputs(action, inputs);
}

WM::WMControllerStats WM::WMController::stats(void) const
{
  return {
    currentStep : this->currentStep,
    currentStepTime : this->stepTime
  };
}

void WM::WMController::updateCurrentStepTime(const WMInputs &inputs)
{
  if (!inputs.tamper)
    this->stepTime += millis() - this->lastStepTime;

  this->lastStepTime = millis();
}

void WM::WMController::updateNextStep(WMStepAction &action, const WMInputs &inputs)
{
  if (this->shouldGotoNextStep(action, inputs))
  {
    this->stepTime = 0;
    this->currentStep = action.nextStep;
  }
}

WM::WMOutputs WM::WMController::computeOutputs(WMStepAction &action, const WMInputs &inputs) const
{
  return {
    motor : computeOutput(action.motor, inputs, this->stepTime),
    agitate : computeOutput(action.agitate, inputs, this->stepTime),
    centrifuge : computeOutput(action.centrifuge, inputs, this->stepTime),
    valve : computeOutput(action.valve, inputs, this->stepTime),
  };
}

bool WM::WMController::computeOutput(
    const WMOutputCondition &condition,
    const WMInputs &inputs,
    WMTime time) const
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

bool WM::WMController::shouldGotoNextStep(WMStepAction &action, const WMInputs &inputs) const
{
  if (inputs.skip)
    return true;

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
