/*
 * SimulationException.h
 *
 *  Created on: May 4, 2014
 *      Author: Kamran Amini <kam.cpp@gmail.com>
 */

#ifndef SIMULATION_EXCEPTION_H_
#define SIMULATION_EXCEPTION_H_

#ifndef NULL
#define NULL 0
#endif

#include <string>
#include <exception>

#include "enums.h"

class SimulationException: public std::exception {
  public:
    SimulationException(SimulationExceptionType type = SimulationExceptionType_None, std::string message = "", std::exception *innerException = NULL) :
        type_(type), message_(message), innerException_(innerException) {
    }
    virtual ~SimulationException(void) throw () {
    }

    virtual const char* what(void) throw () {
      return message_.c_str();
    }

    virtual std::exception* getInnerException(void) const {
      return innerException_;
    }

  private:
    SimulationExceptionType type_;
    std::string message_;
    std::exception *innerException_;
};

#endif /* SIMULATION_EXCEPTION_H_ */
