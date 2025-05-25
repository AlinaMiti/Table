#include "ArrayTable.h"

Key ArrayTable::GetKey(DataPos position) const{
    if(!IsEmpty()){
        switch (position)
        {
        case First:
            return _records[0]->_key;
        case Current:
            return _records[_curPos]->_key;
        case Last:
            return _records[_dataCount-1]->_key;
        default:
            break;
        }
    }
    return "";
}

PDatValue ArrayTable::GetValuePtr(DataPos position) const{
    if(!IsEmpty()){
        switch (position)
        {
        case First:
            return _records[0]->_data;
        case Current:
            return _records[_curPos]->_data;
        case Last:
            return _records[_dataCount-1]->_data;
        default:
            break;
        }
    }
    return nullptr;
}

bool ArrayTable::Reset(){
    _curPos = 0;
    return IsTabEnded();
}

bool ArrayTable::IsTabEnded() const{
    return _curPos >= _dataCount;
}

bool ArrayTable::GoNext(){
    if(!IsTabEnded()){
        _curPos++;
    }
    return IsTabEnded();
}

bool ArrayTable::SetCurrentPos(size_t pos){
    _curPos = (pos < _dataCount) ? pos : 0;
    return IsTabEnded();
}

//
PDatValue ArrayTable::FindRecord(const Key& key) {
    _efficientcy = 0;
    for(size_t i = 0; i < _dataCount; i++) {
        _efficientcy++;
        if(_records[i]->GetKey() == key) {
            _curPos = i;
            return _records[i]->GetData();
        }
    }
    return nullptr;
}

void ArrayTable::InsRecord(const Key& key, PDatValue value) {
    if(IsFull()) {
        throw "Table is full";
    }
    if(FindRecord(key) != nullptr) {
        throw "Duplicate key";
    }
    _records[_dataCount++] = new TabRecord(key, value);
}

void ArrayTable::DelRecord(const Key& key) {
    if(FindRecord(key) == nullptr) {
        throw "Record not found";
    }
    
    delete _records[_curPos];
    
    for(size_t i = _curPos; i < _dataCount - 1; i++) {
        _records[i] = _records[i+1];
    }
    _records[--_dataCount] = nullptr;
}
//