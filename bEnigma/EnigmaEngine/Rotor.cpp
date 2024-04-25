#include "Rotor.h"
#include "./ResidueInt/RInt.h"



#pragma region Private

#pragma endregion

#pragma region Public

    #pragma region Constructors and Destructors

        Rotor::Rotor(int serialNumber, int rotation, int notch) {
            setGates(serialNumber);
            this->rotation = RInt(26, rotation, RIntType::POSITIV);
            this->notch = notch;
        }
        Rotor::Rotor() {
            std::vector<int> v_epnty = {0};
            Rotor(1,0,25);
        }
        Rotor::~Rotor()
        {
        }

    #pragma endregion

    #pragma region Getters

        int Rotor::getRotation() {
            return rotation.getNumber();
        }
        int Rotor::getNotch() {
            return notch;
        }
        int Rotor::getSerialNumber() {
            return serialNumber;
        }
        std::vector<int> Rotor::getFront() {
            return gates[0];
        }
        std::vector<int> Rotor::getBack() {
            return gates[1];
        }
        std::vector<std::vector<int>> Rotor::getGates() {
            return gates;
        }
    
    #pragma endregion

    #pragma region Setters
    
        void Rotor::setRotation(int rotation) {
            this->rotation.setNumber(rotation);
        }
        void Rotor::setNotch(int notch) {
            this->notch = notch;
        }
        void Rotor::setGates(int serialNumber) {
            this->serialNumber = serialNumber;
            switch (serialNumber)
            {
            case 1:
                this->gates = std::vector<std::vector<int>> {
                    {  4,  9, 10,  2,  7,  1, -3,  9, 13, 16,  3,  8,  2,  9, 10, -8,  7,  3,  0, -4,-20,-13,-21, -6,-22,-16},
                    { 20, 21, 22,  3, -4, -2, -1,  8, 13, 16, -9, -7,-10, -3, -2,  4, -9,  6,  0, -8, -3,-13, -9, -7,-10,-16}
                };
                break;
            case 2:
                this->gates = std::vector<std::vector<int>> {
                    {  0,  8,  1,  7, 14,  3, 11, 13, 15, -8,  1, -4, 10,  6, -2,-13,  0,-11,  7, -6, -5,  3,-17, -2,-10,-21},
                    {  0,  8, 13, -1, 21, 17, 11,  4, -3, -8, -7, -1,  2,  6, 10,  5,  0,-11,-14, -6,-13,  2,-10,-15, -3, -7}
                };
                break;
            case 3:
                this->gates = std::vector<std::vector<int>> {
                    {  1,  2,  3,  4,  5,  6, -4,  8,  9, 10, 13, 10, 13,  0, 10,-11, -8,  5,-12,-19,-10, -9, -2, -5, -8,-11},
                    { 19, -1,  4, -2, 11, -3, 12, -4,  8, -5, 10, -6,  9,  0, 11, -8,  8, -9,  5,-10,  2,-10, -5,-13,-10,-13}
                };
                break;
            case 4:
                this->gates = std::vector<std::vector<int>> {
                    {  4,  8, 10, 22, -4,  6, 18, 16, 13, -8, 12, -6, -10,  4,  2,  5, -2, -4,  1, -1, -5,-13,-12,-16,-18,-22},
                    {  4,  8, 10, 22, -4,  6, 18, 16, 13, -8, 12, -6, -10,  4,  2,  5, -2, -4,  1, -1, -5,-13,-12,-16,-18,-22}
                };
                break;
            default: // 5
                this->gates = std::vector<std::vector<int>> {
                    { 16, 23,  5, 11,  2,  8, -2, -5, 13,  6,  8, -1, 11,  6, -5,  2,  9, -6,  4,-16,-15, -9,-22,-22,-16, -5},
                    { 22, 22,  5, 16,  2, 15, -2, -5, 16,  5,  1,  6,  9, -8,-11, -6,-16, -2, -8, -6,  5,-13, -4,-11,-23, -9}
                };
                break;
            }
        
        }
    
    #pragma endregion

    bool Rotor::rotate() {
        if (rotation.getNumber() == notch) {
            rotation++;
            return true;
        } else {
            rotation++;
            return false;
        }
    }

    int Rotor::codeForward(int index) {
        RInt i = RInt(26, index, RIntType::POSITIV);
        i -= rotation.getNumber();
        i += gates[0][i.getNumber()];
        i += rotation.getNumber();
        return i.getNumber();
    }

    int Rotor::codeBackward(int index) {
        RInt i = RInt(26, index, RIntType::POSITIV);
        i -= rotation.getNumber();
        i += gates[1][i.getNumber()];
        i += rotation.getNumber();
        return i.getNumber();
    }

    std::string Rotor::toString() {
        return "[ Sn: " + std::to_string(serialNumber) +
               " | R: " + std::to_string(rotation.getNumber()) +
               " | N: " + std::to_string(notch) + " ]";
    }
#pragma endregion

