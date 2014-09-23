/*
 * Simulator.cpp
 *
 *  Created on: Apr 11, 2014
 *      Author: Kamran Amini <kam.cpp@gmail.com>
 */

#define NULL 0

#include <iostream>
#include <sstream>
#include <string>

#include "Simulator.h"
#include "WorldInterface.h"
#include "Timer.h"
#include "SimulationData.h"
#include "utils.h"
#include "config.h"

Simulator::Simulator(void) :
    runNumber_(0) {
  world_ = NULL;
  timer_ = new Timer();
}

Simulator::~Simulator(void) {
  delete timer_;
}

std::string Simulator::start(void) {
  return startSimulation();
}

void Simulator::startAsynch(void) {
  // TODO This method should be implemented in order to start simulation in a separate thread.
}

std::string Simulator::startSimulation(void) {
  std::stringstream ss;
  if (PRODUCE_SIMULATION_JSON) {
    ss << "{";
    ss << "\"cycles\": ";
    ss << "[";
  }
  timer_->reset();
  while (timer_->hasMoreSteps()) {
    SimulationData *simulationData = new SimulationData(this, timer_->getCurrent());
    simulationData->setRunNumber(runNumber_);
    world_->cycle(simulationData);
    if (PRODUCE_SIMULATION_JSON) {
      ss << "{";
      ss << "\"time\": \"" << timer_->getCurrent() << "\", ";
      ss << "\"world\": " << world_->getJson();
      ss << "}";
    }
    delete simulationData;
    timer_->advance();
    if (PRODUCE_SIMULATION_JSON) {
      if (timer_->hasMoreSteps()) {
        ss << ", ";
      }
    }
    // mySleep(1);
  }
  if (PRODUCE_SIMULATION_JSON) {
    ss << "]";
    ss << "}";
    ss << std::endl;
  }
  return ss.str();
}
