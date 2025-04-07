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
        _tabSize = tabSize;
        _records = new PTabRecord[_tabSize];
        for(size_t i = 0; i < _tabSize; i++){
            _records[i] = nullptr;
        }
        _curPos = 0;
    }
    ~ArrayTable(){
        for(size_t i = 0; i < _dataCount; i++){ //_dataCount реальное количество элементов
            delete [] _records[i];
        }
        delete [] _records;
    }

    //Информационные методы
    virtual bool IsFull() const{
        return _dataCount >= _tabSize;
    }
    size_t GetTabSize() const{
        return _tabSize;
    }
    virtual Key GetKey() const{
        return GetKey(Current);
    }
    virtual PDatValue GetValuePtr() const{ //возврат текущей записи
        return GetValuePtr(DataPos::Current);
    }

    virtual Key GetKey(DataPos position) const; //возврат значения ключа
    virtual PDatValue GetValuePtr(DataPos position) const;

    //методы навигации
    virtual bool Reset();  //сброс текущего положения на начало
    virtual bool IsTabEnded() const;  //дошли ли до последней записи
    virtual bool GoNext();  //переместиться на следщ запись

    virtual bool SetCurrentPos(size_t pos); //устанавливает CurrentPos
    size_t GetCurrentPos() const{
        return _curPos;
    }

    friend class SortTable;
};