# RSA-encryption-decryption

 This program can create simple key pairs (public and private), cipher and decipher numbers and find the private key with help of the public key.

All the functions (expecet main) are in the header.h file with comments. One command to run this code in the terminal is:

"g++ main.cpp -include header.h -o main" and "./main" afterwards (both without quotation marks).

> Currently the program will crash if you don't enter integers, this will be fixed soon. There is one C++11 part in the rsaFactoring function.
I hope you enjoy this code and I'd love some feedback.


# Math behind the code

### Creating Key pairs
1. Choose two prime number p and q
2. n = p * q
3. phi(n) = (p-1) * (q-1) (https://en.wikipedia.org/wiki/Euler%27s_totient_function, 12.08.2021)
4. e is usally a constant of 65535 or 2^16 - 1.
5. Check if 1 < phi(n) > e
6. solve for d with d * e ≡ 1 mod phi(n)

public key = (e, n)
private key = (d, n)


### Cipher

c - ciphered number
m - deciphered number
e - first part of public key
n - second part of public key

c = m^e mod n


### Decipher

c - ciphered number
m - deciphered number
d - first part of private key
n - second part of private key

m = c^d mod n


### Get private key with public key

e - first part of public key
d - first part of private key
n - second part of private and public key

1. Find the prime factors of n 
(e.g. 3*5 = 15, prime factors of 15 are 3 and 5)
2. Find phi(n) with help of the prime factors
(e.g. phi(15) = (3-1)*(5-1) = 8
3. solve for d with d * e ≡ 1 mod phi(n)



AUG 2021
