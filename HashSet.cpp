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
	//first check things
	//is value already in table? if so, return
	if(lookup(value)){
		return;
	}
	nitems ++;
	if(nitems >= nslots){
		rehash();
	}
	uint64_t newValue = strfn -> hash(value);
	uint64_t location = intfn -> hash(newValue);
	while(slots[location]){
		location = (location + 1) % nslots;
	}
	slots[location] = new string(value);
}

void HashSet::rehash(){
  int oldSlots = nslots;
	nslots *= 2; //set a new capacity for table
	string** temp = slots; //create a temporary array to store info in 
	slots = new string*[nslots]; //create new array double the size to hash into
	nitems = 0; //make new table empty so we can hash into it
	for (int i = 0; i < nslots; i++) {
		slots[i] = NULL;
	}
  //CLEAN MEMORY
	delete intfn;
	intfn = new SquareRootHash(100, nslots);
  //now, we insert elements from old, temp array into new one
	for (int i = 0; i < oldSlots; i++) { 
		if (temp[i] != 0) {
			insert(*temp[i]); //insert item into table
			delete temp[i];  //free up space in old array
		}
	}
	delete [] temp; //get rid of temp array
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

