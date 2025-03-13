#include <iostream>
#include <cstdlib> 
#include <string>

namespace strutil {
    std::string toUpper(const std:: string& original) {
        std::string result = original;
        for (char& c : result) {
            if (c >= 'a' && c <= 'z') {
                    c -= 32;
            }            
        }
        return result; 
    }

    std::string rand(int length) {
        std::string result;
        for(int i = 0; i < length; i++) {
            result += 'a' + ::rand() % 26;
        }
        return result;
    }

    std::string longestWordLength(const std:: string& str) {
        int maxLength = 0;
        int currentLength = 0;

        for (char c : str) {
            if (c == ' ') {
                if (currentLength > maxLength) {
                    maxLength = currentLength;
                    currentLength = 0;
                } else {
                    currentLength++;
                }
            }
        }
        if (currentLength > maxLength) {
            maxLength = currentLength;
        }
    }

    std::string rot13() {

    }

    std::string count0occurence(){

    }
}

int main() {
    std::cout << strutil::toUpper("sfsahfhasfafj") << std::endl;
}