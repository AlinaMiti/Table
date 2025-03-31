#include "ScanTable.h"

PDatValue ScanTable::FindRecord(const Key& key){

}

void ScanTable::InsRecord(const Key& key, PDatValue value){
    if(IsFull()){
        throw "Table is full";
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
        _records[_curPos] = _records[_dataCount-1];
        _dataCount--;
    }
}