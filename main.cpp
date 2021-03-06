#include "header.h"

// obviously
using namespace std;



bool isPrime(long long n)
{
    // Corner case 2
    if(n == 2)
    {
        return true;
    }
    // Filter numbers
    else if (n < 2 || n%2 == 0)
    {
        return false;
    }
    // Check from 2 to n-1, only odd numbers
    for (int i = 3; i < sqrt(n); i += 2)
    {
        if (n % i == 0)
        {
            return false;
        }
    }
    return true;
}



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



unsigned long long modinverse(unsigned long long a, unsigned long long n)
{
    unsigned long long u = extgcd(a, n);
    return u%n;
}



result createKeys()
{
    const int e = 65535; // constant e (2^16-1) part of the public key 
    unsigned long long  n = 0; // n = p*q
    unsigned long long phi = 0; // phi(n) = (p-1)*(q-1) https://en.wikipedia.org/wiki/Euler%27s_totient_function 12.08.2021
    unsigned long long p = 0; // first prime number
    unsigned long long q = 0; // second prime number

    cout << "Encoding works with two prime numbers \n";

    while(true)
    {
        // Input of first prime number
        cout << "Choose your first prime number: \n ";
        cin >> p;
        usleep(100);
        while(cin.fail())
        {
            cout << "Error. Not a number. \n ";
            cin.clear();
            cin.ignore(256,'\n');
            cin >> p;
        }
        usleep(100);
        while(!isPrime(p))
        {
            cout << "Error. Not prime. \n ";
            cin.clear();
            cin.ignore(256,'\n');
            cin >> p;
        }
        usleep(100);


        // Input of second prime number
        cout << "Choose your second prime number: \n ";
        cin >> q;
        usleep(100);
        while(cin.fail())
        {
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


        // Calucaltions of n, phi(n) and checking if phi > e
        n = p*q;
        phi = (p-1) * (q-1);
        if(phi <= e)
        {
            cout << "Those prime numbers are not big enough. \n";
        }else
        {
            cout << "Success! \n";
            break;
        }
    }

    unsigned long long d = modinverse(e, phi);

    // Overwriting phi, p, q
    phi = 0;
    p = 0;
    q = 0;
    result results = {e, d, n};
    return results;
}



unsigned long long modular_pow(unsigned long long base, unsigned long long exponent, unsigned long long modulus)
{
    // Corner cases
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
}



unsigned long long encryption(unsigned long long m, unsigned long long e, unsigned long long n)
{
    unsigned long long c = modular_pow(m, e, n);
    return c;
}



unsigned long long decryption(unsigned long long c, unsigned long long d, unsigned long long n)
{
    unsigned long long m = modular_pow(c, d, n); // TODO: translate to String
    return m;
}



void primeFactors(vector<unsigned long long>& factors, long long n)
{
    // This condition is to handle the case when n
    // is a prime number greater than 2
   
    
    // Print the number of 2s that divide n
    while (n % 2 == 0)
    {
        factors.push_back(2);
        n = n/2;
        if(factors.size() == 2)
        {
            return;
        }

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
            if(factors.size() == 2)
            {
            return;
            }
        }
    }
    if (isPrime(n))
    {
        factors.push_back(n);
    }
    return;
}



unsigned long long rsaFactoring(unsigned long long e, unsigned long long n)
{
    vector<unsigned long long> factors;
    unsigned long long phi = 1;

    primeFactors(factors, n);
    
    // C++ 11 part
    for(auto &i : factors)
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
        cout << "To create a new key pair - press: c" << endl;
        cout << "To encrpyt a number with the public key - press: e" << endl;
        cout << "To decrpyt a number with the private key - press: d" << endl;
        cout << "To get the private key from the public key - press: f" << endl;
        cout << "To quit - press: q" << endl;
        cout << "-------------------------------------------------------" << endl;
        cout << "Input: ";
        char state; cin >> state;
        usleep(10000);
        // create Keys
        if(strcmp(&state, "c") == 0)
        {
            // Inputs inside the function, because they have to be checked for prime numbers
            unsigned long long e; unsigned long long d; unsigned long long n;
            result results = createKeys();

            // Ouputs
            cout << "Public key: " << results.e << " " << results.n << endl;
            cout << "Private key: " << results.d << " " << results.n << endl;
        }
        // Encrypt message
        else if(strcmp(&state, "e") == 0)
        {
            // Inputs
            cout << "Enter number to cipher: ";
            unsigned long long m; cin >> m;
            cout << "Enter first part of public key: ";
            unsigned long long e; cin >> e;
            cout << "Enter second part of public key: ";
            unsigned long long n; cin >> n;
            
            unsigned long long c = encryption(m, e, n);

            // Output
            cout << "Ciphered number: " << c << endl;
        }
        // Decrypt message
        else if(strcmp(&state, "d") == 0)
        {
            // Inputs
            cout << "Enter ciphered number: ";
            unsigned long long c; cin >> c;
            cout << "Enter first part of private key: ";
            unsigned long long d; cin >> d;
            cout << "Enter second part if private key: ";
            unsigned long long n; cin >> n;

            unsigned long long m = decryption(c, d, n);

            // Ouput
            cout << "Decrypted number: " << m << endl;
        }
        // Get the private Key from the public key using prime factorisation
        else if(strcmp(&state, "f") == 0)
        {
            // Inputs
            cout << "Enter first part of public key: ";
            unsigned long long e; cin >> e;
            cout << "Enter second part if public key: ";
            unsigned long long n; cin >> n;
            
            unsigned long long d = rsaFactoring(e, n);

            // Outputs
            cout << "Public key: " << e << " " << n << endl;
            cout << "Private key: " << d << " " << n << endl;
        }
        // Quit program
        else if(strcmp(&state, "q") == 0)
        {
            break;

        }
    }
    return 0;
}
