/*
 * CarStoryEvent.h
 *
 *  Created on: Apr 18, 2014
 *      Author: Kamran Amini <kam.cpp@gmail.com>
 */

#ifndef CAR_STORY_EVENT_H_
#define CAR_STORY_EVENT_H_

#ifndef NULL
#define NULL 0
#endif

#include <string>
#include <sstream>
#include <iomanip>

#include "enums.h"
#include "JsonableInterface.h"

class TvChannel;

class CarStoryEvent: public JsonableInterface {
  public:
    CarStoryEvent(void) :
        time_(-1.0), status_(CarStoryEventStatus_None), tvChannel_(NULL) {
    }
    virtual ~CarStoryEvent(void) {
    }

    inline double getTime(void) const {
      return time_;
    }
    inline void setTime(double time) {
      time_ = time;
    }

    inline CarStoryEventStatus getStatus(void) const {
      return status_;
    }
    inline void setStatus(CarStoryEventStatus status) {
      status_ = status;
    }

    inline TvChannel* getTvChannel(void) const {
      return tvChannel_;
    }
    inline void setTvChannel(TvChannel* tvChannel) {
      tvChannel_ = tvChannel;
    }

    virtual std::string getJson(void) const;

  private:
    double time_;
    CarStoryEventStatus status_;
    TvChannel *tvChannel_;
};

#endif /* CAR_STORY_EVENT_H_ */
