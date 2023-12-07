#include "EllipticCurve.cpp"

class ElGamalElliptic {
private:
    EllipticCurve curve;
    std::pair<BigInt, BigInt> basePoint;  // Точка P на еліптичній кривій

public:
    ElGamalElliptic(EllipticCurve curve, std::pair<BigInt, BigInt> basePoint)
            : curve(curve), basePoint(basePoint) {}

    // Генерація ключів
    std::pair<std::pair<BigInt, BigInt>, BigInt> generateKeys() {
        BigInt privateKey = generateRandomNumber(2, curve.p - 1);
        std::pair<BigInt, BigInt> publicKey = curve.scalarMultiply(privateKey, basePoint.first, basePoint.second);

        return std::make_pair(publicKey, privateKey);
    }

    // Шифрування повідомлення
    std::pair<std::pair<BigInt, BigInt>, std::pair<BigInt, BigInt>> encrypt(BigInt message, std::pair<BigInt, BigInt> publicKey) {
        BigInt k = generateRandomNumber(2, curve.p - 1);
        std::pair<BigInt, BigInt> C1 = curve.scalarMultiply(k, basePoint.first, basePoint.second);
        std::pair<BigInt, BigInt> C2 = curve.addPoints({message, 0}, curve.scalarMultiply(k, publicKey.first, publicKey.second));

        return std::make_pair(C1, C2);
    }

    // Розшифрування шифротексту
    BigInt decrypt(std::pair<std::pair<BigInt, BigInt>, std::pair<BigInt, BigInt>> ciphertext, BigInt privateKey) {
        std::pair<BigInt, BigInt> S = curve.scalarMultiply(privateKey, ciphertext.first.first, ciphertext.first.second);
        std::pair<BigInt, BigInt> inverseS = {S.first, -S.second};  // Обернена точка S

        std::pair<BigInt, BigInt> M = curve.addPoints(ciphertext.second, inverseS.first, inverseS.second);

        return M.first;
    }
};
