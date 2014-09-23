/*
 * CarStory.h
 *
 *  Created on: Apr 18, 2014
 *      Author: Kamran Amini <kam.cpp@gmail.com>
 */

#ifndef CAR_STORY_H_
#define CAR_STORY_H_

#include <vector>

class CarStoryEvent;
class Car;

class CarStory {
  public:
    CarStory(unsigned int id) :
        id_(id) {
    }
    virtual ~CarStory(void);

    inline void addEvent(CarStoryEvent *traceEntry) {
      events_.push_back(traceEntry);
    }

    inline unsigned int getId(void) const {
      return id_;
    }

    inline CarStoryEvent* getEvent(int index) const {
      return events_[index];
    }

    inline unsigned int getEventsCount(void) const {
      return events_.size();
    }

    std::vector<CarStoryEvent*> getEventsBetweenTimes(Car *car, double t1, double t2) const;

  private:
    unsigned int id_;
    std::vector<CarStoryEvent*> events_;
};

#endif /* CAR_STORY_H_ */
