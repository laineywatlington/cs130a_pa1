# cs130a_pa1
pa 1 for cs 130a
Program One
Due May 7 at 4:00 PM
In this assignment, you will investigate Bloom filters.  Bloom filters are
data structures that represent sets  and allow the user to query whether a given
item is a member of the set or not. They use hash functions and a clever storage
mechanism to  represent sets  using very little memory.  The cost of this is the
occasional false positive - a Bloom filter may report that an item is in the set
when it is not.
A Bloom filter consists of  m bits  and k hash functions  that hash items to
integers  in the range [0, m).  In a Bloom filter  representing the empty set,
all the bits are set to zero.  To add an item to the set,  run that item through
all the hash functions;  use the results as indices into the bits array, and set
those bits to one.  To test if an item is in the set,  run that item through all
the hash functions;  use the results to index into the bits and report true only
if all the referenced bits were ones.
You will implement  a Bloom filter  and a hash set (for use as a baseline).  You
will then experiment with changing the values of the Bloom filter parameters and
write a short report on your findings.

Part One: The Code
This repo contains starter code that compares a Bloom filter against a hash set,
which  is used  as a baseline  to report  each  Bloom  filter  lookup  as a true
negative,  false positive, etc.  The starter code will handle the testing logic,
input,  and output  for you,  but you'll need  to implement the  data structures
and hash functions yourself:

You'll find the BloomFilter class declared in BloomFilter.h;  implement it
in BloomFilter.cpp.
The HashSet class  declared in HashSet.h is the true set your Bloom filter
will be compared against. Implement it in HashSet.cpp. Note that it's a set,
not a map, and that you only need to implement insertion and lookup.  Use open
address hashing with a hash function and probing scheme of your choice.
The  StringHashes.h  header file contains  class declarations  for functions
used to map  arbitrary-length strings  to integers.  The comments in that file
explain the functions used.  Implement these in StringHashes.cpp.
The IntegerHashes.h file contains class declarations for hash functions that
map arbitrary integers to integers in a given range (for use in a Bloom filter
or hash table). The comments explain how each function works.  Implement these
in IntegerHashes.cpp.

Turn in your code  on Gradescope.  The automated tests  will make sure that your
code behaves as expected.  You will also be graded on coding style.

Part Two: The Report
Now that you have a working Bloom filter, you can experiment with its parameters
and see how the  false positive rate  changes.  For all six  (string hash,
integer hash)  pairs,  perform the experiments  listed below.  Graph and explain
your results.
You'll need a dataset to perform these experiments; a dataset with about 100,000
unique strings  should give you good results  and still run quickly.  The  IMDb
datasets are a good option, but you'll want to preprocess them to extract a
single column, remove duplicates, and extract a subset of the desired size.

The parameter  n  represents  the number of items  in the set.  Take a Bloom
filter with m = 1,000 and k = 10. How does its false positive rate  change
as n varies from 1 to 1,000?
The parameter m controls the number of bits in the Bloom filter. Take a very
"full" Bloom filter with m = 10, k = 10, and n = 10. How does increasing
m change the false positive rate?
The parameter k  controls the number  of hash  functions used.  Take a Bloom
filter with m = 100,000 and n = 10,000.  How does the  false positive rate
change as k varies from 1 to 100?

Make sure your report mentions what data set you used and gives an evaluation of
the hash functions.  Turn it in on Gradescope.

Miscellaneous

This is an individual assignment.  No group work!
Your code must compile with no warnings (the -Werror flag enforces this).
You may not use global variables or any data structures from other libraries.
Do not edit  bloom.cpp  or any of the *.h files;  your code will be tested
against the originals.
The summary includes false negatives; this may be useful for debugging, but if
your code is working properly, this number will always be zero.
The starter code has -t and -f flags, which are intended to make it easier
to to script your experiments  and create  CSV  or  TSV  files.  The cut and
paste command line tools will be useful if you do this!
