/*
 * Environment.h
 *
 *  Created on: Apr 20, 2014
 *      Author: Kamran Amini <kam.cpp@gmail.com>
 */

#ifndef ENVIRONEMNT_H_
#define ENVIRONEMNT_H_

#ifndef NULL
#define NULL 0
#endif

class Simulator;
class WorldInterface;
class AbstractNetworkInfrastructure;
class ConfigurationInterface;

class Environment {
  private:
    static Environment* instance_;

  public:
    static Environment* getInstance(void) {
      if (instance_ == NULL) {
        instance_ = new Environment();
      }
      return instance_;
    }

  protected:
    Environment(void);
    virtual ~Environment(void);

  public:
    inline Simulator* getSimulator(void) const {
      return simulator_;
    }
    inline void setSimulator(Simulator *simulator) {
      simulator_ = simulator;
    }

    inline WorldInterface* getWorld(void) const {
      return world_;
    }
    inline void setWorld(WorldInterface *world) {
      world_ = world;
    }

    inline ConfigurationInterface* getConfiguration(void) const {
      return configuration_;
    }
    inline void setConfiguration(ConfigurationInterface *configuration) {
      configuration_ = configuration;
    }

    inline AbstractNetworkInfrastructure* getNetworkInfra(void) const {
      return networkInfra_;
    }
    inline void setNetworkInfra(AbstractNetworkInfrastructure *networkInfra) {
      networkInfra_ = networkInfra;
    }

    double getCurrentSimulationTime(void) const;

    virtual void setup(void);
    virtual void startEverything(void);

  private:
    ConfigurationInterface *configuration_;
    AbstractNetworkInfrastructure *networkInfra_;
    WorldInterface *world_;
    Simulator *simulator_;
};

#endif /* ENVIRONEMNT_H_ */
