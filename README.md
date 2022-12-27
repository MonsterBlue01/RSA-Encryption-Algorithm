# RSA Cryptography

## Usage:
```console
$ make
$ ./main
```

## Functions:

+ `generate_n_bit_long_prime`
    * Implement: The first thing to do is generate random numbers. Since the pseudo-random numbers generated using the same seeds are basically the same as ordinary numbers, the current time can be used as seeds as random numbers. After generating the random number, we need to ensure that the random number satisfies the provided parameters (specified bits). Then you need to make sure that the generated numbers are prime numbers. At first I tried to generate another one directly when a number was not random, but later found that it would be faster to directly increment the original number. The last step is to return the generated random number.
    * Function: This function is considered a helper function. It is an integral step in generating public key pairs and private key pairs.
+ `find_coprime`
    * Implement: From the point of view of mathematical principles, if you want to find numbers that are relatively prime to φ, try one by one slowly. But it can be optimized here. 65537 is suitable for most situations. So I start directly with 65537. If I encounter a number that is not relatively prime to 65537, I will slowly increment65537 until the condition is met again.
    * Function: This function can be understood as a helper function. When we generate private key pair and public key pair, there is a step to calculate φ = (p-1)*(q-1). Then we need to find a number that is relatively prime to φ. This function can be used at that time. Of course, this can actually be implemented directly in that function, but hierarchy can reduce the complexity of the code, so I think this can make the program easier to debug.

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