/*
 * CarStoryEvent.cpp
 *
 *  Created on: May 10, 2014
 *      Author: Kamran Amini <kam.cpp@gmail.com>
 */

#include "CarStoryEvent.h"
#include "TvChannel.h"

std::string CarStoryEvent::getJson(void) const {
  std::stringstream ss;
  ss << "{";
  ss << "\"time\": \"" << time_ << "\", ";
  ss << "\"channel\": " << tvChannel_->getJson() << ", ";
  ss << "\"status\": \"" << status_ << "\" ,";
  ss << "\"statusString\": \"";
  switch (status_) {
  case CarStoryEventStatus_Viewing:
    ss << "Viewing";
    break;
  case CarStoryEventStatus_Zapping:
    ss << "Zapping";
    break;
  default:
    ss << "None";
    break;
  }
  ss << "\"";
  ss << "}";
  return ss.str();
}

