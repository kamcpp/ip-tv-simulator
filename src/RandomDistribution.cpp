/*
 * RandomDistribution.cpp
 *
 *  Created on: Apr 21, 2014
 *      Author: Kamran Amini <kam.cpp@gmail.com>
 */

#include "RandomDistribution.h"
#include "RandomHelper.h"

double RandomDistribution::calculateNextValue(void) {
  int max = static_cast<int>(RandomHelper::next(7));
  double a = RandomHelper::next(1, max);
  double b = RandomHelper::next();
  n_ += (a + b);
  return n_;
}
