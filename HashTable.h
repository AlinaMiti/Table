#pragma once
#include "Table.h"
//расчитывает индекс куда положить запись

class HashTable : public Table{
protected:
    //size_t _efficiency; 
    size_t _tabSize;
    virtual size_t HashFunc(const Key& key);
    size_t _collisions = 0;
public:
    
    HashTable(size_t size = 101): Table(), _tabSize(size) {}

    void ResetCollisions() { _collisions = 0; }
    size_t GetEfficiency() const { return _efficientcy; }
    void ResetEfficiency() { _efficientcy = 0; }
    size_t GetCollisionCount() const { return _collisions; }
    float GetLoadFactor() const {
        return static_cast<float>(_dataCount) / _tabSize;
    }

    size_t GetTabSize() const { 
        return _tabSize; 
    }
};