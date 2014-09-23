/*
 * AbstractDistribution.h
 *
 *  Created on: Apr 20, 2014
 *      Author: Kamran Amini <kam.cpp@gmail.com>
 */

#ifndef ABSTRACT_DISTRIBUTION_H_
#define ABSTRACT_DISTRIBUTION_H_

/*
 * A base class for all statistical distibutions. Each distribution is a set
 * of real numbers like a series, represented by double type, each one assigned 
 * an index starting from zero.
 */
class AbstractDistribution {
  public:
    AbstractDistribution(void) :
        currentIndex_(-1), currentValue_(0.0) {
    }
    virtual ~AbstractDistribution(void) {
    }

    inline int getCurrentIndex(void) const {
      return currentIndex_;
    }

    inline double getCurrentValue(void) const {
      return currentValue_;
    }

    /*
     * Calculates next value in the distribution. It advances the current
     * index and updates current value of the distribution.
     */
    virtual double next(void) {
      currentValue_ = calculateNextValue();
      currentIndex_++;
      return currentValue_;
    }

    /*
     * If the distribution is ascending, this method accepts a target
     * and calculates the next value if the target is greater than current
     * value. Target is usually an external concept like time, which is 
     * growing and we want to generate new values in the distribution
     * when it passes our current value.
     */
    virtual bool nextIf(double target) {
      if (currentIndex_ < 0) {
        next();
        return nextIf(target);
      }
      /* Check if target has passed the current value. */
      if (target >= currentValue_) {

        next();
        return true;
      }
      return false;
    }

    virtual void reset(void) {
      resetCalculation();
      currentIndex_ = 0;
      currentValue_ = 0.0;
    }

  protected:
    /* Calculates the next value. This method should be overwritten by the
     * implementation.
     */
    virtual double calculateNextValue(void) = 0;
    virtual void resetCalculation(void) = 0;

  private:
    int currentIndex_;
    double currentValue_;

};

#endif /* ABSTRACT_DISTRIBUTION_H_ */
