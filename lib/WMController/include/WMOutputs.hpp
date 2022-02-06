#ifndef WMOUTPUTS_HPP
#define WMOUTPUTS_HPP

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

#endif // WMOUTPUTS_HPP
