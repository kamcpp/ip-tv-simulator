/*
 * main.cpp
 *
 *  Created on: Apr 10, 2014
 *      Author: Kamran Amini <kam.cpp@gmail.com>
 */

#include <iostream>
#include <fstream>
#include <string>

#include "Environment.h"

int main(int argc, char **argv) {

  Environment::getInstance()->setup();
  Environment::getInstance()->startEverything();

  std::cout << "Press any key to exit ...";
  std::cin.get();

  return 0;
}

