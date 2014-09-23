/*
 * CarStoryFileReaderInterface.h
 *
 *  Created on: Apr 18, 2014
 *      Author: Kamran Amini <kam.cpp@gmail.com>
 */

#ifndef CAR_STORY_FILE_READER_INTERFACE_H_
#define CAR_STORY_FILE_READER_INTERFACE_H_

class CarStory;

class CarStoryFileReaderInterface {
  public:
    CarStoryFileReaderInterface(void) {
    }
    virtual ~CarStoryFileReaderInterface(void) {
    }

    virtual CarStory* read(void) = 0;
};

#endif /* CAR_STORY_FILE_READER_INTERFACE_H_ */
