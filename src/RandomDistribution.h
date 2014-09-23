/*
 * RandomDistribution.h
 *
 *  Created on: Apr 20, 2014
 *      Author: Kamran Amini <kam.cpp@gmail.com>
 */

#ifndef RANDOM_DISTRIBUTION_H_
#define RANDOM_DISTRIBUTION_H_

#include "AbstractDistribution.h"

class RandomDistribution: public AbstractDistribution {
  public:
    RandomDistribution(void) :
        AbstractDistribution(), n_(0.0) {
    }
    virtual ~RandomDistribution(void) {
    }

  protected:
    virtual double calculateNextValue(void);
    virtual void resetCalculation(void) {
      n_ = 0.0;
    }

  private:
    double n_;
};

#endif /* RANDOM_DISTRIBUTION_H_ */
