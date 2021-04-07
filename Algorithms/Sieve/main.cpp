#include <iostream>
#include "Sieve.h"
#include "../Powers/Powers.h"
#include "ctime"

#define BENCH_START 1
#define BENCH_END 9

#define TO_STRING(x) #x

int main() {

    std::vector<int> primes = sieve(100);
    std::cout << "|primes| = " << primes.size() << std::endl;
    for (auto val : primes)
        std::cout << val << std::endl;

    std::cout << "--------------------Benchmarking--------------------\n";
    std::cout << "Generating primes using sieve(n), n in [1e" << BENCH_START <<
              ", 1e" << BENCH_END << "]" << std::endl;
    double time_total = 0;
    long primes_total = 0;
    for (int i = BENCH_START; i <= BENCH_END; i++) {
        clock_t time_start = clock();
        long pi_i = sieve(pow_it(10, i)).size();
        double time_duration = (clock() - time_start) / double(CLOCKS_PER_SEC);
        time_total += time_duration;
        primes_total += pi_i;
        std::cout << "pi(1e" << i << ") = " << std::setw(BENCH_END < 12 ? 12 : 30) << pi_i <<
        " in " << std::setw(10) << time_duration << "s" << std::endl;
    }
    std::cout << "time spend generating " << primes_total << " primes: " << time_total << "s" << std::endl;
    return 0;
}
