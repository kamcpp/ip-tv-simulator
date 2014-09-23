/*
 * Vector.h
 *
 *  Created on: Apr 22, 2014
 *      Author: Kamran Amini <kam.cpp@gmail.com>
 */

#ifndef VECTOR_H_
#define VECTOR_H_

#include <sstream>
#include <string>

#include "ClonnableInterface.h"
#include "JsonableInterface.h"

class Vector: public ClonnableInterface, public JsonableInterface {
  public:
    Vector(double x = 0.0, double y = 0.0, double z = 0.0) :
        x_(x), y_(y), z_(z) {
    }
    virtual ~Vector(void) {
    }

    inline double getX(void) const {
      return x_;
    }
    inline void setX(double x) {
      x_ = x;
    }

    inline double getY(void) const {
      return y_;
    }
    inline void setY(double y) {
      y_ = y;
    }

    inline double getZ(void) const {
      return z_;
    }
    inline void setZ(double z) {
      z_ = z;
    }

    Vector* multiply(double c) {
      Vector *rv = newInstance();
      rv->setX(c * getX());
      rv->setY(c * getY());
      rv->setZ(c * getZ());
      return rv;
    }

    Vector* add(Vector *v) {
      Vector *rv = newInstance();
      rv->setX(v->getX() + getX());
      rv->setY(v->getY() + getY());
      rv->setZ(v->getZ() + getZ());
      return rv;
    }

    Vector* subtract(Vector *v) {
      Vector *rv = newInstance();
      rv->setX(v->getX() - getX());
      rv->setY(v->getY() - getY());
      rv->setZ(v->getZ() - getZ());
      return rv;
    }

    inline virtual void* clone(void) {
      Vector *v = new Vector(x_, y_, z_);
      return v;
    }

    inline virtual std::string toString(void) const {
      std::stringstream ss;
      ss << "Vector(" << getX() << ", " << getY() << ", " << getZ() << ")";
      return ss.str();
    }

    inline virtual std::string getJson(void) const {
      std::stringstream ss;
      ss << "{";
      ss << "\"type\": \"Vector\", \"x\": \"" << getX() << "\", \"y\": \"" << getY() << "\", \"z\": \"" << getZ() << "\"";
      ss << "}";
      return ss.str();
    }

  protected:
    virtual Vector* newInstance(void) {
      return new Vector();
    }

  private:
    double x_;
    double y_;
    double z_;
};

#endif /* VECTOR_H_ */
