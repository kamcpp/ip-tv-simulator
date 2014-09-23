/*
 * AbstractIpTvWorld.h
 *
 *  Created on: May 16, 2014
 *      Author: Kamran Amini <kam.cpp@gmail.com>
 */

#ifndef ABSTRACT_IP_TV_WORLD_H_
#define ABSTRACT_IP_TV_WORLD_H_

#include <vector>
#include <algorithm>

#include "IpTvWorldInterface.h"
#include "enums.h"

class Road;
class DistributionInterface;
class SimulationData;
class AccessPoint;
class Position;
class WorldDynamicsInterface;

class AbstractIpTvWorld: public IpTvWorldInterface {
  public:
    AbstractIpTvWorld(void);
    virtual ~AbstractIpTvWorld(void);

    inline std::vector<AccessPoint*> getAccessPoints(void) const {
      return accessPoints_;
    }

    inline std::vector<Road*> getRoads(void) const {
      return roads_;
    }

    virtual WorldDynamicsInterface* getDynamics(void);
    virtual void cycle(SimulationData *simulationData);
    virtual std::vector<AccessPoint*> getCoveringAccessPointsInPosition(Position *p);

  protected:
    virtual AccessPoint* getNextAccessPoint(AccessPoint *accessPoint, LaneDirection direction);

  protected:
    unsigned int carCounter_;
    std::vector<Road*> roads_;
    std::vector<AccessPoint*> accessPoints_;
    WorldDynamicsInterface *worldDynamics_;
};

#endif /* ABSTRACT_IP_TV_WORLD_H_ */
