/*
 * IStillNeedTheChannelPcbhpCommand.h
 *
 *  Created on: May 4, 2014
 *      Author: Kamran Amini <kam.cpp@gmail.com>
 */

#ifndef I_STILL_NEED_THE_CHANNEL_PCBHP_COMMAND_H_
#define I_STILL_NEED_THE_CHANNEL_PCBHP_COMMAND_H_

#ifndef NULL
#define NULL 0
#endif

#include "PreserveChannelBeforeHandoverProtocolCommand.h"

class TvChannel;

class IStillNeedTheChannelPcbhpCommand: public PreserveChannelBeforeHandoverProtocolCommand {
  public:
    IStillNeedTheChannelPcbhpCommand(TvChannel *channel = NULL) :
        PreserveChannelBeforeHandoverProtocolCommand(channel) {
    }
    virtual ~IStillNeedTheChannelPcbhpCommand(void) {
    }

    virtual PreserveChannelBeforeHandoverProtocolCommandType getType(void) const {
      return PreserveChannelBeforeHandoverProtocolCommandType_IStillNeedTheChannel;
    }
};

#endif /* I_STILL_NEED_THE_CHANNEL_PCBHP_COMMAND_H_ */
