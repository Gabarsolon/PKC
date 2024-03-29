
#include <stdio.h>
#include <math.h>

#define false 0
#define true 1

typedef unsigned long long int BIG_NUMBER;

// Utility function to do modular exponentiation.
// It returns (x^y) % p
BIG_NUMBER modularExponentiation(BIG_NUMBER x, BIG_NUMBER y, BIG_NUMBER p)
{
	BIG_NUMBER res = 1;	 // Initialize result
	x = x % p; // Update x if it is more than or
	// equal to p
	while (y > 0)
	{
		// If y is odd, multiply x with result
		if (y & 1)
			res = (res * x) % p;

		// y must be even now
		y = y >> 1; // y = y/2
		x = (x * x) % p;
	}
	return res;
}

int miillerTest(BIG_NUMBER n, BIG_NUMBER a, BIG_NUMBER s, BIG_NUMBER t)
{
	//check if a^t = 1
	BIG_NUMBER x = modularExponentiation(a, pow(2, 0) * t, n);
	printf("For j=0: %I64u\n", x);
	if (x == 1)
		return true;

	BIG_NUMBER prevX = x;
	for (BIG_NUMBER j = 1; j <= s; j ++) {
		//check if a^(2^j)*t = 1
		x = modularExponentiation(a, pow(2, j) * t, n);
		printf("For j=%I64u: %I64u\n", j, x);
		if (x == 1) {
			if (prevX == n - 1)
				return true;

			else
				return false;
		}
		prevX = x;
	}

	return false;
}

// It returns false if n is composite and returns true if n
// is probably prime. k is an input parameter that determines
// accuracy level. Higher value of k indicates more accuracy.
int isPrime(BIG_NUMBER n, BIG_NUMBER k)
{
	// Corner cases
	if (n < 2)
		return false;
	if (n == 2 || n == 3 || n == 5)
		return true;
	if (n % 2 == 0)
		return false;


	// Find s and t such that n - 1 = 2^s * t
	BIG_NUMBER s = 0;
	BIG_NUMBER t = n - 1;
	while (t % 2 == 0) {
		s += 1;
		t = t / 2;
	}

	printf("---------------------------------\n");
	printf("s = %I64u\n", s);
	printf("t = %I64u\n", t);

	// Iterate given number of 'k' times

	BIG_NUMBER a = 2;
	printf("------------------------------------\n");
	printf("Iteration k=%I64u for a=%d\n", 1, a);
	if (!miillerTest(n, a, s, t))
		return false;
	a = 3;

	for (int i = 1; i < k; i++) {
		printf("------------------------------------\n");
		printf("Iteration k=%I64u for a=%d\n", i + 1, a);
		if (!miillerTest(n, a, s, t))
			return false;
		a += 2;
	}
	printf("----------------------------------\n");

	return true;
}

// Driver program
int main()
{
	int k = 3; // Number of iterations
	BIG_NUMBER n;

	//for (int i = 2; i < 100; i++)
	//	if (isPrime(i, k))
	//		printf("\n\n\n\n\%d\n\n\n\n", i);

	while (true) {
		printf("Input n: ");
		scanf("%I64u", &n);

		printf("-----------------------------------------------\n");
		if (isPrime(n, k))
			printf("%I64u IS PRIME WITH PROBABILITY: %f\n", n, 1 - 1 / pow(4, k));
		else
			printf("%I64u IS COMPOSITE\n", n);
		printf("------------------------------------------------\n");
	}

		
	return 0;
}
