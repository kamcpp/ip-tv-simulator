/*
 * HelloAccessPointCommand.h
 *
 *  Created on: Aug 4, 2014
 *      Author: Kamran Amini <kam.cpp@gmail.com>
 */

#ifndef HELLO_ACCESS_POINT_COMMAND_H_
#define HELLO_ACCESS_POINT_COMMAND_H_

#include "../enums.h"
#include "UnderlyingNegotiationCommand.h"

class DeviceAddress;

class HelloAccessPointCommand: public UnderlyingNegotiationCommand {
  public:
    HelloAccessPointCommand(DeviceAddress *deviceAddress)
        : UnderlyingNegotiationCommand(deviceAddress) {
    }
    virtual ~HelloAccessPointCommand(void) {
    }

    inline virtual UnderlyingNegotationCommandType getType(void) const {
      return UnderlyingNegotationCommandType_Hello;
    }
};

#endif /* HELLO_ACCESS_POINT_COMMAND_H_ */
