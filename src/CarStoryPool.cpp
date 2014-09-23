/*
 * CarStoryPool.cpp
 *
 *  Created on: Apr 23, 2014
 *      Author: Kamran Amini <kam.cpp@gmail.com>
 */

#include <iostream>

#include "CarStoryPool.h"
#include "RandomHelper.h"

CarStoryPool* CarStoryPool::instance_ = NULL;

CarStoryPool* CarStoryPool::getInstance(void) {
  if (instance_ == NULL) {
    instance_ = new CarStoryPool();
  }
  return instance_;
}

CarStory* CarStoryPool::getRandomCarStory(void) const {
  unsigned int index = static_cast<unsigned int>(RandomHelper::next(carStories_.size()));
  return carStories_[index];
}

