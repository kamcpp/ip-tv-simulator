/*
 * Car.cpp
 *
 *  Created on: Apr 22, 2014
 *      Author: Kamran Amini <kam.cpp@gmail.com>
 */

#include <string>
#include <sstream>
#include <iostream>

#include "Car.h"
#include "Timer.h"
#include "Position.h"
#include "Velocity.h"
#include "NetworkDevice.h"
#include "RandomHelper.h"
#include "IpTvWorldInterface.h"
#include "Message.h"
#include "AbstractNetworkInfrastructure.h"
#include "AccessPoint.h"
#include "Environment.h"
#include "Simulator.h"
#include "Timer.h"
#include "SimulationResult.h"
#include "TvChannel.h"
#include "Lane.h"
#include "config.h"
#include "Commands/JoinPcbhpCommand.h"
#include "Commands/LeavePcbhpCommand.h"
#include "Commands/IStillNeedTheChannelPcbhpCommand.h"
#include "Commands/PreserveChannelBeforeHandoverProtocolCommand.h"
#include "Commands/HelloAccessPointCommand.h"
#include "Commands/ByeAccessPointCommand.h"
#include "Commands/IStillNeedTheChannelPcbhpCommand.h"

Car::Car(WorldInterface *world, unsigned int id, double birthMoment, Lane *lane)
    : WorldObject(world), id_(id), lastEventIndex_(0), handingOver_(false), inLane_(false), usesIpTvService_(false), birthMoment_(birthMoment), lane_(lane), watchingTvChannel_(
    NULL), currentAccessPoint_(NULL) {
  internalTimer_ = new Timer();
  networkDevice_ = new NetworkDevice((unsigned int) (RandomHelper::next(50000)));
}

Car::~Car(void) {
  delete internalTimer_;
  delete networkDevice_;
}

std::string Car::getJson(void) const {
  std::stringstream ss;
  ss.setf(std::ios::fixed, std::ios::floatfield);
  ss.precision(10);

  ss << std::endl;
  ss << "{";
  ss << "\"type\": \"Car\", \"id\": \"" << getId() << "\", \"birthMoment\": \"" << getBirthMoment() << "\", \"internalTimerCurrent\": \"" << getInternalTimer()->getCurrent() << "\", \"velocity\": " + getVelocity()->getJson() << ", \"position\": " << getPosition()->getJson();
  ss << "}";
  ss << std::endl;
  return ss.str();
}

void Car::checkIncomingMessages(void) throw (NotSupportedCommandException&) {
  while (networkDevice_->hasMorMessages()) {
    Message *message = networkDevice_->takeMessage();
    PreserveChannelBeforeHandoverProtocolCommand *pcbhpCommand = dynamic_cast<PreserveChannelBeforeHandoverProtocolCommand*>(message->getCommand());
    if (pcbhpCommand == NULL) {
      throw NotSupportedCommandException();
    }
    switch (pcbhpCommand->getType()) {
    case PreserveChannelBeforeHandoverProtocolCommandType_JoinAccepted:
      watchingTvChannel_ = pcbhpCommand->getTvChannel();
      break;
    case PreserveChannelBeforeHandoverProtocolCommandType_JoinRejected:
      SimulationResult::getInstance()->incrementNumberOfBlockedJoinRequests();
      if (handingOver_) {
        SimulationResult::getInstance()->incrementNumberOfLostJoinRequestsWhileHandingOver();
      }
      break;
    case PreserveChannelBeforeHandoverProtocolCommandType_LeaveAccepted:
      break;
    case PreserveChannelBeforeHandoverProtocolCommandType_LeaveRejected:
      break;
    case PreserveChannelBeforeHandoverProtocolCommandType_WhoNeedsTheChannel:
      if (pcbhpCommand->getTvChannel() == watchingTvChannel_) {
        try {
          sayIStillNeedTheTvChannel();
        } catch (NoCoveringAccessPointException &e) {
          std::cout << "ERROR at Car::checkIncomingMessages(...): LOST ANTENA" << std::endl;
        }
      }
      break;
    default:
      break;
    }
    handingOver_ = false;
    networkDevice_->purgeMessage(message);
  }
}

IpTvWorldInterface* Car::getIpTvWorld(void) const {
  IpTvWorldInterface *ipTvWorld = dynamic_cast<IpTvWorldInterface*>(getWorld());
  return ipTvWorld;
}

