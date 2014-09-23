/*
 * NotSupportedCommandException.h
 *
 *  Created on: May 5, 2014
 *      Author: Kamran Amini <kam.cpp@gmail.com>
 */

#ifndef NOT_SUPPORTED_COMMAND_EXCEPTION_H_
#define NOT_SUPPORTED_COMMAND_EXCEPTION_H_

#include "SimulationException.h"

class NotSupportedCommandException: public SimulationException {
  public:
    NotSupportedCommandException() :
        SimulationException(SimulationExceptionType_NoCoveringAccessPoint, "Not supported command.") {
    }
    virtual ~NotSupportedCommandException(void) throw () {
    }
};

#endif /* NOT_SUPPORTED_COMMAND_EXCEPTION_H_ */
