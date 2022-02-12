#include "WMSteps.hpp"

const char *convertWMStepToString(WM::WMSteps step)
{
  switch (step)
  {
  case WM::WMSteps::standby:
    return "standby";
  case WM::WMSteps::fillIn:
    return "fill in";
  case WM::WMSteps::agitate:
    return "agitate";
  case WM::WMSteps::soak:
    return "soak";
  case WM::WMSteps::agitate2:
    return "agitate 2";
  case WM::WMSteps::drainOut:
    return "drain out";
  case WM::WMSteps::centrifuge:
    return "centrifuge";
  case WM::WMSteps::fillIn2:
    return "fill in 2";
  case WM::WMSteps::agitate3:
    return "agitate 3";
  case WM::WMSteps::drainOut2:
    return "drain out 2";
  case WM::WMSteps::centrifuge2:
    return "centrifuge 2";
  default:
    return "--";
  }
}