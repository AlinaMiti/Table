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
        os << " | " << _math << " | " << _physics << " | " << _sport << " | " << _psychology <<  " | " << _history << " |";
    }

    virtual DatValue* GetCopy() override {
        return new Marks(_math, _physics, _sport, _psychology, _history);
    }
    int GetMath() const{
        return _math;
    }
    int GetPhysics()const{
        return _physics;
    }
    int GetSport()const{
        return _sport;
    }
    int GetPsychology()const{
        return _psychology;
    }
    int GetHistory()const{
        return _history;
    }
};