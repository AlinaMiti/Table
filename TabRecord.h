#pragma once
#include "DatValue.h"


using Key = std::string;

class TabRecord : public DatValue{
protected:
    PDatValue _data;
    Key _key;
public:
    TabRecord(Key key = "", PDatValue data = nullptr);
    void SetKey(Key key);
    Key GetKey() const;
    void SetData(PDatValue data);
    PDatValue GetData() const;

    virtual PDatValue GetCopy();
    TabRecord& operator=(const TabRecord& tr);

    virtual bool operator==(const TabRecord& tr) const; 
    virtual bool operator>(const TabRecord& tr) const; 
    virtual bool operator<(const TabRecord& tr) const; 

    friend class ScanTable;
    friend class ArrayTable;
    friend class SortTable;


};