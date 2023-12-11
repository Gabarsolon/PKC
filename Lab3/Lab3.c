
#include <stdio.h>

#define false 0
#define true 1

// Utility function to do modular exponentiation.
// It returns (x^y) % p
int power(int x, unsigned int y, int p)
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

// This function is called for all k trials. It returns
// false if n is composite and returns true if n is
// probably prime.
// d is an odd number such that d*2 = n-1
// for some r >= 1
int miillerTest(int d, int n)
{
	// Pick a random number in [2..n-1]
	int a = 2 + rand() % (n - 2);

	// Compute a^d % n
	int x = power(a, d, n);

	if (x == 1 || x == n - 1)
		return true;

	// Keep squaring x while one of the following doesn't
	// happen
	// (i) d does not reach n-1
	// (ii) (x^2) % n is not 1
	// (iii) (x^2) % n is not n-1
	while (d != n - 1)
	{
		x = (x * x) % n;
		d *= 2;

		if (x == 1)	 return false;
		if (x == n - 1) return true;
	}

	// Return composite
	return 0;
}

// It returns false if n is composite and returns true if n
// is probably prime. k is an input parameter that determines
// accuracy level. Higher value of k indicates more accuracy.
int isPrime(int n, int k)
{
	// Corner cases
	if (n < 2)
		return false;
	if (n == 2)
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
	for (int i = 0; i < k; i++)
		if (!miillerTest(t, n))
			return false;

	return true;
}

// Driver program
int main()
{
	int k = 3; // Number of iterations
	int n;

	printf("Input n: ");
	scanf("%d", &n);
	
	if (isPrime(n, k))
		printf("%d IS PRIME", n);
	else
		printf("%d IS COMPOSITE", n);
		
	return 0;
}
