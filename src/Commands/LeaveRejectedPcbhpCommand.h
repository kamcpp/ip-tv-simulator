/*
 * LeaveRejectedPcbhpCommand.h
 *
 *  Created on: May 5, 2014
 *      Author: Kamran Amini <kam.cpp@gmail.com>
 */

#ifndef LEAVE_REJECTED_PCBHP_COMMAND_H_
#define LEAVE_REJECTED_PCBHP_COMMAND_H_

#include "PreserveChannelBeforeHandoverProtocolCommand.h"

class TvChannel;

class LeaveRejectedPcbhpCommand: public PreserveChannelBeforeHandoverProtocolCommand {
  public:
    LeaveRejectedPcbhpCommand(TvChannel *channel = NULL) :
        PreserveChannelBeforeHandoverProtocolCommand(channel) {
    }
    virtual ~LeaveRejectedPcbhpCommand(void) {
    }

    inline virtual PreserveChannelBeforeHandoverProtocolCommandType getType(void) const {
      return PreserveChannelBeforeHandoverProtocolCommandType_LeaveRejected;
    }
};

#endif /* LEAVE_REJECTED_PCBHP_COMMAND_H_ */
