/*
 * SimpleIpTvWorld.h
 *
 *  Created on: Apr 11, 2014
 *      Author: Kamran Amini <kam.cpp@gmail.com>
 */

#ifndef SIMPLE_IP_TV_WORLD_H_
#define SIMPLE_IP_TV_WORLD_H_

#include <vector>

#include "IpTvWorldInterface.h"

class Road;
class DistributionInterface;
class SimulationData;
class AccessPoint;
class Position;

class SimpleIpTvWorld: public IpTvWorldInterface {
  public:
    SimpleIpTvWorld(void);
    virtual ~SimpleIpTvWorld(void);

    virtual WorldDynamicsInterface* getDynamics(void);

    virtual bool prepare(void);
    virtual void cycle(SimulationData *simulationData);

    inline std::vector<AccessPoint*> getAccessPoints(void) const {
      return accessPoints_;
    }

    virtual std::vector<AccessPoint*> getCoveringAccessPointsInPosition(Position *p);

    virtual std::string getJson(void) const;

  private:
    unsigned int carCounter_;
    Road *road_;
    std::vector<AccessPoint*> accessPoints_;
};

#endif /* SIMPLE_IP_TV_WORLD_H_ */
