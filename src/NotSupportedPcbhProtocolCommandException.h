/*
 * NotSupportedPcbhProtocolCommand.h
 *
 *  Created on: May 5, 2014
 *      Author: Kamran Amini <kam.cpp@gmail.com>
 */

#ifndef NOT_SUPPORTED_PCBH_PROTOCOL_COMMAND_EXCEPTION_H_
#define NOT_SUPPORTED_PCBH_PROTOCOL_COMMAND_EXCEPTION_H_

#include "SimulationException.h"

class NotSupportedPcbhProtocolCommandException: public SimulationException {
  public:
    NotSupportedPcbhProtocolCommandException(void) :
        SimulationException(SimulationExceptionType_NotSupportedPcbhProtocolCommand, "Not supported PCBH protocol command.") {
    }
    virtual ~NotSupportedPcbhProtocolCommandException(void) throw () {
    }
};

#endif /* NOT_SUPPORTED_PCBH_PROTOCOL_COMMAND_EXCEPTION_H_ */
