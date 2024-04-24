#include "./EnigmaEngine/Enigma.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>

enum class Mode {
    MAIN_MENU,
    CRYPTING,
    MAIN_SETTINGS,
    ROTOR_SETTINGS,
    SWITCHBOARD_SETTINGS,
    EXIT
};

void printMode(Mode mode);

#pragma region Input_Syntaxes

    std::regex modeSwitcher("#[1-4]");  // for mode switcher instatnly
    std::regex yesNoChoice("[1-2]");    // for yes or no choices
    std::regex menuTriOptions("[1-3]");
    std::regex menuQuatroOptions("[1-4]"); 
    std::regex rotorOptions("[1-6]"); // for rotor settings
    std::regex setOneRotor("(I|II|III):[1-5],[A-Z],[A-Z]"); //for set one rotor ex. I:1,A,Z or II:2,B,Y or III:3,C,X
    std::regex setAllRotors("[1-5](,[A-Z]){2}(\\|[1-5](,[A-Z]){2}){2}"); //for set all rotors ex. 1,A,Z|2,B,Y|3,C,X
    std::regex changeOneRotor("(I|II|III):[1-5]"); //for change one rotor ex. I:1 or II:2 or III:3
    std::regex changeAllRotors("[1-5](\\|[1-5]){2}"); //for change all rotors ex. 1|2|3
    std::regex setOneROrN("(I|II|III):[A-Z]"); //for set one rotation ex. I:A or II:B or III:C
    std::regex setAllROrN("[A-Z](\\|[A-Z]){2}"); //for set all rotations ex. A|B|C
    std::regex Connection("[A-Z]-[A-Z]"); //for add connection ex. A-B

#pragma endregion

#pragma region Prints

    void printMainMenu(std::string eMsg);
    void printCrypting();

    // Settings
    void printMainSettingsMenu(std::string eMsg);
    // Rotor settings
    void printRotorSettingsMenu(Enigma enigma, std::string eMsg);
    // Set Rotor
    void pirntSetRotorChoice(std::string eMsg);
    void printSetOneRotor(std::string eMsg);
    void printSetAllRotors(std::string eMsg);
    // Change Rotor
    void printChangeRotorChoice(std::string eMsg);
    void printChangeOneRotor(std::string eMsg);
    void printChangeAllRotors(std::string eMsg);
    // Set Rotation
    void printSetRotationChoice(std::string eMsg);
    void printSetOneRotation(std::string eMsg);
    void printSetAllRotations(std::string eMsg);
    // Set Notch
    void printSetNotchChoice(std::string eMsg);
    void printSetOneNotch(std::string eMsg);
    void printSetAllNotches(std::string eMsg);
    // Reset all rotors
    void printResetAllRotors(std::string eMsg);
    // Switchboard settings
    void printSwitchboardSettingsMenu(Enigma enigma, std::string eMsg);
    void printAddConnection(std::string eMsg);
    void printRemoveConnection(std::string eMsg);
    void printResetSwitchboard(std::string eMsg);

#pragma endregion

bool isModeSwitcher(std::string input, Mode *mode);
bool isSerialNumberCrash(std::string input, Enigma enigma);

#pragma region Input

    void inputMainMenu(std::string input, Mode *mode);
    void inputCrypting(std::string input, Mode *mode, Enigma *enigma);
    // Settings
    void inputMainSettingsMenu(std::string input, Mode *mode);
    #pragma region Rotor settings
        // Rotor settings
        void inputRotorSettingsMenu(std::string input, Mode *mode, Enigma *enigma);
        // Set Rotor
        void inputSetRotorChoice(std::string input, Mode *mode, Enigma *enigma);
        void inputSetOneRotor(std::string input, Mode *mode, Enigma *enigma);
        void inputSetAllRotors(std::string input, Mode *mode, Enigma *enigma);

        // Change Rotor
        void inputChangeRotorChoice(std::string input, Mode *mode, Enigma *enigma);
        void inputChangeOneRotor(std::string input, Mode *mode, Enigma *enigma);
        void inputChangeAllRotors(std::string input, Mode *mode, Enigma *enigma);

        // Set Rotation
        void inputSetRotationChoice(std::string input, Mode *mode, Enigma *enigma);
        void inputSetOneRotation(std::string input, Mode *mode, Enigma *enigma);
        void inputSetAllRotations(std::string input, Mode *mode, Enigma *enigma);

        // Set Notch
        void inputSetNotchChoice(std::string input, Mode *mode, Enigma *enigma);
        void inputSetOneNotch(std::string input, Mode *mode, Enigma *enigma);
        void inputSetAllNotches(std::string input, Mode *mode, Enigma *enigma);
        // Reset all rotors
        void inputResetAllRotors(std::string input, Mode *mode, Enigma *enigma);
    #pragma endregion
    #pragma region Switchboard settings
        void inputSwitchboardSettingsMenu(std::string input, Mode *mode, Enigma *enigma);
        void inputAddConnection(std::string input, Mode *mode, Enigma *enigma);
        void inputRemoveConnection(std::string input, Mode *mode, Enigma *enigma);
        void inputResetSwitchboard(std::string input, Mode *mode, Enigma *enigma);
    #pragma endregion
