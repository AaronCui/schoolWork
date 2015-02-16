#include "hash.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

Hash::Hash(int _size) {
	//constructor
	size = _size;
	totalProbes = 0;
	numInserts = 0;
	table = new int [size];
	for (int i=0; i<size; i++) {
		table[i] = EMPTY;
	}
}

Hash::~Hash() {
	//deconstructor
	delete[] table;
}

void Hash::tallyProbes(int p) {
	// Add the number of probes, p, for one insert operation to the tally.
	totalProbes += p;
	numInserts++;
}

void Hash::printStats() {
	std::cout << "Average probes/insert = " <<
			probeRate() << " = " <<
			totalProbes << "/" << numInserts << std::endl;
}

float Hash::probeRate() {
	return (float)totalProbes / (float)numInserts;
}

int Hash::hash(int k) {
	return k % size;
}

void Hash::qinsert(int k) {
	// Insert k in the hash table.
	// Use open addressing with quadratic probing and hash(k) = k % m.
	int i = 0;
	int p = 0;
	for (i; i < size*10 ; i++)
		{
			p++;
			// f(i) = i^2
			if(table[(hash(k)+i*i)%size] == EMPTY){
				table[(hash(k)+i*i)%size] = k;
				tallyProbes(p);
				break;
			}
			
			
		}
	
	/*	
		Question 2: a)
		When load factor is relatively small or less than half the size of array. 
		Quadratic becomes to obviously win around when load is half the size. 
		
		b)
		The secondary hash function should differ from the original one therefore
		different numbers have a higher chance to hash to a different entry.
		It can be made the same as quadratic if the secondary hash function does similar
		e.g. hash2(k) = hash1(k) (+ i) 
		
		our implementation shows similar result once the size and load get large enough
		
		A better implementation is the current one, where it should behave much independently
		from hash1(k). Where hash2(k) = a prime number - k % the prime number. 
		
		c)
		About 100 or above in size at 50% load 

		d)
		Double without knowing the size. Because in the full range of possibilities
		ie from 1 - infinite, the most likely best performing is double hashing. 
		Usually the trade off is in cache performance, but without this in consideration
		double hashing should always be the default solution for the least clustering
		If you want to maintain some balance between cache performance and collision
		then choose quadratic. 
		
		
		*/
		
		
	// Tips:
	// - Look at the lecture slides if you don't remember how to implement these.
	// - You need to prevent against infinite loops. You should limit the number
	// of times you probe and print an error message upon exceeding this limit.
	// - You're welcome to add new declarations to hash.h, add to the constructor,
	// include libraries, or anything else you need. Just make it work.
	// - You're also welcome to modify the main() method to automate your testing.
	// In fact, you should!

	// add your code here
}


void Hash::linsert(int k) {
	// Insert k in the hash table.
	// Use open addressing with linear probing and hash(k) = k % m.
	int i = 0;
	int p = 0;
	for (i; i < size*10 ; i++)
		{
			p++;
			// f(i) = i^2
			if(table[(hash(k)+i)%size] == EMPTY){
				table[(hash(k)+i)%size] = k;
				tallyProbes(p);
			break;
			}
			
		}
	
	//add your code here
}

int Hash::hash2(int k) {
	return (11939 - k %11939);
}

void Hash::dinsert(int k) {
	// Insert k in the hash table.
	// Use open addressing with double hashing. Use the existing hash function
	// and also implement a second hash function.

	
	
	int i = 0;
	int p = 0;
	for (i; i < size*10 ; i++)
		{
			p++;
			if(table[(hash(k)+i*hash2(k))%size] == EMPTY){
				table[(hash(k)+i*hash2(k))%size] = k;
				tallyProbes(p);
			
			// f(i) = i^2
			/*if(table[(hash(k)+i*hash(k))%size] == EMPTY){
				table[(hash(k)+i*hash(k))%size] = k;
				tallyProbes(p);
			*/
			
				break;
			}
		
		}
	
	
	//add your code here
}

void Hash::print() {
	// Print the content of the hash table.

	for (int i=0; i<size; i++) {
		std::cout<<"["<<i<<"] ";
		if (table[i] != EMPTY)
			std::cout << table[i];
		std::cout << std::endl;
	}
}

void usage(char* argv[]) {
	std::cerr << "Usage: " << argv[0] << " scheme numberOfKeys sizeOfTable" << std::endl;
	exit(-1);
}

int main(int argc, char *argv[]) {
	int n, size;
	srand(time(0));

	if (argc != 4) {
		usage(argv);
	}
	n = atoi(argv[2]);
	size = atoi(argv[3]);
	Hash H(size);

	switch(argv[1][0]) {
	case 'l':
		for (int i=0; i<n; i++) {
			H.linsert(rand() + 1);
		}
		   H.print();
		std::cout << "Linear: ";
		H.printStats();
		break;
	case 'q':
		for (int i=0; i<n; i++) {
			H.qinsert(rand() + 1);
		}
		    H.print();
		std::cout << "Quadratic: ";
		H.printStats();
		break;
	case 'd':
		for (int i=0; i<n; i++) {
			H.dinsert(rand() + 1);
		}
		    H.print();
		std::cout << "Double Hashing: ";
		H.printStats();
		break;
	default:
		usage(argv);
	}
}
