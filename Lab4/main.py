from rsa import RSA

rsa = RSA()
plaintext = "HELLO_WORLD"
ciphertext = rsa.encrypt(plaintext)
decrypted_message = rsa.decrypt(ciphertext)
print("Original message:", plaintext)
print("Ciphertext:", ciphertext)
print("Decrypted message:", decrypted_message)