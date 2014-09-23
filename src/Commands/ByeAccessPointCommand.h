/*
 * ByeAccessPointCommand.h
 *
 *  Created on: Aug 4, 2014
 *      Author: Kamran Amini <kam.cpp@gmail.com>
 */

#ifndef BYE_ACCESS_POINT_COMMAND_H_
#define BYE_ACCESS_POINT_COMMAND_H_

#include "../enums.h"
#include "UnderlyingNegotiationCommand.h"

class DeviceAddress;

class ByeAccessPointCommand: public UnderlyingNegotiationCommand {
  public:
    ByeAccessPointCommand(DeviceAddress *deviceAddress)
        : UnderlyingNegotiationCommand(deviceAddress) {
    }
    virtual ~ByeAccessPointCommand(void) {
    }

    inline virtual UnderlyingNegotationCommandType getType(void) const {
      return UnderlyingNegotationCommandType_Bye;
    }
};

#endif /* BYE_ACCESS_POINT_COMMAND_H_ */
