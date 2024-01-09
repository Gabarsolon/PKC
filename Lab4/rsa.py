import utils

KEY_BIT_LENGTH = 1024


class RSA:
    def __init__(self, k, l):
        # plaintext block size
        self.k = k
        # ciphertext block size
        self.l = l
        # generate the keys and required variables
        self.p = utils.generate_random_prime(KEY_BIT_LENGTH)
        self.q = utils.generate_random_prime(KEY_BIT_LENGTH)
        self.n = self.p * self.q
        self.phi = (self.p - 1) * (self.q - 1)
        self.e = utils.random_natural_number_smaller_and_coprime_with_another_number(self.phi)

        # TODO: Compute private key

        self.public_key = (self.n, self.e)

    def encrypt(self, plaintext):
        # split the text and write the numerical equivalents
        numerical_equivalents = []
        for i in range(0, len(plaintext), self.k):
            numerical_equivalents.append(plaintext[i:self.k])
