#include <iostream>
#include <ctime>
#include <cstdlib>
#include <fstream>

void testElGamalElliptic() {
    // Встановлюємо параметри еліптичної кривої
    BigInt p("23");
    BigInt a("1");
    BigInt b("1");
    BigInt n("7");
    BigInt gx("11");
    BigInt gy("1");

    EllipticCurve curve(p, a, b, n, gx, gy);
    std::pair<BigInt, BigInt> basePoint(gx, gy);

    ElGamalElliptic elGamal(curve, basePoint);

    // Тест 1: Перевірка генерації ключів
    std::cout << "Test 1: Key generation\n";
    auto keys = elGamal.generateKeys();
    std::cout << "Public Key: (" << keys.first.first << ", " << keys.first.second << ")\n";
    std::cout << "Private Key: " << keys.second << "\n";

    // Тест 2: Перевірка шифрування та розшифрування
    std::cout << "\nTest 2: Encryption and decryption\n";
    BigInt message("5");
    std::pair<BigInt, BigInt> publicKey = keys.first;
    auto ciphertext = elGamal.encrypt(message, publicKey);
    std::cout << "Original Message: " << message << "\n";
    std::cout << "Ciphertext (C1, C2): (" << ciphertext.first.first << ", " << ciphertext.first.second << "), (" << ciphertext.second.first << ", " << ciphertext.second.second << ")\n";

    BigInt decryptedMessage = elGamal.decrypt(ciphertext, keys.second);
    std::cout << "Decrypted Message: " << decryptedMessage << "\n";
    std::cout << (decryptedMessage == message ? "Encryption and decryption successful!\n" : "Encryption and decryption failed!\n");
}

void testPollardsRho() {
    std::cout << "Test Pollard's Rho\n";
    BigInt N("8051");
    std::cout << "Number to factorize: " << N << "\n";

    BigInt factor = pollardsRho(N);
    std::cout << "Factor: " << factor << "\n";
}

void testModularExponentiation() {
    std::cout << "\nTest Modular Exponentiation\n";
    BigInt base("7");
    BigInt exponent("3");
    BigInt modulus("11");

    BigInt result = modularExponentiation(base, exponent, modulus);

    std::cout << base << "^" << exponent << " % " << modulus << " = " << result << "\n";
}

void testModInverse() {
    std::cout << "Test ModInverse\n";
    BigInt a("3");
    BigInt m("11");

    BigInt result = ModInverse(a, m);

    std::cout << a << "^(-1) % " << m << " = " << result << "\n";
}

void testSolveSystem() {
    std::cout << "\nTest SolveSystem\n";

    std::vector<BigInt> residues{BigInt("2"), BigInt("3"), BigInt("1")};  // Замініть на ваші залишки
    std::vector<BigInt> moduli{BigInt("3"), BigInt("4"), BigInt("5")};     // Замініть на ваші модулі

    BigInt result = SolveSystem(residues, moduli);

    std::cout << "Solution: " << result << "\n";
}

int main() {
    // Ініціалізація генератора випадкових чисел
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    // Генеруємо випадкові параметри для тестування
    BigInt a(rand() % 1000);
    BigInt b(rand() % 1000);
    BigInt p(rand() % 1000 + 1000);

    std::cout << "Testing with parameters:" << std::endl;
    std::cout << "a: " << a << std::endl;
    std::cout << "b: " << b << std::endl;
    std::cout << "p: " << p << std::endl;

    // Тестування функцій
    BigInt resultModExp = modularExponentiation(a, b, p);
    BigInt resultGCD = gcd(a, b);
    BigInt resultLCM = lcm(a, b);
    BigInt resultEuler = eulerFunction(p);
    int resultMobius = mobiusFunction(p);

    std::cout << "Results:" << std::endl;
    std::cout << "Modular Exponentiation: " << resultModExp << std::endl;
    std::cout << "GCD: " << resultGCD << std::endl;
    std::cout << "LCM: " << resultLCM << std::endl;
    std::cout << "Euler Function: " << resultEuler << std::endl;
    std::cout << "Mobius Function: " << resultMobius << std::endl;

    // Тестування символу Лежандра
    BigInt legendreA(rand() % 1000);
    BigInt legendreP(rand() % 1000 + 1000);
    int resultLegendre = legendreSymbol(legendreA, legendreP);
    std::cout << "Legendre Symbol: (" << legendreA << "/" << legendreP << ") = " << resultLegendre << std::endl;

    // Тестування символу Якобі
    int jacobiA = rand() % 1000;
    int jacobiN = rand() % 1000 + 1000;
    int resultJacobi = jacobiSymbol(jacobiA, jacobiN);
    std::cout << "Jacobi Symbol: (" << jacobiA << "/" << jacobiN << ") = " << resultJacobi << std::endl;

    // Тестування дискретного логарифма
    BigInt baseDL(rand() % 1000);
    BigInt targetDL(rand() % 1000);
    BigInt primeDL(rand() % 1000 + 1000);
    BigInt resultDL = discreteLogarithm(baseDL, targetDL, primeDL);
    std::cout << "Discrete Logarithm: log_" << baseDL << "(" << targetDL << ") % " << primeDL << " = " << resultDL << std::endl;

    // Тестування простоти числа за допомогою таблиці довгих простих чисел
    std::ifstream primeFile("primes.txt");  // Потрібно завантажити файл primes.txt
    BigInt testNumber(rand() % 1000 + 1000);  // Виберіть величину за необхідністю
    int primeCount = 0;
    int nthPrime = 1;

    if (primeFile.is_open()) {
        BigInt currentPrime;
        while (primeFile >> currentPrime) {
            ++primeCount;
            if (currentPrime == testNumber) {
                std::cout << testNumber << " is prime. It is the " << nthPrime << " prime number in the table." << std::endl;
                break;
            }
            nthPrime++;
        }

        if (primeCount == nthPrime) {
            std::cout << testNumber << " is not prime." << std::endl;
        }

        primeFile.close();
    } else {
        std::cerr << "Unable to open prime number file." << std::endl;
    }

    // Ініціалізація генератора випадкових чисел
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    // Генеруємо величину бітів для класу RSA
    int numBits = 64;  // Виберіть величину за необхідністю

    // Тестування класу RSA
    RSA rsa(numBits);

    // Генеруємо випадкове повідомлення
    BigInt message = generateRandomNumber(1, rsa.getPublicKey() - 1);

    // Шифруємо та дешифруємо повідомлення
    BigInt ciphertext = rsa.encrypt(message);
    BigInt decryptedMessage = rsa.decrypt(ciphertext);

    // Виводимо результати
    std::cout << "Original Message: " << message << std::endl;
    std::cout << "Encrypted Message: " << ciphertext << std::endl;
    std::cout << "Decrypted Message: " << decryptedMessage << std::endl;

    // Перевірка правильності дешифрування
    if (message == decryptedMessage) {
        std::cout << "Decryption successful. Original message is recovered." << std::endl;
    } else {
        std::cerr << "Decryption failed. Original message is not recovered." << std::endl;
    }

    testElGamalElliptic();
    testPollardsRho();
    testModularExponentiation();
    testModInverse();
    testSolveSystem();

    return 0;
}
