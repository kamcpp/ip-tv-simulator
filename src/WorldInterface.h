/*
 * WorldInterface.h
 *
 *  Created on: Apr 11, 2014
 *      Author: Kamran Amini <kam.cpp@gmail.com>
 */

#ifndef WORLD_INTERFACE_H_
#define WORLD_INTERFACE_H_

#include "JsonableInterface.h"

class SimulationData;
class WorldDynamicsInterface;

/*
 * An interface for all worlds. IP-TV World is our dominant world in current
 * usage but this allow us to expand our definition of a World, if needed. In
 * this model, each world has a Dynamics which it is a set of physical rules 
 * applied to objects inside that world. Since the world object is used inside
 * a simulation loop, cycle(...) method is called with each iteration in the
 * simulation. cycle(...) method advances the world and triggers events inside 
 * it. An implementation of this interface should provide a very detailed and
 * precise order of actions for this method.
 */
class WorldInterface: public JsonableInterface {
  public:
    virtual ~WorldInterface(void) {
    }

    /*
     * Returns a pointer to Dynamics object of this world.
     */
    virtual WorldDynamicsInterface* getDynamics(void) = 0;

    /*
     * Prepares the world. Calling this method, simply, initializes
     * the world.
     */
    virtual bool prepare(void) = 0;

    /*
     * A world continues to live by calling this method. Whenever the world
     * needs to get advanced, this method should be called. Calling this
     * method changes the state of the world. You can imagine a world as
     * many seperate screenshots, each of them taken by calling this 
     * method. Since this method will be called inside a simulation loop,
     * simulation data is passed to it.
     */
    virtual void cycle(SimulationData *simulationData) = 0;
};

#endif /* WORLDMODEL_INTERFACE_H_ */
