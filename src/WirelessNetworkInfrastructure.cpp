/*
 * WirelessNetworkInfrastructure.cpp
 *
 *  Created on: May 1, 2014
 *      Author: Kamran Amini <kam.cpp@gmail.com>
 */

#include "WirelessNetworkInfrastructure.h"
#include "Message.h"
#include "NetworkDevice.h"

WirelessNetworkInfrastructure::WirelessNetworkInfrastructure(void) {
}

WirelessNetworkInfrastructure::~WirelessNetworkInfrastructure(void) {
}

void WirelessNetworkInfrastructure::transferMessage(Message *message) {
  NetworkDevice *device = lookupDevice(message->getDestinationAddress());
  if (device != NULL) {
    device->addMessage(message);
  }
}

