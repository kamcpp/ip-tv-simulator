/*
 * ConfigurationInterface.h
 *
 *  Created on: Apr 20, 2014
 *      Author: Kamran Amini <kam.cpp@gmail.com>
 */

#ifndef CONFIGURATION_INTERFACE_H_
#define CONFIGURATION_INTERFACE_H_

#include <string>

class ConfigurationInterface {
  public:
    ConfigurationInterface(void) {
    }
    virtual ~ConfigurationInterface(void) {
    }
  public:
    virtual std::string getCarStoriesBaseDirectory(void) const = 0;
};

#endif /* CONFIGURATION_INTERFACE_H_ */
