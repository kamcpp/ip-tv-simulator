/*
 * Packet.cpp
 *
 *  Created on: May 1, 2014
 *      Author: Kamran Amini <kam.cpp@gmail.com>
 */

#include "Message.h"
#include "RandomHelper.h"
#include "DeviceAddress.h"
#include "Command.h"

Message::Message(DeviceAddress *sourceAddress, DeviceAddress *destinationAddress, Command *command, double currentTime) :
    id_(0), generationTime_(0), sourceAddress_(NULL), destinationAddress_(NULL), command_(command) {
  id_ = (unsigned int) RandomHelper::next(50000);
  generationTime_ = currentTime;
  sourceAddress_ = static_cast<DeviceAddress*>(sourceAddress->clone());
  destinationAddress_ = static_cast<DeviceAddress*>(destinationAddress->clone());
  command_->numberOfUsages_++;
}

Message::~Message(void) {
  command_->numberOfUsages_--;
  if (command_->numberOfUsages_ == 0) {
    delete command_;
  }
  delete sourceAddress_;
  delete destinationAddress_;
}

