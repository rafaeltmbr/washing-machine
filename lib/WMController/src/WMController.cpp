#include "../include/WMController.hpp"
#include "../util/createStepConditionMapping.cpp"

WM::WMController::WMController()
{
  currentStep = WMSteps::standby;
  stepTime = 0;
  lastStepTime = millis();
  stepConditionMapping = createStepConditionMapping();
  lastSkipState = false;
}

WM::WMController::WMController(const WMControllerConfig &config)
{
  WM::WMController();
  intermittentTime = config.intermittentTime;
}

WM::WMOutputs WM::WMController::exec(const WMInputs &inputs)
{
  auto action = stepConditionMapping[currentStep];

  updateCurrentStepTime(inputs);
  updateNextStep(action, inputs);

  return computeOutputs(action, inputs);
}

WM::WMControllerStats WM::WMController::stats(void) const
{
  return {
    currentStep : currentStep,
    currentStepTime : stepTime
  };
}

void WM::WMController::updateCurrentStepTime(const WMInputs &inputs)
{
  if (inputs.tamper)
    stepTime += millis() - lastStepTime;

  lastStepTime = millis();
}

void WM::WMController::updateNextStep(WMStepAction &action, const WMInputs &inputs)
{
  if (shouldGotoNextStep(action, inputs))
  {
    stepTime = 0;
    currentStep = action.nextStep;
  }
}

WM::WMOutputs WM::WMController::computeOutputs(WMStepAction &action, const WMInputs &inputs) const
{
  return {
    motor : computeOutput(action.motor, inputs),
    agitate : computeOutput(action.agitate, inputs),
    centrifuge : computeOutput(action.centrifuge, inputs),
    valve : computeOutput(action.valve, inputs),
  };
}

bool WM::WMController::computeOutput(
    const WMOutputCondition &condition,
    const WMInputs &inputs) const
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
    return (stepTime / intermittentTime) % 2;
  }
}

bool WM::WMController::shouldGotoNextStep(WMStepAction &action, const WMInputs &inputs)
{
  if (inputs.skip && !lastSkipState)
    return (lastSkipState = true);

  if (!inputs.skip)
    lastSkipState = false;

  switch (action.nextStepCondition)
  {
  case WMNextStepCondition::pressure:
    return inputs.pressure;
  case WMNextStepCondition::startButton:
    return inputs.start;
  case WMNextStepCondition::time:
  default:
    return stepTime >= action.duration;
  }
}
