/*
 * NoCoveringAccessPointException.h
 *
 *  Created on: May 4, 2014
 *      Author: Kamran Amini <kam.cpp@gmail.com>
 */

#ifndef NO_COVERING_ACCESS_POINT_EXCEPTION_H_
#define NO_COVERING_ACCESS_POINT_EXCEPTION_H_

#include "SimulationException.h"

class NoCoveringAccessPointException: public SimulationException {
  public:
    NoCoveringAccessPointException(void) :
        SimulationException(SimulationExceptionType_NoCoveringAccessPoint, "No covering access point.") {
    }
    virtual ~NoCoveringAccessPointException(void) throw () {
    }
};

#endif /* NO_COVERING_ACCESS_POINT_EXCEPTION_H_ */
