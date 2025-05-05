#include "ListHashTable.h"

ListHashTable::ListHashTable(size_t tabSize){
    _lists = new std::forward_list<PTabRecord>[tabSize];
    _tabSize = tabSize;
    _curList = 0;
}

ListHashTable::~ListHashTable(){
    for(size_t i = 0; i < _tabSize; i++){   //перепроверить
        for(auto rec: _lists[i]){
            delete rec;
        }
    }
    delete [] _lists;
}