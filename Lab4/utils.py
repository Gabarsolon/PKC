import random

ASCII_CODE_OF_A = 65


def letter_to_numerical_equivalent(letter):
    return 0 if letter == '_' else letter.upper() - ASCII_CODE_OF_A + 1


# Pre generated primes
first_primes_list = [2, 3, 5, 7, 11, 13, 17, 19, 23, 29,
                     31, 37, 41, 43, 47, 53, 59, 61, 67,
                     71, 73, 79, 83, 89, 97, 101, 103,
                     107, 109, 113, 127, 131, 137, 139,
                     149, 151, 157, 163, 167, 173, 179,
                     181, 191, 193, 197, 199, 211, 223,
                     227, 229, 233, 239, 241, 251, 257,
                     263, 269, 271, 277, 281, 283, 293,
                     307, 311, 313, 317, 331, 337, 347, 349]


def nBitRandom(n):
    # Returns a random number
    # between 2**(n-1)+1 and 2**n-1'''
    return random.randrange(2 ** (n - 1) + 1, 2 ** n - 1)


def getLowLevelPrime(n):
    '''Generate a prime candidate divisible
    by first primes'''
    while True:
        # Obtain a random number
        pc = nBitRandom(n)

        # Test divisibility by pre-generated
        # primes
        for divisor in first_primes_list:
            if pc % divisor == 0 and divisor ** 2 <= pc:
                break
        else:
            return pc


def repeatedSquaringModularExponentiation(base, exponent, modulus):
    """
    Function used to compute the remainder of base^exponent divided by modulus
    base ^ exponent = remainder (modulus)
    :param base: number in [2, number-1)
    :param exponent: 2^s * d
    :param modulus: composite odd number (2^s * d + 1)
    :return: remainder
    """
    if modulus == 1:
        return 0  # n%1 == 0 always true
    remainder = 1  # we assume that the remainder is 1
    base = base % modulus
    while exponent > 0:
        if exponent % 2 == 1:
            remainder = (remainder * base) % modulus  # remainder is multiplied by base and we get the new remainder
        exponent = exponent // 2
        base = (base * base) % modulus  # continue squaring
    return remainder


def millerTest(n, a, s, t):
    x = repeatedSquaringModularExponentiation(a, t, n)

    if x == 1:
        return True

    prevX = x
    for j in range(1, s + 1):
        x = repeatedSquaringModularExponentiation(a, 2 ** j * t, n)
        if x == 1:
            if prevX == n - 1:
                return True
            else:
                return False
        prevX = x

    return False


def isMillerRabinPassed(n):
    '''Run 20 iterations of Rabin Miller Primality test'''
    k = 3

    # Find s and t such that n - 1 = 2 ^ s * t
    s = 0
    t = n - 1
    while t % 2 == 0:
        s += 1
        t = t / 2

    a = 2
    if millerTest(n, a, s, t) is False:
        return False

    a = 3
    for i in range(1, k):
        if millerTest(n, a, s, t) is False:
            return False
        a += 2

    return True
