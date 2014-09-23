/*
 * TvChannelPool.cpp
 *
 *  Created on: May 10, 2014
 *      Author: Kamran Amini <kam.cpp@gmail.com>
 */

#include <cmath>

#include "TvChannelPool.h"
#include "TvChannel.h"
#include "config.h"
#include "RandomHelper.h"

TvChannelPool* TvChannelPool::instance_ = NULL;

double TvChannelPool::getZappingTransformProbability(TvChannel *sourceChannel, TvChannel *destinationChannel) {
  return zappingTransformProbability_[(sourceChannel->getNumber() - 1) * tvChannels_.size() + (destinationChannel->getNumber() - 1)];
}

double TvChannelPool::getZappingTransformProbabilityCummutative(TvChannel *sourceChannel, TvChannel *destinationChannel) {
  return zappingTransformProbabilityCummutative_[(sourceChannel->getNumber() - 1) * tvChannels_.size() + (destinationChannel->getNumber() - 1)];
}

TvChannel* TvChannelPool::getFirstChannel(void) {
  double rand = RandomHelper::next();
  if (rand == 1.0) {
    return tvChannels_[tvChannelsToPopularitiesMap_[tvChannels_[tvChannels_.size() - 1]] - 1];
  } else {
    for (unsigned int left = 0; left < tvChannels_.size(); left++) {
      unsigned int right = left + 1;
      // std::cout << "F: rand: " << rand << ", left: " << left << ", vleft: " << channelPopularityCummutative_[left] << ", right: " << right << ", vright: " << channelPopularityCummutative_[right] << std::endl;
      if (rand >= channelPopularityCummutative_[left] && rand < channelPopularityCummutative_[right]) {
        return popularitiesToTvChannelsMap_[right];
      }
    }
  }
  return tvChannels_[0];
}

TvChannel* TvChannelPool::getNextChannel(TvChannel *previousTvChannel) {
  double rand = RandomHelper::next();
  if (rand == 1.0) {
    return tvChannels_[tvChannels_.size() - 1];
  } else {
    for (unsigned int left = 0; left < tvChannels_.size(); left++) {
      unsigned int right = left + 1;
      // std::cout << "N: rand: " << rand << ", left: " << left << ", vleft: " << zappingTransformProbabilityCummutative_[previousTvChannel->getNumber() * (tvChannels_.size() + 1) + left] << ", right: " << right << ", vright: "
      //		<< zappingTransformProbabilityCummutative_[previousTvChannel->getNumber() * (tvChannels_.size() + 1) + right] << std::endl;
      if (rand >= zappingTransformProbabilityCummutative_[previousTvChannel->getNumber() * (tvChannels_.size() + 1) + left] && rand < zappingTransformProbabilityCummutative_[previousTvChannel->getNumber() * (tvChannels_.size() + 1) + right]) {
        return tvChannels_[right - 1];
      }
    }
  }
  return tvChannels_[0];
}

void TvChannelPool::generateTvChannels(unsigned int numberOfTvChannels) {
  for (unsigned int i = 1; i <= numberOfTvChannels; i++) {
    TvChannel *tvChannel = new TvChannel(i);
    tvChannel->setMaximumNumberOfWatchers(MAX_WATCHERS_PER_CHANNEL);
    addTvChannel(tvChannel);
  }
}

