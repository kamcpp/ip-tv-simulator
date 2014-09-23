/*
 * WhoNeedsTheChannelPcbhpCommand.h
 *
 *  Created on: 20 Sept. 2014
 *      Author: Kamran Amini <kam.cpp@gmail.com>
 */

#ifndef WHO_NEEDS_THE_CHANNEL_PCBHP_COMMAND_H_
#define WHO_NEEDS_THE_CHANNEL_PCBHP_COMMAND_H_

#include "PreserveChannelBeforeHandoverProtocolCommand.h"

class TvChannel;

class WhoNeedsTheChannelPcbhpCommand: public PreserveChannelBeforeHandoverProtocolCommand {
  public:
    WhoNeedsTheChannelPcbhpCommand(TvChannel *tvChannel = NULL)
        : PreserveChannelBeforeHandoverProtocolCommand(tvChannel) {
    }
    virtual ~WhoNeedsTheChannelPcbhpCommand(void) {
    }

    inline virtual PreserveChannelBeforeHandoverProtocolCommandType getType() const {
      return PreserveChannelBeforeHandoverProtocolCommandType_WhoNeedsTheChannel;
    }
};

#endif /* WHO_NEEDS_THE_CHANNEL_PCBHP_COMMAND_H_ */
