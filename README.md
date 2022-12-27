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
+ `generate_key_pair`
    * Implement: The first thing to do is to generate two large prime numbers using `generate_key_pair`. Next, subtract one from the two large prime numbers and multiply them together to get φ. Then multiply the original two large prime numbers directly to get n. The next step is to find numbers that are relatively prime to φ. The previous `find_coprime` can be used in this step. All that needs to be done is to find a number that is relatively prime to φ and define it as e. The next step is to find the multiplicative inverse of e mod φ. Since the entire program is implemented based on the GMP library, mpz_invert can better implement this function. After this step, all the most basic calculations to generate a key pair are done.
    * Function: What this function does is generate a private key pair and a public key pair. The private key pair is used to decrypt information, and the public key pair is used to encrypt information.
+ `encrypt`
    * Implement: Encryption is generally achieved by $c = m^e\mod n$. Since this program is implemented based on the GMP library, mpz_pown can fulfill this mission very well.
    * Function: This function is used to encrypt the numbers converted from text.
+ `string_to_number`
    * Implement: The string_to_number function converts a string to a number by interpreting each character in the string as a number in the base-256 number system. For example, the string $1234$ will be converted to $1 \times 256^3 + 2 \times 256^2 + 3 \times 256^1 + 4 \times 256^0$.
    * Function: Since RSA encryption is basically implemented based on mathematical calculations, it may be difficult to directly encrypt strings. So a better way is to convert the string to a 256-base number and then implement encryption.
+ `decrypt`
    * Implement: Decryption is generally achieved by $m = c^d\mod n$. Since this program is implemented based on the GMP library, mpz_pown can fulfill this mission very well.
    * Function: This function is used to decrypt numbers that were ever converted from strings.
+ `number_to_string`
    * Implement: The way this function implements converting numbers to strings is the opposite of converting strings to numbers before. This function will only operate a byte at the same time and convert it to the corresponding character.
    * Function: Since the string was converted to a number earlier, the number needs to be converted to a string now.

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