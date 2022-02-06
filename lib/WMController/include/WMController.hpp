#ifndef WMCONTROLLER_HPP
#define WMCONTROLLER_HPP

#include <Arduino.h>
#include <map>
#include "./WMInputs.hpp"
#include "./WMOutputs.hpp"
#include "./WMStepCondition.hpp"

#ifndef WM_DEFAULT_INTERMITTENT_TIME
#define WM_DEFAULT_INTERMITTENT_TIME 30
#endif

namespace WM
{
  class WMControllerConfig
  {
  public:
    WMTime intermittentTime = WM_DEFAULT_INTERMITTENT_TIME;
  };

  class WMController
  {
  private:
    WMSteps currentStep;
    WMTime stepTime;
    WMTime intermittentTime;
    WMTime lastStepTime;
    std::map<WM::WMSteps, WM::WMStepAction> stepConditionMapping;

    void updateCurrentStepTime(WMInputs);
    void updateNextStep(WMStepAction, WMInputs);
    bool computeOutput(WMOutputCondition, WMInputs, WMTime);
    WMOutputs computeOutputs(WMStepAction, WMInputs);
    bool gotoNextStep(WMStepAction, WMInputs);

  public:
    WMController();
    WMController(WMControllerConfig &);
    WMOutputs exec(WMInputs);
  };
}

#endif // WMCONTROLLER_HPP