#include "HashSet.h"

using namespace std

HashSet::HashSet(){
  //initialization
  nitems = 0;
  nslots = 100;
  intfn = new SquareRootHash(5, nslots);
  strfn = new JenkinsHash;
  slots = new string * [nslots];
  //set every slot to null
  for(i = 0; i < nslots; ++i){
    slots[i] = NULL;
  }
}

HashSet::~HashSet(){
  //delete every value in slots
  for(i = 0; i < nslots; ++i){
    delete slots[i];
  }
  //clean up
  delete [] slots;
  delete intfn;
  delete strfn;
}

void HashSet::rehash(){
  int oldSlots = nslots;
  nslots *= 2;  //set a new capacity for table
  string ** temp = slots; //temporary table to hold info
  //now, create a new table from slots !
  slots = new string * [nslots];
  //figure out later 
  
}
