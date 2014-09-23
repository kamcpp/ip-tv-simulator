/*
 * TvChannel.h
 *
 *  Created on: May 9, 2014
 *      Author: Kamran Amini <kam.cpp@gmail.com>
 */

#ifndef TV_CHANNEL_H_
#define TV_HANNEL_H_

#include <string>
#include <sstream>

#include "JsonableInterface.h"

class TvChannel: public JsonableInterface {
  public:
    TvChannel(unsigned int number = 0, std::string name = "") :
        number_(number), popularity_(0), maximumNumberOfWatchers_(0) {
      if (name.length() == 0 && number > 0) {
        std::stringstream ss;
        ss << "CHANNEL_" << number;
        name_ = ss.str();
      }
    }
    virtual ~TvChannel(void) {
    }

    inline unsigned int getNumber(void) const {
      return number_;
    }
    inline void setNumber(unsigned int number) {
      number_ = number;
    }

    inline unsigned int getPopularity(void) const {
      return popularity_;
    }
    inline void setPopularity(unsigned int popularity) {
      popularity_ = popularity;
    }

    inline unsigned int getMaximumNumberOfWatchers(void) const {
      return maximumNumberOfWatchers_;
    }
    inline void setMaximumNumberOfWatchers(unsigned int maximumNumberOfWatchers) {
      maximumNumberOfWatchers_ = maximumNumberOfWatchers;
    }

    inline std::string getName(void) const {
      return name_;
    }

    inline void setName(std::string name) {
      name_ = name;
    }

    virtual std::string getJson(void) const {
      std::stringstream ss;
      ss << "{";
      ss << "\"number\": \"" << number_ << "\", ";
      ss << "\"popularity\": \"" << popularity_ << "\", ";
      ss << "\"name\": \"" << name_ << "\", ";
      ss << "\"maximumNumberOfWatchers\": \"" << maximumNumberOfWatchers_ << "\", ";
      ss << "}";
      return ss.str();
    }

  private:
    unsigned int number_;
    unsigned int popularity_;                   // NOTICE: Zero is not valid for popularity.
    unsigned int maximumNumberOfWatchers_;
    std::string name_;
};

#endif /* TV_CHANNEL_H_ */
