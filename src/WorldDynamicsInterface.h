/*
 * WorldDynamics.h
 *
 *  Created on: Apr 22, 2014
 *      Author: Kamran Amini <kam.cpp@gmail.com>
 */

#ifndef WORLD_DYNAMICS_INTERFACE_H_
#define WORLD_DYNAMICS_INTERFACE_H_

class WorldObject;
class WorldDynamicsInterface;

class WorldDynamicsInterface {
  public:
    WorldDynamicsInterface(void) {
    }
    virtual ~WorldDynamicsInterface(void) {
    }

    virtual void move(WorldObject *object, double duration) = 0;
};

#endif /* WORLD_DYNAMICS_INTERFACE_H_ */
