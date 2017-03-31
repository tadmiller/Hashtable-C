/**
*
* @author Theodore Miller
* @description This .h file defines various useful functions that I am using for the HashTable.
*
*/

#ifndef etc_h
#define etc_h

// Returns base to the power of exp
int power(int base, int exp)
{
    if(exp <= 0)
        return 1;

    int result = 1;

    while (exp)
    {
        if (exp & 1)
            result *= base;

        exp >>= 1;
        base *= base;
    }

    return result;
}

// Checks if a number is prime.
bool is_prime(int p)
{   // Most common numbers are divisible by one of these three. Saves us some time.
    if (p % 2 == 0 || p % 3 == 0 || p % 5 == 0)
        return false;

    int i = 7;

    for (i; i < p; i += 2)
    {
        if (p % i == 0)
            return false;
    }

    return true;
}

/**
* Returns the next prime > p
*/
int next_prime(int p)
{
    while (!is_prime(++p));

    return p;
}

#endif
