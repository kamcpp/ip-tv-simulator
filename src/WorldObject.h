/*
 * WorldObject.h
 *
 *  Created on: Apr 11, 2014
 *      Author: Kamran Amini <kam.cpp@gmail.com>
 */

#ifndef WORLD_OBJECT_H_
#define WORLD_OBJECT_H_

#ifndef NULL
#define NULL 0
#endif

#include "JsonableInterface.h"

class Position;
class Velocity;
class WorldInterface;

class WorldObject: public JsonableInterface {
  public:
    WorldObject(WorldInterface *world, Position *position = NULL);
    virtual ~WorldObject(void);

    inline WorldInterface* getWorld(void) const {
      return world_;
    }

    inline Position* getPosition(void) const {
      return position_;
    }

    inline Velocity* getVelocity(void) const {
      return velocity_;
    }

    void moveTo(Position *position);

  private:
    Position *position_;
    Velocity *velocity_;
    WorldInterface *world_;
};

#endif /* WORLD_OBJECT_H_ */
