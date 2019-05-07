#include "HashSet.h"
#include <string>
#include <cstdint>
#include <iostream>
using namespace std;

HashSet::HashSet(){
  //initialization
  nitems = 0;
  nslots = 100;
  intfn = new DivisionHash(0, nslots);
  strfn = new JenkinsHash();
  slots = new string * [nslots];
  //set every slot to null
  for(int i = 0; i < nslots; ++i){
    slots[i] = NULL;
  }
}

HashSet::~HashSet(){
  //delete every value in slots
  for(int i = 0; i < nslots; ++i){
    delete slots[i];
  }
  //clean up
  delete [] slots;
  delete intfn;
  delete strfn;
}

bool HashSet::lookup(const std::string& value) const{
  int i = 0;
  uint64_t location = strfn -> hash(value);
  uint64_t newValue = intfn -> hash(location);
  while(true){
    //if not in
    if(!(slots[newValue + i])){
      return false;
    }
    //if in
    if(*(slots[newValue + i]) == value){
      return true;
    }
    else{
      //check next value
      i++;
    }
  }
  return false;
}

void HashSet::insert(const std::string& value){
  //first, check some stuff
  if(lookup(value) == true){
    return;
  }
  if(nitems >= nslots){
    rehash();
  }
  uint64_t location = strfn -> hash(value);
  uint64_t newValue = intfn -> hash(location);
  int i = 0;
  while(true){
    if(slots[newValue + i]){
      i++;
      continue;
    }
    slots[newValue + i] = new std::string(value);
    nitems++;
    return;
  }
}

void HashSet::rehash(){
  int oldSlots = nslots;
  nslots *= 2;  //set a new capacity for table
  string ** temp = slots; //temporary table to hold info
  //now, create a new table from slots !
  slots = new string * [nslots];
  nitems = 0;
  //initialize everything to null so that we can hash into it 
  for(int i = 0; i < nslots; i++){
    slots[i] = NULL;
  }
  delete intfn;
  intfn = new SquareRootHash(5, nslots);
  for(int i = 0; i < oldSlots; i++){
    if(temp[i] != 0){
      insert(*temp[i]);
      delete temp[i];
    }
  }
  delete [] temp;
}
