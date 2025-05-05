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

PDatValue ArrayHash::FindRecord(Key key){
    _efficientcy = 0;
    _freePos = -1;
    PDatValue PVal = nullptr;
    _curPos = HashFunc(key)%_tabSize;
    for(size_t i = 0; i < _tabSize; i++){
        _efficientcy++;
        if(_records[_curPos] == nullptr)
            break;
        else{
            if(_records[_curPos] == _mark){
                if(_freePos == -1){
                    _freePos = _curPos;
                }
            }
            else{
                if(_records[_curPos]->GetKey() == key){
                    PVal = _records[_curPos]->GetData();
                    break;
                }
            }
            _curPos = GetNextPos(_curPos);
        }
    }
    return PVal;
}

void ArrayHash::InsRecord(const Key& key, PDatValue value){
    if(IsFull()) throw "Table is full";
    
    PDatValue PVal = FindRecord(key); 
    if(PVal != nullptr) throw "Dublicate";
    if(_freePos != -1) 
        _curPos = _freePos;
    _records[_curPos] = new TabRecord(key, value);
    _dataCount++;
    
}

void ArrayHash::DelRecord(const Key& key) {
    PDatValue PVal = FindRecord(key);
    if(PVal == nullptr) throw "Record not found";
    delete _records[_curPos];
    _records[_curPos] = _mark;
    _dataCount--;
}


bool ArrayHash::Reset() {
    _curPos = 0;
    while(_curPos < _tabSize){
        if(_records[_curPos] != nullptr && _records[_curPos] != _mark){
            break;
        }
        _curPos++;
    }
    return IsTabEnded();
}  

bool ArrayHash::IsTabEnded()const {
    return _curPos >= _tabSize;  //??проверить эту функцию
}

bool ArrayHash::GoNext() {
    if(!IsTabEnded()){
        while(_curPos < _tabSize){
            if(_records[_curPos] != nullptr && _records[_curPos] != _mark) break;
            _curPos++;
        }
    }
    return IsTabEnded();
}
    
Key ArrayHash::GetKey()const {
    return (_curPos >= _tabSize) ? "" : _records[_curPos]->GetKey();
}

PDatValue ArrayHash::GetValue()const {
    return (_curPos >= _tabSize) ? nullptr : _records[_curPos]->GetData();
}

    