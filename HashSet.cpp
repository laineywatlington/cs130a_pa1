#include "HashSet.h"

using namespace std

HashSet::HashSet(){
  nitems = 0;
  nslots = 100000;
  intfn = new SquareRootHash(5, nslots);
  strfn = new JenkinsHash;
  slots = new string * [nslots];
  for(i = 0; i < nslots; i++){
    slots[i] = nullptr;
  }
}
