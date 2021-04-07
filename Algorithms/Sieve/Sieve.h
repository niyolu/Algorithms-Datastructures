//
// Created by NiJoL on 07.04.2021.
//

#ifndef SIEVE_SIEVE_H
#define SIEVE_SIEVE_H

#include <iostream>
#include <iomanip>
#include <vector>

std::vector<int> sieve(unsigned int n) {
    std::vector<bool> isPrime(n, true);
    for (int i = 2; i*i < n; i++) {
        if (!isPrime[i - 1]) continue;
        for (int j = 2*i; j <= n; j += i)
            isPrime[j - 1] = false;
    }
    std::vector<int> primes;
    for (int i = 1; i < isPrime.size(); i++)
        if (isPrime[i])
            primes.push_back(i + 1);
    return primes;
}
#endif //SIEVE_SIEVE_H
