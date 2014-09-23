/*
 * NetworkInfrastructure.h
 *
 *  Created on: May 1, 2014
 *      Author: Kamran Amini <kam.cpp@gmail.com>
 */

#ifndef ABSTRACT_NETWORK_INFRASTRUCTURE_H_
#define ABSTRACT_NETWORK_INFRASTRUCTURE_H_

#ifndef NULL
#define NULL 0
#endif

#include <vector>
#include <algorithm>

#include "NetworkDeviceNotFoundException.h"

class NetworkDevice;
class Message;
class DeviceAddress;

class AbstractNetworkInfrastructure {
  public:
    AbstractNetworkInfrastructure(void);
    virtual ~AbstractNetworkInfrastructure(void);

    inline virtual void registerNetworkDevice(NetworkDevice *device) {
      registeredDevices_.push_back(device);
    }

    inline virtual void unregisterNetworkDevice(NetworkDevice *device) {
      registeredDevices_.erase(std::remove(registeredDevices_.begin(), registeredDevices_.end(), device), registeredDevices_.end());
    }

    virtual NetworkDevice* lookupDevice(DeviceAddress *deviceAddress) throw (NetworkDeviceNotFoundException&);
    virtual void transferMessage(Message *message) = 0;

  private:
    std::vector<NetworkDevice*> registeredDevices_;
};

#endif /* ABSTRACT_NETWORK_INFRASTRUCTURE_H_ */
