#include "HashSet.h"

using namespace std

HashSet::HashSet(){
  nitems = 0;
  nslots = 100000;
  intfn = new SquareRootHash(5, nslots);
  strfn = new JenkinsHash;
  slots = new string * [nslots];
  for(i = 0; i < nslots; ++i){
    slots[i] = nullptr;
  }
}

HashSet::~HashSet(){
  //delete every value in slots
  for(i = 0; i < nslots; ++i){
    //if something exists here, delete it
    if(slots[i]){
      delete slots[i];
    }
  }
  //clean up
  delete [] slots;
  delete intfn;
  delete strfn;
}
