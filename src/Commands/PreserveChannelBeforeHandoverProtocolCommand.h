/*
 * PreserveChannelBeforeHandoverProtocolCommand.h
 *
 *  Created on: May 3, 2014
 *      Author: Kamran Amini <kam.cpp@gmail.com>
 */

#ifndef PRESERVE_CHANNEL_BEFORE_HANDOVER_PROTOCOL_COMMAND_H_
#define PRESERVE_CHANNEL_BEFORE_HANDOVER_PROTOCOL_COMMAND_H_

#ifndef NULL
#define NULL 0
#endif

#include "../Command.h"
#include "../enums.h"

class TvChannel;

class PreserveChannelBeforeHandoverProtocolCommand: public Command {
  public:
    PreserveChannelBeforeHandoverProtocolCommand(TvChannel *channel = NULL) :
        tvChannel_(channel) {
    }
    virtual ~PreserveChannelBeforeHandoverProtocolCommand(void) {
    }

    inline TvChannel* getTvChannel(void) const {
      return tvChannel_;
    }
    inline void setTvChannel(TvChannel *tvChannel) {
      tvChannel_ = tvChannel;
    }

    virtual PreserveChannelBeforeHandoverProtocolCommandType getType(void) const = 0;

  private:
    TvChannel *tvChannel_;
};

#endif /* PRESERVE_CHANNEL_BEFORE_HANDOVER_PROTOCOL_COMMAND_H_ */
