#ifndef WM_INPUTS_HPP
#define WM_INPUTS_HPP

namespace WM
{
  typedef int AnalogInput;

  class WMInputs
  {
  public:
    bool start;
    bool tamper;
    bool pressure;
    bool skip;
    AnalogInput agitate2Time;
    AnalogInput centrifugeTime;
    AnalogInput agitate3Time;
    AnalogInput centrifuge2Time;
  };
}

#endif // WM_INPUTS_HPP