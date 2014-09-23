/*
 * LeavePcbhpCommand.h
 *
 *  Created on: May 3, 2014
 *      Author: Kamran Amini <kam.cpp@gmail.com>
 */

#ifndef LEAVE_PCBHPC_OMMAND_H_
#define LEAVE_PCBHP_COMMAND_H_

#include "PreserveChannelBeforeHandoverProtocolCommand.h"

class LeavePcbhpCommand: public PreserveChannelBeforeHandoverProtocolCommand {
  public:
    LeavePcbhpCommand(TvChannel *tvChannel = NULL) :
        PreserveChannelBeforeHandoverProtocolCommand(tvChannel) {
    }
    virtual ~LeavePcbhpCommand(void) {
    }

    inline virtual PreserveChannelBeforeHandoverProtocolCommandType getType(void) const {
      return PreserveChannelBeforeHandoverProtocolCommandType_Leave;
    }
};

#endif /* LEAVE_PCBHP_COMMAND_H_ */
