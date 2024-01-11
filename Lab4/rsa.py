import math

import utils

KEY_BIT_LENGTH = 1024


class RSA:
    def __init__(self):
        # generate the keys and required variables
        self.p = utils.generate_random_prime(KEY_BIT_LENGTH)
        self.q = utils.generate_random_prime(KEY_BIT_LENGTH)
        self.n = self.p * self.q
        self.phi = (self.p - 1) * (self.q - 1)
        self.e = utils.random_natural_number_smaller_and_coprime_with_another_number(self.phi)
        # plaintext block size
        self.k = int(math.log(self.n, 27))
        # ciphertext block size
        self.l = self.k + 1

        self.public_key = (self.n, self.e)

        self.private_key=(utils.multinv(self.e,self.phi))


    def encrypt(self, plaintext):
        # split the text and write the numerical equivalents
        splitted_text = []
        for i in range(0, len(plaintext), self.k):
            splitted_text.append(plaintext[i:self.k + i])

        # add blank spaces if the last split term is smaller than k block size
        while len(splitted_text[-1]) < self.k:
            splitted_text[-1] += '_'

        # write the numerical equivalents
        numerical_equivalents = []
        for splitted_term in splitted_text:
            numerical_equivalent = utils.string_to_numerical_equivalent(splitted_term)
            numerical_equivalents.append(numerical_equivalent)

        # encrypt m^e mod n
        encrypted_numerical_equivalents = []
        for numerical_equivalent in numerical_equivalents:
            encrypted_numerical_equivalent = \
                utils.repeatedSquaringModularExponentiation(numerical_equivalent, self.e, self.n)
            encrypted_numerical_equivalents.append(encrypted_numerical_equivalent)

        # write the literal equivalents
        ciphertext = ""
        for encrypted_numerical_equivalent in encrypted_numerical_equivalents:
            ciphertext += utils.numerical_equivalent_to_string(encrypted_numerical_equivalent, self.l)

        return ciphertext


    def decrypt(self, ciphertext):
    # Split the ciphertext into blocks of size self.l
        ciphertext_blocks = []
        for i in range(0, len(ciphertext), self.l):
            block = ciphertext[i:i + self.l]
            ciphertext_blocks.append(block)

    # Convert each block back to numerical equivalents
        numerical_equivalents = []
        for block in ciphertext_blocks:
            numerical_equivalent = utils.string_to_numerical_equivalent(block)
            numerical_equivalents.append(numerical_equivalent)

    # Decrypt c^d mod n for each block
        decrypted_numerical_equivalents = []
        for numerical_equivalent in numerical_equivalents:
            decrypted_numerical_equivalent = utils.repeatedSquaringModularExponentiation(numerical_equivalent, self.private_key, self.n)
            decrypted_numerical_equivalents.append(decrypted_numerical_equivalent)

    # Convert the numerical equivalents back to the original message
        decrypted_message = ""
        for num in decrypted_numerical_equivalents:
            decrypted_message += utils.numerical_equivalent_to_string(num, self.k)

        return decrypted_message.rstrip('_')  # Remove trailing underscores added during encryption