#pragma endregion

int main() {
    Enigma enigma = Enigma();
    Mode mode = Mode::MAIN_MENU;
    std::string input;
    while (mode != Mode::EXIT)
    {
        // std::cout<<"Begin:";
        // printMode(mode);
        // Print without error message
        switch (mode)
        {
        case Mode::MAIN_MENU:
            printMainMenu("");
            std::cin >> input;
            inputMainMenu(input, &mode);
            break;
        case Mode::CRYPTING:
            printCrypting();
            std::cin >> input;
            inputCrypting(input, &mode, &enigma);
            break;
        case Mode::MAIN_SETTINGS:
            printMainSettingsMenu("");
            std::cin >> input;
            inputMainSettingsMenu(input, &mode);
            break;
        case Mode::ROTOR_SETTINGS:    
            printRotorSettingsMenu(enigma, "");
            std::cin >> input;
            inputRotorSettingsMenu(input, &mode, &enigma);
            break;
        case Mode::SWITCHBOARD_SETTINGS:
            printSwitchboardSettingsMenu(enigma, "");
            std::cin >> input;
            inputSwitchboardSettingsMenu(input, &mode, &enigma);
            break;
        default:
            mode = Mode::EXIT;
            break;
        }
    }
    return 0;
}

#pragma region Prints
    void printMode(Mode mode) {
        std::cout << "Mode: ";
        switch (mode)
        {
        case Mode::MAIN_MENU:
            std::cout << "MAIN_MENU";
            break;
        case Mode::CRYPTING:
            std::cout << "CRYPTING";
            break;
        case Mode::MAIN_SETTINGS:
            std::cout << "MAIN_SETTINGS";
            break;
        case Mode::ROTOR_SETTINGS:
            std::cout << "ROTOR_SETTINGS";
            break;
        case Mode::SWITCHBOARD_SETTINGS:
            std::cout << "SWITCHBOARD_SETTINGS";
            break;
        case Mode::EXIT:
            std::cout << "EXIT";
            break;
        default:
            break;
        }
        std::cout << std::endl;
    }

    void printMainMenu(std::string eMsg) {
        system("cls");
        std::cout << "                     ENIMGA MACHINE"                      << std::endl;
        std::cout << "--------------------------------------------------------" << std::endl;
        std::cout << "[ In any mode switch with #1,#2 or #3 | #4 -> Mainmenu ]" << std::endl;
        std::cout << "1. Crypting"                                              << std::endl;
        std::cout << "2. Settings"                                              << std::endl;
        std::cout << "3. Exit"                                                  << std::endl;
        if (eMsg.length() > 0)
            std::cout <<"\n!!! "<< eMsg <<" !!!"<< std::endl;
        std::cout << "Choose an option: ";
    }

    void printCrypting() {
        system("cls");
        std::cout << "                   CRYPTING"                     << std::endl;
        std::cout << "-----------------------------------------------" << std::endl;
        std::cout << "[ Finish:  #4 -> Mainmenu   or   #3 -> Exit   ]" << std::endl<< std::endl;
        std::cout << "!! Non-(english)alphabetic characters will be ignored, !!\n" 
                  << "!! but will not cause error.                           !!"<< std::endl<< std::endl;
        std::cout << "Enter text to crypt: \n"                       << std::endl;
    }

    #pragma region Settings

        void printMainSettingsMenu(std::string eMsg) {
            system("cls");
            std::cout << "                SETTINGS"                 << std::endl;
            std::cout << "----------------------------------------" << std::endl;
            std::cout << "1. Rotors"                                << std::endl;
            std::cout << "2. Switchboard"                           << std::endl;
            std::cout << "3. Back"                                  << std::endl;
            if (eMsg.length() > 0)
                std::cout <<"\n!!! "<< eMsg <<" !!!"<< std::endl;
            std::cout << "Choose an option: ";
        }

        #pragma region Rotor_settings
        
            void printRotorSettingsMenu( Enigma enigma, std::string eMsg) {
                system("cls");
                std::cout << "             ROTOR SETTINGS"              << std::endl;
                std::cout << "----------------------------------------" << std::endl;
                enigma.printRotors();
                std::cout << "1. Set full rotor"                        << std::endl;
                std::cout << "2. Change serial number"                     << std::endl;
                std::cout << "3. Set rotation"                     << std::endl;
                std::cout << "4. Set notch"                         << std::endl;
                std::cout << "5. Reset all rotors"                      << std::endl;
                std::cout << "6. Back"                                  << std::endl;
                if (eMsg.length() > 0)
                    std::cout <<"\n!!! "<< eMsg <<" !!!"<< std::endl;
                std::cout << "Choose an option: " << std::endl;
            }

            #pragma region Rotor_settings_options
                // Set rotor
                void pirntSetRotorChoice(std::string eMsg) {
                    std::cout << "----------------------------------------" << std::endl;
                    std::cout << "Set rotor:"                            << std::endl;
                    std::cout << "1. ONE"                     << std::endl;
                    std::cout << "2. ALL"                     << std::endl;
                    std::cout << "3. Cancel"                     << std::endl;
                    if (eMsg.length() > 0)
                        std::cout <<"\n!!! "<< eMsg <<" !!!"<< std::endl;
                    std::cout << "Choose an option: ";
                }
                void printSetOneRotor(std::string eMsg) {
                    std::cout << "----------------------------------------" << std::endl;
                    std::cout << "Set ONE rotor:"                      << std::endl;
                    std::cout << "Syntax: Roro's number:Serial number,Rotation,Notch" << std::endl;
                    std::cout << "Rotor's number is roman number (I-III) Serial number is beetwen 1-5,"
                              << "Rotation and Notch are one letter A-Z!\n" << std::endl;
                    if (eMsg.length() > 0)
                        std::cout <<"\n!!! "<< eMsg <<" !!!"<< std::endl;
                    std::cout << "Enter your settings: ";
                }
                void printSetAllRotors(std::string eMsg) {
                    std::cout << "----------------------------------------" << std::endl;
                    std::cout << "Set ALL rotors:"                     << std::endl;
                    std::cout << "Syntax: Serial number,Rotation,Notch|...|..."<< std::endl;
                    std::cout << "Serial number is beetwen 1-5, Rotation and Notch are one letter A-Z!\n" << std::endl;
                    if (eMsg.length() > 0)
                        std::cout <<"\n!!! "<< eMsg <<" !!!"<< std::endl;
                    std::cout << "Enter your settings: ";
                }
                // Change rotor
                void printChangeRotorChoice(std::string eMsg) {
                    std::cout << "----------------------------------------" << std::endl;
                    std::cout << "Change rotor:"                        << std::endl;
                    std::cout << "1. ONE"                     << std::endl;
                    std::cout << "2. ALL"                     << std::endl;
                    std::cout << "3. Cancel"                     << std::endl;
                    if (eMsg.length() > 0)
                        std::cout <<"\n!!! "<< eMsg <<" !!!"<< std::endl;
                    std::cout << "Choose an option:";
                }
                void printChangeOneRotor(std::string eMsg) {
                    std::cout << "----------------------------------------" << std::endl;
                    std::cout << "Change ONE rotor:"                   << std::endl;
                    std::cout << "Syntax: Rotor's number:Serial number"                << std::endl;
                    std::cout << "Rotor's number is roman number (I-III), Serial number is beetwen 1 and 5!\n" << std::endl;
                    if (eMsg.length() > 0)
                        std::cout <<"\n!!! "<< eMsg <<" !!!"<< std::endl;
                    std::cout << "Enter your settings: ";
                }
                void printChangeAllRotors(std::string eMsg) {
                    std::cout << "----------------------------------------" << std::endl;
                    std::cout << "Change ALL rotors:"                  << std::endl;
                    std::cout << "Syntax: Serial number|...|..."<< std::endl;
                    std::cout << "Serial number is beetwen 1 and 5!\n" << std::endl;
                    if (eMsg.length() > 0)
                        std::cout <<"\n!!! "<< eMsg <<" !!!"<< std::endl;
                    std::cout << "Enter your settings: ";
                }
                // Set Rotation
                void printSetRotationChoice(std::string eMsg) {
                    std::cout << "----------------------------------------" << std::endl;
                    std::cout << "Set rotation:"                        << std::endl;
                    std::cout << "1. ONE"                     << std::endl;
                    std::cout << "2. ALL"                     << std::endl;
                    std::cout << "3. Cancel"                     << std::endl;
                    if (eMsg.length() > 0)
                        std::cout <<"\n!!! "<< eMsg <<" !!!"<< std::endl;
                    std::cout << "Choose an option:";
                }
                void printSetOneRotation(std::string eMsg) {
                    std::cout << "----------------------------------------" << std::endl;
                    std::cout << "Set ONE rotation:"                   << std::endl;
                    std::cout << "Syntax: Rotor's number:Rotation"                << std::endl;
                    std::cout << "Rotor's number is roman number (I-III) Rotation is one letter A-Z!\n" << std::endl;
                    if (eMsg.length() > 0)
                        std::cout <<"\n!!! "<< eMsg <<" !!!"<< std::endl;
                    std::cout << "Enter your settings: ";
                }
                void printSetAllRotations(std::string eMsg) {
                    std::cout << "----------------------------------------" << std::endl;
                    std::cout << "Set ALL rotations:"                  << std::endl;
                    std::cout << "Syntax: Rotation|...|..."<< std::endl;
                    std::cout << "Rotation is one letter A-Z!\n" << std::endl;
                    if (eMsg.length() > 0)
                        std::cout <<"\n!!! "<< eMsg <<" !!!"<< std::endl;
                    std::cout << "Enter your settings: ";
                }
                // Set Notch
                void printSetNotchChoice(std::string eMsg) {
                    std::cout << "----------------------------------------" << std::endl;
                    std::cout << "Set notch:"                           << std::endl;
                    std::cout << "1. ONE"                     << std::endl;
                    std::cout << "2. ALL"                     << std::endl;
                    std::cout << "3. Cancel"                     << std::endl;
                    if (eMsg.length() > 0)
                        std::cout <<"\n!!! "<< eMsg <<" !!!"<< std::endl;
                    std::cout << "Choose an option: ";
                }
                void printSetOneNotch(std::string eMsg) {
                    std::cout << "----------------------------------------" << std::endl;
                    std::cout << "Set ONE notch:"                      << std::endl;
                    std::cout << "Syntax: Rotor's number:Notch"                << std::endl;
                    std::cout << "Rotor's number is roman number (I-III) Notch is one letter A-Z!\n" << std::endl;
                    if (eMsg.length() > 0)
                        std::cout <<"\n!!! "<< eMsg <<" !!!"<< std::endl;
                    std::cout << "Enter your settings: ";
                }
                void printSetAllNotches(std::string eMsg) {
                    std::cout << "----------------------------------------" << std::endl;
                    std::cout << "Set ALL notches:"                    << std::endl;
                    std::cout << "Syntax: Notch|...|..."<< std::endl;
                    std::cout << "Notch is one letter A-Z!\n" << std::endl;
                    if (eMsg.length() > 0)
                        std::cout <<"\n!!! "<< eMsg <<" !!!"<< std::endl;
                    std::cout << "Enter your settings: ";
                }
                // Reset all rotors      
                void printResetAllRotors(std::string eMsg) {
                    std::cout << "----------------------------------------" << std::endl;
                    std::cout << "Reset all rotors:"                    << std::endl;
                    std::cout << "1. YES"                     << std::endl;
                    std::cout << "2. NO"                     << std::endl;
                    if (eMsg.length() > 0)
                        std::cout <<"\n!!! "<< eMsg <<" !!!"<< std::endl;
                    std::cout << "Choose an option: ";
                }    
            #pragma endregion
        #pragma endregion

        void printSwitchboardSettingsMenu(Enigma enigma, std::string eMsg) {
            system("cls");
            std::cout << "           SWITCHBOARD SETTINGS"          << std::endl;
            std::cout << "----------------------------------------" << std::endl;
            enigma.printSwitchboard();
            std::cout << "\n\n1. Add connection"                        << std::endl;
            std::cout << "2. Remove connection"                     << std::endl;
            std::cout << "3. Reset switchboard"                     << std::endl;
            std::cout << "4. Back"                                  << std::endl;
            if (eMsg.length() > 0)
                std::cout <<"\n!!! "<< eMsg <<" !!!"<< std::endl;
            std::cout << "Choose an option: ";
        }
        #pragma region Switchboard_settings_options
            void printAddConnection(std::string eMsg) {
                std::cout << "\n----------------------------------------" << std::endl;
                std::cout << "Add connection:"                        << std::endl;
                std::cout << "Syntax: Letter-Letter"                        << std::endl;
                std::cout << "Letters are alphabetic characters, (A-Z), order does not matter!"       << std::endl;
                if (eMsg.length() > 0)
                    std::cout <<"\n!!! "<< eMsg <<" !!!"<< std::endl;
                std::cout << "Enter your settings: ";
            }
            void printRemoveConnection(std::string eMsg) {
                std::cout << "\n----------------------------------------" << std::endl;
                std::cout << "Remove connection:"                     << std::endl;
                std::cout << "Syntax: Letter-Letter"                        << std::endl;
                std::cout << "Letters are alphabetic characters, (A-Z), order does not matter!"       << std::endl;
                if (eMsg.length() > 0)
                    std::cout <<"\n!!! "<< eMsg <<" !!!"<< std::endl;
                std::cout << "Enter your settings: ";
            }
            void printResetSwitchboard(std::string eMsg) {
                std::cout << "\n----------------------------------------" << std::endl;
                std::cout << "Reset switchboard:"                     << std::endl;
                std::cout << "1. YES"                     << std::endl;
                std::cout << "2. NO"                     << std::endl;
                if (eMsg.length() > 0)
                    std::cout <<"\n!!! "<< eMsg <<" !!!"<< std::endl;
                std::cout << "Choose an option:";
            }
        #pragma endregion
    #pragma endregion

