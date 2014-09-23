/*
 * AbstractIpTvWorld.cpp
 *
 *  Created on: May 16, 2014
 *      Author: Kamran Amini <kam.cpp@gmail.com>
 */

#include <iostream>
#include <ctime>
#include <iomanip>

#include "AbstractIpTvWorld.h"
#include "DefaultWorldDynamics.h"
#include "AccessPoint.h"
#include "Road.h"
#include "Lane.h"
#include "CarStory.h"
#include "CarStoryEvent.h"
#include "SimulationData.h"
#include "Car.h"
#include "Timer.h"
#include "Simulator.h"
#include "Position.h"
#include "Environment.h"
#include "SimulationResult.h"
#include "NetworkDeviceNotFoundException.h"
#include "SimulationException.h"
#include "AbstractNetworkInfrastructure.h"
#include "config.h"

/*
 * A base implementation for all IP-TV worlds. Each IP-TV world has some roads.
 * Each road has some lanes and access points. Cars are moving in lanes and
 * they are interacting with access points to view or change TV channels.
 */
AbstractIpTvWorld::AbstractIpTvWorld(void)
    : carCounter_(0), worldDynamics_(NULL) {
}

AbstractIpTvWorld::~AbstractIpTvWorld(void) {
  if (worldDynamics_ != NULL) {
    delete worldDynamics_;
  }
}

WorldDynamicsInterface* AbstractIpTvWorld::getDynamics(void) {
  if (worldDynamics_ == NULL) {
    worldDynamics_ = new DefaultWorldDynamics();
  }
  return worldDynamics_;
}

std::vector<AccessPoint*> AbstractIpTvWorld::getCoveringAccessPointsInPosition(Position *p) {
  std::vector<AccessPoint*> coveringAPs;
  for (unsigned int i = 0; i < accessPoints_.size(); i++) {
    if (accessPoints_[i]->isPositionInRange(p)) {
      coveringAPs.push_back(accessPoints_[i]);
      break;
    }
  }
  return coveringAPs;
}

AccessPoint* AbstractIpTvWorld::getNextAccessPoint(AccessPoint *accessPoint, LaneDirection direction) {
  unsigned int pos = std::distance(accessPoints_.begin(), std::find(accessPoints_.begin(), accessPoints_.end(), accessPoint));
  if (pos < accessPoints_.size()) {
    if (direction == LaneDirection_LeftToRight) {
      pos++;
      if (pos < accessPoints_.size()) {
        return accessPoints_.at(pos);
      }
      return NULL;
    } else if (direction == LaneDirection_RightToLeft) {
      pos--;
      if (pos >= 0) {
        return accessPoints_.at(pos);
      }
      return NULL;
    }
    return NULL;
  } else {
    std::cout << "WARNING: Access point does not exist in the list." << std::endl;
    return NULL;
  }
}

/*
 * In each cycle, cars are moved, new cars are born and some cars leave the 
 * road. Also, all messages produced by cars and access points are exchanged
 * among them. This allow a narrow and exact inspection of events occurring
 * in a single short cycle of a IP-TV world.
 */
