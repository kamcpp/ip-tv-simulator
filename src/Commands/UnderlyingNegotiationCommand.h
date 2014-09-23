/*
 * NegotiationCommand.h
 *
 *  Created on: Aug 4, 2014
 *      Author: Kamran Amini <kam.cpp@gmail.com>
 */

#ifndef UNDERLYING_NEGOTIATION_COMMAND_H_
#define UNDERLYING_NEGOTIATION_COMMAND_H_

#include "../Command.h"

class DeviceAddress;

class UnderlyingNegotiationCommand: public Command {
  public:
    UnderlyingNegotiationCommand(DeviceAddress *deviceAddress) {
      this->deviceAddress_ = deviceAddress;
    }
    virtual ~UnderlyingNegotiationCommand(void) {
    }

    inline DeviceAddress* getDeviceAddress(void) const {
      return deviceAddress_;
    }

    virtual UnderlyingNegotationCommandType getType() const = 0;

  private:
    DeviceAddress *deviceAddress_;
};

#endif /* UNDERLYGIN_NEGOTIATION_COMMAND_H_ */
