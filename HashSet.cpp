#include "HashSet.h"

using namespace std

HashSet::HashSet(){
  //initialization
  nitems = 0;
  nslots = 100000;
  intfn = new SquareRootHash(5, nslots);
  strfn = new JenkinsHash;
  slots = new string * [nslots];
  //set every slot to null
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

void HashSet::rehash(){
  int newslots = nslots * 2;
  string** temp = slots;
  slots = new string * [newslots];
  nitems = 0;
  for(int i = 0; i < newslots; ++i){
    slots[i] = nullptr;
  }
  delete intfn;
  intfn = new SquareRootHash(5, newslots);
  for(int i = 0; i < newslots / 2; ++i){
    if(temp[i]){
      insert(*temp[i]);
      delete temp[i];
    }
  }
  delete [] temp;
}
      
    }
  }
}
