#ifndef WMSTEPCONDITION_HPP
#define WMSTEPCONDITION_HPP

#include <cstdint>
#include "./WMOutputs.hpp"

#define minutesToMilliseconds(minutes) (((WM::WMTime)minutes) * 60 * 1000)

namespace WM
{
  enum class WMNextStepCondition
  {
    startButton,
    pressure,
    time,
  };

  typedef std::uint32_t WMTime;

  class WMStepAction
  {
  public:
    WMOutputCondition motor;
    WMOutputCondition agitate;
    WMOutputCondition centrifuge;
    WMOutputCondition valve;
    WMSteps nextStep;
    WMNextStepCondition nextStepCondition;
    WMTime duration; // milliseconds
  };
}

#endif // WMSTEPCONDITION_HPP