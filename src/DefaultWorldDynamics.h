/*
 * DefaultWorldDynamics.h
 *
 *  Created on: Apr 22, 2014
 *      Author: Kamran Amini <kam.cpp@gmail.com>
 */

#ifndef DEFAULT_WORLD_DYNAMICS_H_
#define DEFAULT_WORLD_DYNAMICS_H_

#include "WorldDynamicsInterface.h"

class WorldObject;

class DefaultWorldDynamics: public WorldDynamicsInterface {
  public:
    DefaultWorldDynamics(void);
    virtual ~DefaultWorldDynamics(void);

    virtual void move(WorldObject *object, double duration);
};

#endif /* DEFAULT_WORLD_DYNAMICS_H_ */
