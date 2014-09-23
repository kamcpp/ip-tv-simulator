/*
 * DeviceNotFoundException.h
 *
 *  Created on: May 4, 2014
 *      Author: Kamran Amini <kam.cpp@gmail.com>
 */

#ifndef NETWORK_DEVICE_NOT_FOUND_EXCEPTION_H_
#define NETWORK_DEVICE_NOT_FOUND_EXCEPTION_H_

#include "SimulationException.h"

class NetworkDeviceNotFoundException: public SimulationException {
  public:
    NetworkDeviceNotFoundException(void) :
        SimulationException(SimulationExceptionType_NetworkDeviceNotFound, "Network device not found.") {
    }
    virtual ~NetworkDeviceNotFoundException(void) throw () {
    }
};

#endif /* NETWORK_DEVICE_NOT_FOUND_EXCEPTION_H_ */
