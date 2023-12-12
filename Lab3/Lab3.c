
#include <stdio.h>
#include <math.h>

#define false 0
#define true 1

// Utility function to do modular exponentiation.
// It returns (x^y) % p
int modularExponentiation(int x, unsigned int y, int p)
{
	int res = 1;	 // Initialize result
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

int miillerTest(int n, int a, int s, int t)
{
	//check if a^t = 1
	int x = modularExponentiation(a, pow(2, 0) * t, n);
	printf("For j=0: %d\n", x);
	if (x == 1)
		return true;

	int prevX = x;
	for (int j = 1; j <= s; j ++) {
		//check if a^(2^j)*t = 1
		x = modularExponentiation(a, pow(2, j) * t, n);
		printf("For j=%d: %d\n", j, x);
		if (x == 1 && prevX == n-1)
			return true;
		prevX = n - 1;
	}

	return false;
}

// It returns false if n is composite and returns true if n
// is probably prime. k is an input parameter that determines
// accuracy level. Higher value of k indicates more accuracy.
int isPrime(int n, int k)
{
	// Corner cases
	if (n == 2 || n == 3 || n == 5)
		return true;
	if (n % 2 == 0)
		return false;


	// Find s and t such that n - 1 = 2^s * t
	int s = 0;
	int t = n - 1;
	while (t % 2 == 0) {
		s += 1;
		t = t / 2;
	}

	printf("---------------------------------\n");
	printf("s = %d\n", s);
	printf("t = %d\n", t);

	// Iterate given number of 'k' times

	int a = 2;
	printf("------------------------------------\n");
	printf("Iteration k=%d for a=%d\n", 1, a);
	if (!miillerTest(n, a, s, t))
		return false;
	a = 3;

	for (int i = 1; i < k; i++) {
		printf("------------------------------------\n");
		printf("Iteration k=%d for a=%d\n", i + 1, a);
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
	int n;

	//for (int i = 2; i < 100; i++)
	//	if (isPrime(i, k))
	//		printf("\n\n\n\n\%d\n\n\n\n", i);

	printf("Input n: ");
	scanf("%d", &n);
	

	if (isPrime(n, k))
		printf("%d IS PRIME WITH PROBABILITY: %f\n", n, 1 - 1 / pow(4, k));
	else
		printf("%d IS COMPOSITE\n", n);
		
	return 0;
}
