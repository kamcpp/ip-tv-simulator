/*
 * TruncaExponentialDistribution.cpp
 *
 *  Created on: May 6, 2014
 *      Author: Kamran Amini <kam.cpp@gmail.com>
 */

#include <math.h>
#include <iostream>

#include "TruncaExponentialDistribution.h"
#include "RandomHelper.h"
#include "Environment.h"
#include "Simulator.h"
#include "Timer.h"

double TruncaExponentialDistribution::calculateNextValue(void) {
  bool cont = true;
  double distance = 10.0;
  while (cont) {
    double rnd = RandomHelper::next();
    distance = -log(1 - rnd) * averageDistance_;
    if (distance >= minimumDistance_ && distance <= maximumDistacne_) {
      cont = false;
    }
  }
  return Environment::getInstance()->getSimulator()->getTimer()->getCurrent() + (distance / speed_);
}

void TruncaExponentialDistribution::resetCalculation(void) {
}

