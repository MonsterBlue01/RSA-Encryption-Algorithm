#include <gmp.h>    
#include <gmpxx.h>  
#include <iostream>

using namespace std;

void generate_n_bit_long_prime(mpz_class &n, int num_bits) {
    gmp_randstate_t state;
    gmp_randinit_default(state);

    clock_t seed = clock();
    seed = seed / (CLOCKS_PER_SEC / 1000000);
    gmp_randseed_ui(state, seed);
    mpz_urandomb(n.get_mpz_t(), state, num_bits);

    mpz_setbit(n.get_mpz_t(), 0);
    mpz_setbit(n.get_mpz_t(), num_bits - 1);

    while (mpz_probab_prime_p(n.get_mpz_t(), 25) == 0) {
        mpz_add_ui(n.get_mpz_t(), n.get_mpz_t(), 2);
    }

    gmp_randclear(state);
}

mpz_class find_coprime(mpz_class &phi) {
    gmp_randstate_t state;
    gmp_randinit_default(state);

    clock_t seed = clock();
    seed = seed / (CLOCKS_PER_SEC / 1000000);
    gmp_randseed_ui(state, seed);

    mpz_class e;
    e = 65537;

    while (mpz_gcd_ui(NULL, e.get_mpz_t(), phi.get_ui()) != 1) {
        mpz_add_ui(e.get_mpz_t(), e.get_mpz_t(), 2);
    }

    gmp_randclear(state);
    return e;
}

void generate_key_pair(int num_bits, mpz_class &e, mpz_class &d, mpz_class &n) {
    mpz_class p, q, phi;
    generate_n_bit_long_prime(p, num_bits);
    generate_n_bit_long_prime(q, num_bits);
    phi = (p - 1) * (q - 1);
    n = p * q;
    e = find_coprime(phi);
    mpz_invert(d.get_mpz_t(), e.get_mpz_t(), phi.get_mpz_t());
    std::cout << "p: " << p << std::endl;
    std::cout << "q: " << q << std::endl;
    std::cout << "phi: " << phi << std::endl;
    std::cout << "n: " << n << std::endl;
    std::cout << "e: " << e << std::endl;
    std::cout << "d: " << d << std::endl;
}

int main() {
    mpz_class e, d, n;
    generate_key_pair(4096, e, d, n);
    return 0;
}
