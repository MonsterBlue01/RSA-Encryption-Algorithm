#include <gmp.h>    
#include <gmpxx.h>  
#include <iostream>
#include <exception>
#include <fstream>

using namespace std;

void generate_n_bit_long_prime(mpz_class &n, int num_bits);
mpz_class find_coprime(mpz_class &phi);
void generate_key_pair(int num_bits, mpz_class &e, mpz_class &d, mpz_class &n);
void encrypt(mpz_class &m, mpz_class &e, mpz_class &n, mpz_class &c);
void string_to_number(const std::string& str, mpz_class& n);
void number_to_string(const mpz_class& n, std::string& str);
void decrypt(mpz_class &c, mpz_class &d, mpz_class &n, mpz_class &m);