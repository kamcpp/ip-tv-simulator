/*
 * WirelessNetworkInfrastructure.h
 *
 *  Created on: May 1, 2014
 *      Author: Kamran Amini <kam.cpp@gmail.com>
 */

#ifndef WIRELESS_NETWORK_INFRASTRUCTURE_H_
#define WIRELESS_NETWORK_INFRASTRUCTURE_H_

#include "AbstractNetworkInfrastructure.h"

class WirelessNetworkInfrastructure: public AbstractNetworkInfrastructure {
  public:
    WirelessNetworkInfrastructure(void);
    virtual ~WirelessNetworkInfrastructure(void);

    virtual void transferMessage(Message *message);
};

#endif /* WIRELESS_NETWORK_INFRASTRUCTURE_H_ */
