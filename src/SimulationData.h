/*
 * SimulationData.h
 *
 *  Created on: Apr 21, 2014
 *      Author: Kamran Amini <kam.cpp@gmail.com>
 */

#ifndef SIMULATION_DATA_H_
#define SIMULATION_DATA_H_

class Simulator;

class SimulationData {
  public:
    SimulationData(Simulator *simulator, double currentTime = 0) :
        runNumber_(0), currentTime_(currentTime), simulator_(simulator) {
    }
    virtual ~SimulationData(void) {
    }

    inline unsigned int getRunNumber(void) const {
      return runNumber_;
    }
    inline void setRunNumber(unsigned int runNumber) {
      runNumber_ = runNumber;
    }

    inline double getCurrentTime(void) const {
      return currentTime_;
    }
    inline void setCurrentTime(double currentTime) {
      currentTime_ = currentTime;
    }

    inline Simulator* getSimulator(void) const {
      return simulator_;
    }

  private:
    unsigned int runNumber_;
    double currentTime_;
    Simulator *simulator_;
};

#endif /* SIMULATION_DATA_INTERFACE_H_ */
