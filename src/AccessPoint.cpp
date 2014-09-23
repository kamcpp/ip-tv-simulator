/*
 * AccessPoint.cpp
 *
 *  Created on: Apr 11, 2014
 *      Author: Kamran Amini <kam.cpp@gmail.com>
 */

#include <cmath>

#include "AccessPoint.h"
#include "Position.h"
#include "NetworkDevice.h"
#include "RandomHelper.h"
#include "Message.h"
#include "Environment.h"
#include "AbstractNetworkInfrastructure.h"
#include "DeviceAddress.h"
#include "config.h"
#include "TvChannel.h"
#include "Timer.h"
#include "Command.h"
#include "enums.h"
#include "Simulator.h"
#include "Commands/PreserveChannelBeforeHandoverProtocolCommand.h"
#include "Commands/JoinAcceptedPcbhpCommand.h"
#include "Commands/JoinRejectedPcbhpCommand.h"
#include "Commands/LeaveAcceptedPcbhpCommand.h"
#include "Commands/LeaveRejectedPcbhpCommand.h"
#include "Commands/UnderlyingNegotiationCommand.h"
#include "Commands/WhoNeedsTheChannelPcbhpCommand.h"

AccessPoint::AccessPoint(WorldInterface *world, std::string name, Position *position, double rangeDiameter)
    : WorldObject(world, position), rangeDiameter_(rangeDiameter), lastWhoNeedsChannelsBroadcast_(0), name_(name) {
  internalTimer_ = new Timer();
  networkDevice_ = new NetworkDevice((unsigned int) (RandomHelper::next(50000)));
}

AccessPoint::~AccessPoint(void) {
  delete networkDevice_;
}

bool AccessPoint::isPositionInRange(Position *p) {
  return getPosition()->isInNeighborhood(p, getRangeDiameter() / 2);
}