#pragma endregion

    // If input is a mode switcher, change mode and return true
    bool isModeSwitcher(std::string input, Mode *mode) {
        if (std::regex_match(input, modeSwitcher)) {
            switch (input[1])
            {
            case '1':
                *mode = Mode::CRYPTING;
                break;
            case '2':
                *mode = Mode::MAIN_SETTINGS;
                break;
            case '3':
                *mode = Mode::EXIT;
                break;
            case '4':
                *mode = Mode::MAIN_MENU;
                break;
            default:
                break;
            }
            return true;
        } else { return false; }
    }

    bool isSerialNumberCrash(std::string input, Enigma enigma) {
        std::vector<int> serialNumbers = enigma.getRotorsSerialNumbers();
        int inputSerialNumber;
        bool isCrash = false;
        switch (input.length())
        {
        case 3:
            inputSerialNumber = input[2]-'0';
            break;
        case 4:
            inputSerialNumber = input[3]-'0';
            break;
        case 5:
            inputSerialNumber = input[4]-'0';
            break;
        case 7:
            inputSerialNumber = input[2]-'0';
            break;
        case 8:
            inputSerialNumber = input[3]-'0';
            break;
        default://9
            inputSerialNumber = input[4]-'0';
            break;
        }
        for (int i = 0; i < 3; i++)
        {
            if (serialNumbers[i] == inputSerialNumber) {
                isCrash = true;
                break;
            }
        }
        return isCrash;
    }
