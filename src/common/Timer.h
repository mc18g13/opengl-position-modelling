#ifndef TIMER_H
#define TIMER_H

#include <iostream>
#include <chrono>

class Timer {
private:
  typedef std::chrono::high_resolution_clock clock_;
  typedef std::chrono::duration<double, std::ratio<1> > second_;
  std::chrono::time_point<clock_> m_beg;

public:
  Timer();
  void reset();
  double elapsed() const;
};

#endif