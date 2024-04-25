#ifndef ENIGMA_H
#define ENIGMA_H

#include <string>
#include <vector>

#include "Rotor.h"
#include "Switchboard.h"

const std::vector<char> alphabet = std::vector<char> {
                'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K',
                'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V',
                'W', 'X', 'Y', 'Z'
            };
const std::vector<int> reflector = std::vector<int> {
    24, 16, 18,  4, 12, 13,  5, -4,  7, 14,  3, -5,  2, -3, -2, -7,-12,-16,-13,  6,-18,  1, -1,-14,-24, -6
};

enum CryptMode
{
    Encrypt,
    Decrypt
};

class Enigma
{
    private:
        std::vector<Rotor> rotors;
        Switchboard switchboard;
        CryptMode mode;

        char codeC(char letter);
        
    public:
        Enigma();
        ~Enigma();

        #pragma region Rotors

            void changeRotors(int serialNumber1, int serialNumber2, int serialNumber3);
            void changeRotor(int rotor, int serialNumber);
            void setRotations(char rotation1, char rotation2, char rotation3);
            void setRotation(int rotor, char rotation);
            void setNotches(char notch1, char notch2, char notch3);
            void setNotch(int rotor, char notch);
            void resetRotors();

            void turnRotors();
            void printRotors();
            std::vector<int> getRotorsSerialNumbers();
            
        #pragma endregion

        #pragma region Reflector
            int reflect(int index);
        #pragma endregion

        #pragma region Switchboard
            char getSwitchboardConnection(char a);
            void addConnection(char a, char b);
            void removeConnection(char a);
            void resetSwitchboard();
            void printSwitchboard();
        #pragma endregion

        CryptMode getMode();
        void setMode(CryptMode mode);
        std::string getSettings();

        int translateToIndex(char letter);
        char translateToLetter(int index);

        std::string code(std::string message);
        std::string crypt(std::string message);

};


#endif