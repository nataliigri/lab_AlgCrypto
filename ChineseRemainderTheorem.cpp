#include "BigInt.cpp"
#include <vector>

// Функція для знаходження оберненого за модулем числа (a^-1) по модулю m
BigInt ModInverse(BigInt a, BigInt m) {
    BigInt m0 = m;
    BigInt x0 = 0, x1 = 1;

    if (m == 1)
        return 0;

    while (a > 1) {
        BigInt q = a / m;
        BigInt t = m;

        m = a % m;
        a = t;
        t = x0;
        x0 = x1 - q * x0;
        x1 = t;
    }

    if (x1 < 0)
        x1 += m0;

    return x1;
}

// Функція для розв'язання системи лінійних порівнянь за модулем (CRT)
BigInt SolveSystem(std::vector<BigInt> residues, std::vector<BigInt> moduli) {
    int n = residues.size();

    if (n != moduli.size())
        throw std::invalid_argument("The number of residues must be equal to the number of moduli.");

    BigInt product = 1;

    for (int i = 0; i < n; i++)
        product *= moduli[i];

    BigInt result = 0;

    for (int i = 0; i < n; i++) {
        BigInt partialProduct = product / moduli[i];
        result += residues[i] * ModInverse(partialProduct, moduli[i]) * partialProduct;
    }

    return result % product;
}
