#include <iostream>
#pragma once
#include "TabRecord.h"
#include "DatValue.h"

//абстрактный класс

class Table{
protected:
    size_t _dataCount;  //кол-во записей таблицы
    int _efficientcy;  //подсчет эффективности таблицы. За сколько действий выполняем операцию
public:
    Table(){_dataCount = 0; _efficientcy = 0;}
    virtual ~Table(){};

    size_t GetDataCount() const {return _dataCount;}
    int GetEfficiency() const {return _efficientcy;}
    bool IsEmpty() const {return _dataCount == 0;}
    virtual bool IsFull() const = 0;  //у каждого класса реализация своя
    virtual Key GetKey() const = 0;   //значение для текущей записи
    virtual PDatValue GetValue() const = 0;   //значение для текущей записи

    //Основные методы таблиц. У каждой таблицы своя реализация

    virtual PDatValue FindRecord(const Key& key) = 0;
    virtual void InsRecord(const Key& key, PDatValue value) = 0; 
    virtual void DelRecord(const Key& key) = 0;
    
    //Навигация
    // = 0 значит что нет реализацииб но в классе наследнике она необходима
    virtual bool Reset() = 0;  //сброс текущего положения на начало
    virtual bool IsTabEnded() const = 0;  //дошли ли до последней записи
    virtual bool GoNext() = 0;  //переместиться на следщ запись
};