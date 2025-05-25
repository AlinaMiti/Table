#pragma once
#include "ScanTable.h"

//3 вида сортировок/ 2 и 3 рекурсивные
enum SortMethod {Insert, Merge, Quick}; 


class SortTable : public ScanTable {
protected:
    SortMethod _sortMethod; 

    void SortData(); //запускает одну из сортировок
    void InsertSort(PTabRecord* pMem, size_t count);   //сортировка вставками

    void MergeSort(PTabRecord* pMem, size_t count);
    void MergeSorter(PTabRecord* &pData, PTabRecord* &pBuf, size_t count);
    void MergeData(PTabRecord* &pData, PTabRecord* &pBuf, size_t n1, size_t n2);

    void QuickSort(PTabRecord* pMem, size_t count);
    void QuickSplit(PTabRecord* pMem, size_t size, size_t& pivot);

public:
    SortTable(size_t tabSize = 25) : ScanTable(tabSize) {};
    SortTable(const ScanTable& st) {  //конструктор преобразования типов
        *this = st;
    }
    SortTable& operator=(const ScanTable& st); //оператор присваивания

    void SetSortMethod(SortMethod sortMethod){
        _sortMethod = sortMethod;
    }
    SortMethod GetSortMethod() const {
        return _sortMethod;
    }

    virtual PDatValue FindRecord(const Key& key); 
    virtual void InsRecord(const Key& key, PDatValue value); 
    virtual void DelRecord(const Key& key);  
};