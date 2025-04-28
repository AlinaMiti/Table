#include "Table.h"
//расчитывает индекс куда положить запись

class HashTable : public Table{
protected:
    virtual size_t HashFunc(const Key& key);
public:
    HashTable(): Table() {

    }
};