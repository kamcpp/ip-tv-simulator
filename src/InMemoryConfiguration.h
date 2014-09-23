/*
 * InMemoryConfiguration.h
 *
 *  Created on: Apr 20, 2014
 *      Author: Kamran Amini <kam.cpp@gmail.com>
 */

#ifndef IN_MEMORY_CONFIGURATION_H_
#define IN_MEMORY_CONFIGURATION_H_

#include "ConfigurationInterface.h"
#include "config.h"

class InMemoryConfiguration: public ConfigurationInterface {
  public:
    InMemoryConfiguration(void) {
    }
    virtual ~InMemoryConfiguration(void) {
    }

    inline virtual std::string getCarStoriesBaseDirectory(void) const {
      return TRACE_FILES_PATH;
    }
};

#endif /* IN_MEMORY_CONFIGURATION_H_ */
