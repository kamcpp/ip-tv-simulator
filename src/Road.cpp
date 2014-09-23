/*
 * Road.cpp
 *
 *  Created on: Apr 10, 2014
 *      Author: Kamran Amini <kam.cpp@gmail.com>
 */

#include <sstream>

#include "Road.h"
#include "Lane.h"

Road::Road(WorldInterface *world, unsigned int length) :
    WorldObject(world), length_(length) {
}

Road::~Road(void) {
  for (std::vector<Lane*>::iterator it = lanes_.begin(); it != lanes_.end(); it++) {
    delete *it;
  }
}

void Road::setLength(double length) {
  length_ = length;
  for (std::vector<Lane*>::iterator it = lanes_.begin(); it != lanes_.end(); it++) {
    (*it)->setLength(length_);
  }
}

std::string Road::getJson(void) const {
  std::stringstream ss;
  ss << "{";
  ss << "\"type\": \"Road\", \"length\": \"" << getLength() << "\", ";
  ss << "\"lanes\": ";
  ss << "[";
  for (unsigned int i = 0; i < lanes_.size(); i++) {
    Lane *lane = lanes_[i];
    ss << lane->getJson();
    if (i < lanes_.size() - 1) {
      ss << ", ";
    }
  }
  ss << "]";
  ss << "}";
  ss << std::endl;
  return ss.str();
}

