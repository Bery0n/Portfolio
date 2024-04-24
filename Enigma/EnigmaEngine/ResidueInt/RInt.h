#pragma once

enum RIntType {
    POSITIV,
    NEGATIV,
    FULLRANGE
};

class RInt {
    private:
        int modulus;
        int n;
        RIntType type;

        void typeCorrection();

    public:
        #pragma region Constructors and Destructors
            RInt(int moudulus, int n, RIntType type);
            RInt(int modulus, int n);
            RInt(int modulus);
            RInt();
            ~RInt();

        #pragma endregion

        #pragma region Getters

            int getNumber();
            int getModulus();
            int getPositiv();
            int getNegativ();
            RIntType getType();

        #pragma endregion

        #pragma region Setters

            void setNumber(int n);
            void setModulus(int modulus);
            void set(int n, int modulus);
            void setPositiv();
            void setNegativ();
            void setFullranged();
            void setType(RIntType type);
            
        #pragma endregion
        
        #pragma region Operators
            
            #pragma region Increment

                RInt operator++() {
                    n++;
                    return *this;
                }
                RInt operator++(int) {
                    RInt temp = *this;
                    ++(n);
                    return temp;
                }

                //Addition
                RInt operator+(int m) {
                    this->n += m;
                    return *this;
                }
                RInt operator+=(int m){
                    n += m;
                    return *this;
                }

            #pragma endregion
            #pragma region Decrement 

                RInt operator--() {
                    n--;
                    return *this;
                }
                RInt operator--(int) {
                    RInt temp = *this;
                    --(n);
                    return temp;
                }

                //Subtraction
                RInt operator-(int m) {
                    this->n -= m;
                    return *this;
                }
                RInt operator-=(int m){
                    this->n -= m;
                    return *this;
                }

            #pragma endregion
        #pragma endregion
};