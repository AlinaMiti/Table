#include "DatValue.h"

class Marks : public DatValue{
protected:
    int _math;
    int _physics;
    int _sport;
    int _psychology;
    int _history;
public:
    void Print(int math, int physics, int sport, int psychology, int history){
        std::cout<< " | " << math << " | " << physics << " | " << sport << " | " << psychology <<  " | " << history << " |";
    }
};