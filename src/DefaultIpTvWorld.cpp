/*
 * DefaultIpTvWorld.cpp
 *
 *  Created on: Apr 11, 2014
 *      Author: Kamran Amini <kam.cpp@gmail.com>
 */

#define NULL 0

#include <iostream>
#include <sstream>
#include <iomanip>

#include "DefaultIpTvWorld.h"
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
#include "CarStoryLoader.h"
#include "config.h"
#include "AccessPoint.h"
#include "Environment.h"
#include "AbstractNetworkInfrastructure.h"
#include "SimulationResult.h"

DefaultIpTvWorld::DefaultIpTvWorld(void) :
    AbstractIpTvWorld() {
}

DefaultIpTvWorld::~DefaultIpTvWorld(void) {
  for (unsigned int i = 0; i < roads_.size(); i++) {
    delete roads_[i];
  }
  for (unsigned int i = 0; i < accessPoints_.size(); i++) {
    delete accessPoints_[i];
  }
}

std::string DefaultIpTvWorld::getJson(void) const {
  std::stringstream ss;
  ss << "{";
  ss << "\"type\": \"DefaultIpTvWorld\", \"carCounter\": \"" << carCounter_ << "\", \"road\": " << roads_[0]->getJson();
  ss << "}";
  return ss.str();
}

bool DefaultIpTvWorld::prepare(void) {
  CarStory *carStory1 = CarStoryLoader::getInstance()->readNext();
  if (carStory1 == NULL) {
    return false;
  }
  CarStory *carStory2 = CarStoryLoader::getInstance()->readNext();
  if (carStory2 == NULL) {
    delete carStory1;
    return false;
  }
  CarStory *carStory3 = CarStoryLoader::getInstance()->readNext();
  if (carStory3 == NULL) {
    delete carStory1;
    delete carStory2;
    return false;
  }
  CarStory *carStory4 = CarStoryLoader::getInstance()->readNext();
  if (carStory4 == NULL) {
    delete carStory1;
    delete carStory2;
    delete carStory3;
    return false;
  }
  CarStory *carStory5 = CarStoryLoader::getInstance()->readNext();
  if (carStory5 == NULL) {
    delete carStory1;
    delete carStory2;
    delete carStory3;
    delete carStory4;
    return false;
  }
  CarStory *carStory6 = CarStoryLoader::getInstance()->readNext();
  if (carStory6 == NULL) {
    delete carStory1;
    delete carStory2;
    delete carStory3;
    delete carStory4;
    delete carStory5;
    return false;
  }

  Lane *leftToRightLane1 = new Lane(this);
  leftToRightLane1->setDirection(LaneDirection_LeftToRight);
  Position *pos = new Position(0.0, 0.0);
  leftToRightLane1->moveTo(pos);
  delete pos;
  leftToRightLane1->setName("left-to-right-lane-1");
  leftToRightLane1->setLength(10000.0);
  leftToRightLane1->setMaximumSpeed(22.3); // 80 Km/h
  leftToRightLane1->setMinimumSpeed(0);
  leftToRightLane1->setCarStory(carStory1);

  Lane *leftToRightLane2 = new Lane(this);
  leftToRightLane2->setDirection(LaneDirection_LeftToRight);
  pos = new Position(0.0, 10.0);
  leftToRightLane2->moveTo(pos);
  delete pos;
  leftToRightLane2->setName("left-to-right-lane-2");
  leftToRightLane2->setLength(10000.0);
  leftToRightLane2->setMaximumSpeed(27.8); // 100 Km/h
  leftToRightLane2->setMinimumSpeed(0);
  leftToRightLane2->setCarStory(carStory2);

  Lane *leftToRightLane3 = new Lane(this);
  leftToRightLane3->setDirection(LaneDirection_LeftToRight);
  pos = new Position(0.0, 20.0);
  leftToRightLane3->moveTo(pos);
  delete pos;
  leftToRightLane3->setName("left-to-right-lane-3");
  leftToRightLane3->setLength(10000.0);
  leftToRightLane3->setMaximumSpeed(33.4); // 120 Km/h
  leftToRightLane3->setMinimumSpeed(0);
  leftToRightLane3->setCarStory(carStory3);

  Lane *rightToLeftLane3 = new Lane(this);
  rightToLeftLane3->setDirection(LaneDirection_RightToLeft);
  pos = new Position(0.0, 30.0);
  rightToLeftLane3->moveTo(pos);
  delete pos;
  rightToLeftLane3->setName("right-to-left-lane-3");
  rightToLeftLane3->setLength(10000.0);
  rightToLeftLane3->setMaximumSpeed(33.4); // 120 Km/h
  rightToLeftLane3->setMinimumSpeed(0);
  rightToLeftLane3->setCarStory(carStory4);

  Lane *rightToLeftLane2 = new Lane(this);
  rightToLeftLane2->setDirection(LaneDirection_RightToLeft);
  pos = new Position(0.0, 40.0);
  rightToLeftLane2->moveTo(pos);
  delete pos;
  rightToLeftLane2->setName("right-to-left-lane-2");
  rightToLeftLane2->setLength(10000.0);
  rightToLeftLane2->setMaximumSpeed(27.8); // 100 Km/h
  rightToLeftLane2->setMinimumSpeed(0);
  rightToLeftLane2->setCarStory(carStory5);

  Lane *rightToLeftLane1 = new Lane(this);
  rightToLeftLane1->setDirection(LaneDirection_RightToLeft);
  pos = new Position(0.0, 50.0);
  rightToLeftLane1->moveTo(pos);
  delete pos;
  rightToLeftLane1->setName("right-to-left-lane-1");
  rightToLeftLane1->setLength(10000.0);
  rightToLeftLane1->setMaximumSpeed(22.3); // 80 Km/h
  rightToLeftLane1->setMinimumSpeed(0);
  rightToLeftLane1->setCarStory(carStory6);

  Road *road = new Road(this);
  road->addLane(leftToRightLane1);
  road->addLane(leftToRightLane2);
  road->addLane(leftToRightLane3);
  road->addLane(rightToLeftLane3);
  road->addLane(rightToLeftLane2);
  road->addLane(rightToLeftLane1);
  road->setLength(10000.0);

  SimulationResult::getInstance()->incrementNumberOfLanes();
  SimulationResult::getInstance()->incrementNumberOfLanes();
  SimulationResult::getInstance()->incrementNumberOfLanes();
  SimulationResult::getInstance()->incrementNumberOfLanes();
  SimulationResult::getInstance()->incrementNumberOfLanes();
  SimulationResult::getInstance()->incrementNumberOfLanes();

  roads_.push_back(road);

  Position *pos1 = new Position(0.0, 0.0);
  AccessPoint *ap1 = new AccessPoint(this, "AP_1", pos1, ACCESS_POINT_DIAMETER);
  delete pos1;

  Position *pos2 = new Position(INTER_ACCESS_POINT_DISTANCE, 0.0);
  AccessPoint *ap2 = new AccessPoint(this, "AP_2", pos2, ACCESS_POINT_DIAMETER);
  delete pos2;

  Position *pos3 = new Position(2 * INTER_ACCESS_POINT_DISTANCE, 0.0);
  AccessPoint *ap3 = new AccessPoint(this, "AP_3", pos3, ACCESS_POINT_DIAMETER);
  delete pos3;

  Position *pos4 = new Position(3 * INTER_ACCESS_POINT_DISTANCE, 0.0);
  AccessPoint *ap4 = new AccessPoint(this, "AP_4", pos4, ACCESS_POINT_DIAMETER);
  delete pos4;

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
