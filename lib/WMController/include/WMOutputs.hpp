#ifndef WM_OUTPUTS_HPP
#define WM_OUTPUTS_HPP

#include "./WMSteps.hpp"

namespace WM
{

  class WMOutputs
  {
  public:
    bool motor;
    bool agitate;
    bool centrifuge;
    bool valve;
  };

  enum class WMOutputCondition
  {
    forceLow,
    forceHigh,
    pressure,
    tamper,
    pressureAndTamper,
    intermittent,
  };

}

#endif // WM_OUTPUTS_HPP
