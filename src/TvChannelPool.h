/*
 * TvChannelPool.h
 *
 *  Created on: May 10, 2014
 *      Author: Kamran Amini <kam.cpp@gmail.com>
 */

#ifndef TV_CHANNEL_POOL_H_
#define TV_CHANNEL_POOL_H_

#ifndef NULL
#define NULL 0
#endif

#include <vector>
#include <map>

class TvChannel;

class TvChannelPool {
  public:
    static TvChannelPool* getInstance(void) {
      if (instance_ == NULL) {
        instance_ = new TvChannelPool();
      }
      return instance_;
    }

  private:
    static TvChannelPool *instance_;

  public:
    TvChannelPool(void) :
        zappingTransformProbability_(NULL), zappingTransformProbabilityCummutative_(NULL), channelPopularity_(NULL), channelPopularityCummutative_(NULL) {
    }
    virtual ~TvChannelPool(void) {
    }

    inline void addTvChannel(TvChannel *tvChannel) {
      tvChannels_.push_back(tvChannel);
    }
    inline unsigned int getNumberOfTvChannels(void) const {
      return tvChannels_.size();
    }
    inline TvChannel* getTvChannel(unsigned int index) {
      return tvChannels_[index];
    }

    inline TvChannel* getTvChannelByPopularity(unsigned int popularity) {
      if (popularitiesToTvChannelsMap_.find(popularity) == popularitiesToTvChannelsMap_.end()) {
        return NULL;
      }
      return popularitiesToTvChannelsMap_[popularity];
    }

    inline unsigned int getPopularityForTvChannel(TvChannel *tvChannel) {
      if (tvChannelsToPopularitiesMap_.find(tvChannel) == tvChannelsToPopularitiesMap_.end()) {
        return 0;  // NOTICE: Zero is not a valid value for popularity.
      }
      return tvChannelsToPopularitiesMap_[tvChannel];
    }

    double getZappingTransformProbability(TvChannel *sourceChannel, TvChannel *destinationChannel);
    double getZappingTransformProbabilityCummutative(TvChannel *sourceChannel, TvChannel *destinationChannel);

    virtual void generateTvChannels(unsigned int numberOfTvChannels);
    virtual void calculatePopularityForTvChannels(void);

    virtual TvChannel* getFirstChannel(void);
    virtual TvChannel* getNextChannel(TvChannel *previousTvChannel);

  private:
    std::vector<TvChannel*> tvChannels_;
    std::map<unsigned int, TvChannel*> popularitiesToTvChannelsMap_;
    std::map<TvChannel*, unsigned int> tvChannelsToPopularitiesMap_;
    double *zappingTransformProbability_;
    double *zappingTransformProbabilityCummutative_;
    double *channelPopularity_;
    double *channelPopularityCummutative_;
};

#endif /* TV_CHANNEL_POOL_H_ */
