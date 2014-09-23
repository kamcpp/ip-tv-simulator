/*
 * Environment.cpp
 *
 *  Created on: Apr 20, 2014
 *      Author: Kamran Amini <kam.cpp@gmail.com>
 */

#include <iostream>
#include <fstream>
#include <ctime>

#include "Environment.h"
#include "InMemoryConfiguration.h"
#include "Simulator.h"
#include "WirelessNetworkInfrastructure.h"
#include "CarStoryLoader.h"
#include "DefaultIpTvWorld.h"
#include "SimpleIpTvWorld.h"
#include "Timer.h"
#include "SimulationResult.h"
#include "config.h"
#include "RandomHelper.h"
#include "TvChannelPool.h"

Environment* Environment::instance_ = 0;

Environment::Environment(void) :
    networkInfra_(NULL), world_(NULL), simulator_(NULL) {
  RandomHelper::setRandomSeed(std::time(0));
  configuration_ = new InMemoryConfiguration();
}

Environment::~Environment(void) {
  delete configuration_;
}

double Environment::getCurrentSimulationTime(void) const {
  return getSimulator()->getTimer()->getCurrent();
}
void Environment::setup(void) {
  std::cout << "Generating channels ..." << std::endl;
  TvChannelPool::getInstance()->generateTvChannels(NUMBER_OF_CHANNELS);
  TvChannelPool::getInstance()->calculatePopularityForTvChannels();
  RandomHelper::setTimeSeed();
}

void Environment::startEverything(void) {
  unsigned runCounter = 0;
  std::time_t simulationStartTime = std::time(NULL);
  networkInfra_ = NULL;
  world_ = NULL;
  simulator_ = NULL;
  while (true) {
    SimulationResult::getInstance()->reset();
    networkInfra_ = new WirelessNetworkInfrastructure();
    world_ = new DefaultIpTvWorld();
    bool result = world_->prepare();
    if (result) {
      runCounter++;
      simulator_ = new Simulator();
      simulator_->setRunNumber(runCounter);
      simulator_->setWorld(world_);
      simulator_->getTimer()->setEnd(SIMULATION_END_TIME);
      simulator_->getTimer()->setStep(SIMULATION_STEP);
      std::cout << "Starting synch simulator ..." << std::endl;
      if (simulator_->getTimer()->getEnd() < 0) {
        std::cout << "ERROR: Simulation timer has no end." << std::endl;
        return;
      }

      std::time_t start = std::time(NULL);
      std::string json = simulator_->start();
      std::time_t end = std::time(NULL);

      std::cout << "\n";
      std::cout << "Simulation is finished." << std::endl;
      std::cout << std::endl;
      std::cout << "Simulation took " << (end - start) << " seconds = " << (end - start) / 60 << " minutes." << std::endl;
      std::cout << SimulationResult::getInstance()->getJson() << std::endl;
      std::cout << "-------------------" << std::endl;

      if (PRODUCE_SIMULATION_JSON) {
        std::stringstream ss;
        ss << OUTPUT_DIRECTORY << "/SIMULATION_JSON_" << simulationStartTime << "_RUN_" << runCounter << ".txt";
        std::fstream jsonFile(ss.str().c_str(), std::ios::out);
        jsonFile << json << std::endl;
        jsonFile.close();
      }
      if (PRODUCE_RESULT_FILE) {
        std::stringstream ss;
        ss << OUTPUT_DIRECTORY << "/RESULT_FILE_" << simulationStartTime << ".txt";
        std::fstream resultFile(ss.str().c_str(), std::ios::out | std::ios::app);
        resultFile << "Simulation took " << (end - start) << " seconds = " << (end - start) / 60 << " minutes." << std::endl;
        resultFile << SimulationResult::getInstance()->getJson() << std::endl;
        resultFile << "===============================" << std::endl;
        resultFile.close();
      }
    }

    if (networkInfra_ != NULL) {
      delete networkInfra_;
      networkInfra_ = NULL;
    }
    if (world_ != NULL) {
      delete world_;
      world_ = NULL;
    }
    if (simulator_ != NULL) {
      delete simulator_;
      simulator_ = NULL;
    }
  }
}
