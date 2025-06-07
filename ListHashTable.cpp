#include "ListHashTable.h"

ListHashTable::ListHashTable(size_t tabSize): HashTable(tabSize){
    _lists = new std::list<PTabRecord>[tabSize];
    //_curList = 0;
}

ListHashTable::~ListHashTable(){
    for(size_t i = 0; i < _tabSize; i++){   //перепроверить
        for(auto& rec: _lists[i]){
            delete rec;
        }
    }
    delete [] _lists;
}



bool ListHashTable::IsFull() const{
    bool Res = false;
    try{
        TabRecord* a = new TabRecord();
        delete a;
    }
    catch (const char*){Res = true;}
    return Res;
}

bool ListHashTable::Reset(){
    _curList = 0;
    while (_curList < _tabSize && _lists[_curList].empty()) {
        _curList++;
    }
    if (_curList < _tabSize) {
        _curElem = _lists[_curList].begin(); //итератор на начало
    }
    return IsTabEnded();
}

bool ListHashTable::IsTabEnded()const {
    return _curList >= _tabSize;
}

bool ListHashTable::GoNext(){
    if(!IsTabEnded()){
        bool flag = false;
        while(_lists[_curList].empty()){
            flag = true;
            _curList++;
            _curElem = _lists[_curList].begin();
        }
        if(!flag) _curElem++;

        if(_curElem == _lists[_curList].end()){
            _curList++;
            _curElem = _lists[_curList].begin();
        }
    }
    return IsTabEnded();
}

Key ListHashTable::GetKey() const{
    if(IsTabEnded()) return "";
    return (*_curElem)->GetKey();
}

PDatValue ListHashTable::GetValue() const{
    if(IsTabEnded()) return nullptr;
    return (*_curElem)->GetData();
}

// void ListHashTable::InsRecord(const Key& key, PDatValue value, bool allowDuplicates) {
//         if (IsFull()) throw std::runtime_error("Table is full");
        
//         size_t hash = HashFunc(key);
        
//         if (!allowDuplicates) {
//             for (const auto& rec : _lists[hash]) {
//                 if (rec->GetKey() == key) {
//                     throw std::runtime_error("Duplicate key: " + key);
//                 }
//             }
//         }
        
//         _lists[hash].push_front(new TabRecord(key, value));
//         _dataCount++;
        
//         if (!_lists[hash].empty()) {
//             _collisions++;
//         }
//     }

void ListHashTable::InsRecord(const Key& key, PDatValue value){
    if(IsFull()){
        throw "No Memory";
    }
    // PDatValue tmp = FindRecord(key);
    // if(tmp != nullptr){
    //     throw "Duplication";
    // }
    if (key.empty()) {
        throw std::invalid_argument("Key cannot be empty");
    }
    
    if (value == nullptr) {
        throw std::invalid_argument("Value cannot be null");
    }

    size_t hash = HashFunc(key);

    for (const auto& rec : _lists[hash]) {
        _efficientcy++;
        if (rec->GetKey() == key) {
            throw "Duplication";
        }
    }
    
    if (!_lists[hash].empty()) {
        _collisions++;
    }
    
    _lists[hash].push_front(new TabRecord(key, value));
    _dataCount++;
}

void ListHashTable::DelRecord(const Key& key){
    ResetEfficiency();
    size_t hash = HashFunc(key);

    for (auto it = _lists[hash].begin(); it != _lists[hash].end(); ++it) {
        _efficientcy++; 
        if ((*it)->GetKey() == key) {
            delete *it;
            _lists[hash].erase(it);
            //_efficiency++; 
            _dataCount--;
            //Reset(); // Сброс итератора после удаления
            return;
        }
    }
    throw "Key not found";
}


//
PDatValue ListHashTable::FindRecord(const Key& key) {
    ResetEfficiency();
    size_t hashIndex = HashFunc(key);
    //size_t hashIndex = HashFunc(key) % _tabSize;
    
    for (auto it = _lists[hashIndex].begin(); it != _lists[hashIndex].end(); ++it) {
        _efficientcy++;
        if ((*it)->GetKey() == key) {
            _curList = hashIndex;
            _curElem = it;
            return (*it)->GetData();
        }
    }
    
    return nullptr;
}
//