void AbstractIpTvWorld::cycle(SimulationData *simulationData) {
  /* Loop iterating over roads */
  for (unsigned int roadCounter = 0; roadCounter < roads_.size(); roadCounter++) {
    Road *road = roads_[roadCounter];
    /* Loop iterating over lanes */
    for (unsigned int laneCounter = 0; laneCounter < road->getLanesCount(); laneCounter++) {
      Lane* lane = road->getLane(laneCounter);
      /* Trying to generate a new car. In some cycles, we don't have any car generated. */
      Car *car = lane->generateCar(carCounter_);
      if (car != NULL) {
        /* Car is generated. */
        if (VERBOSE_GENERATE_CAR) {
          std::cout << "GENERATE: Lane[" << lane->getName() << "].Car[" << car->getId() << "] is generated at " << simulationData->getCurrentTime() << std::endl;
        }
        SimulationResult::getInstance()->incrementNumberOfCars();
        carCounter_++;
      }
      /* Loop iterating over cars */
      for (unsigned int carCounter = 0; carCounter < lane->getCarsLength(); carCounter++) {
        Car *car = lane->getCar(carCounter);
        if (car->isInLane() /* Car is still in the road */&& car->getBirthMoment() < simulationData->getCurrentTime() /* Car is already born */
        ) {
          /* Move the car according to defined Dynamics */
          getDynamics()->move(car, simulationData->getSimulator()->getTimer()->getStep());
          if (VERBOSE_MOVE) {
            std::cout << "MOVE: Lane[" << lane->getName() << "].Car[" << car->getId() << "] is moved to " << car->getPosition()->getX() << "." << std::endl;
          }
          /* Each car has an internal timer, counting cycles from birth moment.
           * Increment internal timer by SIMULATION_STEP.
           */
          car->getInternalTimer()->advance();
        }
        if (car->isInLane() /* Car is still in the road */&& car->getPosition()->getX() > lane->getLength() /* Car is outside of the road */) {
          if (VERBOSE_EXIT_CAR) {
            std::cout << "EXIT: Lane[" << lane->getName() << "].Car[" << car->getId() << "] exited the lane." << std::endl;
          }
          /* Car is not in lane anymore. Car has leaved the road. */
          car->setInLane(false);
        }
        if (car->isInLane() /* Car is in the road */&& car->usesIpTvService() /* Car uses IP-TV service. */) {
          car->checkIncomingMessages();
          /* Obtain a list of events which they should have been occurred in this cycle according to the car story.
           * Each lane has a car story which describes the actions performed by a single car in that lane.
           */
          std::vector<CarStoryEvent*> events = car->getLane()->getCarStory()->getEventsBetweenTimes(car, car->getInternalTimer()->getCurrent() - car->getInternalTimer()->getStep() /* currentTime - SIMULATION_STEP */, car->getInternalTimer()->getCurrent() /* currentTime */);
          /* Loop iterating over events */
          for (unsigned int carStoryEventCounter = 0; carStoryEventCounter < events.size(); carStoryEventCounter++) {
            CarStoryEvent *e = events[carStoryEventCounter];
            /* Checking type of event */
            switch (e->getStatus()) {
            case CarStoryEventStatus_Viewing:
              /* Car is viewing the channel. Just check for hand-over event. */
              try {
              car->checkForHandover();
              } catch (NoCoveringAccessPointException &e) {
                std::cout << "ERROR: LOST ANTENNA ...";
              }
              break;
            case CarStoryEventStatus_Zapping:
              /* Car should change the channel. */
              try {
                /* Car sends a JOIN_CHANNEL request. If it is viewing a channel, it sends a LEAVE_CHANNEL request prior to join request. */
                car->join(e->getTvChannel());
                SimulationResult::getInstance()->incrementNumberOfRequests();
              } catch (NoCoveringAccessPointException &e) {
                /* No access point is in range */
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
        } else /* Car is not in the road */{
          /* Remove the car from lane. */
          lane->removeCar(car);
          /* Unregister network device. */
          Environment::getInstance()->getNetworkInfra()->unregisterNetworkDevice(car->getNetworkDevice());
          SimulationResult::getInstance()->decrementNumberOfCars();
          carCounter_--;
          delete car;
        }
      }
      for (unsigned int accessPointCounter = 0; accessPointCounter < accessPoints_.size(); accessPointCounter++) {
        AccessPoint *accessPoint = accessPoints_.at(accessPointCounter);
        accessPoint->getInternalTimer()->advance();
        accessPoint->checkIncomingMessages();
        if (accessPoint->shouldAskAboutWhoNeedsChannels()) {
          accessPoint->askWhoNeedsChannels();
        }
      }
    }
  }
  if (MUTE) {
    std::cout.setf(std::ios_base::fixed, std::ios_base::floatfield);
    std::cout.precision(0);
    std::cout << "Run: " << simulationData->getRunNumber() << ", ";
    std::cout.precision(2);
    std::cout << "Time: " << simulationData->getCurrentTime() << "/" << Environment::getInstance()->getSimulator()->getTimer()->getEnd() << " (" << 100 * (simulationData->getCurrentTime() / Environment::getInstance()->getSimulator()->getTimer()->getEnd()) << " %), ";
    std::cout << "\r";
    /* std::cout.precision(0);
     std::cout << "Lanes: " << SimulationResult::getInstance()->getNumberOfLanes() << ", ";
     std::cout << "Cars: " << SimulationResult::getInstance()->getNumberOfCars() << ", ";
     std::cout << "Handovers: " << SimulationResult::getInstance()->getNumberOfHandovers() << ", ";
     std::cout << "Reqs.: " << SimulationResult::getInstance()->getNumberOfRequests() << ", ";
     std::cout << "Blocked Reqs.: " << SimulationResult::getInstance()->getNumberOfBlockedJoinRequests() << ", ";
     std::cout << "Handover Blocked Reqs.: " << SimulationResult::getInstance()->getNumberOfLostJoinRequestsWhileHandingOver() << "\r"; */
  }
}

