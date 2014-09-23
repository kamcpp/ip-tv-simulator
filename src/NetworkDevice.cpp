/*
 * NetworkDevice.cpp
 *
 *  Created on: May 1, 2014
 *      Author: Kamran Amini <kam.cpp@gmail.com>
 */

#include "NetworkDevice.h"
#include "DeviceAddress.h"
#include "Message.h"

NetworkDevice::NetworkDevice(unsigned int id) {
  address_ = new DeviceAddress(id);
}

NetworkDevice::NetworkDevice(DeviceAddress *deviceAddress) {
  address_ = (DeviceAddress*) deviceAddress->clone();
}

NetworkDevice::~NetworkDevice(void) {
  delete address_;
}

void NetworkDevice::purgeMessage(Message *message) {
  delete message;
}

void NetworkDevice::sendMessage(Message *message) {

}
