#include "ListHashTable.h"

ListHashTable::ListHashTable(size_t tabSize){
    _lists = new std::list<PTabRecord>[tabSize];
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

bool ListHashTable::IsFull(){
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
    _curPos = 0;
    _curElem = _lists[_curList].begin(); //итератор на начало
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

void ListHashTable::InsRecord(const Key& key, PDatValue value){
    if(IsFull()){
        throw "No Memory";
    }
    PDatValue tmp = FindRecord(key);
    if(tmp != nullptr){
        throw "Duplication";
    }
    _lists[_curList].push_front(new TabRecord(key, value));
    _dataCount++;
}

void ListHashTable::DelRecord(const Key& key){
    PDatValue tmp = FindRecord(key);
    if(tmp == nullptr){
        throw "No record";
    }
    _dataCount--;
    _lists[_curList].erase(_curElem);  
}
