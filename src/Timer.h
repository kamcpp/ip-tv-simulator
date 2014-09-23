/*
 * Timer.h
 *
 *  Created on: Apr 12, 2014
 *      Author: Kamran Amini <kam.cpp@gmail.com>
 */

#ifndef TIMER_H_
#define TIMER_H_

#include "enums.h"

class Timer {
  public:
    Timer(double start = 0.0, double end = -1.0, double step = 0.000001, TimeUnit timeUnit = TimeStepUnit_Millisecond) :
        current_(start), start_(start), end_(end), step_(step), timeUnit_(timeUnit) {
    }
    virtual ~Timer(void) {
    }

    inline double getStart(void) const {
      return start_;
    }
    inline void setStart(double start) {
      start = start_;
    }

    inline double getEnd(void) const {
      return end_;
    }
    inline void setEnd(double end) {
      end_ = end;
    }

    inline double getStep(void) const {
      return step_;
    }
    inline void setStep(double step) {
      step_ = step;
    }

    inline TimeUnit getTimeUnit(void) const {
      return timeUnit_;
    }
    inline void setTimeUnit(TimeUnit timeUnit) {
      timeUnit_ = timeUnit;
    }

    inline double getCurrent(void) const {
      return current_;
    }

    inline void reset(void) {
      current_ = start_;
    }

    inline bool advance(void) {
      if (!hasMoreSteps()) {
        current_ = end_;
        return false;
      }
      current_ += step_;
      return true;
    }

    inline bool hasMoreSteps(void) const {
      if (end_ < 0) {
        return true;
      }
      return current_ <= end_;
    }

  private:
    double current_;
    double start_;
    double end_;
    double step_;
    TimeUnit timeUnit_;
};

#endif /* TIMER_H_ */
