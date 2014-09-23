/*
 * IpTvWorldInterface.h
 *
 *  Created on: May 4, 2014
 *      Author: Kamran Amini <kam.cpp@gmail.com>
 */

#ifndef IP_TV_WORLD_INTERFACE_H_
#define IP_TV_WORLD_INTERFACE_H_

#include <vector>

#include "WorldInterface.h"

class AccessPoint;
class Position;

class IpTvWorldInterface: public WorldInterface {
  public:
    IpTvWorldInterface(void) {
    }
    virtual ~IpTvWorldInterface(void) {
    }

    virtual std::vector<AccessPoint*> getCoveringAccessPointsInPosition(Position *p) = 0;
};

#endif /* IP_TV_WORLD_INTERFACE_H_ */
