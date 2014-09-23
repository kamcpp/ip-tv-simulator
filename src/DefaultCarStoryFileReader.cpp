/*
 * DefaultTraceInputReader.cpp
 *
 *  Created on: Apr 18, 2014
 *      Author: Kamran Amini <kam.cpp@gmail.com>
 */

#include <iostream>
#include <fstream>
#include <stdlib.h>

#include "DefaultCarStoryFileReader.h"
#include "CarStory.h"
#include "StringHelper.h"
#include "CarStoryEvent.h"
#include "TvChannelPool.h"
#include "utils.h"
#include "TvChannel.h"
#include "RandomHelper.h"

DefaultCarStoryFileReader::DefaultCarStoryFileReader(unsigned int id, std::string filePath) :
    id_(id), filePath_(filePath) {
}

DefaultCarStoryFileReader::~DefaultCarStoryFileReader(void) {
}

CarStory* DefaultCarStoryFileReader::read(void) {
  CarStory *carStory = new CarStory(id_);
  StringHelper stringHelper;
  std::ifstream infile(filePath_.c_str());
  if (!infile.good()) {
    std::cout << "ERROR: Error in reading file '" << filePath_ << "'." << std::endl;
    return NULL;
  }
  // RandomHelper::setTimeSeed();
  TvChannel *previousChannel = NULL;
  bool first = true;
  std::string line;
  while (std::getline(infile, line)) {
    std::vector<std::string> tokens = stringHelper.split(line, ' ');
    CarStoryEvent *carStoryEvent = new CarStoryEvent();
    if (first) {
      TvChannel *tvChannel = TvChannelPool::getInstance()->getFirstChannel();
      carStoryEvent->setTvChannel(tvChannel);
      previousChannel = tvChannel;
      first = false;
    } else {
      TvChannel *tvChannel = TvChannelPool::getInstance()->getNextChannel(previousChannel);
      carStoryEvent->setTvChannel(tvChannel);
      previousChannel = tvChannel;
    }
    // std::cout << "Assigned channel: " << carStoryEvent->getTvChannel()->getNumber() << std::endl;
    if (tokens.size() == 3) {
      carStoryEvent->setTime(atof(tokens[0].c_str()));
      int state = atoi(tokens[2].c_str());
      switch (state) {
      case 1:
        carStoryEvent->setStatus(CarStoryEventStatus_Viewing);
        break;
      case 2:
        carStoryEvent->setStatus(CarStoryEventStatus_Zapping);
        break;
      }
      carStory->addEvent(carStoryEvent);
    } else {
      delete carStoryEvent;
    }
  }
  infile.close();
  return carStory;
}
