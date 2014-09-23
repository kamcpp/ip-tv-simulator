/*
 * DefaultCarStoryFileReader.h
 *
 *  Created on: Apr 18, 2014
 *      Author: Kamran Amini <kam.cpp@gmail.com>
 */

#ifndef DEFAULT_CAR_STORY_FILE_READER_H_
#define DEFAULT_CAR_STORY_FILE_READER_H_

#include <string>

#include "CarStoryFileReaderInterface.h"

class DefaultCarStoryFileReader: public CarStoryFileReaderInterface {
  public:
    DefaultCarStoryFileReader(unsigned int id, std::string filePath);
    virtual ~DefaultCarStoryFileReader(void);

    inline unsigned int getId(void) const {
      return id_;
    }

    inline std::string getFilePath(void) const {
      return filePath_;
    }
    inline void setFilePath(std::string filePath) {
      filePath_ = filePath;
    }

    virtual CarStory* read(void);

  private:
    unsigned int id_;
    std::string filePath_;
};

#endif /* DEFAULT_CAR_STORY_FILE_READER_H_ */
