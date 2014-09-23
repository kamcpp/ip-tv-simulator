/*
 * PreserveChannelPcbhpCommand.h
 *
 *  Created on: Aug 2, 2014
 *      Author: Kamran Amini <kam.cpp@gmail.com>
 */

#ifndef PRESERVE_CHANNEL_PCBHP_COMMAND_H_
#define PRESERVE_CHANNEL_PCBHP_COMMAND_H_

#ifndef NULL
#define NULL 0
#endif

#include "PreserveChannelBeforeHandoverProtocolCommand.h"

class PreserveChannelPcbhpCommand: public PreserveChannelBeforeHandoverProtocolCommand {
  public:
    PreserveChannelPcbhpCommand(TvChannel *tvChannel = NULL)
        : PreserveChannelBeforeHandoverProtocolCommand(tvChannel) {
    }

    virtual ~PreserveChannelPcbhpCommand(void) {
    }

    inline virtual PreserveChannelBeforeHandoverProtocolCommandType getType(void) const {
      return PreserveChannelBeforeHandoverProtocolCommandType_PreserveChannel;
    }
};

#endif /* PRESERVE_CHANNEL_PCBHP_COMMAND_H_ */
