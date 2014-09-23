/*
 * CarStory.cpp
 *
 *  Created on: Apr 19, 2014
 *      Author: Kamran Amini <kam.cpp@gmail.com>
 */

#include <iostream>

#include "CarStory.h"
#include "CarStoryEvent.h"
#include "Car.h"

CarStory::~CarStory(void) {
  for (unsigned int i = 0; i < events_.size(); i++) {
    delete events_[i];
  }
}

std::vector<CarStoryEvent*> CarStory::getEventsBetweenTimes(Car *car, double t1, double t2) const {
  std::vector<CarStoryEvent*> foundEvents;
  unsigned int i = car->getLastEventIndex();
  for (; i < events_.size(); i++) {
    CarStoryEvent *e = events_[i];
    if (e->getTime() >= t1 && e->getTime() < t2) {
      foundEvents.push_back(e);
    }
    if (e->getTime() > t2) {
      break;
    }
  }
  car->setLastEventIndex(i);
  return foundEvents;
}
