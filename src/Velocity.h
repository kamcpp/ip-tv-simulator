/*
 * Velocity.h
 *
 *  Created on: Apr 22, 2014
 *      Author: Kamran Amini <kam.cpp@gmail.com>
 */

#ifndef VELOCITY_H_
#define VELOCITY_H_

#include "Vector.h"

class Velocity: public Vector {
  public:
    Velocity(double x = 0.0, double y = 0.0, double z = 0.0) :
        Vector(x, y, z) {
    }
    virtual ~Velocity(void) {
    }

    inline virtual void* clone(void) {
      Velocity *v = new Velocity(getX(), getY(), getZ());
      return v;
    }

    inline virtual std::string getJson(void) const {
      std::stringstream ss;
      ss << "{";
      ss << "\"type\": \"Velocity\", \"x\": \"" << getX() << "\", \"y\": \"" << getY() << "\", \"z\": \"" << getZ() << "\"";
      ss << "}";
      return ss.str();
    }

  protected:
    virtual Vector* newInstance(void) {
      return new Velocity();
    }
};

#endif /* VELOCITY_H_ */
