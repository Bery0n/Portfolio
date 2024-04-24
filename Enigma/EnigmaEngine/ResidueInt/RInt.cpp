#include "RInt.h"

#pragma region Private

    void RInt::typeCorrection() {
        if (type == RIntType::POSITIV) {
            setPositiv();
        } else if (type == RIntType::NEGATIV) {
            setNegativ();
        } else if (type == RIntType::FULLRANGE) {
            setFullranged();
        }
    }

#pragma endregion
#pragma region Public

    #pragma region Constructors and Destructors
        RInt::RInt(int modulus, int n, RIntType type) : modulus(modulus), type(type) {
            this->n = n;
            switch (type) {
            case RIntType::POSITIV:
                setPositiv();
                break;
            case RIntType::NEGATIV:
                setNegativ();
                break;
            default:
                break;
            }
        }
        RInt::RInt(int modulus, int n) {
            RInt(modulus, n, RIntType::FULLRANGE);
        }
        RInt::RInt(int modulus) {
            RInt(modulus, n, RIntType::FULLRANGE);
        }
        RInt::RInt() {
            RInt(2, 0, RIntType::FULLRANGE);
        }
        RInt::~RInt(){
            delete &n;
            delete &modulus;
        }

    #pragma endregion

    #pragma region Getters

        int RInt::getNumber() {
            typeCorrection();
            return n;
        }
        int RInt::getModulus() {
            return modulus;
        }
        int RInt::getPositiv() {
            return (n>=0)?n:(n+modulus);
        }
        int RInt::getNegativ() {
            return (n<=0)?n:(n-modulus);
        }
        RIntType RInt::getType() {
            return type;
        }

    #pragma endregion

    #pragma region Setters

        void RInt::setNumber(int n) {
            this->n = n;
            typeCorrection();
        }
        void RInt::setModulus(int modulus) {
            this->modulus = modulus;
        }
        void RInt::set(int n, int modulus) {
            this->modulus = modulus;
            setNumber(n);
        }
        void RInt::setPositiv() {
            if (n < 0) {
                while (n < 0) { n += modulus; } 
            } else if (n >= modulus) {
                while (n >= modulus) { n -= modulus; }
            }
        }
        void RInt::setNegativ() {
            if (n > 0) {
                while (n > 0) { n -= modulus; } 
            } else if (n <=  modulus * -1) {
                while (n <= modulus * -1) { n -= modulus; }
            }
        }
        void RInt::setFullranged() {
            if (n >= modulus) {
                setPositiv();
            } else if (n <= modulus * -1) {
                setNegativ();
            }
        }
        void RInt::setType(RIntType type) {
            this->type = type;
            typeCorrection();
        }
    #pragma endregion

#pragma endregion