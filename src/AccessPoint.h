/*
 * AccessPoint.h
 *
 *  Created on: Apr 11, 2014
 *      Author: Kamran Amini <kam.cpp@gmail.com>
 */

#ifndef ACCESS_POINT_H_
#define ACCESS_POINT_H_

#include <string>
#include <vector>
#include <map>
#include <set>

#include "WorldObject.h"
#include "NotSupportedCommandException.h"
#include "NotSupportedPcbhProtocolCommandException.h"

class NetworkDevice;
class TvChannel;
class Timer;
class DeviceAddress;
class Command;

class AccessPoint: public WorldObject {
  public:
    AccessPoint(WorldInterface *world, std::string name, Position *position, double rangeDiameter = 100);
    virtual ~AccessPoint(void);

    inline double getRangeDiameter(void) const {
      return rangeDiameter_;
    }
    inline void setRangeDiameter(double rangeDiameter) {
      rangeDiameter_ = rangeDiameter;
    }

    inline std::string getName(void) const {
      return name_;
    }
    inline void setName(std::string name) {
      name_ = name;
    }

    inline Timer* getInternalTimer(void) const {
      return internalTimer_;
    }

    inline NetworkDevice* getNetworkDevice(void) const {
      return networkDevice_;
    }

    bool isPositionInRange(Position *p);

    virtual void checkIncomingMessages(void) throw (NotSupportedCommandException&, NotSupportedPcbhProtocolCommandException&);
    virtual void broadcast(Command *command) throw (NotSupportedCommandException&, NotSupportedPcbhProtocolCommandException&);
    virtual void askWhoNeedsChannels(void);

    inline virtual bool shouldAskAboutWhoNeedsChannels(void) const {
      // TODO
      return true;
    }

    virtual std::string getJson(void) const {
      return "";
    }
  protected:

    inline std::vector<TvChannel*> getWatchingChannels(void) {
      std::vector<TvChannel*> channels;
      for (std::map<TvChannel*, unsigned int>::iterator it = tvChannelWatchers_.begin(); it != tvChannelWatchers_.end(); it++) {
        channels.push_back(it->first);
      }
      return channels;
    }

  private:
    double rangeDiameter_;		// Unit: Meter(s)
    double lastWhoNeedsChannelsBroadcast_;
    std::string name_;
    Timer *internalTimer_;
    NetworkDevice *networkDevice_;
    std::map<TvChannel*, unsigned int> tvChannelWatchers_;
    std::set<DeviceAddress*> addressesInRange_;
};

#endif /* ACCESS_POINT_H_ */
