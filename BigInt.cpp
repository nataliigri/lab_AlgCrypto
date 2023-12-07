#include <iostream>
#include <vector>
#include <cmath>

class BigInt {
private:
    std::vector<int> digits;

public:
    BigInt() {}

    BigInt(int num) {
        while (num > 0) {
            digits.push_back(num % 10);
            num /= 10;
        }
    }

    friend std::ostream& operator<<(std::ostream& os, const BigInt& num) {
        for (int i = num.digits.size() - 1; i >= 0; --i)
            os << num.digits[i];
        return os;
    }
};

// Додаткові функції для довгої арифметики тут

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

// Функція для обчислення найбільшого спільного дільника (НСД) двох чисел
BigInt gcd(BigInt a, BigInt b) {
    while (b != 0) {
        BigInt temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Функція для обчислення найменшого спільного кратного (НСК) двох чисел
BigInt lcm(BigInt a, BigInt b) {
    return (a * b) / gcd(a, b);
}

// Функція обчислення функції Ейлера для числа n
BigInt eulerFunction(BigInt n) {
    BigInt result = n;

    for (BigInt i = 2; i * i <= n; ++i) {
        if (n % i == 0) {
            while (n % i == 0)
                n /= i;
            result -= result / i;
        }
    }

    if (n > 1)
        result -= result / n;

    return result;
}

// Функція обчислення функції Мьобіуса для числа n
int mobiusFunction(BigInt n) {
    int count = 0;
    BigInt temp = n;

    for (BigInt i = 2; i * i <= temp; ++i) {
        if (temp % i == 0) {
            ++count;
            temp /= i;

            if (temp % i == 0) {
                // Число має квадратний множник, тому Мьобіуса буде 0
                return 0;
            }
        }
    }

    if (temp > 1)
        ++count;

    return (count % 2 == 0) ? 1 : -1;
}

// Функція для обчислення символу Лежандра (a/p)
int legendreSymbol(BigInt a, BigInt p) {
    BigInt exponent = (p - 1) / 2;
    BigInt result = modularExponentiation(a, exponent, p);
    return (result == p - 1) ? -1 : result.toInt();
}

// Функція для обчислення символу Якобі (a/n), де n - непарне число
int jacobiSymbol(int a, int n) {
    if (n <= 0 || n % 2 == 0) {
        std::cerr << "Invalid input for Jacobi symbol." << std::endl;
        return 0;
    }

    int result = 1;

    while (a != 0) {
        while (a % 2 == 0) {
            a /= 2;
            int r = n % 8;
            if (r == 3 || r == 5)
                result = -result;
        }

        std::swap(a, n);

        if (a % 4 == 3 && n % 4 == 3)
            result = -result;

        a %= n;
    }

    return (n == 1) ? result : 0;
}

// Функція для обчислення дискретного логарифма (алгоритм "великий крок - малий крок")
BigInt discreteLogarithm(BigInt base, BigInt target, BigInt prime) {
    BigInt m = static_cast<int>(ceil(sqrt(prime)));
    std::vector<std::pair<BigInt, BigInt>> babySteps;

    // Обчислюємо baby steps
    BigInt babyStep = 1;
    for (BigInt i = 0; i < m; ++i) {
        babySteps.emplace_back(babyStep, i);
        babyStep = (babyStep * base) % prime;
    }

    // Обчислюємо giant steps та перевіряємо співпадіння з baby steps
    BigInt giantStep = target;
    BigInt giantStepMultiplier = modularExponentiation(base, m, prime);
    for (BigInt i = 0; i < m; ++i) {
        for (const auto& babyStepPair : babySteps) {
            if (giantStep == babyStepPair.first)
                return i * m + babyStepPair.second;
        }

        giantStep = (giantStep * giantStepMultiplier) % prime;
    }

    return -1; // Дискретний логарифм не знайдено
}