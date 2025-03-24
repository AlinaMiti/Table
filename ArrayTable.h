#pragma once
#include "Table.h"

//перечисление для обозначения нашего положения в таблице
enum DataPos {First, Current, Last}; //Current - где-то не в начале и не в конце

using PTabRecord = TabRecord*;

class ArrayTable : public Table{  //огранизация памяти для хранения элементов
protected:
    size_t _tabSize; 
    size_t _curPos; //на какой позиции мы находимся
    PTabRecord* _records; //массив указателей на рекордс
public:
    ArrayTable(size_t tabSize = 25){

    }
    ~ArrayTable() {};

    //Информационные методы
    virtual bool IsFull() const;
    size_t GetTabSize() const;



};