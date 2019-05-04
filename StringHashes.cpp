#include "StringHashes.h"

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

uint64_t PearsonHash::hash(const std::string& input) const{
  
}
