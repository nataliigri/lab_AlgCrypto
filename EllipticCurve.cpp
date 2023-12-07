#include "BigInt.cpp"

class EllipticCurve {
public:
    BigInt a, b, p;  // Коефіцієнти еліптичної кривої (y^2 = x^3 + ax + b) над полем p

    EllipticCurve(BigInt a, BigInt b, BigInt p) : a(a), b(b), p(p) {}

    // Перевірка, чи лежить точка (x, y) на еліптичній кривій
    bool isPointOnCurve(BigInt x, BigInt y) {
        return (y * y) % p == (x * x * x + a * x + b) % p;
    }

    // Додавання точок P і Q на еліптичній кривій
    std::pair<BigInt, BigInt> addPoints(BigInt x1, BigInt y1, BigInt x2, BigInt y2) {
        // Реалізація додавання точок на еліптичній кривій
        // ...

        // Приклад: просте додавання для тестування
        BigInt slope = (y2 - y1) * modularInverse(x2 - x1, p) % p;
        BigInt x3 = (slope * slope - x1 - x2) % p;
        BigInt y3 = (slope * (x1 - x3) - y1) % p;

        return std::make_pair(x3, y3);
    }

    // Добуток точки P на скаляр k
    std::pair<BigInt, BigInt> scalarMultiply(BigInt k, BigInt x, BigInt y) {
        // Реалізація добутку точки на скаляр
        // ...

        // Приклад: простий метод подвоєння для тестування
        std::pair<BigInt, BigInt> result = std::make_pair(x, y);

        for (BigInt i = 1; i < k; ++i) {
            result = addPoints(result.first, result.second, x, y);
        }

        return result;
    }
};
