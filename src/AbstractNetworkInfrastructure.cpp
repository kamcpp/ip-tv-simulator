/*
 * AbstractNetworkInfrastructure.cpp
 *
 *  Created on: May 1, 2014
 *      Author: Kamran Amini <kam.cpp@gmail.com>
 */

#include "AbstractNetworkInfrastructure.h"
#include "NetworkDevice.h"
#include "DeviceAddress.h"

AbstractNetworkInfrastructure::AbstractNetworkInfrastructure(void) {
}

AbstractNetworkInfrastructure::~AbstractNetworkInfrastructure(void) {
}

NetworkDevice* AbstractNetworkInfrastructure::lookupDevice(DeviceAddress *deviceAddress) throw (NetworkDeviceNotFoundException&) {
  for (unsigned int i = 0; i < registeredDevices_.size(); i++) {
    NetworkDevice *device = registeredDevices_[i];
    if (device->getAddress()->equals(deviceAddress)) {
      return device;
    }
  }
  throw NetworkDeviceNotFoundException();
}

