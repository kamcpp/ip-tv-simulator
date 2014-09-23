/*
 * DefaultIpTvWorld.h
 *
 *  Created on: Apr 11, 2014
 *      Author: Kamran Amini <kam.cpp@gmail.com>
 */

#ifndef DEFAULT_IP_TV_WORLD_H_
#define DEFAULT_IP_TV_WORLD_H_

#include <vector>

#include "AbstractIpTvWorld.h"

class Road;
class SimulationData;

class DefaultIpTvWorld: public AbstractIpTvWorld {
  public:
    DefaultIpTvWorld(void);
    virtual ~DefaultIpTvWorld(void);

    virtual bool prepare(void);

    virtual std::string getJson(void) const;
};

#endif /* DEFAULT_IP_TV_WORLD_H_ */
