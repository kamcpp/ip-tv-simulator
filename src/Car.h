/*
 * Car.h
 *
 *  Created on: Apr 10, 2014
 *      Author: Kamran Amini <kam.cpp@gmail.com>
 */

#ifndef CAR_H_
#define CAR_H_

#ifndef NULL
#define NULL 0
#endif

#include "WorldObject.h"
#include "NoCoveringAccessPointException.h"
#include "NotSupportedCommandException.h"
#include "NotSupportedPcbhProtocolCommandException.h"

class Lane;
class WorldInterface;
class Timer;
class NetworkDevice;
class IpTvWorldInterface;
class AccessPoint;
class TvChannel;
class DeviceAddress;
class Command;

class Car: public WorldObject {
  public:
    Car(WorldInterface *world, unsigned int id = 0, double birthMoment = 0.0, Lane *lane = NULL);
    virtual ~Car(void);

    inline unsigned int getId(void) const {
      return id_;
    }
    inline void setId(unsigned int id) {
      id_ = id;
    }

    inline unsigned int getLastEventIndex(void) const {
      return lastEventIndex_;
    }
    inline void setLastEventIndex(unsigned int lastEventIndex) {
      lastEventIndex_ = lastEventIndex;
    }

    inline bool usesIpTvService(void) const {
      return usesIpTvService_;
    }
    inline void setUsesIpTvService(bool usesIpTvService) {
      usesIpTvService_ = usesIpTvService;
    }

    inline TvChannel* getWatchingTvChannel(void) const {
      return watchingTvChannel_;
    }
    inline void setWatchingTvChannel(TvChannel *watchingTvChannel) {
      watchingTvChannel_ = watchingTvChannel;
    }

    inline bool isInLane(void) const {
      return inLane_;
    }
    inline void setInLane(bool inLane) {
      inLane_ = inLane;
    }

    inline double getBirthMoment(void) const {
      return birthMoment_;
    }
    inline void setBirthMoment(double birthMoment) {
      birthMoment_ = birthMoment;
    }

    inline Lane* getLane(void) const {
      return lane_;
    }
    inline void setLane(Lane *lane) {
      lane_ = lane;
    }

    inline Timer* getInternalTimer(void) const {
      return internalTimer_;
    }

    inline NetworkDevice* getNetworkDevice(void) const {
      return networkDevice_;
    }

    IpTvWorldInterface* getIpTvWorld(void) const;

    void join(TvChannel *tvChannel) throw (NoCoveringAccessPointException&);
    void leave(TvChannel *tvChannel) throw (NoCoveringAccessPointException&);
    void leaveCurrentTvChannel(void) throw (NoCoveringAccessPointException&);
    void sayIStillNeedTheTvChannel(void) throw (NoCoveringAccessPointException&);

    void checkForHandover(void) throw (NoCoveringAccessPointException&);

    virtual std::string getJson(void) const;
    virtual void checkIncomingMessages(void) throw (NotSupportedCommandException&);

  protected:
    void sendCommand(Command *command, bool checkForHandOver = true, DeviceAddress *targetAddress = NULL) throw (NoCoveringAccessPointException&);

  private:
    unsigned int id_;
    unsigned int lastEventIndex_;
    bool handingOver_;
    bool inLane_;
    bool usesIpTvService_;
    double birthMoment_;
    Lane *lane_;
    Timer *internalTimer_;
    TvChannel *watchingTvChannel_;
    NetworkDevice *networkDevice_;
    AccessPoint *currentAccessPoint_;
};

#endif /* CAR_H_ */
