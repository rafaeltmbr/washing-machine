#ifndef WMINPUTS_HPP
#define WMINPUTS_HPP

namespace WM
{
  typedef short unsigned AnalogInput;

  class WMInputs
  {
  public:
    bool start;
    bool tamper;
    bool pressure;
    AnalogInput agitate2Time;
    AnalogInput centrifugeTime;
    AnalogInput agitate3Time;
    AnalogInput centrifuge2Time;
  };
}

#endif // WMINPUTS_HPP