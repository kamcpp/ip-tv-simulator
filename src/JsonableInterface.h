/*
 * JsonableInterface.h
 *
 *  Created on: Apr 25, 2014
 *      Author: Kamran Amini <kam.cpp@gmail.com>
 */

#ifndef JSONABLE_INTERFACE_H_
#define JSONABLE_INTERFACE_H_

#include <string>

/*
 * An interface for all objects which they can be serialized to JSON.
 */
class JsonableInterface {
  public:
    JsonableInterface(void) {
    }
    virtual ~JsonableInterface(void) {
    }

    /*
     * Serialization method. This method should return a JSON string
     * representing the desired object.
     */
    virtual std::string getJson(void) const = 0;
};

#endif /* JSONABLE_INTERFACE_H_ */
