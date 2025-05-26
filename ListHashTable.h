#pragma once
#include <forward_list> 
#include <list> 
#include "HashTable.h"
#include "ArrayHash.h"

class ListHashTable : public HashTable{
private:
    size_t _tabSize;
    size_t _curPos; //позиция в списке
    size_t _curList;  //текущая позиция в массиве
    std::list<PTabRecord>* _lists; //массив списков
    std::list<PTabRecord>::iterator _curElem;
public:
    ListHashTable(size_t tabSize);
    ~ListHashTable();

    bool IsFull();  //всегда false
    PDatValue FindRecord(Key key);    //поиск по ключу
    void InsRecord(const Key& key, PDatValue value) override;  //добавление записи
    void DelRecord(const Key& key) override;  //удаление записи

    //Навигация
    
    bool Reset() override;    //сбрасывает на стартовую позицию
    bool IsTabEnded() const override; //находимся ли мы в конце таблицы
    bool GoNext() override;
    
    Key GetKey() const override;
    PDatValue GetValue() const override;
};