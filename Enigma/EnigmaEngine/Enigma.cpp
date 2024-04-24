#include "Enigma.h"
#include "Rotor.h"
#include "Switchboard.h"

#include <iostream>
#include <string>
#include <stdexcept>

#pragma region Private

    char Enigma::codeC(char letter) {
        // printRotors();
        int index = translateToIndex(this->switchboard.convert(letter));
        // std::cout <<"Index: " << index <<" Letter "<<letter << std::endl;
        for (int i = 0; i < 3; i++) {
            index = this->rotors[i].codeForward(index);
            // std::cout << i << " | " << index << "/" << translateToLetter(index) << std::endl;
        }
        index = reflect(index);
        // std::cout << "Ref: " << index << "/" << translateToLetter(index) << std::endl;
        for (int i = 2; i >= 0; i--) {
            index = this->rotors[i].codeBackward(index);
            // std::cout << i << " | " << index << "/" << translateToLetter(index) << std::endl;
        }
        index = translateToIndex(this->switchboard.convert(translateToLetter(index)));
        // std::cout << "Index: " << index << " Result: " << translateToLetter(index) << std::endl<<std::endl;
        turnRotors();
        // printRotors();
        return translateToLetter(index);
    }

#pragma endregion
#pragma region Public
    #pragma region Constructors and Destructors

        Enigma::Enigma() {
            this->switchboard = Switchboard(alphabet);
            resetRotors();
            this->mode = CryptMode::Encrypt;
        }
        Enigma::~Enigma() {
        }

    #pragma endregion

    #pragma region Rotors

        void Enigma::changeRotors(int serialNumber1, int serialNumber2, int serialNumber3) {
            rotors[0].setGates(serialNumber1);
            rotors[1].setGates(serialNumber2);
            rotors[2].setGates(serialNumber3);            
        }
        void Enigma::changeRotor(int rotor, int serialNumber) {
            rotors[rotor].setGates(serialNumber);
        }

        void Enigma::setRotations(char rotation1, char rotation2, char rotation3) {
            this->rotors[0].setRotation(translateToIndex(rotation1));
            this->rotors[1].setRotation(translateToIndex(rotation2));
            this->rotors[2].setRotation(translateToIndex(rotation3));
        }
        void Enigma::setRotation(int rotor, char rotation) {
            this->rotors[rotor].setRotation(translateToIndex(rotation));
        }

        void Enigma::setNotches(char notch1, char notch2, char notch3) {
            rotors[0].setNotch(translateToIndex(notch1));
            rotors[1].setNotch(translateToIndex(notch2));
            rotors[2].setNotch(translateToIndex(notch3));
        }
        void Enigma::setNotch(int rotor, char notch) {
            rotors[rotor].setNotch(translateToIndex(notch));
        }

        void Enigma::resetRotors() {
            this->rotors = std::vector<Rotor> {
                Rotor(1,0,25),
                Rotor(2,0,25),
                Rotor(3,0,25)
            };
        }

        void Enigma::turnRotors() {
            if (this->rotors[0].rotate()) {
                if (this->rotors[1].rotate()) {
                    this->rotors[2].rotate();
                }
            }
        }

        void Enigma::printRotors() {
            std::cout << "Rotor        |  I | II | III" << std::endl;
            std::cout << "-------------+----+----+----+" << std::endl;
            std::cout << "Serialnumber ";
            for (int i = 0; i < 3; i++) {
                std::cout << "|  " <<  rotors[i].getSerialNumber() << " ";
            }
            std::cout << "\n-------------+----+----+----+" << std::endl;
            std::cout << "Rotation     ";
            for (int i = 0; i < 3; i++)
            {
                std::cout << "|  " << translateToLetter(rotors[i].getRotation()) << " ";
            }
            std::cout << "\n-------------+----+----+----+" << std::endl;
            std::cout << "Notch        ";
            for (int i = 0; i < 3; i++)
            {
                std::cout << "|  " << translateToLetter(rotors[i].getNotch()) << " ";
            }
            std::cout << std::endl << "-------------+----+----+----+\n" << std::endl;
        }
        
        std::vector<int> Enigma::getRotorsSerialNumbers() {
            std::vector<int> result;
            for (int i = 0; i < 3; i++) {
                result.push_back(rotors[i].getSerialNumber());
            }
            return result;
        }
    #pragma endregion

    #pragma region Reflector

        int Enigma::reflect(int index) {
            return index + reflector[index];
        }
    #pragma endregion
    #pragma region Switchboard

        char Enigma::getSwitchboardConnection(char a) {
            return this->switchboard.convert(a);
        }
        void Enigma::addConnection(char a, char b) {
            this->switchboard.setConnection(a, b);
        }
        void Enigma::removeConnection(char a) {
            this->switchboard.removeConnection(a);
        }
        void Enigma::resetSwitchboard() {
            this->switchboard.reset();
        }
        void Enigma::printSwitchboard() {
            this->switchboard.print();
        }

    #pragma endregion
    
    CryptMode Enigma::getMode() {
        return this->mode;
    }
    void Enigma::setMode(CryptMode mode) {
        this->mode = mode;
    }
    std::string Enigma::getSettings() {
        std::string result = "Rotors: ";
        result += "I:" + rotors[0].toString() + " II:" + rotors[1].toString() + " III:" + rotors[2].toString() + "\n";
        result += this->switchboard.toString();
        return result;
    }

    int Enigma::translateToIndex(char letter) {
        for (int i = 0; i < alphabet.size(); i++) {
            if (alphabet[i] == letter) {
                return i;
            }
        }
        return -1;
    }
    char Enigma::translateToLetter(int index) {
        return alphabet[index];
    }

    std::string Enigma::code(std::string message) {
        std::string result = "";
        for (int i = 0; i < message.size(); i++) {
            if (isalpha(message[i])){
                char c = toupper(message[i]);
                // std::cout << "Char: " << c << std::endl;
                result += codeC(c);
            }
        }
        // std::cout << "Result: " << result << std::endl;
        return result;
    }
    // std::string Enigma::crypt(std::string message) {
    //     std::string result = "";
    //     for (int i = 0; i < message.size(); i++) {
    //         if (isalpha(message[i])){
    //             char c = toupper(message[i]);
    //             result += codeC(c);
    //         }
    //     }
    //     if (this->mode == CryptMode::Encrypt) {
    //         std::string fragmentedResult = "";
    //         for (int i = 0; i < result.size(); i++) {
    //             fragmentedResult += result[i];
    //             if (i % 4 == 3) {
    //                 if (i % 16 == 15) {
    //                     fragmentedResult += "\n";
    //                 }
    //                 else {
    //                     fragmentedResult += " ";
    //                 }
    //             } 
    //         }
    //         result = fragmentedResult;
    //     }
    //     // std::cout << "Result: " << result << std::endl;
    //     return result;
    // }
    
#pragma endregion
