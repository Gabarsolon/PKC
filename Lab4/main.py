from rsa import RSA

print("Generating RSA keys....")
rsa = RSA()
print("RSA keys generated successfully")
print("------------------------------------------")

while True:
    text = input("Input a text: ")
    encrypted_message = rsa.encrypt(text)
    print("Encrypted text: " + encrypted_message)
    print("Decrypted text: " + rsa.decrypt(encrypted_message))
    print("-----------------------------------------")
