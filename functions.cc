#include "functions.hh"

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
    mpz_class e;
    e = 65537;

    while (mpz_gcd_ui(NULL, e.get_mpz_t(), phi.get_ui()) != 1) {
        mpz_add_ui(e.get_mpz_t(), e.get_mpz_t(), 2);
    }
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
}

void encrypt(mpz_class &m, mpz_class &e, mpz_class &n, mpz_class &c) {
    mpz_powm(c.get_mpz_t(), m.get_mpz_t(), e.get_mpz_t(), n.get_mpz_t());
}

void string_to_number(const std::string& str, mpz_class& n) {
    n = 0;
    for (char c : str) {
        n <<= 8;
        n += c;
    }
}

void number_to_string(const mpz_class& n, std::string& str) {
    str = "";
    mpz_class m = n;
    while (m != 0) {
        char c = m.get_si() & 0xff;
        str = c + str;
        m >>= 8;
    }
}

void decrypt(mpz_class &c, mpz_class &d, mpz_class &n, mpz_class &m) {
    mpz_powm(m.get_mpz_t(), c.get_mpz_t(), d.get_mpz_t(), n.get_mpz_t());   // m = c^d mod n
}