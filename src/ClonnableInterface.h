/*
 * ClonnableInterface.h
 *
 *  Created on: Apr 11, 2014
 *      Author: Kamran Amini <kam.cpp@gmail.com>
 */

#ifndef CLONNABLE_INTERFACE_H_
#define CLONNABLE_INTERFACE_H_

class ClonnableInterface {
  public:
    virtual ~ClonnableInterface(void) {
    }

    virtual void* clone(void) = 0;
};

#endif /* CLONNABLE_INTERFACE_H_ */
