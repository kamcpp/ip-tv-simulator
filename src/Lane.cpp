/*
 * Lane.cpp
 *
 *  Created on: Apr 26, 2014
 *      Author: Kamran Amini <kam.cpp@gmail.com>
 */

#include <sstream>

#include "Lane.h"
#include "Car.h"
#include "Position.h"
#include "Velocity.h"
#include "Simulator.h"
#include "Timer.h"
#include "Environment.h"
#include "AbstractNetworkInfrastructure.h"
#include "AbstractDistribution.h"
#include "TruncaExponentialDistribution.h"
#include "CarStory.h"
#include "RandomHelper.h"

Lane::Lane(WorldInterface *world, LaneDirection direction, double maximumSpeed, double minimumDistance, double maximumDistance, double averageDistance, double length, double minimumSpeed) :
    WorldObject(world), length_(length), minimumSpeed_(minimumSpeed), maximumSpeed_(maximumSpeed), minimumDistance_(minimumDistance), maximumDistance_(maximumDistance), averageDistance_(averageDistance), direction_(direction), carGenerationDistribution_(
    NULL), carStory_(NULL) {
  carGenerationDistribution_ = new TruncaExponentialDistribution(maximumSpeed_, minimumDistance_, maximumDistance_, averageDistance_);
}

Lane::~Lane(void) {
  for (unsigned int i = 0; i < cars_.size(); i++) {
    delete cars_[i];
  }
  delete carGenerationDistribution_;
  delete carStory_;
}

void Lane::addCar(Car *car) {
  cars_.push_back(car);
  car->setLane(this);
}
void Lane::removeCar(Car *car) {
  cars_.erase(std::remove(cars_.begin(), cars_.end(), car), cars_.end());
  car->setLane(NULL);
}

Car* Lane::generateCar(unsigned int id) {
  bool changed = carGenerationDistribution_->nextIf(Environment::getInstance()->getSimulator()->getTimer()->getCurrent());
  if (changed) {
    Car *car = new Car(getWorld(), id, Environment::getInstance()->getSimulator()->getTimer()->getCurrent());

    car->getVelocity()->setX(getMaximumSpeed());
    car->getVelocity()->setY(0.0);
    car->getVelocity()->setZ(0.0);

    car->getPosition()->setX(0.0);
    car->getPosition()->setY(getPosition()->getY());
    car->getPosition()->setZ(0.0);

    car->setInLane(true);
    /* Only 10% of all cars use IP-TV service. */
    car->setUsesIpTvService(RandomHelper::next() < 0.1);

    car->getInternalTimer()->setStep(Environment::getInstance()->getSimulator()->getTimer()->getStep());
    car->getInternalTimer()->setTimeUnit(Environment::getInstance()->getSimulator()->getTimer()->getTimeUnit());

    Environment::getInstance()->getNetworkInfra()->registerNetworkDevice(car->getNetworkDevice());

    addCar(car);
    return car;
  }
  return NULL;
}

std::string Lane::getJson(void) const {
  std::stringstream ss;
  ss << std::endl;
  ss << "{";
  ss << "\"type\": \"Lane\", \"length\": \"" << getLength() << "\", \"minimumSpeed\": \"" << getMinimumSpeed() << "\", \"maximumSpeed\": \"" << getMaximumSpeed() << "\", \"direction\": \"" << getDirection() << "\", \"name\": \"" << getName() << "\", \"velocity\": " + getVelocity()->getJson()
      << ", \"position\": " << getPosition()->getJson() << ", ";
  ss << "\"cars\": [";
  for (unsigned int i = 0; i < cars_.size(); i++) {
    Car *car = cars_[i];
    ss << car->getJson();
    if (i < cars_.size() - 1) {
      ss << ", ";
    }
  }
  ss << "]";
  ss << "}";
  ss << std::endl;
  return ss.str();
}

void Lane::updateCarGenerationDistribution(void) {
  if (carGenerationDistribution_ != NULL) {
    TruncaExponentialDistribution *truncaExponentialDitribution = dynamic_cast<TruncaExponentialDistribution*>(carGenerationDistribution_);
    if (truncaExponentialDitribution != NULL) {
      truncaExponentialDitribution->setAverageDistance(getAverageDistance());
      truncaExponentialDitribution->setMaximumDistance(getMaximumDistance());
      truncaExponentialDitribution->setMinimumDistance(getMinimumDistance());
      truncaExponentialDitribution->setSpeed(getMaximumSpeed());
    }
  }
}