void Car::join(TvChannel *tvChannel) throw (NoCoveringAccessPointException&) {
  leave(watchingTvChannel_);
  sendCommand(new JoinPcbhpCommand(tvChannel));
  SimulationResult::getInstance()->incrementNumberOfRequests();
  if (VERBOSE_JOIN_CHANNEL) {
    std::cout << "JOIN at " << Environment::getInstance()->getCurrentSimulationTime() << ": Lane[" << getLane()->getName() << "].Car[" << getId() << "] at pos " << getPosition()->getX() << " -> Sending JOIN command on channel[" << tvChannel->getName() << "] to AP[" << currentAccessPoint_->getName()
        << "] ..." << std::endl;
  }
}

void Car::leave(TvChannel *tvChannel) throw (NoCoveringAccessPointException&) {
  if (watchingTvChannel_ == tvChannel && watchingTvChannel_ != NULL) {
    sendCommand(new LeavePcbhpCommand(tvChannel));
    SimulationResult::getInstance()->incrementNumberOfRequests();
    if (VERBOSE_LEAVE_CHANNEL) {
      std::cout << "LEAVE at " << Environment::getInstance()->getCurrentSimulationTime() << ": Lane[" << getLane()->getName() << "].Car[" << getId() << "] at pos " << getPosition()->getX() << " -> Sending LEAVE command on channel[" << tvChannel->getName() << "] to AP["
          << currentAccessPoint_->getName() << "] ..." << std::endl;
    }
  }
}

void Car::leaveCurrentTvChannel(void) throw (NoCoveringAccessPointException&) {
  leave(watchingTvChannel_);
}

void Car::sayIStillNeedTheTvChannel(void) throw (NoCoveringAccessPointException&) {
  if (watchingTvChannel_ != NULL) {
    sendCommand(new IStillNeedTheChannelPcbhpCommand(watchingTvChannel_));
    if (VERBOSE_I_STILL_NEED_CHANNEL) {
      std::cout << "I_STILL at " << Environment::getInstance()->getCurrentSimulationTime() << ": Lane[" << getLane()->getName() << "].Car[" << getId() << "] -> Sending I_STILL_NEED_THE_CHANNEL command on channel[" << watchingTvChannel_->getName() << "] to AP[" << currentAccessPoint_->getName()
          << "] ..." << std::endl;
    }
  }
}

void Car::checkForHandover(void) throw (NoCoveringAccessPointException&) {
  std::vector<AccessPoint*> accessPoints = getIpTvWorld()->getCoveringAccessPointsInPosition(getPosition());
  if (accessPoints.size() == 0) {
    watchingTvChannel_ = NULL;
    throw NoCoveringAccessPointException();
  }
  /* Note: If there are more than one access point available,
   * we choose first, in this implementation of course.
   */
  if (currentAccessPoint_ == NULL) {
    currentAccessPoint_ = accessPoints[0];
    sendCommand(new HelloAccessPointCommand(getNetworkDevice()->getAddress()), false);
  } else {
    if (currentAccessPoint_ != accessPoints[0]) {
      handingOver_ = true;
      sendCommand(new ByeAccessPointCommand(getNetworkDevice()->getAddress()), false);
      currentAccessPoint_ = accessPoints[0];
      sendCommand(new HelloAccessPointCommand(getNetworkDevice()->getAddress()), false);
      SimulationResult::getInstance()->incrementNumberOfHandovers();
      if (VERBOSE_HANDOVER) {
        std::cout << "HANDOVER: Lane[" << getLane()->getName() << "].Car[" << getId() << "] at " << getPosition()->getX() << " -> Handing over at " << Environment::getInstance()->getCurrentSimulationTime() << "..." << std::endl;
      }
    } else {
      handingOver_ = false;
    }
  }
}

void Car::sendCommand(Command *command, bool checkForHandOver, DeviceAddress *targetAddress) throw (NoCoveringAccessPointException&) {
  if (targetAddress == NULL) {
    if (checkForHandOver) {
      checkForHandover();
    }
    targetAddress = currentAccessPoint_->getNetworkDevice()->getAddress();
  }
  Message *message = new Message(getNetworkDevice()->getAddress(), targetAddress, command, Environment::getInstance()->getCurrentSimulationTime());
  Environment::getInstance()->getNetworkInfra()->transferMessage(message);
}