#pragma region Input

    void inputMainMenu(std::string input, Mode *mode) {
        while (!std::regex_match(input, menuTriOptions) && !std::regex_match(input, modeSwitcher))
        {
            printMainMenu("Input must be a number between 1-3 or a # switcher");
            std::cin >> input;
        }
        std::cout << input;
        if (!isModeSwitcher(input, mode)) {
            switch (input[0])
            {
            case '1':
                *mode = Mode::CRYPTING;
                break;
            case '2':
                *mode = Mode::MAIN_SETTINGS;
                break;
            default:
                *mode = Mode::EXIT;
                break;
            }
        }
    }

    void inputCrypting(std::string input, Mode *mode, Enigma *enigma) {
        std::ofstream file("Enigma_result.txt");
        if (!file) {
            std::cerr << "The output file could not be opened!" << std::endl;
            std::cin.get();
            return;
        }
        // Print start settings
        file << (*enigma).getSettings() << std::endl << std::endl;
    
        std::string str = "";
        std::string result = "";
        while (!isModeSwitcher(input, mode))
        {
            str += (*enigma).code(input);
            std::cin >> input;
        }
        // Fragment result
        for (int i = 0; i < str.length(); i++)
        {
            if (i % 4 == 0 && i != 0) {
                result += " ";
            }
            if (i % 16 == 0 && i != 0) {
                result += "\n";
            } 
            result += str[i];
        }
    
        // Print result
        file << result << std::endl;
        file.close();
    }

    #pragma region Settings
        void inputMainSettingsMenu(std::string input, Mode *mode) {
                while (!std::regex_match(input, menuTriOptions) && !std::regex_match(input, modeSwitcher))
                {
                    printMainMenu("Input must be a number between 1-3 or a # switcher");
                    std::cin >> input;
                }
                if (!isModeSwitcher(input, mode)) {
                    switch (input[0])
                    {
                    case '1':
                        *mode = Mode::ROTOR_SETTINGS;
                        break;
                    case '2':
                        *mode = Mode::SWITCHBOARD_SETTINGS;
                        break;
                    default:
                        *mode = Mode::MAIN_MENU;
                        break;
                    }
                }
        }

        #pragma region Rotor_settings
            //TODO: correct menu options
            void inputRotorSettingsMenu(std::string input, Mode *mode, Enigma *enigma) {
                while (!std::regex_match(input, rotorOptions) && !std::regex_match(input, modeSwitcher))
                {
                    printRotorSettingsMenu(*enigma, "Input must be a number between 1-6 or a # switcher");
                    std::cin >> input;
                }
                if (!isModeSwitcher(input, mode)) {
                    switch (input[0])
                    {
                    case '1':
                        pirntSetRotorChoice("");
                        inputSetRotorChoice(input, mode, enigma);
                        break;
                    case '2':
                        printChangeRotorChoice("");
                        inputChangeRotorChoice(input, mode, enigma);
                        break;
                    case '3':
                        printSetRotationChoice("");
                        inputSetRotationChoice(input, mode, enigma);
                        break;
                    case '4':
                        printSetNotchChoice("");
                        inputSetNotchChoice(input, mode, enigma);
                        break;
                    case '5':
                        printResetAllRotors("");
                        inputResetAllRotors(input, mode, enigma);
                        break;
                    default:
                        *mode = Mode::MAIN_SETTINGS;
                        break;
                    }
                }
            }

            #pragma region Rotor_settings_options
                // Set rotor
                void inputSetRotorChoice(std::string input, Mode *mode, Enigma *enigma) {
                    std::cin>>input;
                    while (!std::regex_match(input, menuTriOptions) && !std::regex_match(input, modeSwitcher))
                    {   
                        printRotorSettingsMenu(*enigma, "");
                        pirntSetRotorChoice("Input must be a number between 1-3 or a # switcher");
                        std::cin >> input;
                    }
                    if (!isModeSwitcher(input, mode)) {
                        switch (input[0])
                        {
                        case '1':
                            printRotorSettingsMenu(*enigma, "");
                            printSetOneRotor("");
                            inputSetOneRotor(input, mode, enigma);
                            break;
                        case '2':
                            printRotorSettingsMenu(*enigma, "");
                            printSetAllRotors("");
                            inputSetAllRotors(input, mode, enigma);
                            break;
                        default:
                            *mode = Mode::ROTOR_SETTINGS;
                            break;
                        }
                    }
                }
                void inputSetOneRotor(std::string input, Mode *mode, Enigma *enigma) {
                    std::cin>>input;
                    while ((!std::regex_match(input, setOneRotor) && !std::regex_match(input, modeSwitcher)) ||
                            (std::regex_match(input, setOneRotor) && isSerialNumberCrash(input, *enigma)))
                    {
                        if ((std::regex_match(input, setOneRotor) && isSerialNumberCrash(input, *enigma)))
                        {
                            printRotorSettingsMenu(*enigma, "");
                            printSetOneRotor("Serial numbers must be different from the others, try again or cancle with # switcher!");
                        } else {
                            printRotorSettingsMenu(*enigma, "");
                            printSetOneRotor("Invalid syntax or value, try again or cancle with # switcher!");
                        }
                        std::cin >> input;
                    }
                    if (!isModeSwitcher(input, mode)) {
                        switch (input.length()) {
                        case 7:
                            //for example I:1,A,Z
                            //            0123456
                            (*enigma).changeRotor(0, input[2] -'0');
                            (*enigma).setRotation(0, input[4]);
                            (*enigma).setNotch(0, input[6]);
                            break;
                        case 8:
                            //for example II:2,B,Y
                            //            01234567
                            (*enigma).changeRotor(1, input[3] - '0');
                            (*enigma).setRotation(1, input[5]);
                            (*enigma).setNotch(1, input[7]);
                            break;
                        default: // length 9
                            //for example III:3,C,X
                            //            012345678
                            (*enigma).changeRotor(2, input[4] - '0');
                            (*enigma).setRotation(2, input[6]);
                            (*enigma).setNotch(2, input[8]);
                            break;
                        }
                    }
                }
                void inputSetAllRotors(std::string input, Mode *mode, Enigma *enigma) {
                    std::cin>>input;
                    // while not valid syntax an  not mode switcher
                    // or valid syntax, but serial numbers are the same
                    while ((!std::regex_match(input, setAllRotors) && !std::regex_match(input, modeSwitcher)) ||
                        (std::regex_match(input, setAllRotors) && (input[0] == input[6] || input[0] == input[12] || input[6] == input[12])))
                    {    
                        // if valid syntax, but serial numbers are the same
                        if (std::regex_match(input, setAllRotors) &&
                            (input[0] == input[6] || input[0] == input[12] || input[6] == input[12])) {
                            printRotorSettingsMenu(*enigma, "");
                            printSetAllRotors("Serial numbers must be different, try again or cancle with # switcher!");
                        } else {
                        // if not valid syntax or value
                            printRotorSettingsMenu(*enigma, "");
                            printSetAllRotors("Invalid syntax or value, try again or cancle with # switcher!");
                        }
                        std::cin >> input;
                    }
                    if (!isModeSwitcher(input, mode)) {
                        //for example 1,A,Z|2,B,Y|3,C,X
                        //            01234567890123456
                        (*enigma).changeRotors(input[0]-'0', input[6]-'0', input[12]-'0');
                        (*enigma).setRotations(input[2], input[8], input[14]);
                        (*enigma).setNotches(input[4], input[10], input[16]);                             
                    }
                }
        
                // Change rotor
                void inputChangeRotorChoice(std::string input, Mode *mode, Enigma *enigma) {
                    std::cin>>input;
                    while (!std::regex_match(input, menuTriOptions) && !std::regex_match(input, modeSwitcher))
                    {   
                        printRotorSettingsMenu(*enigma, "");
                        printChangeRotorChoice("Input must be a number between 1-3 or a # switcher");
                        std::cin >> input;
                    }
                    if (!isModeSwitcher(input, mode)) {
                        switch (input[0])
                        {
                        case '1':
                            printRotorSettingsMenu(*enigma, "");
                            printChangeOneRotor("");
                            inputChangeOneRotor(input, mode, enigma);
                            break;
                        case '2':
                            printRotorSettingsMenu(*enigma, "");
                            printChangeAllRotors("");
                            inputChangeAllRotors(input, mode, enigma);
                            break;
                        default:
                            *mode = Mode::ROTOR_SETTINGS;
                            break;
                        }
                    }
                }
                void inputChangeOneRotor(std::string input, Mode *mode, Enigma *enigma) {
                    std::cin>>input;
                    
                    while ((!std::regex_match(input, changeOneRotor) && !std::regex_match(input, modeSwitcher)) ||
                          (std::regex_match(input, changeOneRotor) && isSerialNumberCrash(input, *enigma)))
                    {
                        if ((std::regex_match(input, changeOneRotor) && isSerialNumberCrash(input, *enigma)))
                        {
                            printRotorSettingsMenu(*enigma, "");
                            printChangeOneRotor("Serial numbers must be different from the others, try again or cancle with # switcher!");
                        } else {
                            printRotorSettingsMenu(*enigma, "");
                            printChangeOneRotor("Invalid syntax or value, try again or cancle with # switcher!");
                        }
                        std::cin >> input;
                    }
                    if (!isModeSwitcher(input, mode)) {
                        switch (input.length()) {
                        case 3:
                            //for example I:2
                            //            012
                            (*enigma).changeRotor(0, input[2]-'0');
                            break;
                        case 4:
                            //for example II:3
                            //            0123
                            (*enigma).changeRotor(1, input[3]-'0');
                            break;
                        default: // length 5
                            //for example III:4
                            //            01234
                            (*enigma).changeRotor(2, input[4]-'0');
                            break;
                        }
                    }
                }
                void inputChangeAllRotors(std::string input, Mode *mode, Enigma *enigma) {
                    std::cin>>input;
                    while ((!std::regex_match(input, changeAllRotors) && !std::regex_match(input, modeSwitcher)) ||
                        (std::regex_match(input, changeAllRotors) && (input[0] == input[2] || input[0] == input[4] || input[2] == input[4])))
                    {    
                        // if valid syntax, but serial numbers are the same
                        if (std::regex_match(input, changeAllRotors) &&
                            (input[0] == input[2] || input[0] == input[4] || input[2] == input[4])) {
                            printRotorSettingsMenu(*enigma, "");
                            printSetAllRotors("Serial numbers must be different, try again or cancle with # switcher!");
                        } else {
                        // if not valid syntax or value
                            printRotorSettingsMenu(*enigma, "");
                            printSetAllRotors("Invalid syntax or value, try again or cancle with # switcher!");
                        }
                        std::cin >> input;
                    }
                    if (!isModeSwitcher(input, mode)) {
                        //for example A|B|C
                        //            01234
                        (*enigma).changeRotors(input[0]-'0', input[2]-'0', input[4]-'0');
                    }
                }

                // Set Rotation
                void inputSetRotationChoice(std::string input, Mode *mode, Enigma *enigma) {
                    std::cin>>input;
                    while (!std::regex_match(input, menuTriOptions) && !std::regex_match(input, modeSwitcher))
                    {   
                        printRotorSettingsMenu(*enigma, "");
                        printSetRotationChoice("Input must be a number between 1-3 or a # switcher");
                        std::cin >> input;
                    }
                    if (!isModeSwitcher(input, mode)) {
                        switch (input[0])
                        {
                        case '1':
                            printRotorSettingsMenu(*enigma, "");
                            printSetOneRotation("");
                            inputSetOneRotation(input, mode, enigma);
                            break;
                        case '2':
                            printRotorSettingsMenu(*enigma, "");
                            printSetAllRotations("");
                            inputSetAllRotations(input, mode, enigma);
                            break;
                        default:
                            *mode = Mode::ROTOR_SETTINGS;
                            break;
                        }
                    }
                }
                void inputSetOneRotation(std::string input, Mode *mode, Enigma *enigma) {
                    std::cin >> input;
                    while (!std::regex_match(input, setOneROrN) && !std::regex_match(input, modeSwitcher))
                    {
                        printRotorSettingsMenu(*enigma, "");
                        printSetOneRotation("Invalid syntax or value, try again or cancle with # switcher!");
                        std::cin >> input;
                    }
                    if (!isModeSwitcher(input, mode)) {
                        switch (input.length()) {
                        case 3:
                            //for example I:A
                            //            012
                            (*enigma).setRotation(0, input[2]);
                            break;
                        case 4:
                            //for example II:B
                            //            0123
                            (*enigma).setRotation(1, input[3]);
                            break;
                        default: // length 5
                            //for example III:C
                            //            01234
                            (*enigma).setRotation(2, input[4]);
                            break;
                        }
                    }
                }
                void inputSetAllRotations(std::string input, Mode *mode, Enigma *enigma) {
                    std::cin >> input;
                    while (!std::regex_match(input, setAllROrN) && !std::regex_match(input, modeSwitcher))
                    { 
                        printRotorSettingsMenu(*enigma, "");
                        printSetAllRotations("Invalid syntax or value, try again or cancle with # switcher!");
                        std::cin >> input;
                    }
                    if (!isModeSwitcher(input, mode)) {
                        //for example A|B|C
                        //            01234
                        (*enigma).setRotations(input[0], input[2], input[4]);
                    }
                }

                // Set Notch
                void inputSetNotchChoice(std::string input, Mode *mode, Enigma *enigma) {
                    std::cin >> input;
                    while (!std::regex_match(input, menuTriOptions) && !std::regex_match(input, modeSwitcher))
                    {   
                        printRotorSettingsMenu(*enigma, "");
                        printSetNotchChoice("Input must be a number between 1-3 or a # switcher");
                        std::cin >> input;
                    }
                    if (!isModeSwitcher(input, mode)) {
                        switch (input[0])
                        {
                        case '1':
                            printRotorSettingsMenu(*enigma, "");
                            printSetOneNotch("");
                            inputSetOneNotch(input, mode, enigma);
                            break;
                        case '2':
                            printRotorSettingsMenu(*enigma, "");
                            printSetAllNotches("");
                            inputSetAllNotches(input, mode, enigma);
                            break;
                        default:
                            *mode = Mode::ROTOR_SETTINGS;
                            break;
                        }
                    }
                }
                void inputSetOneNotch(std::string input, Mode *mode, Enigma *enigma) {
                    std::cin >> input;
                    while (!std::regex_match(input, setOneROrN) && !std::regex_match(input, modeSwitcher))
                    {
                        printRotorSettingsMenu(*enigma, "");
                        printSetOneNotch("Invalid syntax or value, try again or cancle with # switcher!");
                        std::cin >> input;
                    }
                    if (!isModeSwitcher(input, mode)) {
                        switch (input.length()) {
                        case 3:
                            //for example I:A
                            //            012
                            (*enigma).setNotch(0, input[2]);
                            break;
                        case 4:
                            //for example II:B
                            //            0123
                            (*enigma).setNotch(1, input[3]);
                            break;
                        default: // length 5
                            //for example III:C
                            //            01234
                            (*enigma).setNotch(2, input[4]);
                            break;
                        }
                    }
                }
                void inputSetAllNotches(std::string input, Mode *mode, Enigma *enigma) {
                    std::cin >> input;
                    while (!std::regex_match(input, setAllROrN) && !std::regex_match(input, modeSwitcher))
                    { 
                        printRotorSettingsMenu(*enigma, "");
                        printSetAllNotches("Invalid syntax or value, try again or cancle with # switcher!");
                        std::cin >> input;
                    }
                    if (!isModeSwitcher(input, mode)) {
                        //for example A|B|C
                        //            01234
                        (*enigma).setNotches(input[0], input[2], input[4]);
                    }
                }

                // Reset all rotors
                void inputResetAllRotors(std::string input, Mode *mode, Enigma *enigma) {
                    std::cin >> input;
                    while (!std::regex_match(input, yesNoChoice) && !std::regex_match(input, modeSwitcher))
                    {   
                        printRotorSettingsMenu(*enigma, "");
                        printResetAllRotors("Input must be a number between 1-2 or a # switcher");
                        std::cin >> input;
                    }
                    if (!isModeSwitcher(input, mode)) {
                        if (input[0] == '1') {
                            (*enigma).resetRotors();
                        } else {
                            *mode = Mode::ROTOR_SETTINGS;
                        }
                    }
                }
            #pragma endregion
        #pragma endregion
        
        #pragma region Switchboard_settings
            void inputSwitchboardSettingsMenu(std::string input, Mode *mode, Enigma *enigma) {
                while (!std::regex_match(input, menuQuatroOptions) && !std::regex_match(input, modeSwitcher))
                {
                    printMainMenu("Input must be a number between 1-4 or a # switcher");
                    std::cin >> input;
                }
                if (!isModeSwitcher(input, mode)) {
                    switch (input[0])
                    {
                    case '1':
                        printAddConnection("");
                        inputAddConnection(input, mode, enigma);
                        break;
                    case '2':
                        printRemoveConnection("");
                        inputRemoveConnection(input, mode, enigma);
                        break;
                    case '3':
                        printResetSwitchboard("");
                        inputResetSwitchboard(input, mode, enigma);
                        break;
                    default:
                        *mode = Mode::MAIN_SETTINGS;
                        break;
                    }
                }
            }
            void inputAddConnection(std::string input, Mode *mode, Enigma *enigma) {
                std::cin >> input;
                while (!std::regex_match(input, Connection) && !std::regex_match(input, modeSwitcher))
                {
                    printSwitchboardSettingsMenu(*enigma, "");
                    printAddConnection("Invalid syntax or value, try again or cancle with # switcher!");
                    std::cin >> input;
                }
                if (!isModeSwitcher(input, mode)) {
                    //for example A-B
                    //            012
                    (*enigma).addConnection(input[0], input[2]);
                }
            }
            void inputRemoveConnection(std::string input, Mode *mode, Enigma *enigma) {
                std::cin >> input;
                while (!std::regex_match(input, Connection) && !std::regex_match(input, modeSwitcher))
                {
                    printSwitchboardSettingsMenu(*enigma, "");
                    printRemoveConnection("Invalid syntax or value, try again or cancle with # switcher!");
                    std::cin >> input;
                }
                if (!isModeSwitcher(input, mode)) {
                    //for example A-B
                    //            012
                    (*enigma).removeConnection(input[0]);
                }
            }
            void inputResetSwitchboard(std::string input, Mode *mode, Enigma *enigma) {
                std::cin >> input;
                while (!std::regex_match(input, yesNoChoice) && !std::regex_match(input, modeSwitcher))
                {   
                    printSwitchboardSettingsMenu(*enigma, "");
                    printResetSwitchboard("Input must be a number between 1-2 or a # switcher");
                    std::cin >> input;
                }
                if (!isModeSwitcher(input, mode)) {
                    if (input[0] == '1') {
                        (*enigma).resetSwitchboard();
                    }
                }
            }
        #pragma endregion
    #pragma endregion
#pragma endregion