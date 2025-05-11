#pragma once
#include <iostream>

//от нее будет наследоваться класс (типа судент/массив оценок) с полями ключ и value. Тут переопределим Принт. Имя и оценки 

class DatValue{
protected:
    virtual void Print(std::ostream& os) const = 0;

public:
    DatValue(){}
    virtual DatValue* GetCopy() = 0;

    friend std::ostream& operator<<(std::ostream& os, const DatValue& dv){
        if(&dv != nullptr){
            dv.Print(os);
        }
        return os;
    }

    virtual bool operator==(const DatValue& dv) const{
        return false;
    }

    virtual ~DatValue() {}
};

using PDatValue = DatValue*;