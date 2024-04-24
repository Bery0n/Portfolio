#pragma once

#include <unordered_map>
#include <string>
#include <vector>

class Switchboard {
    private:
        std::unordered_map<char, char> connections;
        std::vector<char> alphabet;

        // char* getPointer(char a);

    public:
        Switchboard(std::vector<char> alphabet);
        Switchboard();
        ~Switchboard();

        #pragma region Connections
            void reset();
            void reset(std::vector<char> alphabet);
            void setConnection(char a, char b);
            void removeConnection(char a);

            bool isEmpty();
        #pragma endregion
        
        char convert(char a);
        void print();
        std::string toString();
};