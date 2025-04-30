#ifndef FRACTION_HPP
#define FRACTION_HPP

#include <iostream>

class Ulamek {
    public:
        Ulamek(int a, int b);
        
        Ulamek operator+(const Ulamek& other) const;
        Ulamek operator-(const Ulamek& other) const;
        Ulamek operator*(const Ulamek& other) const;
        Ulamek operator/(const Ulamek& other) const;
        bool operator==(const Ulamek& other) const;
    
        friend std::ostream& operator<<(std::ostream& os, const Ulamek& f) {
            os << f.a << "/" << f.b;
            return os;
        }
    
    private:
        void optimize();
    
        int a;
        int b; 
    };
    
#endif