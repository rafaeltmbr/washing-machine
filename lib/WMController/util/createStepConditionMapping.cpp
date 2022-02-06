#include "../include/WMStepCondition.hpp"
#include <map>

std::map<WM::WMSteps, WM::WMStepAction> createStepConditionMapping(void)
{
  std::map<WM::WMSteps, WM::WMStepAction> conditionMapping;

  conditionMapping[WM::WMSteps::standby] = {
    motor : WM::WMOutputCondition::forceLow,
    agitate : WM::WMOutputCondition::forceLow,
    centrifuge : WM::WMOutputCondition::forceLow,
    valve : WM::WMOutputCondition::forceLow,
    nextStep : WM::WMSteps::fillIn,
    nextStepCondition : WM::WMNextStepCondition::startButton,
    duration : 0,
  };

  conditionMapping[WM::WMSteps::fillIn] = {
    motor : WM::WMOutputCondition::forceLow,
    agitate : WM::WMOutputCondition::forceLow,
    centrifuge : WM::WMOutputCondition::forceLow,
    valve : WM::WMOutputCondition::tamper,
    nextStep : WM::WMSteps::agitate,
    nextStepCondition : WM::WMNextStepCondition::pressure,
    duration : 0,
  };

  conditionMapping[WM::WMSteps::agitate] = {
    motor : WM::WMOutputCondition::pressureAndTamper,
    agitate : WM::WMOutputCondition::pressure,
    centrifuge : WM::WMOutputCondition::forceLow,
    valve : WM::WMOutputCondition::forceLow,
    nextStep : WM::WMSteps::soak,
    nextStepCondition : WM::WMNextStepCondition::time,
    duration : minutesToMilliseconds(2),
  };

  conditionMapping[WM::WMSteps::soak] = {
    motor : WM::WMOutputCondition::forceLow,
    agitate : WM::WMOutputCondition::forceLow,
    centrifuge : WM::WMOutputCondition::forceLow,
    valve : WM::WMOutputCondition::forceLow,
    nextStep : WM::WMSteps::agitate2,
    nextStepCondition : WM::WMNextStepCondition::time,
    duration : minutesToMilliseconds(15),
  };

  conditionMapping[WM::WMSteps::agitate2] = {
    motor : WM::WMOutputCondition::pressureAndTamper,
    agitate : WM::WMOutputCondition::pressure,
    centrifuge : WM::WMOutputCondition::forceLow,
    valve : WM::WMOutputCondition::forceLow,
    nextStep : WM::WMSteps::drainOut,
    nextStepCondition : WM::WMNextStepCondition::time,
    duration : minutesToMilliseconds(5),
  };

  conditionMapping[WM::WMSteps::drainOut] = {
    motor : WM::WMOutputCondition::tamper,
    agitate : WM::WMOutputCondition::forceLow,
    centrifuge : WM::WMOutputCondition::forceLow,
    valve : WM::WMOutputCondition::forceLow,
    nextStep : WM::WMSteps::centrifuge,
    nextStepCondition : WM::WMNextStepCondition::time,
    duration : minutesToMilliseconds(1),
  };

  conditionMapping[WM::WMSteps::centrifuge] = {
    motor : WM::WMOutputCondition::tamper,
    agitate : WM::WMOutputCondition::forceLow,
    centrifuge : WM::WMOutputCondition::forceHigh,
    valve : WM::WMOutputCondition::intermittent,
    nextStep : WM::WMSteps::fillIn2,
    nextStepCondition : WM::WMNextStepCondition::time,
    duration : minutesToMilliseconds(2),
  };
  conditionMapping[WM::WMSteps::fillIn2] = {
    motor : WM::WMOutputCondition::forceLow,
    agitate : WM::WMOutputCondition::forceLow,
    centrifuge : WM::WMOutputCondition::forceLow,
    valve : WM::WMOutputCondition::tamper,
    nextStep : WM::WMSteps::agitate3,
    nextStepCondition : WM::WMNextStepCondition::pressure,
    duration : 0,
  };

  conditionMapping[WM::WMSteps::agitate3] = {
    motor : WM::WMOutputCondition::pressureAndTamper,
    agitate : WM::WMOutputCondition::pressure,
    centrifuge : WM::WMOutputCondition::forceLow,
    valve : WM::WMOutputCondition::forceLow,
    nextStep : WM::WMSteps::drainOut2,
    nextStepCondition : WM::WMNextStepCondition::time,
    duration : minutesToMilliseconds(2),
  };

  conditionMapping[WM::WMSteps::drainOut2] = {
    motor : WM::WMOutputCondition::tamper,
    agitate : WM::WMOutputCondition::forceLow,
    centrifuge : WM::WMOutputCondition::forceLow,
    valve : WM::WMOutputCondition::forceLow,
    nextStep : WM::WMSteps::centrifuge2,
    nextStepCondition : WM::WMNextStepCondition::time,
    duration : minutesToMilliseconds(1),
  };

  conditionMapping[WM::WMSteps::centrifuge2] = {
    motor : WM::WMOutputCondition::tamper,
    agitate : WM::WMOutputCondition::forceLow,
    centrifuge : WM::WMOutputCondition::forceHigh,
    valve : WM::WMOutputCondition::forceLow,
    nextStep : WM::WMSteps::standby,
    nextStepCondition : WM::WMNextStepCondition::time,
    duration : minutesToMilliseconds(3),
  };

  return conditionMapping;
}