#include "HashTable.h"
#include "ArrayTable.h"

class ArrayHash : public HashTable{
protected:
    size_t _tabSize; 
    size_t _curPos; 
    PTabRecord* _records;
    size_t _freePos;
    size_t _hashStep; //хранение шага для проходки по таблицам(счетчик сдвига)
    PTabRecord _mark; //пометка
    size_t GetNextPos(size_t pos){ //переход на слдщ элемент если прошлый занят
        return (pos + _hashStep) % _tabSize;
    }
public:
    ArrayHash(size_t size = 100, size_t hashStep = 7);
    ~ArrayHash();

    bool IsFull();
    PDatValue FindRecord(Key key);
    void InsRecord(const Key& key, PDatValue value) override;
    void DelRecord(const Key& key) override;

    //Навигация
    
    bool Reset() override;  
    bool IsTabEnded() const override;
    bool GoNext() override;
    
    Key GetKey() const override;
    PDatValue GetValue() const override;
};