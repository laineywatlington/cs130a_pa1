#include "IntegerHashes.h"
#include "StringHashes.h"
#include "BloomFilter.h"

using namespace std; 

BloomFilter::BloomFilter(int k, int m, std::string strfn, std::string intfn){
	this->k = k; 
	this->m = m;
	intfns = new IntegerHash*[k]; 
        bits = new uint64_t[m]; 
	if(strfn == "jenkins"){
		this -> strfn = new JenkinsHash();
	}
	else if(strfn == "pearson"){
		this -> strfn = new PearsonHash(); 
	}
	if(intfn == "division"){
		for(int i = 0; i < k; i ++){
			DivisionHash* divisionhash = new DivisionHash(i, m);  
			intfns[i] = divisionhash; 
		}
	}
	else if(intfn == "reciprocal"){
		for(int i = 0; i < k; i ++){
			ReciprocalHash* reciprocalhash = new ReciprocalHash(i, m); 
			intfns[i] = reciprocalhash; 
		} 
	}
	else if(intfn == "squareroot"){	
		for(int i = 0; i < k; i ++){
			SquareRootHash* squareroothash = new SquareRootHash(i, m); 
			intfns[i] = squareroothash; 
		}
	}

}

/*void BloomFilter::insert(const std::string& value){
	for(int i = 0; i < k; i++){
		uint64_t newValue = strfn -> hash(value);
		uint64_t location = intfns[i] -> hash(newValue); 
		bits[location / 64] |= (uint64_t(1) << (location % 64)); 
	}
}

bool BloomFilter::lookup(const std::string& value) const{
	for (int i = 0; i < k; i++) {
		uint64_t location = strfn -> hash(value);
		uint64_t newValue = intfns[i] -> hash(location);
		if (!(bits[newValue/64] & (static_cast<uint64_t>(1) << (newValue % 64)))) {
			return false;
		}
	}
	return true;
}
*/

void BloomFilter::insert(const std::string& value){
	uint64_t newValue = strfn ->  hash(value);
	for(int i = 0; i < k; i++){
		uint64_t location = intfns[i] -> hash(newValue);
		uint64_t index = (location / 64);
		int number = location % 64;
		uint64_t k = (uint64_t(1) << number);
		bits[index] |= k;
    }
}

bool BloomFilter::lookup(const std::string& value) const{
	uint64_t newValue = strfn -> hash(value);
	for(int i = 0; i < k; i++){
		uint64_t location = intfns[i] -> hash(newValue);
		int index = (location / 64);
		int number = location % 64;
		uint64_t val = bits[index] >> location;
		if((val & uint64_t(1)) == 0){
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
