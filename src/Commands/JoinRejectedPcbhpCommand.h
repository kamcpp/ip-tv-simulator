/*
 * JoinRejectedPcbhpCommand.h
 *
 *  Created on: May 5, 2014
 *      Author: Kamran Amini <kam.cpp@gmail.com>
 */

#ifndef JOIN_REJECTED_PCBHP_COMMAND_H_
#define JOIN_REJECTED_PCBHP_COMMAND_H_

#include "PreserveChannelBeforeHandoverProtocolCommand.h"

class TvChannel;

class JoinRejectedPcbhpCommand: public PreserveChannelBeforeHandoverProtocolCommand {
  public:
    JoinRejectedPcbhpCommand(TvChannel *channel = NULL) :
        PreserveChannelBeforeHandoverProtocolCommand(channel) {
    }
    virtual ~JoinRejectedPcbhpCommand(void) {
    }

    inline virtual PreserveChannelBeforeHandoverProtocolCommandType getType(void) const {
      return PreserveChannelBeforeHandoverProtocolCommandType_JoinRejected;
    }
};

#endif /* JOIN_REJECTED_PCBHP_COMMAND_H_ */
