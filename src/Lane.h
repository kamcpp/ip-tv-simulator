/*
 * Lane.h
 *
 *  Created on: Apr 10, 2014
 *      Author: Kamran Amini <kam.cpp@gmail.com>
 */

#ifndef LANE_H_
#define LANE_H_

#include <string>
#include <vector>
#include <algorithm>

#include "WorldObject.h"
#include "enums.h"

class Car;
class CarStory;
class WorldObject;
class AbstractDistribution;

class Lane: public WorldObject {
  public:
    Lane(WorldInterface *world, LaneDirection direction = LaneDirection_None, double maximumSpeed = 120.0, double minimumDistance = 10.0, double maximumDistance = 30.0, double averageDistance = 20.0, double length = 1000.0, double minimumSpeed = 0.0);
    virtual ~Lane(void);

    inline double getLength(void) const {
      return length_;
    }
    inline void setLength(double length) {
      length_ = length;
      updateCarGenerationDistribution();
    }

    inline double getMinimumDistance(void) const {
      return minimumDistance_;
    }
    inline void setMinimumDistance(double minimumDistance) {
      minimumDistance_ = minimumDistance;
      updateCarGenerationDistribution();
    }

    inline double getMaximumDistance(void) const {
      return maximumDistance_;
    }
    inline void setMaximumDistance(double maximumDistance) {
      maximumDistance_ = maximumDistance;
      updateCarGenerationDistribution();
    }

    inline double getAverageDistance(void) const {
      return averageDistance_;
    }
    inline void setAverageDistance(double averageDistance) {
      averageDistance_ = averageDistance;
      updateCarGenerationDistribution();
    }

    inline double getMinimumSpeed(void) const {
      return minimumSpeed_;
    }
    inline void setMinimumSpeed(double minimumSpeed) {
      minimumSpeed_ = minimumSpeed;
      updateCarGenerationDistribution();
    }

    inline double getMaximumSpeed(void) const {
      return maximumSpeed_;
    }
    inline void setMaximumSpeed(double maximumSpeed) {
      maximumSpeed_ = maximumSpeed;
      updateCarGenerationDistribution();
    }

    inline LaneDirection getDirection(void) const {
      return direction_;
    }
    inline void setDirection(LaneDirection direction) {
      direction_ = direction;
      updateCarGenerationDistribution();
    }

    inline AbstractDistribution* getCarGenerationDistribution(void) const {
      return carGenerationDistribution_;
    }
    inline void setCarGenerationDistribution(AbstractDistribution *carGenerationDistribution) {
      carGenerationDistribution_ = carGenerationDistribution;
      updateCarGenerationDistribution();
    }

    inline CarStory* getCarStory(void) const {
      return carStory_;
    }
    inline void setCarStory(CarStory *carStory) {
      carStory_ = carStory;
    }

    inline std::string getName(void) const {
      return name_;
    }
    inline void setName(std::string name) {
      name_ = name;
      updateCarGenerationDistribution();
    }

    inline Car* getCar(int index) const {
      return cars_[index];
    }
    inline double getCarsLength(void) const {
      return cars_.size();
    }

    void addCar(Car *car);
    void removeCar(Car *car);
    virtual Car* generateCar(unsigned int id);

    virtual std::string getJson(void) const;

  private:
    void updateCarGenerationDistribution(void);

  private:
    double length_; 			// Unit: Meter(s)
    double minimumSpeed_;		// Unit: Meter(s) / Second(s)
    double maximumSpeed_;		// Unit: Meter(s) / Second(s)
    double minimumDistance_;    // Unit: Meter(s)
    double maximumDistance_;    // Unit: Meter(s)
    double averageDistance_;    // Unit: Meter(s)
    LaneDirection direction_;
    AbstractDistribution *carGenerationDistribution_;
    CarStory *carStory_;
    std::string name_;
    std::vector<Car*> cars_;
};

#endif /* LANE_H_ */
