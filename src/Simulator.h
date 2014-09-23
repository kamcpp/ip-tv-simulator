/*
 * Simulator.h
 *
 *  Created on: Apr 10, 2014
 *      Author: Kamran Amini <kam.cpp@gmail.com>
 */

#ifndef SIMULATOR_H_
#define SIMULATOR_H_

#include <vector>
#include <string>

class WorldInterface;
class Timer;

class Simulator {
  public:
    Simulator(void);
    virtual ~Simulator(void);

    inline unsigned int getRunNumber(void) const {
      return runNumber_;
    }
    inline void setRunNumber(unsigned int runNumber) {
      runNumber_ = runNumber;
    }

    inline WorldInterface* getWorld(void) const {
      return world_;
    }
    inline void setWorld(WorldInterface *world) {
      world_ = world;
    }

    inline Timer* getTimer(void) const {
      return timer_;
    }

    inline std::string getFinalJsonReport(void) const {
      return finalJsonReport_;
    }

    std::string start(void);
    void startAsynch(void);

  protected:
    virtual std::string startSimulation(void);

  private:
    unsigned int runNumber_;
    std::string finalJsonReport_;
    WorldInterface *world_;
    Timer *timer_;
};

#endif /* SIMULATOR_H_ */
