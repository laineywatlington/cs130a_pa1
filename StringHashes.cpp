#include "StringHashes.h"

// This implements Bob Jenkins' "one at a time" hash function
uint64_t JenkinsHash::hash(const std::string& input) const{
  uint32_t hash = 0;
  size_t length = input.length();
  size_t i;
  for(i = 0; i < length; i++){
    hash += input[i];
    hash += (hash << 10);
    hash ^= (hash >> 6);
  }
  hash += (hash << 3);
  hash ^= (hash >> 11);
  hash += (hash << 15);
  return hash;
}

// This implements Peter Pearson's eight-bit hash
// It uses a very simple lookup table: T[i] = 255 - i
uint64_t PearsonHash::hash(const std::string& input) const{
  uint8_t hash = 0;
	for (const uint8_t &bit : input) {
		hash = 255 - (hash ^ bit);
	}
	return hash;
}
