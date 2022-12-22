#include <gmp.h>
#include <gmpxx.h>
#include <iostream>

using namespace std;

void generate_n_bit_long_prime(mpz_t n, int num_bits) {
    gmp_randstate_t state;
    gmp_randinit_default(state);

    clock_t seed = clock();
    seed = seed / (CLOCKS_PER_SEC / 1000000);
    gmp_randseed_ui(state, seed);
    mpz_urandomb(n, state, num_bits);

    mpz_setbit(n, 0);
    mpz_setbit(n, num_bits - 1);

    while (mpz_probab_prime_p(n, 25) == 0) {
        mpz_add_ui(n, n, 2);
    }

    gmp_randclear(state);
}

void get_gcd(mpz_t result, const mpz_t a, const mpz_t b) {
    mpz_gcd(result, a, b);                                  // Calculate the GCD of a and b and store it in result
}

int main() {
    mpz_t n;
    for (int i = 0; i < 10; i++) {
        generate_n_bit_long_prime(n, 4096);
        std::cout << n << std::endl;
    }
    std::cout << n << std::endl;
    return 0;
}