#ifndef HEADER_H
#define HEADER_H


#include <stdio.h>
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>
#include <vector>

// obviously
using namespace std;

// Checks if number is prime
// @param n  integer to be checked
// @return true or false
bool isPrime(long long n);

// Finds the greatest common divisor of two integers a and b \n
// source: https://www.inf.hs-flensburg.de/lang/krypto/algo/euklid.htm#section3 12.08.2021
// @param a first integer
// @param b second integer
// @returns u (only variable that is needed in this code)
unsigned long long extgcd(unsigned long long a, unsigned long long b);

// source: https://www.inf.hs-flensburg.de/lang/krypto/grund/inverses-element.htm 12.08.2021
// @param a inverse to be calculated
// @param n modulo number
// @returns the modinverse
unsigned long long modinverse(unsigned long long a, unsigned long long n);

// simple struct to return three results
struct result{
    unsigned long long e; // first public key part
    unsigned long long d; // first private key part
    unsigned long long n; // second private and public key part
};

// Creates the public and private key pairs
// @returns results as a struct with the key pairs
result createKeys();

// Modular exponentiation (b^e mod m) \n
// source: https://en.wikipedia.org/wiki/Modular_exponentiation 12.08.2021
// @param base integer b
// @param exponent exponent of integer b 
// @param modulus divided by integer m
// @return c the remainder
unsigned long long modular_pow(unsigned long long base, unsigned long long exponent, unsigned long long modulus);


// decrypts numbers with c = m^e mod n
// @param m number to be ciphered
// @param e first part of public key
// @param n second part if public key
// @return c the ciphered number
unsigned long long encryption(unsigned long long m, unsigned long long e, unsigned long long n);

// decrypts numbers with m = c^d mod n
// @param c ciphered number
// @param d first part of private key
// @param n second part if private key
// @return m the decrypted number
unsigned long long decryption(unsigned long long c, unsigned long long d, unsigned long long n);

// source: https://www.geeksforgeeks.org/print-all-prime-factors-of-a-given-number/ 12.08.2021
// @param factors vector of factors of n
// @param n integer for prime factorization
void primeFactors(vector<unsigned long long>& factors, long long n);

// finds the private key form the public key with help of prime factorization
// @param e first part of public key 
// @param n second part of public key
// @returns d the first part of the private key
unsigned long long rsaFactoring(unsigned long long e, unsigned long long n);

#endif