#include "IntegerHashes.h"
#include <cmath>
using namespace std;

IntegerHash::IntegerHash(uint64_t i, unint64_t m){ //initilizing stuff
  this -> i = i;
  this -> m = m;
}

DivisionHash::DivisionHash(uint64_t i, uint64_t m){ //initializing stuff... can i do this using integerhash?
  this -> i = i;
  this -> j = j;
}

// This function uses the "division method" of hashing
// It first multiplies the input by i + 1, then reduces the result modulo m
uint64_t DivisionHash::hash(uint64_t input) const{
  uint64_t newinput = input * (i + 1);
  return newinput % m;
}

// This function uses the "multiplication method" of hashing
// It multiplies the input by 1 / (i + 2), then multiplies the fractional part by m
ReciprocalHash::ReciprocalHash(uint64_t i, uint64_t m) : IntegerHash(i, m){ //let integerhash initialize everything so i dont have to keep doing it
  b = 1 / (i + 2);
}

uint64_t ReciprocalHash::hash(uint64_t input) const{
  double newinput1 = input * b;
  uint64_t newinput2 = static_cast<uint64_t>(input * b);
  static_cast<uint64_t>
}
