/*
 * CarStoryLoader.h
 *
 *  Created on: Apr 28, 2014
 *      Author: Kamran Amini <kam.cpp@gmail.com>
 */

#ifndef CAR_STORY_LOADER_H_
#define CAR_STORY_LOADER_H_

#include <string>

class CarStory;

class CarStoryLoader {
  public:
    static CarStoryLoader* getInstance(void);

  private:
    static CarStoryLoader *instance_;

  public:
    CarStoryLoader(std::string baseDirectoryPath) :
        counter_(1), baseDirectoryPath_(baseDirectoryPath) {
    }
    virtual ~CarStoryLoader(void) {
    }

    inline virtual void reset(void) {
      counter_ = 1;
    }

    virtual CarStory* readNext(void);

  private:
    unsigned int counter_;
    std::string baseDirectoryPath_;
};

#endif /* CAR_STORY_LOADER_H_ */
