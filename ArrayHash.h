#include "HashTable.h"
#include "ArrayTable.h"

class ArrayHash : public HashTable{
protected:
    size_t _tabSize; 
    size_t _curPos; 
    PTabRecord* _records;
    int _freePos;  //первое пустое место где можно поставить элемент
    size_t _hashStep; //хранение шага для проходки по таблицам(счетчик сдвига)
    PTabRecord _mark; //пометка (удаленные ранее элементы)
    size_t GetNextPos(size_t pos){ //переход на слдщ элемент если прошлый занят
        return (pos + _hashStep) % _tabSize;
    }
public:
    ArrayHash(size_t size = 100, size_t hashStep = 7);
    ~ArrayHash();

    bool IsFull();
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