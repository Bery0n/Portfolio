#include <iostream>
#include <fstream>
#include <stdexcept>
#include <unordered_map>
#include <map>
#include <string>
#include <cmath>

std::unordered_map<char, int> createLetterMap() {
    std::unordered_map<char, int> frequency;
    frequency['a'] = 0;
    frequency['b'] = 0;
    frequency['c'] = 0;
    frequency['d'] = 0;
    frequency['e'] = 0;
    frequency['f'] = 0;
    frequency['g'] = 0;
    frequency['h'] = 0;
    frequency['i'] = 0;
    frequency['j'] = 0;
    frequency['k'] = 0;
    frequency['l'] = 0;
    frequency['m'] = 0;
    frequency['n'] = 0;
    frequency['o'] = 0;
    frequency['p'] = 0;
    frequency['q'] = 0;
    frequency['r'] = 0;
    frequency['s'] = 0;
    frequency['t'] = 0;
    frequency['u'] = 0;
    frequency['v'] = 0;
    frequency['w'] = 0;
    frequency['x'] = 0;
    frequency['y'] = 0;
    frequency['z'] = 0;
    return frequency;

}
char convertToEng(int x, int y){
    char ch;
    if (x == -61) {
        switch (y)
        {
        case -95:  // á
            ch = 'a'; break;
        case -127: // Á
            ch = 'a'; break;
        case -87:  // é
            ch = 'e'; break;
        case -119: // É
            ch = 'e'; break;
        case -83:  // í
            ch = 'i'; break;
        case -115: // Í
            ch = 'i'; break;
        case -77:  // ó
            ch = 'o'; break;
        case -109: // Ó
            ch = 'o'; break;
        case -74:  // ö
            ch = 'o'; break;
        case -106: // Ö
            ch = 'o'; break;
        /*case -70:  // ú
            ch = 'u'; break;
        case -102: // Ú
            ch = 'u'; break;
        case -68:  // ü
            ch = 'u'; break;
        case -100: // Ü
            ch = 'u'; break;*/
        default:
            ch = 'u'; break;
        }

    } else if (x == -59) {
        switch (y)
        {
        case -111: // ő
            ch = 'o'; break;
        case -112: // Ő
            ch = 'o'; break;
        /*case -79:  // ű
            ch = 'u'; break;
        case -80:  // Ű
            ch = 'u'; break;*/
        default:
            ch = 'u'; break;
        }
    }
    
    
    return ch;
}

/*void printFrequency(std::unordered_map<char, int> frequency){

    std::ofstream file("Output.txt");
     if (!file) {
        std::cerr << "The output file could not be opened!" << std::endl;
        return;
    }

    file << "Letter frequency:" << std::endl;
    for (const auto &i : frequency) {
        file << i.first << " : " << i.second << std::endl;
    }
    return;
}*/
void printRnOFrequency(std::unordered_map<char, int> frequency){
    std::ofstream file("Output.txt");
    if (!file) {
        std::cerr << "The output file could not be opened!" << std::endl;
        return;
    }

    std::map<char, int> orderedFrequency;
    std::map<int, std::string> rankedFrequency;
    int n;
    char c;
    std::string str;
    float N = 0;

    for ( auto &i : frequency) {
        c = i.first; str = i.first; n = i.second;
        N += n;
        orderedFrequency[c] = n;
        rankedFrequency[n] += str + " ";
    }

    std::cout << "            Ranked frequency:" << std::endl
              << "------------------------------------------" << std::endl
              << "(Frequency : Letters : Percentage) Sum: " << N << " pcs" << std::endl;
    file      << "            Ranked frequency:" << std::endl
              << "------------------------------------------" << std::endl
              << "(Frequency : Letters : Percentage) Sum: " << N << " pcs" << std::endl;
    
    
    for (auto it = rankedFrequency.rbegin(); it != rankedFrequency.rend(); it++) {
        std::cout << it->first << " : " << it->second << ", " << std::round((it->first/N)*100)/100  << "%" << std::endl;
        file << it->first << " : " << it->second << ", " << std::round((it->first/N)*100)/100  << "%" << std::endl;
    }

    std::cout << std::endl << std::endl
                << "                  Ordered frequency:" << std::endl
                << "----------------------------------------------------------" << std::endl
                << "(Letter : Frequency : Percentage)  Sum: " << N << " pcs" << std::endl << std::endl;
    file  << std::endl << std::endl
                << "                  Ordered frequency:" << std::endl
                << "----------------------------------------------------------" << std::endl
                << "(Letter : Frequency : Percentage)  Sum: " << N << " pcs" << std::endl << std::endl;
    for (auto &i : orderedFrequency) {
        if (i.second > 0) {
            std::cout << i.first << " : " << i.second << ", " << std::round((i.second/N)*100)/100  << "%" << std::endl;
            file << i.first << " : " << i.second << ", " << std::round((i.second/N)*100)/100 << "%" << std::endl;
        }
    }
    std::cout << rankedFrequency[0] << " : 0" << std::endl;
    file << rankedFrequency[0] << " : 0" << std::endl;
}

int main(){
    std::cout << "Enter filename (e.g.: filename.txt): ";
    std::string filename;
    std::cin >> filename;

    try
    {
        //open file
        std::ifstream file(filename);
        //check file
        if (!file) {
            throw std::runtime_error("File does not found!");
        } else {
            //storage (char, frequency)
            std::unordered_map<char, int> frequency = createLetterMap();

            //read file
            char c;
            int HunCh = 0; // for the first negative number of hungaryan character

            while (file.get(c)){
                //converting hungaryan character to english
                if (int(c)<0) {
                    if (HunCh) {
                        c = convertToEng(HunCh,int(c));
                        HunCh = 0;
                    } else {
                        HunCh = int(c);
                    }
                }
                // count letter
                if (isalpha(c)) {
                    frequency[tolower(c)]++;
                }
            }
            file.close();

            //print output
            // printFrequency(frequency);
            printRnOFrequency(frequency);
            
            std::cout << "Press enter to exit...";
            std::cin.get();
            std::cin.get();
        }

        
    }
    catch(const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        std::cout << "Press enter to exit...";
        std::cin.get();
        std::cin.get();
    }

    
    return 0;
}