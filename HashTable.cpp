#include "HashTable.h"
//саммая быстрая хэш функция в перемешивании  +балл
size_t HashTable::HashFunc(const Key& key){
    size_t index = 0;
    size_t size = key.size();
    for(size_t i = 0; i < size; i++){
        index += (size_t)key[i];
        //index = (index << 3) + key[i];

    }
    return index;
}