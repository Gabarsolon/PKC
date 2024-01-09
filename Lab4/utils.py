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


def isMillerRabinPassed(n):
    '''Run 20 iterations of Rabin Miller Primality test'''
    maxDivisionsByTwo = 0
    ec = n - 1
    while ec % 2 == 0:
        ec >>= 1
        maxDivisionsByTwo += 1
    assert (2 ** maxDivisionsByTwo * ec == n - 1)

    def trialComposite(round_tester):
        if pow(round_tester, ec, n) == 1:
            return False
        for i in range(maxDivisionsByTwo):
            if pow(round_tester, 2 ** i * ec, n) == n - 1:
                return False
        return True

    # Set number of trials here
    numberOfRabinTrials = 20
    for i in range(numberOfRabinTrials):
        round_tester = random.randrange(2, n)
        if trialComposite(round_tester):
            return False
    return True


def generate_random_prime(number_of_bits):
    while True:
        candidate = getLowLevelPrime(number_of_bits)
        if isMillerRabinPassed(candidate) is False:
            continue
        return candidate