void AccessPoint::checkIncomingMessages() throw (NotSupportedCommandException&, NotSupportedPcbhProtocolCommandException&) {
  while (networkDevice_->hasMorMessages()) {
    Message *message = networkDevice_->takeMessage();
    PreserveChannelBeforeHandoverProtocolCommand *pcbhpcommand = dynamic_cast<PreserveChannelBeforeHandoverProtocolCommand*>(message->getCommand());
    UnderlyingNegotiationCommand *underlyingNegotiationCommand = dynamic_cast<UnderlyingNegotiationCommand*>(message->getCommand());
    if (pcbhpcommand == NULL && underlyingNegotiationCommand == NULL) {
      throw NotSupportedCommandException();
    }
    if (underlyingNegotiationCommand != NULL) {
      std::set<DeviceAddress*>::iterator it;
      switch (underlyingNegotiationCommand->getType()) {
      case UnderlyingNegotationCommandType_Hello:
        addressesInRange_.insert(underlyingNegotiationCommand->getDeviceAddress());
        break;
      case UnderlyingNegotationCommandType_Bye:
        it = addressesInRange_.find(underlyingNegotiationCommand->getDeviceAddress());
        addressesInRange_.erase(it);
        break;
      case UnderlyingNegotationCommandType_None:
      default:
        break;
      }
    } else if (pcbhpcommand != NULL) {

      switch (pcbhpcommand->getType()) {
      case PreserveChannelBeforeHandoverProtocolCommandType_Join:
        if (tvChannelWatchers_.find(pcbhpcommand->getTvChannel()) == tvChannelWatchers_.end()) {
          tvChannelWatchers_[pcbhpcommand->getTvChannel()] = 0;
        }
        if (tvChannelWatchers_[pcbhpcommand->getTvChannel()] < pcbhpcommand->getTvChannel()->getMaximumNumberOfWatchers()) {
          tvChannelWatchers_[pcbhpcommand->getTvChannel()]++;
          if (VERBOSE_JOIN_CHANNEL) {
            std::cout << Environment::getInstance()->getCurrentSimulationTime() << ": AP[" << getName() << "] -> Sending JOIN_ACCEPTED command on channel[" << pcbhpcommand->getTvChannel()->getName() << "] to NET_DEV[" << message->getSourceAddress()->getId() << "] ..." << std::endl;
          }
          Command *command = new JoinAcceptedPcbhpCommand(pcbhpcommand->getTvChannel());
          Message *newMessage = new Message(getNetworkDevice()->getAddress(), message->getSourceAddress(), command, Environment::getInstance()->getCurrentSimulationTime());
          Environment::getInstance()->getNetworkInfra()->transferMessage(newMessage);
        } else {
          if (VERBOSE_JOIN_CHANNEL) {
            std::cout << Environment::getInstance()->getCurrentSimulationTime() << ": AP[" << getName() << "] -> Sending JOIN_REJECTED command on channel[" << pcbhpcommand->getTvChannel()->getName() << "] to NET_DEV[" << message->getSourceAddress()->getId() << "] ..." << std::endl;
          }
          Command *command = new JoinRejectedPcbhpCommand(pcbhpcommand->getTvChannel());
          Message *newMessage = new Message(getNetworkDevice()->getAddress(), message->getSourceAddress(), command, Environment::getInstance()->getCurrentSimulationTime());
          Environment::getInstance()->getNetworkInfra()->transferMessage(newMessage);
        }
        break;
      case PreserveChannelBeforeHandoverProtocolCommandType_Leave:
        if (tvChannelWatchers_.find(pcbhpcommand->getTvChannel()) == tvChannelWatchers_.end()) {
          if (VERBOSE_LEAVE_CHANNEL) {
            std::cout << Environment::getInstance()->getCurrentSimulationTime() << ": AP[" << getName() << "] -> Non-Watched Channel ... Sending LEAVE_REJECTED command on channel[" << pcbhpcommand->getTvChannel()->getName() << "] to NET_DEV[" << message->getSourceAddress()->getId() << "] ..."
                << std::endl;
          }
          Command *command = new LeaveRejectedPcbhpCommand(pcbhpcommand->getTvChannel());
          Message *newMessage = new Message(getNetworkDevice()->getAddress(), message->getSourceAddress(), command, Environment::getInstance()->getCurrentSimulationTime());
          Environment::getInstance()->getNetworkInfra()->transferMessage(newMessage);
        } else {
          if (tvChannelWatchers_[pcbhpcommand->getTvChannel()] > 0) {
            tvChannelWatchers_[pcbhpcommand->getTvChannel()]--;
            if (VERBOSE_LEAVE_CHANNEL) {
              std::cout << Environment::getInstance()->getCurrentSimulationTime() << ": AP[" << getName() << "] -> Sending LEAVE_ACCEPTED command on channel[" << pcbhpcommand->getTvChannel()->getName() << "] to NET_DEV[" << message->getSourceAddress()->getId() << "] ..." << std::endl;
            }
            Command *command = new LeaveAcceptedPcbhpCommand(pcbhpcommand->getTvChannel());
            Message *newMessage = new Message(getNetworkDevice()->getAddress(), message->getSourceAddress(), command, Environment::getInstance()->getCurrentSimulationTime());
            Environment::getInstance()->getNetworkInfra()->transferMessage(newMessage);
          } else {
            if (VERBOSE_LEAVE_CHANNEL) {
              std::cout << Environment::getInstance()->getCurrentSimulationTime() << ": AP[" << getName() << "] -> Non-Watched List Channel ... Sending LEAVE_REJECTED command on channel[" << pcbhpcommand->getTvChannel()->getName() << "] to NET_DEV[" << message->getSourceAddress()->getId() << "] ..."
                  << std::endl;
            }
            Command *command = new LeaveRejectedPcbhpCommand(pcbhpcommand->getTvChannel());
            Message *newMessage = new Message(getNetworkDevice()->getAddress(), message->getSourceAddress(), command, Environment::getInstance()->getCurrentSimulationTime());
            Environment::getInstance()->getNetworkInfra()->transferMessage(newMessage);
          }
        }
        break;
      default:
        break;
      }
    }
    networkDevice_->purgeMessage(message);
  }
}

void AccessPoint::broadcast(Command *command) throw (NotSupportedCommandException&, NotSupportedPcbhProtocolCommandException&) {
  for (std::set<DeviceAddress*>::iterator it = addressesInRange_.begin(); it != addressesInRange_.end(); it++) {
      Message *message = new Message(getNetworkDevice()->getAddress(), *it, command, Environment::getInstance()->getCurrentSimulationTime());
      Environment::getInstance()->getNetworkInfra()->transferMessage(message);
  }
}

void AccessPoint::askWhoNeedsChannels(void){
  std::vector<TvChannel*> watchingChannels = getWatchingChannels();
  for (std::vector<TvChannel*>::iterator it = watchingChannels.begin(); it != watchingChannels.end(); it++) {
    Command *command = new WhoNeedsTheChannelPcbhpCommand(*it);
    broadcast(command);
    lastWhoNeedsChannelsBroadcast_ = Environment::getInstance()->getSimulator()->getTimer()->getCurrent();
  }
}
