#include "DatValue.h"
#pragma once

class Marks : public DatValue{
protected:
    int _math;
    int _physics;
    int _sport;
    int _psychology;
    int _history;
public:
    Marks(int math = 0, int physics = 0, int sport = 0, int psychology = 0, int history = 0)
        : _math(math), _physics(physics), _sport(sport), _psychology(psychology), _history(history) {}

    //void Print(int math, int physics, int sport, int psychology, int history)
    virtual void Print(std::ostream& os) const override{
        std::cout<< " | " << _math << " | " << _physics << " | " << _sport << " | " << _psychology <<  " | " << _history << " |";
    }

    virtual DatValue* GetCopy() override {
        return new Marks(_math, _physics, _sport, _psychology, _history);
    }

    // virtual void Print(std::ostream& os) const override {
    //     os << std::setw(8) << std::left << "Math:" << std::setw(4) << _math
    //        << std::setw(9) << std::left << "Physics:" << std::setw(4) << _physics
    //        << std::setw(8) << std::left << "Sport:" << std::setw(4) << _sport
    //        << std::setw(11) << std::left << "Psychology:" << std::setw(4) << _psychology
    //        << std::setw(9) << std::left << "History:" << std::setw(4) << _history;
    // }
};