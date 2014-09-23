/*
 * SimpleIpTvWorld.cpp
 *
 *  Created on: Apr 11, 2014
 *      Author: Kamran Amini <kam.cpp@gmail.com>
 */

#define NULL 0

#include <iostream>
#include <sstream>
#include <iomanip>

#include "SimpleIpTvWorld.h"
#include "Road.h"
#include "Lane.h"
#include "SimulationData.h"
#include "RandomDistribution.h"
#include "Car.h"
#include "Timer.h"
#include "Position.h"
#include "Velocity.h"
#include "DefaultWorldDynamics.h"
#include "Simulator.h"
#include "CarStory.h"
#include "CarStoryEvent.h"
#include "AccessPoint.h"
#include "SimulationResult.h"
#include "NoCoveringAccessPointException.h"
#include "NetworkDeviceNotFoundException.h"
#include "AbstractNetworkInfrastructure.h"
#include "Environment.h"
#include "NetworkDevice.h"
#include "config.h"
#include "Commands/JoinPcbhpCommand.h"
#include "Commands/LeavePcbhpCommand.h"

SimpleIpTvWorld::SimpleIpTvWorld(void) :
    carCounter_(0), road_(NULL) {
}

SimpleIpTvWorld::~SimpleIpTvWorld(void) {
  delete road_;
}

WorldDynamicsInterface* SimpleIpTvWorld::getDynamics(void) {
  return new DefaultWorldDynamics();
}

std::string SimpleIpTvWorld::getJson(void) const {
  std::stringstream ss;
  ss << "{";
  ss << "\"type\": \"SimpleIpTvWorld\", \"carCounter\": \"" << carCounter_ << "\", \"road\": " << road_->getJson();
  ss << "}";
  return ss.str();
}

std::vector<AccessPoint*> SimpleIpTvWorld::getCoveringAccessPointsInPosition(Position *p) {
  std::vector<AccessPoint*> coveringAPs;
  for (unsigned int i = 0; i < accessPoints_.size(); i++) {
    if (accessPoints_[i]->isPositionInRange(p)) {
      coveringAPs.push_back(accessPoints_[i]);
      break;
    }
  }
  return coveringAPs;
}

bool SimpleIpTvWorld::prepare(void) {
  Lane *lane = new Lane(this);
  lane->setDirection(LaneDirection_LeftToRight);
  lane->moveTo(new Position(0.0, 0.0));
  lane->setName("main-lane");
  lane->setLength(ROAD_LENGTH);
  lane->setMaximumSpeed(INNER_LANE_SPEED);
  lane->setMinimumSpeed(0);
  lane->setMinimumDistance(INNER_LANE_MINIMUM_DISTANCE);
  lane->setMaximumDistance(INNER_LANE_MAXIMUM_DISTANCE);
  lane->setAverageDistance(INNER_LANE_AVERAGE_DISTANCE);

  road_ = new Road(this);
  road_->addLane(lane);
  road_->setLength(ROAD_LENGTH);

  AccessPoint *ap1 = new AccessPoint(this, "AP_1", new Position(0.0, 0.0), ACCESS_POINT_DIAMETER);
  AccessPoint *ap2 = new AccessPoint(this, "AP_2", new Position(INTER_ACCESS_POINT_DISTANCE, 0.0),
  ACCESS_POINT_DIAMETER);
  AccessPoint *ap3 = new AccessPoint(this, "AP_3", new Position(2 * INTER_ACCESS_POINT_DISTANCE, 0.0),
  ACCESS_POINT_DIAMETER);
  AccessPoint *ap4 = new AccessPoint(this, "AP_4", new Position(3 * INTER_ACCESS_POINT_DISTANCE, 0.0),
  ACCESS_POINT_DIAMETER);

  accessPoints_.push_back(ap1);
  accessPoints_.push_back(ap2);
  accessPoints_.push_back(ap3);
  accessPoints_.push_back(ap4);

  Environment::getInstance()->getNetworkInfra()->registerNetworkDevice(ap1->getNetworkDevice());
  Environment::getInstance()->getNetworkInfra()->registerNetworkDevice(ap2->getNetworkDevice());
  Environment::getInstance()->getNetworkInfra()->registerNetworkDevice(ap3->getNetworkDevice());
  Environment::getInstance()->getNetworkInfra()->registerNetworkDevice(ap4->getNetworkDevice());

  return true;
}

void SimpleIpTvWorld::cycle(SimulationData *simulationData) {
  for (unsigned int i = 0; i < road_->getLanesCount(); i++) {
    Lane* lane = road_->getLane(i);
    Car *car = lane->generateCar(carCounter_);
    if (car != NULL) {
      if (VERBOSE_GENERATE_CAR) {
        std::cout << "GENERATE: Car[" << car->getId() << "] is generated at " << simulationData->getCurrentTime() << std::endl;
      }
      carCounter_++;
    }
    for (unsigned int j = 0; j < lane->getCarsLength(); j++) {
      Car *car = lane->getCar(j);
      if (car->isInLane() && car->getBirthMoment() < simulationData->getCurrentTime()) {
        getDynamics()->move(car, simulationData->getSimulator()->getTimer()->getStep());
        if (VERBOSE_MOVE) {
          std::cout << "MOVE: Car[" << car->getId() << "] is moved to " << car->getPosition()->getX() << "." << std::endl;
        }
        car->getInternalTimer()->advance();
      }
      if (car->isInLane() && car->getPosition()->getX() > lane->getLength()) {
        // std::cout << "EXIT: Car[" << car->getId() << "] exited the lane." << std::endl;
        car->setInLane(false);
      }
      if (car->isInLane()) {
        std::vector<CarStoryEvent*> events = car->getLane()->getCarStory()->getEventsBetweenTimes(car, car->getInternalTimer()->getCurrent() - car->getInternalTimer()->getStep(), car->getInternalTimer()->getCurrent());
        for (unsigned int k = 0; k < events.size(); k++) {
          CarStoryEvent *e = events[k];
          switch (e->getStatus()) {
          case CarStoryEventStatus_Viewing:
            break;
          case CarStoryEventStatus_Zapping:
            try {
              car->join(e->getTvChannel());
              SimulationResult::getInstance()->incrementNumberOfRequests();
            } catch (NoCoveringAccessPointException &e) {
              SimulationResult::getInstance()->incrementNumberOfLostJoinRequestsWhileHandingOver();
            } catch (NetworkDeviceNotFoundException &e) {
              std::cout << "ERROR: A network device in the world is not registered." << std::endl;
            } catch (SimulationException &e) {
              std::cout << "ERROR: " << e.what() << std::endl;
            } catch (...) {
              std::cout << "ERROR: GENERAL ERROR WHILE SENDING LEAVE COMMAND." << std::endl;
            }
            break;
          default:
            break;
          }
        }

      } else {
        lane->removeCar(car);
        Environment::getInstance()->getNetworkInfra()->unregisterNetworkDevice(car->getNetworkDevice());
        delete car;
      }
    }
  }
}
