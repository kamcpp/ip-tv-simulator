/*
 * JoinAcceptedPcbhpCommand.h
 *
 *  Created on: May 5, 2014
 *      Author: Kamran Amini <kam.cpp@gmail.com>
 */

#ifndef JOIN_ACCEPTED_PCBHP_COMMAND_H_
#define JOIN_ACCEPTED_PCBHP_COMMAND_H_

#include "PreserveChannelBeforeHandoverProtocolCommand.h"

class JoinAcceptedPcbhpCommand: public PreserveChannelBeforeHandoverProtocolCommand {
  public:
    JoinAcceptedPcbhpCommand(TvChannel *channel = NULL) :
        PreserveChannelBeforeHandoverProtocolCommand(channel) {
    }
    virtual ~JoinAcceptedPcbhpCommand(void) {
    }

    inline virtual PreserveChannelBeforeHandoverProtocolCommandType getType(void) const {
      return PreserveChannelBeforeHandoverProtocolCommandType_JoinAccepted;
    }
};

#endif /* JOIN_ACCEPTED_PCBHP_COMMAND_H_ */
