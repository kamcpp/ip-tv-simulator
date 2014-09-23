/*
 * DeviceAddress.h
 *
 *  Created on: May 1, 2014
 *      Author: Kamran Amini <kam.cpp@gmail.com>
 */

#ifndef DEVICE_ADDRESS_H_
#define DEVICE_ADDRESS_H_

#include "enums.h"
#include "ClonnableInterface.h"

class DeviceAddress: public ClonnableInterface {
  public:
    DeviceAddress(unsigned int id = 0) :
        id_(id) {
    }
    virtual ~DeviceAddress(void) {
    }

    inline unsigned int getId(void) const {
      return id_;
    }
    inline void setId(unsigned int id) {
      id_ = id;
    }

    inline virtual void* clone(void) {
      DeviceAddress *newDeviceAddress = new DeviceAddress();
      newDeviceAddress->setId(id_);
      return newDeviceAddress;
    }

    inline virtual bool equals(DeviceAddress *deviceAddress) {
      return id_ == deviceAddress->getId();
    }

  private:
    unsigned int id_;
};

#endif /* DEVICE_ADDRESS_H_ */
