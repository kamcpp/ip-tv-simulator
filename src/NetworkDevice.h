/*
 * NetworkDevice.h
 *
 *  Created on: May 1, 2014
 *      Author: Kamran Amini <kam.cpp@gmail.com>
 */

#ifndef NETWORK_DEVICE_H_
#define NETWORK_DEVICE_H_

#ifndef NULL
#define NULL 0
#endif

#include <queue>
#include <iostream>

class Message;
class DeviceAddress;
class MessageProcessorInterface;

class NetworkDevice {
  public:
    NetworkDevice(unsigned int id);
    NetworkDevice(DeviceAddress *deviceAddress);
    virtual ~NetworkDevice(void);

    inline DeviceAddress* getAddress(void) const {
      return address_;
    }
    inline void setAddress(DeviceAddress *address) {
      address_ = address;
    }

    inline virtual void acceptMessage(Message *message) {
      inputBuffer_.push(message);
    }
    inline virtual Message* takeIncomingMessage(void) {
      if (inputBuffer_.empty()) {
        return NULL;
      }
      Message *message = inputBuffer_.front();
      inputBuffer_.pop();
      return message;
    }
    inline virtual bool hasMoreIncomingMessages(void) {
      return !inputBuffer_.empty();
    }

    virtual void purgeMessage(Message *message);
    virtual void sendMessage(Message *message);

  private:
    DeviceAddress *address_;
    std::queue<Message*> inputBuffer_;
    std::queue<Message*> outputBuffer_;
};

#endif /* NETWORK_DEVICE_H_ */
