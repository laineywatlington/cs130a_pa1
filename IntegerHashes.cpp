#include "IntegerHashes.h"
#include <cmath>

IntegerHash::IntegerHash(uint64_t i, uint64_t m): i(i), m(m) {}

DivisionHash::DivisionHash(uint64_t i, uint64_t m): IntegerHash(i,m) {}

uint64_t DivisionHash::hash(uint64_t input) const {
	uint64_t key = input * (i + 1);
	return key % m;
}

ReciprocalHash::ReciprocalHash(uint64_t i, uint64_t m): IntegerHash(i,m) {
	b = 1.0 / (i + 2);
}


uint64_t ReciprocalHash::hash(uint64_t input) const {
	return static_cast<uint64_t>(m * ((input * b) - static_cast<uint64_t>(input * b)));
}

SquareRootHash::SquareRootHash(uint64_t i, uint64_t m): IntegerHash(i,m) {
	b = std::sqrt(4*i + 3);
}

uint64_t SquareRootHash::hash(uint64_t input) const {
	return static_cast<uint64_t>(m * ((input * b) - static_cast<uint64_t>(input * b)));
}
