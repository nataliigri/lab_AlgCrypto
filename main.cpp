#include <iostream>
#include "BigInt.cpp"
#include "ChineseRemainderTheorem.cpp"
#include "PollardsRho.cpp"
#include "EllipticCurve.cpp"
#include "ElGamalElliptic.cpp"
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


BigInt chipollasAlgorithm(BigInt a, BigInt p) {
    if (legendreSymbol(a, p) != 1) {
        std::cerr << "No solution exists for the given parameters." << std::endl;
        return -1; // Виходить, що не існує дискретного квадратного кореня для заданих параметрів
    }

    // Ваш код для алгоритму Чіпполі тут

    return -1; // Повертаємо -1, оскільки потрібно реалізувати алгоритм Чіпполі
}

bool isPrime_SolovayStrassen(BigInt n, int k) {
    if (n <= 1)
        return false;
    if (n == 2 || n == 3)
        return true;
    if (n % 2 == 0)
        return false;

    for (int i = 0; i < k; ++i) {
        BigInt a = rand() % (n - 3) + 2; // Генеруємо випадкове число у діапазоні [2, n-2]

        BigInt x = modularExponentiation(a, (n - 1) / 2, n);
        if (x != 1 && x != n - 1)
            return false;

        BigInt legendre = legendreSymbol(a, n);
        BigInt jacobi = jacobiSymbol(a, n);

        if (legendre != jacobi)
            return false;
    }

    return true;
}

int main() {
    // Приклад використання алгоритму Полларда (p-1)
    BigInt N = 5959;

    std::cout << "Original number: " << N << std::endl;

    BigInt factor = pollardsRho(N);

    if (factor == N) {
        std::cout << "Unable to factorize the number. It may be prime." << std::endl;
    } else {
        BigInt otherFactor = N / factor;
        std::cout << "Factors: " << factor << " and " << otherFactor << std::endl;
    }

    // Приклад використання функції Ейлера та Мьобіуса
    BigInt eulerNumber = 12;
    std::cout << "Euler's Totient Function(" << eulerNumber << "): " << eulerFunction(eulerNumber) << std::endl;

    BigInt mobiusNumber = 30;
    std::cout << "Möbius Function(" << mobiusNumber << "): " << mobiusFunction(mobiusNumber) << std::endl;

    // Приклад використання китайської теореми залишків
    std::vector<BigInt> residues = {2, 3, 2};
    std::vector<BigInt> moduli = {5, 7, 3};

    BigInt solution = SolveSystem(residues, moduli);
    std::cout << "Solution to the system: " << solution << std::endl;

    // Приклад використання алгоритму "великий крок - малий крок"
    BigInt base = 2;
    BigInt target = 8;
    BigInt prime = 11;

    std::cout << "Discrete Logarithm of " << target << " to the base " << base << " mod " << prime << " is: "
              << discreteLogarithm(base, target, prime) << std::endl;

    // Приклад використання алгоритму Чіпполі для знаходження дискретного квадратного кореня
    BigInt aChipolla = 5;
    BigInt pChipolla = 17;

    BigInt sqrtModP = chipollasAlgorithm(aChipolla, pChipolla);
    if (sqrtModP != -1) {
        std::cout << "Discrete square root of " << aChipolla << " modulo " << pChipolla << " is: " << sqrtModP << std::endl;
    }

    int keyBitsRSA = 128;  // Млжна замініти на більше значення для більшої безпеки
    RSA rsa(keyBitsRSA);

    BigInt plaintextRSA = 42;

    // Шифруємо повідомлення
    BigInt ciphertextRSA = rsa.encrypt(plaintextRSA);
    std::cout << "Encrypted message (RSA): " << ciphertextRSA << std::endl;

    // Розшифровуємо повідомлення
    BigInt decryptedMessageRSA = rsa.decrypt(ciphertextRSA);
    std::cout << "Decrypted message (RSA): " << decryptedMessageRSA << std::endl;

    // Параметри для еліптичних кривих
    BigInt a = 2;
    BigInt b = 2;
    BigInt p = 17;
    EllipticCurve curve(a, b, p);

    // Базова точка на еліптичній кривій
    std::pair<BigInt, BigInt> basePoint(5, 1);

    // Створення об'єкта криптосистеми Ель-Гамаля на еліптичних кривих
    ElGamalElliptic elGamal(curve, basePoint);

    // Генерація ключів
    auto keys = elGamal.generateKeys();
    std::pair<BigInt, BigInt> publicKey = keys.first;
    BigInt privateKey = keys.second;

    std::cout << "Public Key: (" << publicKey.first << ", " << publicKey.second << ")\n";
    std::cout << "Private Key: " << privateKey << "\n\n";

    // Повідомлення для шифрування
    BigInt message = 7;
    std::cout << "Original Message: " << message << "\n";

    // Шифрування
    auto ciphertext = elGamal.encrypt(message, publicKey);
    std::pair<BigInt, BigInt> C1 = ciphertext.first;
    std::pair<BigInt, BigInt> C2 = ciphertext.second;

    std::cout << "Ciphertext (C1, C2):\n";
    std::cout << "(" << C1.first << ", " << C1.second << "), ";
    std::cout << "(" << C2.first << ", " << C2.second << ")\n\n";

    // Розшифрування
    BigInt decryptedMessage = elGamal.decrypt(ciphertext, privateKey);
    std::cout << "Decrypted Message: " << decryptedMessage << "\n";

    return 0;
}
