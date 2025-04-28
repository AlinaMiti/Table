#include "ArrayHash.h"


ArrayHash::ArrayHash(size_t size = 100, size_t hashStep = 7) : HashTable(), _tabSize(size), _hashStep(hashStep){
    _records = new PTabRecord[_tabSize];
    for(size_t i = 0; i < _tabSize; i++){
        _records[i] = nullptr;
    }
    _mark = new TabRecord("", nullptr);
}
ArrayHash::~ArrayHash(){
    for(size_t i = 0; i < _tabSize; i++){
        if(_records[i] != nullptr)
            delete _records[i];
    }
    delete [] _records;
    delete _mark;
}

bool ArrayHash::IsFull(){
    return _dataCount >= _tabSize;
}
PDatValue ArrayHash::FindRecord(Key key){}
void ArrayHash::InsRecord(const Key& key, PDatValue value){}
void ArrayHash::DelRecord(const Key& key) {}


bool ArrayHash::Reset() {}  
bool ArrayHash::IsTabEnded()const {}
bool ArrayHash::GoNext() {}
    
Key ArrayHash::GetKey()const {}
PDatValue ArrayHash::GetValue()const {}

    