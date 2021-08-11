#include <stdio.h>
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>
#include <vector>



using namespace std;


// Checks if number is prime
// @param n  integer to be checked
// @return true or false
bool isPrime(long long n)
{
    // Corner cases
    if (n < 2){
        return false;
    }
    // Check from 2 to n-1
    for (int i = 2; i < sqrt(n); i++){
        if (n % i == 0){
            return false;
        }
    }
    return true;
}



// Finds the greatest common divisor of two integers a and b \n
// source: https://www.inf.hs-flensburg.de/lang/krypto/algo/euklid.htm#section3
// @param a first integer
// @param b second integer
// @return u 
unsigned long long extgcd(unsigned long long a, unsigned long long b)
{
    unsigned long long q = 0;

    unsigned long long u = 1;
    unsigned long long s = 0;

    unsigned long long v = 0;
    unsigned long long t = 1;
    
    unsigned long long temp = 0;
    unsigned long long temp2 = 0;
    unsigned long long temp3 = 0;

    while(b != 0)
    {
        q = a / b;
        
        temp = b;
        b = a - q*b;
        a = temp;

        temp2 = s;
        s = u - q*s;
        u = temp2;

        temp3 = t;
        t = v - q*t;
        v = temp3;
    }

    return u;
}



// https://www.inf.hs-flensburg.de/lang/krypto/grund/inverses-element.htm
// @param a
// @param b
unsigned long long modinverse(unsigned long long a, unsigned long long n)
{
    unsigned long long u = extgcd(a, n);
    return u%n;
}

int createKeys()
{
    unsigned long long s, t;
    const int e = 65535; // constant e (2^16-1)
    unsigned long long phi = 0;
    int n = 0;
    unsigned long long p = 0;
    unsigned long long q = 0;

    cout << "Encoding works with two prime numbers \n";

    while(true)
    {
        
        cout << "Choose your first prime number: \n ";
        cin >> p;

        usleep(100);
        while(cin.fail()) {
            cout << "Error. Not a number. \n ";
            cin.clear();
            cin.ignore(256,'\n');
            cin >> p;
        }
        usleep(100);
        while(!isPrime(p)) {
            cout << "Error. Not prime. \n ";
            cin.clear();
            cin.ignore(256,'\n');
            cin >> p;
        }
        usleep(100);

       
        cout << "Choose your second prime number: \n ";
        cin >> q;

        usleep(100);
        while(cin.fail()) {
            cout << "Error. Not a number. \n ";
            cin.clear();
            cin.ignore(256,'\n');
            cin >> q;
        }
        usleep(100);
        while(!isPrime(q)) {
            cout << "Error. Not prime. \n ";
            cin.clear();
            cin.ignore(256,'\n');
            cin >> q;
        }
        usleep(1000);


        n = p*q;
        phi = (p-1) * (q-1);

        if(phi <= e){
            cout << "Those prime numbers are not big enough. \n";
        }else{
            cout << "Success! \n";
            break;
        }
    }


    unsigned long long d = modinverse(e, phi);
    // unsigned long long d = gcdExtendedRecursive(p, q, &s, &t);
    cout << "Public key: " << e << " " << n << endl;
    cout << "Private key: " << d << " " << n << endl;
    phi = 0;
    p = 0;
    q = 0;


    return 0;
 
    // d * e === 1 (mod Phi)
    // print out public and privare key
    // remove p, q and phi from memory
}

// https://en.wikipedia.org/wiki/Modular_exponentiation
// @param base
// @param exponent
// @param modulus
long long modular_pow(long long base, long long exponent, long long modulus)
{
    if(modulus == 1)
    {
        return 0;
    }

    unsigned long long c = 1;
    for(int i = 0; i < exponent; i++)
    {   
        c *= base;
        c = c % modulus;
    }
    
    return c;

    /*

    

    function modular_pow(base, exponent, modulus) is
    if modulus = 1 then
        return 0
    c := 1
    for e_prime = 0 to exponent-1 do
        c := (c * base) mod modulus
    return c
    */
}




unsigned long long encryption()
{
    unsigned long long b; cin >> b; // TODO: string
    unsigned long long e; cin >> e;
    unsigned long long n; cin >> n;


    unsigned long long c = modular_pow(b, e, n);

    cout << "Cypher: " << c << endl;


    return c;
}

unsigned long long decryption()
{
    unsigned long long c; cin >> c; // cypher message
    unsigned long long d; cin >> d; // private key
    unsigned long long n; cin >> n; // second part of private key


    unsigned long long m = modular_pow(c, d, n); // TODO: translate to String

    cout << "Message: " << m << endl;

    return m;
}

// source: https://www.geeksforgeeks.org/print-all-prime-factors-of-a-given-number/
// @param factors vector of factors of n
// @param n integer for prime factorization
void primeFactors(vector<unsigned long long>& factors, long long n)
{
    // This condition is to handle the case when n
    // is a prime number greater than 2
   
    
    // Print the number of 2s that divide n
    while (n % 2 == 0)
    {
        factors.push_back(2);
        n = n/2;
        cout << "2 and " << n << endl;

    }
 
    // n must be odd at this point. So we can skip
    // one element (Note i = i +2)
    for (int i = 3; i <= sqrt(n); i = i + 2)
    {
        // While i divides n, print i and divide n
        while (n % i == 0)
        {
            factors.push_back(i);
            n = n/i;
        }
    }
    if (isPrime(n))
    {
        factors.push_back(n);
    }
    return;
}
// Test xD







unsigned long long rsaFactoring(long long c, unsigned long long e, unsigned long long n)
{
    vector<unsigned long long> factors;
    unsigned long long phi = 1;

    primeFactors(factors, n);
    // C++ 11 part
    for (auto &i : factors)
    {
        phi *= i-1;
    }

    unsigned long long d = modinverse(e, phi);



    return d;
}



















// Choose between creating keys, encryption, decryption and rsaFactoring
int main()
{
    while(true)
    {
        //  Menu
        cout << "-------------------------------------------------------" << endl;
        cout << "Welcome to the RSA calculator:" << endl;
        cout << "To create a new key pair - press :c" << endl;
        cout << "To encrpyt a message with the public key - press: e" << endl;
        cout << "To deencrpyt a message with the private key - press: d" << endl;
        cout << "To get the private key from the public key - press: f" << endl;
        cout << "To quit - press: q" << endl;
        cout << "-------------------------------------------------------" << endl;
        cout << "Input: ";
        char state; cin >> state;
        usleep(10000);
        // create Keys
        if(strcmp(&state, "c") == 0)
        {
            cin.clear();
            createKeys();
        }
        // Encrypt message
        else if(strcmp(&state, "e") == 0)
        {
            cin.clear();
            encryption();
        }
        // Decrypt message
        else if(strcmp(&state, "d") == 0)
        {
            cin.clear();
            decryption();
        }
        // Get the private Key from the public key using prime factorisation
        else if(strcmp(&state, "f") == 0)
        {
            // Inputs
            cout << "Enter ciphered message: ";
            long long c; cin >> c;
            cout << "Enter first part of public key: ";
            unsigned long long e; cin >> e;
            cout << "Enter second part if public key: ";
            unsigned long long n; cin >> n;
            
            unsigned long long d = rsaFactoring(c, e, n);

            // Outputs
            cout << "Public key: " << e << " " << n << endl;
            cout << "Private key: " << d << " " << n << endl;
        }
        // Quit program
        else if(strcmp(&state, "q") == 0){
            break;

        }
    }
    return 0;
}
