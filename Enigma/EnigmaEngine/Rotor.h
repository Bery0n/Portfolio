#pragma once

#include "./ResidueInt/RInt.h"

#include <vector>
#include <string>
class Rotor
{
    private:
        int serialNumber;
        RInt rotation;
        int notch;
        std::vector<std::vector<int>> gates;
        
    public:
        Rotor(int serialNumber, int rotation, int notch);
        Rotor();
        ~Rotor();

        #pragma region Getters

            int getRotation();
            int getNotch();
            int getSerialNumber();
            std::vector<int> getFront();
            std::vector<int> getBack();
            std::vector<std::vector<int>> getGates();

        #pragma endregion

        #pragma region Setters
            void setRotation(int rotation);
            void setNotch(int notch);
            void setGates(int serialNumber);

        #pragma endregion

        bool rotate();
        int codeForward(int index);
        int codeBackward(int index);

        std::string toString();

        



};