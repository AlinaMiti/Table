#include "SortTable.h"

void SortTable::SortData(){
    if (_dataCount == 0) return;
    _efficientcy = 0;
    switch (_sortMethod)
    {
    case SortMethod::Insert:
        InsertSort(_records, _dataCount);
        break;
    case SortMethod::Merge:
        MergeSort(_records, _dataCount);
        break;
    case SortMethod::Quick:
        QuickSort(_records, _dataCount);
        break;
    default:
        throw std::runtime_error("Invalid sort method");
    }
}
void SortTable::InsertSort(PTabRecord* pMem, size_t count){
    PTabRecord tmp;
    _efficientcy = 0;
    for(int i = 1, j; i < _dataCount; i++){
        tmp = _records[i];
        for(j = i - 1; j > -1; j--){
            _efficientcy++;
            if (_records[j] -> _key > tmp->_key){
                _records[j+1] = _records[j];
                _efficientcy++;
            }
            else{
                break;
            }
        }
        _records[j+1] = tmp;
    }
    
}

void SortTable::MergeSort(PTabRecord* pMem, size_t count){  //алгоритм деления 
    PTabRecord* pData = _records;
    PTabRecord* pBuff = new PTabRecord[_dataCount]; //буфер для отсортированных элементов
    PTabRecord* pTmp = pBuff;
    _efficientcy = 0; 
    MergeSorter(pData, pBuff, _dataCount);
    if(pData == pTmp){
        for(size_t i = 0; i < _dataCount; i++){
            pBuff[i] = pData[i];
        }
    }
    delete pTmp;
}

void SortTable::MergeSorter(PTabRecord* &pData, PTabRecord* &pBuf, size_t count){
    size_t n1 = (count + 1)/2;
    size_t n2 = count - n1;
    if(count > 2){
        PTabRecord *pData2 = pData + n1;
        PTabRecord *pBuf2 = pBuf + n1;
        MergeSorter(pData, pBuf, n1);
        MergeSorter(pData2, pBuf2, n2);
    }
    MergeData(pData, pBuf, n1, n2);
}

void SortTable::MergeData(PTabRecord* &pData, PTabRecord* &pBuf, size_t n1, size_t n2){
    size_t i = 0, i1 = 0, i2 = 0;
    PTabRecord *pDat1 = pData, *pDat2 = pData + n1;
    while(i1 < n1 && i2 < n2){
        _efficientcy++;
        if(pDat1[i1] -> _key < pDat2[i2] -> _key){
            pBuf[i++] = pDat1[i1++];
            _efficientcy++;
        }
        else{
            pBuf[i++] = pDat2[i2++];
            _efficientcy++;
        }
    }

    while(i1 < n1) {
        pBuf[i++] = pDat1[i1++];
        _efficientcy++;
    }
    while(i2 < n2) {
        pBuf[i++] = pDat2[i2++];
        _efficientcy++;
    }
    pData = pBuf;
    pBuf = pDat1;
    //_efficientcy += n1 + n2; 
}

void SortTable::QuickSort(PTabRecord* pMem, size_t count){
    size_t pivot;
    size_t n1, n2;
    if(count > 1){
        QuickSplit(pMem, count, pivot);
        n1 = pivot + 1;
        n2 = count - n1;
        QuickSort(pMem, n1-1);
        QuickSort(pMem + n1, n2);
    }
}

void SortTable::QuickSplit(PTabRecord* pMem, size_t size, size_t& pivot){
    PTabRecord pPivot = pMem[0];
    PTabRecord pTmp;
    size_t i1 = 1, i2 = size - 1;
    while(i1 <= i2){
        while(i1 < size && !(pMem[i1] -> _key > pPivot->_key)){
            _efficientcy++;
            i1++;
        }
        while(pMem[i2]->_key > pPivot->_key){
            _efficientcy++;
            i2--;
        }
        if(i1 < i2){
            pTmp = pMem[i1];
            pMem[i1] = pMem[i2];
            pMem[i2] = pTmp;
            _efficientcy+=3;
        }
    } 
    
    pivot = i2;
    pMem[0] = pMem[i2];
    pMem[i2] = pPivot;
    _efficientcy += 2;
}

SortTable& SortTable::operator=(const ScanTable& st){
    std::cout << "pumPum" << std::endl;
    if(_records != nullptr){
        for(size_t i = 0; i < _dataCount; i++)
            delete _records[i];
        delete [] _records;
    }
    _tabSize = st._tabSize;
    _dataCount = st.GetDataCount();
    _records = new PTabRecord[_tabSize];
    for(size_t i = 0; i < _dataCount; i++){
        _records[i] = (PTabRecord)st._records[i]->GetCopy();
    }
    SortData();
    _curPos = 0;
    return *this;
}

PDatValue SortTable::FindRecord(const Key& key){
    _efficientcy = 0;
    size_t left = 0;
    size_t right = _dataCount;
    
    while (left < right) {
        _efficientcy++;
        size_t mid = left + (right - left) / 2;
        
        if (_records[mid]->GetKey() == key) {
            _curPos = mid;
            return _records[mid]->GetData();
        }
        else if (_records[mid]->GetKey() < key) {
            left = mid + 1;
        }
        else {
            right = mid;
        }
    }
    return nullptr;
}   //бинарный поиск   ДОМА СДЕЛАТЬ


void SortTable::InsRecord(const Key& key, PDatValue value){
    if (IsFull())
        throw "Table is full";
    _efficientcy = 0;    
    PDatValue tmp = FindRecord(key);
    //перепаковка:
    for(size_t i = _dataCount; i > _curPos; i--){
        _records[i] = _records[i-1];
        _efficientcy++;
    }
    _records[_curPos] = new TabRecord(key, value);
    _dataCount++;
    _curPos = 0;
}
void SortTable::DelRecord(const Key& key){
    if (IsEmpty())
        throw "Table is Empty";
    _efficientcy = 0;    
    PDatValue tmp = FindRecord(key);
    delete _records[_curPos];
    
    if (tmp != nullptr){
        for(size_t i = _curPos; i < _dataCount-1; i++){
            _records[i] = _records[i+1];
            _efficientcy++;
        }
        _records[_dataCount] = nullptr;
        _dataCount -= 1;
    }
    _curPos = 0;
}