/*
 * CarStoryPool.h
 *
 *  Created on: Apr 23, 2014
 *      Author: Kamran Amini <kam.cpp@gmail.com>
 */

#ifndef CAR_STORY_POOL_H_
#define CAR_STORY_POOL_H_

#include <vector>

class CarStory;

class CarStoryPool {
  public:
    static CarStoryPool* getInstance(void);

  private:
    static CarStoryPool *instance_;

  protected:
    CarStoryPool(void) {
    }
    virtual ~CarStoryPool(void) {
    }

  public:
    inline virtual void addCarStory(CarStory *carStory) {
      carStories_.push_back(carStory);
    }
    inline virtual CarStory* getCarStory(int index) const {
      return carStories_[index];
    }
    inline virtual void clear(void) {
      carStories_.clear();
    }
    CarStory* getRandomCarStory(void) const;

  private:
    std::vector<CarStory*> carStories_;
};

#endif /* CAR_STORY_POOL_H_ */
