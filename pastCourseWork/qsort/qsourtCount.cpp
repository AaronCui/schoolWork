#include <iostream>
#include <ctime>
#include <cstdlib>

int * x;
int comps = 0;
int lown, highn;


void swap(int & a, int & b) {
	int tmp = a;
	a = b;
	b = tmp;
}

int randint(int a, int b) {
	return a + (rand() % (b - a + 1));
}

int randpiv(int n) {
	return rand() % n;
}

void comparisonCount (int n) {

	if (n<= 1)
		return;
	int rand = randpiv(n); //the assumed pivot AFTER swapping which never actually happened
	comps += (n-1);
	comparisonCount (rand - 1);
	comparisonCount (n - rand);
}
	


void quicksort(int a, int b) {
	if (a >= b) return;
	int p = randint(a,b); // pivot
	swap(x[a], x[p]);
	int m = a;
	int i;
	// in-place partition:
	for (i = a+1; i <= b; i++) {
		if (x[i] < x[a])
			swap(x[++m], x[i]);
	}
	swap(x[a],x[m]);
	quicksort(a, m-1);
	quicksort(m+1, b);
}

#define NN 1000

int main(int argc, char *argv[]) {
	srand(time(0));

	// change the following code
	/*
	x = new int[NN];
	for (int i=0; i<NN; ++i) {
		x[i] = rand() % NN;
	}
	
	quicksort(0, NN-1);
	for (int i=0; i<NN; ++i) {
		std::cout << x[i] << " ";
	}*/
	int avg = 0; 
	int sum = 0;
	
	for (int i = 0; i < 100; i++)
	{
		comparisonCount (NN);
		sum += comps;
		comps = 0;
	}
	avg = sum / 100;
	
	std::cout << avg << std::endl;

	//delete[] x;
	return 0;
}
