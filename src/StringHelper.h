/*
 * StringHelper.h
 *
 *  Created on: Apr 19, 2014
 *      Author: Kamran Amini <kam.cpp@gmail.com>
 */

#ifndef STRING_HELPER_H_
#define STRING_HELPER_H_

#include <string>
#include <vector>

class StringHelper {
  public:
    StringHelper(void) {
    }
    virtual ~StringHelper(void) {
    }

    std::vector<std::string> split(const std::string &s, char delim);

  protected:
    std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems);
};

#endif /* STRING_HELPER_H_ */
