#include "BigInt.cpp"
#include <cstdlib>
#include <ctime>

// Функція для обчислення a^n % m в довгій арифметиці
BigInt modularExponentiation(BigInt a, BigInt n, BigInt m) {
    BigInt result = 1;

    a = a % m;

    while (n > 0) {
        if (n % 2 == 1)
            result = (result * a) % m;

        n = n / 2;
        a = (a * a) % m;
    }

    return result;
}

// Алгоритм Полларда (p-1) для факторизації числа N
BigInt pollardsRho(BigInt N) {
    srand(time(srand(time(0));

    BigInt x = rand() % (N - 2) + 2;
    BigInt y = x;
    BigInt d = 1;

    BigInt one = 1;

    BigInt a = rand() % (N - 1) + 1;

    while (d == 1) {
        x = (x * x + a) % N;
        y = (y * y + a) % N;
        y = (y * y + a) % N;

        d = gcd(abs(x - y), N);
    }

    return d;
}

