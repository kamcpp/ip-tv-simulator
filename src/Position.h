/*
 * Position.h
 *
 *  Created on: Apr 11, 2014
 *      Author: Kamran Amini <kam.cpp@gmail.com>
 */

#ifndef POSITION_H_
#define POSITION_H_

#include "Vector.h"

class Position: public Vector {
  public:
    Position(double x = 0.0, double y = 0.0, double z = 0.0) :
        Vector(x, y, z) {
    }
    ~Position(void) {
    }

    inline virtual void* clone(void) {
      Position *p = new Position(getX(), getY(), getZ());
      return p;
    }

    inline void assignFrom(Position *position) {
      setX(position->getX());
      setY(position->getY());
      setZ(position->getZ());
    }

    inline bool isInNeighborhood(Position *p, double radius) {
      return (getX() - p->getX()) * (getX() - p->getX()) + (getY() - p->getY()) * (getY() - p->getY()) <= radius * radius;
    }

    inline virtual std::string getJson(void) const {
      std::stringstream ss;
      ss << "{";
      ss << "\"type\": \"Position\", \"x\": \"" << getX() << "\", \"y\": \"" << getY() << "\", \"z\": \"" << getZ() << "\"";
      ss << "}";
      return ss.str();
    }

  protected:
    virtual Vector* newInstance(void) {
      return new Position();
    }
};

#endif /* POSITION_H_ */
