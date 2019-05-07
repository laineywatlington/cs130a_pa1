#include "IntegerHashes.h"
#include "StringHashes.h"
#include "BloomFilter.h"

using namespace std; 

BloomFilter::BloomFilter(int k, int m, std::string strfn, std::string intfn){
	this->k = k; 
	this->m = m; 
        this -> bits = new uint64_t[m](); 
	intfns = new IntegerHash*[k];
	if(strfn == "jenkins"){
		this -> strfn = new JenkinsHash();
	}
	else if(strfn == "pearson"){
		this -> strfn = new PearsonHash(); 
	}
	if (intfn == "division") {
		for (int i = 0; i < k; ++i) {
			intfns[i] = new DivisionHash(i, m);
		}
	}
	else if (intfn == "reciprocal") {
		for (int i = 0; i < k; ++i) {
			intfns[i] = new ReciprocalHash(i,m);
		}
	}
	else if(intfn == "squareroot"){
		for (int i = 0; i < k; ++i) {
			intfns[i] = new SquareRootHash(i,m);
		}
	}

}

void BloomFilter::insert(const std::string& value){
	for(int i = 0; i < k; i++){
		uint64_t newValue = strfn -> hash(value);
		uint64_t location = intfns[i] -> hash(newValue); 
		bits[location / 64] |= (uint64_t(1) << (location % 64)); 
	}
}

bool BloomFilter::lookup(const std::string& value) const{
	uint64_t newValue = strfn -> hash(value);
	for(int i = 0; i < k; i++){
		uint64_t location = intfns[i]-> hash(newValue);
		int place = (location / 64);
		int number = location % 64;
		uint64_t temp = bits[place] >> number;
		if((temp & uint64_t(1)) == 0){
			return false;
		}
	}
	return true;
}


//destructor
BloomFilter::~BloomFilter(){
	delete [] bits;
	delete strfn;
	for(int i = 0; i < k; i++){
		delete intfns[i];
	}
	delete [] intfns;
}
