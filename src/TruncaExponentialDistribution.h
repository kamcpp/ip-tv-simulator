/*
 * TruncaExponentialDistribution.h
 *
 *  Created on: May 6, 2014
 *      Author: Kamran Amini <kam.cpp@gmail.com>
 */

#ifndef TRUNCA_EXPONENTIAL_DISTRIBUTION_H_
#define TRUNCA_EXPONENTIAL_DISTRIBUTION_H_

#include "AbstractDistribution.h"

class TruncaExponentialDistribution: public AbstractDistribution {
  public:
    TruncaExponentialDistribution(double speed, double minimumDistance, double maximumDistance, double averageDistance) :
        AbstractDistribution(), speed_(speed), minimumDistance_(minimumDistance), maximumDistacne_(maximumDistance), averageDistance_(averageDistance) {
    }
    virtual ~TruncaExponentialDistribution(void) {
    }

    inline double getSpeed(void) const {
      return speed_;
    }
    inline void setSpeed(double speed) {
      speed_ = speed;
    }

    inline double getMinimumDistance(void) const {
      return minimumDistance_;
    }
    inline void setMinimumDistance(double minimumDistance) {
      minimumDistance_ = minimumDistance;
    }

    inline double getMaximumDistance(void) const {
      return maximumDistacne_;
    }
    inline void setMaximumDistance(double maximumDistance) {
      maximumDistacne_ = maximumDistance;
    }

    inline double getAverageDistance(void) const {
      return averageDistance_;
    }
    inline void setAverageDistance(double averageDistance) {
      averageDistance_ = averageDistance;
    }

  protected:
    virtual double calculateNextValue(void);
    virtual void resetCalculation(void);

  private:
    double speed_;
    double minimumDistance_;
    double maximumDistacne_;
    double averageDistance_;
};

#endif /* TRUNCA_EXPONENTIAL_DISTRIBUTION_H_ */
