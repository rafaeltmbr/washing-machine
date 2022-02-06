#ifndef WMSTEPS_HPP
#define WMSTEPS_HPP

namespace WM
{
  enum class WMSteps
  {
    standby = 0, // wait until start
    fillIn,      // fill water in
    agitate,     // agitate the cloth
    soak,        // soak for a while
    agitate2,    // agitate the cloth again
    drainOut,    // drain the water out
    centrifuge,  // dry the cloth
    fillIn2,     // fill water in again
    agitate3,    // agitate on more time
    drainOut2,   // drain the water out
    centrifuge2, // dry the cloth and we're done
  };
}

#endif // WMSTEPS_HPP