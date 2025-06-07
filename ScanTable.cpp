#include "ScanTable.h"

PDatValue ScanTable::FindRecord(const Key& key){
    _efficientcy = 0;
    for(size_t i = 0; i < _dataCount; i++){
        _efficientcy++;
        if(_records[i]->GetKey() == key){
            _curPos = i;
            return _records[i]->GetData();
        }
    }
    _curPos = 0;
    return nullptr;
}

void ScanTable::InsRecord(const Key& key, PDatValue value){
    if(IsFull()){
        throw "Table is full";
    }

    if (FindRecord(key) != nullptr) {
        throw "Duplicate key found";
    }

    else{
        _records[_dataCount] = new TabRecord(key, value);  //нужно определить Принт из DatValue. И использовать уже другой класс
        _dataCount++;
    }

}

void ScanTable::DelRecord(const Key& key){
    PDatValue tmp = FindRecord(key);//поиск ключа
    if(tmp == nullptr){
        throw "This elem not found";
    }
    else{
        delete _records[_curPos];
        _records[_curPos] = _records[_dataCount-1];
        _records[_dataCount - 1] = nullptr;
        _dataCount--;
    }

}