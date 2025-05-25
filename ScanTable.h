#pragma once
#include "ArrayTable.h"

class ScanTable : public ArrayTable {
//все приватные поля в родительском классе
public:
    ScanTable(size_t size = 25) : ArrayTable(size){};
    //основные методы таблиц:
    virtual PDatValue FindRecord(const Key& key) override; //СДЕЛАТЬ САМИМ
    virtual void InsRecord(const Key& key, PDatValue value) override; //добавление записи в таблицу
    virtual void DelRecord(const Key& key) override;   
    //нужно ли override?
};