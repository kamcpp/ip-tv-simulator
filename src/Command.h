/*
 * Command.h
 *
 *  Created on: May 3, 2014
 *      Author: Kamran Amini <kam.cpp@gmail.com>
 */

#ifndef COMMAND_H_
#define COMMAND_H_

class Command {
  public:
    int numberOfUsages_;
  public:
    Command(void) : numberOfUsages_(0) {
    }
    virtual ~Command(void) {
    }
};

#endif /* COMMAND_H_ */
