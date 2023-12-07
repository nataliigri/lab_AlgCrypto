#include <iostream>
#include <cstdlib>
#include <ctime>

class RSA {
private:
    BigInt p, q, n, phi, e, d;

public:
    RSA(int numBits) {
        generateKeys(numBits);
    }

    BigInt encrypt(BigInt message) {
        return modularExponentiation(message, e, n);
    }

    BigInt decrypt(BigInt ciphertext) {
        return modularExponentiation(ciphertext, d, n);
    }

    BigInt getPublicKey() const {
        return e;
    }

    BigInt getPrivateKey() const {
        return d;
    }

private:
    void generateKeys(int numBits) {
        srand(time(nullptr));

        // Генеруємо великі прості числа p та q
        p = generateLargePrime(numBits);
        q = generateLargePrime(numBits);

        // Обчислюємо n та функцію Ейлера
        n = p * q;
        phi = (p - 1) * (q - 1);

        // Вибираємо відкритий ключ e (взаємно простий з phi)
        e = generateRandomNumber(2, phi - 1);

        // Обчислюємо закритий ключ d (модульна обернена до e за mod phi)
        extendedEuclidean(e, phi, d, BigInt()); // d = e^(-1) mod phi
        if (d < 0) d += phi; // Переконуємося, що d додатнє число
    }
};