void TvChannelPool::calculatePopularityForTvChannels(void) {
  double *temp = new double[tvChannels_.size() + 1];
  channelPopularity_ = new double[tvChannels_.size() + 1];
  channelPopularityCummutative_ = new double[tvChannels_.size() + 1];
  for (unsigned int i = 0; i < tvChannels_.size() + 1; i++) {
    temp[i] = 0.0;
    channelPopularity_[i] = 0.0;
    channelPopularityCummutative_[i] = 0.0;
  }

  double sum = 0.0;
  for (unsigned int i = 1; i < tvChannels_.size() + 1; i++) {
    temp[i] = pow(i, -ZIPF_ALPHA);
    // std::cout << "temp[" << i << "]: " << temp[i] << std::endl;
    sum += temp[i];
  }
  // std::cout << "sum: " << sum << std::endl;
  for (unsigned int i = 1; i < tvChannels_.size() + 1; i++) {
    channelPopularity_[i] = temp[i] / sum;
    // std::cout << "CP[ " << i << "]: " << channelPopularity_[i] << std::endl;
  }
  for (unsigned int i = 1; i < tvChannels_.size() + 1; i++) {
    channelPopularityCummutative_[i] = channelPopularityCummutative_[i - 1] + channelPopularity_[i];
    // std::cout << "CPC[ " << i << "]: " << channelPopularityCummutative_[i] << std::endl;
  }

  // Assigning popularities to tv channels
  RandomHelper::setRandomSeed(SRAND_INITIAL_MAPPING);
  bool *flags = new bool[tvChannels_.size() + 1];
  for (unsigned int i = 0; i < tvChannels_.size() + 1; i++) {
    flags[i] = false;
  }
  for (unsigned int i = 1; i < tvChannels_.size() + 1; i++) {
    bool popularityCalculated = false;
    TvChannel *tvChannel = getTvChannel(i - 1);
    while (!popularityCalculated) {
      double random = RandomHelper::next();
      unsigned int calculatedPopularity = 0;
      if (random == 1.0) {
        calculatedPopularity = tvChannels_.size();
      } else {
        calculatedPopularity = (unsigned int) (random * tvChannels_.size() + 1);
      }
      if (!flags[calculatedPopularity]) {
        tvChannel->setPopularity(calculatedPopularity);
        // std::cout << tvChannel->getName() << ".popularity: " << calculatedPopularity << std::endl;
        popularitiesToTvChannelsMap_.insert(std::pair<unsigned int, TvChannel*>(calculatedPopularity, tvChannel));
        tvChannelsToPopularitiesMap_.insert(std::pair<TvChannel*, unsigned int>(tvChannel, calculatedPopularity));
        flags[calculatedPopularity] = true;
        popularityCalculated = true;
      }
    }
  }

  zappingTransformProbability_ = new double[(tvChannels_.size() + 1) * (tvChannels_.size() + 1)];
  zappingTransformProbabilityCummutative_ = new double[(tvChannels_.size() + 1) * (tvChannels_.size() + 1)];

  std::cout << "Making zapping transfrom matrices zero ..." << std::endl;
  for (unsigned int i = 0; i < tvChannels_.size() + 1; i++) {
    for (unsigned int j = 0; j < tvChannels_.size() + 1; j++) {
      zappingTransformProbability_[i * (tvChannels_.size() + 1) + j] = 0.0;
      zappingTransformProbabilityCummutative_[i * (tvChannels_.size() + 1) + j] = 0.0;
    }
  }

  for (unsigned int i = 1; i < tvChannels_.size() + 1; i++) {
    for (unsigned int j = 1; j < tvChannels_.size() + 1; j++) {
      zappingTransformProbability_[i * (tvChannels_.size() + 1) + j] = channelPopularity_[popularitiesToTvChannelsMap_[j]->getNumber()];
      // std::cout << "ZTP[" << i << ", " << j << "]: " << zappingTransformProbability_[i * (tvChannels_.size() + 1) + j] << "  ";
    }
    // std::cout << std::endl;
  }

  for (unsigned int i = 1; i < tvChannels_.size() + 1; i++) {
    for (unsigned int j = 1; j < tvChannels_.size() + 1; j++) {
      zappingTransformProbabilityCummutative_[i * (tvChannels_.size() + 1) + j] = (j > 0 ? zappingTransformProbabilityCummutative_[i * (tvChannels_.size() + 1) + j - 1] : 0.0) + zappingTransformProbability_[i * (tvChannels_.size() + 1) + j];
      // std::cout << "ZTPC[" << i << ", " << j << "]: " << zappingTransformProbabilityCummutative_[i * (tvChannels_.size() + 1) + j] << "  ";
    }
    // std::cout << std::endl;
  }

  delete[] flags;
  delete[] temp;
}

