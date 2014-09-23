/*
 * utils.cpp
 *
 *  Created on: Apr 27, 2014
 *      Author: Kamran Amini <kam.cpp@gmail.com>
 */

#include "utils.h"

#include <iostream>

#ifdef _WIN32
#include <Windows.h>
#endif

#ifdef unix
#include <unistd.h>
#endif

void mySleep(int milliseconds) {
#ifdef _WIN32
  Sleep(milliseconds);
#endif
#ifdef unix
  usleep(milliseconds * 1000);
#endif
}

