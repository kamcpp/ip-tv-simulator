/*
 * StringHelper.cpp
 *
 *  Created on: Apr 19, 2014
 *      Author: Kamran Amini <kam.cpp@gmail.com>
 */

#include "StringHelper.h"

#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>

std::vector<std::string> StringHelper::split(const std::string &s, char delim) {
  std::vector<std::string> elems;
  split(s, delim, elems);
  return elems;
}

std::vector<std::string> & StringHelper::split(const std::string &s, char delim, std::vector<std::string> &elems) {
  std::stringstream ss(s);
  std::string item;
  while (std::getline(ss, item, delim)) {
    elems.push_back(item);
  }
  return elems;
}
