/*
 * LeaveAcceptedPcbhpCommand.h
 *
 *  Created on: May 5, 2014
 *      Author: Kamran Amini <kam.cpp@gmail.com>
 */

#ifndef LEAVE_ACCEPTED_PCBHP_COMMAND_H_
#define LEAVE_ACCEPTED_PCBHP_COMMAND_H_

#include "PreserveChannelBeforeHandoverProtocolCommand.h"

class TvChannel;

class LeaveAcceptedPcbhpCommand: public PreserveChannelBeforeHandoverProtocolCommand {
  public:
    LeaveAcceptedPcbhpCommand(TvChannel *channel = NULL) :
        PreserveChannelBeforeHandoverProtocolCommand(channel) {
    }
    virtual ~LeaveAcceptedPcbhpCommand(void) {
    }

    inline virtual PreserveChannelBeforeHandoverProtocolCommandType getType(void) const {
      return PreserveChannelBeforeHandoverProtocolCommandType_LeaveAccepted;
    }
};

#endif /* LEAVE_ACCEPTED_PCBHP_COMMAND_H_ */
