/*
 * Message.h
 *
 *  Created on: May 1, 2014
 *      Author: Kamran Amini <kam.cpp@gmail.com>
 */

#ifndef MESSAGE_H_
#define MESSAGE_H_

#ifndef NULL
#define NULL 0
#endif

#include <string>

class DeviceAddress;
class Command;

class Message {
  public:
    Message(DeviceAddress *sourceAddress, DeviceAddress *destinationAddress, Command *command, double currentTime);
    virtual ~Message(void);

    inline unsigned int getId(void) const {
      return id_;
    }
    inline void setId(int id) {
      id_ = id;
    }

    inline double getGenerationTime(void) const {
      return generationTime_;
    }

    inline DeviceAddress* getSourceAddress(void) const {
      return sourceAddress_;
    }

    inline DeviceAddress* getDestinationAddress(void) const {
      return destinationAddress_;
    }

    inline Command* getCommand(void) const {
      return command_;
    }
    inline void setCommand(Command *command) {
      command_ = command;
    }

  private:
    unsigned int id_;
    double generationTime_;
    DeviceAddress *sourceAddress_;
    DeviceAddress *destinationAddress_;
    Command *command_;
};

#endif /* MESSAGE_H_ */
