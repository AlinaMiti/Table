#include "HashTable.h"
//саммая быстрая хэш функция в перемешивании  +балл
size_t HashTable::HashFunc(const Key& key){
    _efficientcy++; // Учитываем операцию хеширования
    
    if (key.empty()) {
        return 0;
    }

    // Вычисление хеша (алгоритм djb2)
    size_t hash = 5381; // Начальное значение
    for (char c : key) {
        hash = ((hash << 5) + hash) + static_cast<unsigned char>(c); // hash * 33 + c
    }

    // Дополнительное перемешивание
    hash = (hash ^ (hash >> 16)) % _tabSize;
    // Возвращаем хеш в пределах размера таблицы
    return hash;
}