#include "BloomFilter.h"

//bloom filter constructor
BloomFilter::BloomFilter(int k, int m, std::string strfn, std::string intfn){
  this -> k = k;
  this -> m = m;
  this -> bits = new uint64_t[m];
  //check which kind of hash it is and respon accordingly
  if(strfn == "jenkins"){
    this -> strfn = new JenkinsHash();
  }
  else if(strfn == "pearson"){
    this -> strfn = new PearsonHash();
  }
  intfns = new IntegerHash*[k];
  for(int i = 0; i < k; i++){
    if(intfn == "division"){
      this -> intfns[i] = new DivisionHash(i, m);
    }
    else if(intfn == "reciprocal"){
      this -> intfns[i] = new ReciprocalHash(i, m);
    }
    else if(intfn == "squareroot"){
      this -> intfns[i] = new SquareRootHash(i, m);
    }
  }
}

//destructor
BloomFilter::~BloomFilter(){
  for(int i = 0; i < k; i++){
    delete intfns[i];
  }
  delete [] intfns;
  delete strfn;
  delete [] bits;
}

void BloomFilter::insert(const string& value){
  uint64_t location = strfn -> hash(value);
  for (int i = 0; i < k; i++){
    uint64_t newValue = intfns[i] -> hash(location);
    bits[newValue] = 1;
  }
}

bool BloomFilter::lookup(const string& value) const{
  uint64_t location = strfn -> hash(value);
  for(int i = 0; i < k; i++){
    uint64_t newValue = intfns[i] -> hash(location);
    if(bits[newValue] != 1){
      return false;
    }
  }
  return true;
}
