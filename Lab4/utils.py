import random
import math

ASCII_CODE_OF_A = 65

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


def miller_test(n, a, s, t):
    x = repeatedSquaringModularExponentiation(a, t, n)
    if x == 1:
        return True

    prev_x = x
    for j in range(1, s + 1):
        x = repeatedSquaringModularExponentiation(a, 2 ** j * t, n)
        if x == 1:
            if prev_x == n - 1:
                return True
            return False
        prev_x = x

    return False


def isMillerRabinPassed(n):
    '''Run 20 iterations of Rabin Miller Primality test'''
    k = 20

    s = 0
    t = n - 1
    while t % 2 == 0:
        s += 1
        t = t // 2

    a = 2
    if miller_test(n, a, s, t) is False:
        return False

    a = 3
    for i in range(1, k):
        if miller_test(n, a, s, t) is False:
            return False
        a += 2

    return True


def generate_random_prime(number_of_bits):
    while True:
        candidate = getLowLevelPrime(number_of_bits)
        if isMillerRabinPassed(candidate) is False:
            continue
        return candidate


def euclid(a, b):
    while b != 0:
        r = a % b
        a = b
        b = r
    return a


def random_natural_number_smaller_and_coprime_with_another_number(n):
    while True:
        e = random.randrange(2, n)
        if euclid(e, n) == 1:
            return e


def letter_to_numerical_equivalent(letter):
    return 0 if letter == '_' else ord(letter.upper()) - ASCII_CODE_OF_A + 1


def numerical_equivalent_to_letter(n):
    return '_' if n == 0 else chr(ASCII_CODE_OF_A + n - 1).upper()


def string_to_numerical_equivalent(text):
    p = 1
    result = 0
    for letter in reversed([*text]):
        result += letter_to_numerical_equivalent(letter) * p
        p *= 27
    return result


def numerical_equivalent_to_string(n, l):
    string_equivalent = ""
    for i in range(0, l):
        string_equivalent = numerical_equivalent_to_letter(n % 27) + string_equivalent
        n = n // 27
    return string_equivalent


def gcd_extended(a, b):
    """ Calculates the gcd and Bezout coefficients,
    using the Extended Euclidean Algorithm (non-recursive).
    """
    # Set default values for the quotient, remainder,
    # s-variables and t-variables
    q = 0
    r = 1
    s1 = 1
    s2 = 0
    s3 = 1
    t1 = 0
    t2 = 1
    t3 = 0

    '''
    In each iteration of the loop below, we
    calculate the new quotient, remainder, a, b,
    and the new s-variables and t-variables.
    r decreases, so we stop when r = 0
    '''
    while (r > 0):
        # The calculations
        q = math.floor(a / b)
        r = a - q * b
        s3 = s1 - q * s2
        t3 = t1 - q * t2

        '''
        The values for the next iteration, 
        (but only if there is a next iteration)
        '''
        if (r > 0):
            a = b
            b = r
            s1 = s2
            s2 = s3
            t1 = t2
            t2 = t3

    return abs(b), s2, t2


def multinv(e, phi):
    # Get the gcd and the second Bezout coefficient (t)
    # from the Extended Euclidean Algorithm. (We don't need s)
    my_gcd, _, t = gcd_extended(phi, e)

    # It only has a multiplicative inverse if the gcd is 1
    if (my_gcd == 1):
        return t % phi
    else:
        raise ValueError('{} has no multiplicative inverse modulo {}'.format(e, phi))
