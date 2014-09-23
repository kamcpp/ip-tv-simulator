/*
 * CarStoryLoader.cpp
 *
 *  Created on: Apr 28, 2014
 *      Author: Kamran Amini <kam.cpp@gmail.com>
 */

#include <string>
#include <sstream>
#include <iostream>

#include "CarStoryLoader.h"
#include "DefaultCarStoryFileReader.h"
#include "CarStory.h"
#include "Environment.h"
#include "ConfigurationInterface.h"
#include "config.h"

CarStoryLoader* CarStoryLoader::instance_ = NULL;

CarStoryLoader* CarStoryLoader::getInstance(void) {
  if (instance_ == NULL) {
    instance_ = new CarStoryLoader(Environment::getInstance()->getConfiguration()->getCarStoriesBaseDirectory());
  }
  return instance_;
}

CarStory* CarStoryLoader::readNext(void) {
  if (MAX_TRACE_FILES > 0 && counter_ >= MAX_TRACE_FILES) {
    return NULL;
  }
  std::stringstream filename;
  filename << baseDirectoryPath_ << "/TRACE_" << counter_ << ".que";
  std::cout << "Reading " << filename.str() << " ..." << std::endl;
  DefaultCarStoryFileReader reader(counter_, filename.str());
  CarStory *carStory = reader.read();
  if (carStory != NULL) {
    counter_++;
  }
  return carStory;
}

