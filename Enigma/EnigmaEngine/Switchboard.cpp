#include "Switchboard.h"

#include <vector>
#include <iostream>
#include <algorithm>

#pragma region Private


#pragma endregion

#pragma region Public
    #pragma region Constructors and Destructors

        Switchboard::Switchboard(std::vector<char> alphabet) : alphabet(alphabet){
            reset();
        }
        Switchboard::Switchboard() {
            Switchboard(std::vector<char> {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'});
        }
        Switchboard::~Switchboard()
        {
        }

    #pragma endregion

    #pragma region Connections

        void Switchboard::reset() {
            connections.clear();
            for (int i = 0; i < alphabet.size(); i++) {
                connections.insert(std::make_pair(alphabet[i],alphabet[i]));
            } 
        }
        void Switchboard::reset(std::vector<char> alphabet) {
            this->alphabet = alphabet;
            reset();
        }

        void Switchboard::setConnection(char a, char b) {
            // this removes both directed connections (a->b and b->a)
            removeConnection(a);
            removeConnection(b);
            connections[a] = b;
            connections[b] = a;
        }

        void Switchboard::removeConnection(char a) {
            connections[connections[a]] = connections[a];
            connections[a] = a;
        }

        bool Switchboard::isEmpty() {
            for (int i = 0; i < alphabet.size(); i++) {
                if (connections[alphabet[i]] != alphabet[i]) {
                    return false;
                }
            }
            return true;
        }

    #pragma endregion    

    char Switchboard::convert(char a) {
        return connections[a];
    }

    void Switchboard::print() {
        std::cout << "|";
        for (int i = 0; i < alphabet.size(); i++) {
            std::cout << " " << alphabet[i] <<" |";
        }
        std::cout << std::endl;
        for (int i = 0; i < alphabet.size(); i++)
        {
            std::cout << "+---";
        }
        std::cout << "+" << std::endl << "|";
        for (int i = 0; i < alphabet.size(); i++) {
            if (connections[alphabet[i]] != alphabet[i])
                std::cout << " " << connections[alphabet[i]] <<" |";
            else
                std::cout << "   |";
        }
    }

    std::string Switchboard::toString(){
        if (this->isEmpty())
        {
            return "Switchboard: empty";
        } else {
            std::string line1 = "|";
            std::string line2 = "";
            std::string line3 = "|";
            
            for (int i = 0; i < alphabet.size(); i++) {
                if (connections[alphabet[i]] != alphabet[i]){
                    line1 += " " + std::string(1, alphabet[i]) + " |";
                    line2 += "+---";
                    line3 += " " + std::string(1, connections[alphabet[i]]) + " |";
                }
            }

            line2 += "+";
            return ("Switchboard:\n" + line1 + "\n" + line2 + "\n" + line3);
        }
    }
        
#pragma endregion

