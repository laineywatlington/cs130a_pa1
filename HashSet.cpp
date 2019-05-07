#include "HashSet.h"
#include <string>
#include <cstdint>
#include <iostream>
using namespace std;

HashSet::HashSet(){
  //initialization
  this -> nitems = 0;
  this -> nslots = 100;
  this -> intfn = new DivisionHash(0, nslots);
  this -> strfn = new JenkinsHash();
  this -> slots = new string * [nslots];
  //set every slot to null
  for(int i = 0; i < nslots; ++i){
    slots[i] = NULL;
  }
}

bool HashSet::lookup(const string& value) const{
    uint64_t location = strfn -> hash(value);
    uint64_t newValue = intfn -> hash(location);
    for (int i = 0; i < nslots; i++) {
        if (slots[(newValue + i) % nslots] == NULL) {
            return false;
        }
        else if (*slots[(newValue + i) % nslots] == value) {
            return true;
        }
    }
    return false;
}

void HashSet::insert(const std::string& value){
    uint64_t location = strfn->hash(value);
    uint64_t newValue = intfn->hash(location);
    for (int i = 0; ; i++) {
        if (slots[(newValue + i) % nslots] == NULL) {
            slots[(newValue + i) % nslots] = new string(value);
            nitems++;
            break;
        }
    }
    if (2 * nitems >= nslots) {
        rehash();
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

