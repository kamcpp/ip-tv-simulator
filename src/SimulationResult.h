/*
 * SimulationResult.h
 *
 *  Created on: May 5, 2014
 *      Author: Kamran Amini <kam.cpp@gmail.com>
 */

#ifndef SIMULATION_RESULT_H_
#define SIMULATION_RESULT_H_

#ifndef NULL
#define NULL 0
#endif

#include <sstream>
#include <string>

#include "JsonableInterface.h"
#include "config.h"

class SimulationResult: public JsonableInterface {
  public:
    inline static SimulationResult* getInstance(void) {
      if (instance_ == NULL) {
        instance_ = new SimulationResult();
      }
      return instance_;
    }

  private:
    static SimulationResult* instance_;

  public:
    SimulationResult(void) :
        numberOfLanes_(0), numberOfCars_(0), numberOfRequests_(0), numberOfHandovers_(0), numberOfBlockedJoinRequests_(0), numberOfLostJoinRequestsWhileHandingOver_(0) {
    }
    virtual ~SimulationResult(void) {
    }

    void reset(void) {
      numberOfLanes_ = 0;
      numberOfCars_ = 0;
      numberOfRequests_ = 0;
      numberOfHandovers_ = 0;
      numberOfBlockedJoinRequests_ = 0;
      numberOfLostJoinRequestsWhileHandingOver_ = 0;
    }

    inline unsigned int getNumberOfLanes(void) const {
      return numberOfLanes_;
    }

    inline void incrementNumberOfLanes(void) {
      numberOfLanes_++;
    }

    inline unsigned int getNumberOfCars(void) const {
      return numberOfCars_;
    }
    inline void incrementNumberOfCars(void) {
      numberOfCars_++;
    }
    inline void decrementNumberOfCars(void) {
      numberOfCars_--;
    }

    inline unsigned int getNumberOfRequests(void) const {
      return numberOfRequests_;
    }
    inline void incrementNumberOfRequests(void) {
      numberOfRequests_++;
    }

    inline unsigned int getNumberOfHandovers(void) const {
      return numberOfHandovers_;
    }
    inline void incrementNumberOfHandovers(void) {
      numberOfHandovers_++;
    }

    inline unsigned int getNumberOfBlockedJoinRequests(void) const {
      return numberOfBlockedJoinRequests_;
    }
    inline void incrementNumberOfBlockedJoinRequests(void) {
      numberOfBlockedJoinRequests_++;
    }

    inline unsigned int getNumberOfLostJoinRequestsWhileHandingOver(void) const {
      return numberOfLostJoinRequestsWhileHandingOver_;
    }
    inline void incrementNumberOfLostJoinRequestsWhileHandingOver(void) {
      numberOfLostJoinRequestsWhileHandingOver_++;
    }

    inline double getCbp(void) const {
      return (double) getNumberOfBlockedJoinRequests() / (double) getNumberOfRequests();
    }
    inline double getDp(void) const {
      return (double) getNumberOfLostJoinRequestsWhileHandingOver() / (double) getNumberOfHandovers();
    }
    inline double getBp(void) const {
      return (double) (getNumberOfBlockedJoinRequests() + getNumberOfLostJoinRequestsWhileHandingOver()) / (double) (getNumberOfRequests() + getNumberOfHandovers());
    }

    virtual std::string getJson(void) const {
      std::stringstream ss;
      ss << "{";
      ss << "\"numberOfChannels\": \"" << NUMBER_OF_CHANNELS << "\", " << std::endl;
      ss << "\"maximumNumberOfWatchersPerChannel\": \"" << MAX_WATCHERS_PER_CHANNEL << "\", " << std::endl;
      ss << "\"simulationDuration\": \"" << SIMULATION_END_TIME << "\", " << std::endl;
      ss << "\"numberOfRequests\": \"" << numberOfRequests_ << "\", " << std::endl;
      ss << "\"numberOfHandovers\": \"" << numberOfHandovers_ << "\", " << std::endl;
      ss << "\"numberOfBlockedJoinRequests\": \"" << numberOfBlockedJoinRequests_ << "\", " << std::endl;
      ss << "\"numberOfLostJoinRequestsWhileHandingOver\": \"" << numberOfLostJoinRequestsWhileHandingOver_ << "\", " << std::endl;
      ss << "\"cbp\": \"" << getCbp() << "\", " << std::endl;
      ss << "\"dp\": \"" << getDp() << "\", " << std::endl;
      ss << "\"bp\": \"" << getBp() << "\"";
      ss << "}";
      return ss.str();
    }

  private:
    unsigned int numberOfLanes_;
    unsigned int numberOfCars_;
    unsigned int numberOfRequests_;
    unsigned int numberOfHandovers_;
    unsigned int numberOfBlockedJoinRequests_;
    unsigned int numberOfLostJoinRequestsWhileHandingOver_;
};

#endif /* SIMULATION_RESULT_H_ */
