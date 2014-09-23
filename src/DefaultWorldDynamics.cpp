/*
 * DefaultWorldDynamics.cpp
 *
 *  Created on: Apr 22, 2014
 *      Author: Kamran Amini <kam.cpp@gmail.com>
 */

#include <iostream>

#include "DefaultWorldDynamics.h"
#include "WorldObject.h"
#include "Velocity.h"
#include "Position.h"

DefaultWorldDynamics::DefaultWorldDynamics(void) {
}

DefaultWorldDynamics::~DefaultWorldDynamics(void) {
}

void DefaultWorldDynamics::move(WorldObject *object, double duration) {
  Vector *v = object->getVelocity();
  Vector *p = object->getPosition();
  Vector * v2 = v->multiply(duration);
  Vector *p2 = p->add(v2);
  Position *newPosition = dynamic_cast<Position*>(p2);
  object->moveTo(newPosition);
  delete p2;
  delete v2;
}

