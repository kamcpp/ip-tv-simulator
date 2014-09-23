/*
 * WorldObject.cpp
 *
 *  Created on: Apr 11, 2014
 *      Author: Kamran Amini <kam.cpp@gmail.com>
 */

#include "WorldObject.h"
#include "Position.h"
#include "Velocity.h"

WorldObject::WorldObject(WorldInterface *world, Position *position) :
    world_(world) {
  if (position == NULL) {
    position_ = new Position();
  } else {
    position_ = static_cast<Position*>(position->clone());
  }
  velocity_ = new Velocity();
}

WorldObject::~WorldObject(void) {
  delete position_;
  delete velocity_;
}

void WorldObject::moveTo(Position *position) {
  if (position != NULL) {
    position_->assignFrom(position);
  }
}

