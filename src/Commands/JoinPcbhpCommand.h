/*
 * JoinPcbhpCommand.h
 *
 *  Created on: May 3, 2014
 *      Author: Kamran Amini <kam.cpp@gmail.com>
 */

#ifndef JOIN_PCBHP_COMMAND_H_
#define JOIN_PCBHP_COMMAND_H_

#include "PreserveChannelBeforeHandoverProtocolCommand.h"

class JoinPcbhpCommand: public PreserveChannelBeforeHandoverProtocolCommand {
  public:
    JoinPcbhpCommand(TvChannel *tvChannel = NULL) :
        PreserveChannelBeforeHandoverProtocolCommand(tvChannel) {
    }
    virtual ~JoinPcbhpCommand(void) {
    }

    inline virtual PreserveChannelBeforeHandoverProtocolCommandType getType(void) const {
      return PreserveChannelBeforeHandoverProtocolCommandType_Join;
    }
};

#endif /* JOIN_PCBHP_COMMAND_H_ */
