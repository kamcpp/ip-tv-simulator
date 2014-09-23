/*
 * PreserveChannelPcbhpCommand.h
 *
 *  Created on: Aug 2, 2014
 *      Author: Kamran Amini <kam.cpp@gmail.com>
 */

#ifndef PRESERVE_CHANNEL_ACCEPTED_PCBHP_COMMAND_H_
#define PRESERVE_CHANNEL_ACCEPTED_PCBHP_COMMAND_H_

#ifndef NULL
#define NULL 0
#endif

#include "PreserveChannelBeforeHandoverProtocolCommand.h"

class PreserveChannelPcbhpAcceptedCommand: public PreserveChannelBeforeHandoverProtocolCommand {
  public:
    PreserveChannelPcbhpAcceptedCommand(TvChannel *tvChannel = NULL) :
        PreserveChannelBeforeHandoverProtocolCommand(tvChannel) {
    }

    virtual ~PreserveChannelPcbhpAcceptedCommand(void) {
    }

    inline virtual PreserveChannelBeforeHandoverProtocolCommandType getType(void) const {
      return PreserveChannelBeforeHandoverProtocolCommandType_PreserveChannelAccepted;
    }
};

#endif /* PRESERVE_CHANNEL_ACCEPTED_PCBHP_COMMAND_H_ */
