/*
 *
 *
 * TODO: do it right ffs
 *
 *
 * */

#ifndef SIEVE_SEGMENTED_SIEVE_H
#define SIEVE_SEGMENTED_SIEVE_H
#endif //SIEVE_SEGMENTED_SIEVE_H

#define DEFAULT_STEPS 100

class SegmentedSieve {
private:
    // using segment = std::pair<long, long>;
    std::vector<int> m_primes;
    long m_last_segment;
    unsigned int m_expand_steps;
public:

    SegmentedSieve(unsigned int steps) : m_expand_steps(steps), m_last_segment(0) {};
    SegmentedSieve() : SegmentedSieve(DEFAULT_STEPS) {};

    void expand(unsigned int expand_steps) {
        m_expand_steps = expand_steps;
        expand();
    }

    void expand() {

        std::vector<bool> is_prime(m_expand_steps, true);
        unsigned int s = m_last_segment;
        unsigned int n = m_last_segment + m_expand_steps;
        m_last_segment = n;

        // 1. go through existing primes and cross out their multiples
        for (auto prime : m_primes) {
            for (int i = prime * prime; i <= n; i += prime)
                is_prime[i - s - 1] = false;
        }

        // 2. go to segment start and sieve until segment end
        for (int i = s; i * i < n; i++) {
            if (!is_prime[i - s - 1]) continue;
            for (int j = i * i; j <= n; j += i)
                is_prime[j - s - 1] = false;
        }

        // 3. add primes to vector
        for (int i = 0; i < is_prime.size(); ++i)
            if (is_prime[i])
                m_primes.push_back(i + s);

        // 4. realize you fucked up and have to do a thing between some 2 primes you already generated and then do further things
    }

    std::vector<int> Primes() {
        return m_primes;
    }
};