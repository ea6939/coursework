#include <math.h> // needed for ceil()
#include <stdint.h> // needed for uint64_t
#include <stdio.h> // needed for printf()
#include <stdlib.h>

// Computation functions
void fermatC(int N);
extern uint64_t fermatAssem(int N); // uint64_t as return type returns one word in R0, one word in R1
int gcd(int x, int y);
int lcm(int x, int y);
void primeFactorize(int N, int * prime_factors, int * prime_count);

// Tester functions
void fermatTestbenchC(void);
void fermatTestbenchAssem(void);
void primeFactorizationTest(void);
void gcdTest(void);
void lcmTest(void);

// Helper functions
int isSquare(int x);

int main()
{
	// Test battery for all functions.
	// To check the duration/states for one test, 
	// comment out the other tests.
	
	fermatTestbenchC();
	fermatTestbenchAssem();
	primeFactorizationTest();
	gcdTest();
	lcmTest();
}

void gcdTest(void)
{
	int x = 24;
	int y = 36;
	int z = gcd(x,y); // 12
	// printf("z = %d\n",z);
}

void lcmTest(void) 
{
	int x = 24;
	int y = 36;
	int z = lcm(x,y); // 72
//	printf("z = %d\n",z);
}

int gcd(int x, int y)
{
	// Adapted from http://www.cquestions.com/2008/01/c-program-to-find-gcd-of-number-using.html
	
	if (x < 1 || y < 1) return -1; // error: bad input
	
	while(x != y) {
		if (x > y) {
			return gcd(x-y,y);
		} else {
			return gcd(x,y-x);
		}
		return x;
	}
	return x; // if x == y, gcd = either
}

int lcm(int x, int y)
{
	// Adapted from http://www.cquestions.com/2010/06/write-c-program-to-find-out-lcm-of-two.html
	// (We use gcd() instead of rewriting code!)
	
	if (x < 1 || y < 1) return -1; // error: bad input
	if (x == y) return x;
	return x*y/gcd(x,y); // return value in R0
}

void primeFactorizationTest(void)
{
	int N = 99;
	int prime_factors[32] = {0}; // for 32-bit numbers, max 32 prime factors
	int prime_count = 0;
	
	primeFactorize(N,prime_factors,&prime_count);
	return;
}

void primeFactorize(int N, int * prime_factors, int * prime_count)
{
	// Assume |prime_factors| = 32.
	uint64_t both_factors;
	int f1;
	int f2;
	
	// run fermat once; get two factors, put them into R0, R1 (as 64-bit number)
	both_factors = fermatAssem(N);
	
	// extract factors from 64-bit number using shift
	f1 = both_factors;
	f2 = both_factors >> 32;
	
	// if one of the factors = 1, the other factor is prime
	// otherwise, factorize both factors
	if (f1 == 1) {
		prime_factors[(*prime_count)] = f2;
		(*prime_count)++;
	} else if (f2 == 1) {
		prime_factors[(*prime_count)] = f1;
		(*prime_count)++;
	} else {
		primeFactorize(f1,prime_factors,prime_count);
		primeFactorize(f2,prime_factors,prime_count);
	}
}

void fermatTestbenchC(void) 
{
	// Tests our C implementation of Fermat by
	// factorizing numbers from N = 1 to 100.
	
	int N;
	for (N = 1; N <= 100; N++) {
		fermatC(N);
	}
	return;
}

void fermatTestbenchAssem(void) 
{
	// Tests our assembly implementation of Fermat by
	// factorizing numbers from N = 1 to 100.
	
	int N;
	for (N = 1; N <= 100; N++) {
		fermatAssem(N);
	}
	return;
}	

void fermatC(int N)
{
	// Computes two factors for input N using Fermat's algorithm.
	// (C implementation.)
	int f1, f2, x, y, y_squared;
	
	// N negative or zero
	if (N <= 0)
	{
		f1 = 0;
		f2 = 0;
		return;
	}
	
	// N even
	if (N % 2 == 0) {
		f1 = 2;
		f2 = N / 2;
		printf("f1 = %d, f2 = %d\n",f1,f2);
		return;
	}
		
	// N odd
	x = ceil(sqrt(N));
	y_squared = x*x - N;
	
	while (!isSquare(y_squared)) {
		x++;
		y_squared = x*x - N;
	}
	
	y = sqrt(y_squared);
	f1 = x+y; // R4
	f2 = x-y; // R4
	while (f1 * f2 != N) ; // if the factors don't multiply to N, ERROR
	return;
}

int isSquare(int x) 
{
	// Checks whether x is a perfect square.
	// If yes, return 1; if no, return 0.
	
	int ceilX = ceil(sqrt(x))*ceil(sqrt(x));
	if (x == ceilX) return 1;
	else return 0;
}

