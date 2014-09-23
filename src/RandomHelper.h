/*
 * RandomHelper.h
 *
 *  Created on: Apr 21, 2014
 *      Author: Kamran Amini <kam.cpp@gmail.com>
 */

#ifndef RANDOM_HELPER_H_
#define RANDOM_HELPER_H_

#include <iostream>
#include <cstdlib>

#include "utils.h"

class RandomHelper {
  public:
    static inline double next(void) {
      return (double) (std::rand()) / RAND_MAX;
    }
    static inline double next(double number) {
      return number * next();
    }
    static inline double next(double min, double max) {
      return (max - min) * next() + min;
    }
    static inline void setRandomSeed(int seedValue) {
      srand(seedValue);
    }
    static inline void setTimeSeed(void) {
      srand(time(0));
    }
};

#endif /* RANDOM_HELPER_H_ */
