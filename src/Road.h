/*
 * Road.h
 *
 *  Created on: Apr 10, 2014
 *      Author: Kamran Amini <kam.cpp@gmail.com>
 */

#ifndef ROAD_H_
#define ROAD_H_

#include <vector>
#include "WorldObject.h"

class Lane;

class Road: public WorldObject {
  public:
    Road(WorldInterface *world, unsigned int length = 1000);
    ~Road(void);

    inline void addLane(Lane *lane) {
      lanes_.push_back(lane);
    }
    inline Lane* getLane(int index) const {
      return lanes_[index];
    }

    inline unsigned int getLanesCount(void) const {
      return lanes_.size();
    }

    inline double getLength(void) const {
      return length_;
    }
    void setLength(double length);

    virtual std::string getJson(void) const;

  private:
    double length_;            // Unit: Meter(s)
    std::vector<Lane*> lanes_;
};

#endif /* ROAD_H_ */
