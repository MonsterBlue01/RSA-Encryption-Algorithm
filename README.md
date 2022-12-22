# RSA Cryptography

## Functions:

+ A function to generate prime numbers, which are necessary for RSA encryption and decryption
    - The `generate_n_bit_long_prime` function can use the mpz library to generate large random numbers. This can omit many problems caused by "regular" numbers such as long long.
+ A function to compute the greatest common divisor (gcd) of two numbers, which is used in the process of finding the private and public keys for RSA
    - The `gcd` function uses Euclid's algorithm to find the greatest common divisor of two numbers.
+ A function to compute the modular multiplicative inverse of a number, which is used in the RSA decryption process
    - The `mod_inverse` function uses the extended Euclidean algorithm to find the modular multiplicative inverse of a number.
+ A function to perform modular exponentiation, which is used in both the RSA encryption and decryption processes
    - The `mod_exp` function uses the right-to-left binary method to perform modular exponentiation.
+ A function to generate the public and private keys for RSA, using the prime numbers and other information generated by the above functions
+ A function to encrypt a message using the RSA algorithm and a public key
+ A function to decrypt a message using the RSA algorithm and a private key

## Steps for RSA encryption and decryption:

### Encryption:

1. Generate two prime numbers `p` and `q`
2. Compute `n = p * q`
3. Compute `phi(n) = (p - 1) * (q - 1)`
4. Choose an integer `e` such that `1 < e < phi(n)` and `gcd(e, phi(n)) = 1`
5. Compute `d` such that `d * e = 1 mod phi(n)`
6. Encrypt the message `m` using the public key `(e, n)` as follows:
    - `c = m^e mod n`

### Decryption:

1. Decrypt the message `c` using the private key `(d, n)` as follows:
    - `m = c^d mod n`

## References:

+ [RSA Algorithm](https://en.wikipedia.org/wiki/RSA_(cryptosystem)#Key_generation)
+ [Miller-Rabin Primality Test](https://en.wikipedia.org/wiki/Miller%E2%80%93Rabin_primality_test)
+ [Modular Multiplicative Inverse](https://en.wikipedia.org/wiki/Modular_multiplicative_inverse)
+ [Modular Exponentiation](https://en.wikipedia.org/wiki/Modular_exponentiation)
+ [Greatest Common Divisor](https://en.wikipedia.org/wiki/Greatest_common_divisor)
+ [Euclidean Algorithm](https://en.wikipedia.org/wiki/Euclidean_algorithm)
+ [Extended Euclidean Algorithm](https://en.wikipedia.org/wiki/Extended_Euclidean_algorithm)
+ [Modular Exponentiation](https://en.wikipedia.org/wiki/Modular_exponentiation#Right-to-left_binary_method)
+ [Modular Multiplicative Inverse](https://en.wikipedia.org/wiki/Modular_multiplicative_inverse#Computation)