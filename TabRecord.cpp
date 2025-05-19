#include "TabRecord.h"

TabRecord::TabRecord(Key key, PDatValue data): _key(key), _data(data){}

void TabRecord::SetKey(Key key){
    _key = key;
}
Key TabRecord::GetKey() const{
    return _key;
}
void TabRecord::SetData(PDatValue data){
    _data = data;
}
PDatValue TabRecord::GetData() const{
    return _data;
}
TabRecord& TabRecord::operator=(const TabRecord& tr){
    if(this != &tr){
        _key = tr._key;
        if(_data)
            delete _data;
        _data = tr._data ? tr._data->GetCopy() : nullptr;
    }
    
    return *this;
}

PDatValue TabRecord::GetCopy()  {
    if(_data){
        return new TabRecord(_key, _data->GetCopy());
    }
    return new TabRecord(_key, nullptr);  //указатель на новую копию
}

bool TabRecord::operator==(const TabRecord& tr) const{
    if(_key != tr._key) return false;
    if(_data == nullptr && tr._data == nullptr) return true;
    if(_data == nullptr || tr._data == nullptr) return false;
    return *_data == *tr._data;
}
bool TabRecord::operator>(const TabRecord& tr) const{
    return _key > tr._key;
} 
bool TabRecord::operator<(const TabRecord& tr) const{
    return _key < tr._key;
}