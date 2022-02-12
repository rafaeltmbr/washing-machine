#ifndef WM_CONTROLLER_HPP
#define WM_CONTROLLER_HPP

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

  class WMControllerStats
  {
  public:
    WMSteps currentStep;
    WMTime currentStepTime;
  };

  class WMController
  {
  private:
    WMSteps currentStep;
    WMTime stepTime;
    WMTime intermittentTime;
    WMTime lastStepTime;
    bool lastSkipState;
    std::map<WM::WMSteps, WM::WMStepAction> stepConditionMapping;

    void updateCurrentStepTime(const WMInputs &);
    void updateNextStep(WMStepAction &, const WMInputs &);
    bool computeOutput(const WMOutputCondition &, const WMInputs &) const;
    WMOutputs computeOutputs(WMStepAction &, const WMInputs &) const;
    bool shouldGotoNextStep(WMStepAction &, const WMInputs &);

  public:
    WMController();
    WMController(const WMControllerConfig &);
    WMOutputs exec(const WMInputs &);
    WMControllerStats stats(void) const;
  };
}

#endif // WM_CONTROLLER_HPP