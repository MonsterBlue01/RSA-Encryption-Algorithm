#include <gmp.h>    
#include <gmpxx.h>  
#include <iostream>
#include <exception>
#include <fstream>

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
    mpz_powm(m.get_mpz_t(), c.get_mpz_t(), d.get_mpz_t(), n.get_mpz_t());
}

int main() {
    cout << "Do you want to encrypt or decrypt? (e/d): ";
    char choice;
    cin >> choice;
    while (choice != 'e' && choice != 'd') {
        cout << "Invalid choice. Please enter e or d: ";
        cin >> choice;
    }
    if (choice == 'e') {
        cout << "Do you want to use a file or standard input? (f/s): ";
        cin >> choice;
        while (choice != 'f' && choice != 's') {
            cout << "Invalid choice. Please enter f or s: ";
            cin >> choice;
        }
        if (choice == 'f') {
            cout << "Enter file name: ";
            string file_name;
            cin >> file_name;
            ifstream file(file_name);
            while (!file.is_open()) {
                cout << "Something is wrong. Please enter a valid file name: ";
                cin >> file_name;
                file.open(file_name);
            }
            string contents;
            string line;
            while (getline(file, line)) {
                contents += line + "\n";
            }
            mpz_class m;
            string_to_number(contents, m);
            cout << "Do you already have a key pair? (y/n): ";
            while (choice != 'y' && choice != 'n') {
                cout << "Invalid choice. Please enter y or n: ";
                cin >> choice;
            }
            if (choice == 'y') {
                cout << "Enter the public key(The e in [n, e]): ";
                mpz_class e;
                cin >> e;
                cout << "Enter the modulus(The n in [n, e]): ";
                mpz_class n;
                cin >> n;
                mpz_class c;
                encrypt(m, e, n, c);
                cout << "Encrypted message: " << c << endl;
                file.close();
            } else if (choice == 'n') {
                mpz_class e, d, n;
                generate_key_pair(4096, e, d, n);
                mpz_class c;
                encrypt(m, e, n, c);
                ofstream output_file("output.txt");
                output_file << "Encrypted message(c): " << c << endl;
                output_file << "Part of private key(d): " << d << endl;
                output_file << "Modulus(n): " << n << endl;
                output_file << "Part of public key(e): " << e << endl;
                output_file.close();
                file.close();
            } else {
                throw bad_exception();
            }
        } else if (choice == 's') {
            cout << "Enter the message: ";
            string message;
            cin.ignore();
            getline(cin, message);
            mpz_class m;
            string_to_number(message, m);
            cout << "Do you already have a key pair? (y/n): ";
            cin >> choice;
            while (choice != 'y' && choice != 'n') {
                cout << "Invalid choice. Please enter y or n: ";
                cin >> choice;
            }
            if (choice == 'y') {
                cout << "Enter the public key(The e in [n, e]): ";
                mpz_class e;
                cin >> e;
                cout << "Enter the modulus(The n in [n, e]): ";
                mpz_class n;
                cin >> n;
                mpz_class c;
                encrypt(m, e, n, c);
                cout << "Encrypted message: " << c << endl;
            } else if (choice == 'n') {
                mpz_class e, d, n;
                generate_key_pair(4096, e, d, n);
                mpz_class c;
                encrypt(m, e, n, c);
                ofstream output_file("output.txt");
                output_file << "Encrypted message(c): " << c << endl;
                output_file << "Part of private key(d): " << d << endl;
                output_file << "Modulus(n): " << n << endl;
                output_file << "Part of public key(e): " << e << endl;
                output_file.close();
            } else {
                throw bad_exception();
            }
        } else {
            throw bad_exception();
        }
    } else if (choice == 'd') {
        cout << "**************************************************";
        cout << "ATTENTION: The file should be in the following format (this is line is not contained in input file):" << endl;
        cout << "Encrypted message(c): " << endl;
        cout << "Part of private key(d): " << endl;
        cout << "Modulus(n): " << endl;
        cout << "**************************************************" << endl;
        cout << "Enter file name: ";
        string file_name;
        cin >> file_name;
        ifstream file(file_name);
        while (!file.is_open()) {
            cout << "Something is wrong. Please enter a valid file name: ";
            cin >> file_name;
            file.open(file_name);
        }
        string line1, line2, line3;
        getline(file, line1);
        getline(file, line2);
        getline(file, line3);
        line1.erase(std::remove_if(line1.begin(), line1.end(), [](char c) { return !std::isdigit(c); }), line1.end());
        line2.erase(std::remove_if(line2.begin(), line2.end(), [](char c) { return !std::isdigit(c); }), line2.end());
        line3.erase(std::remove_if(line3.begin(), line3.end(), [](char c) { return !std::isdigit(c); }), line3.end());
        mpz_class c(line1);
        mpz_class d(line2);
        mpz_class n(line3);
        cout << "c: " << c << endl;
        cout << "d: " << d << endl;
        cout << "n: " << n << endl;
        mpz_class m;
        decrypt(c, d, n, m);
        string message;
        number_to_string(m, message);
        cout << "Decrypted message: " << message << endl;
        file.close();
    } else {
        throw bad_exception();
    }
}
