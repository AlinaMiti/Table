#include "TreeTable.h"

PDatValue TreeTable::FindRecord(const Key &key){
    PTreeNode pNode = _pRoot;
    _ppRef = &pNode;
    _efficientcy = 0;
    while(pNode != nullptr){
        _efficientcy++;
        if(pNode->_key == key)
            break;
        if(pNode->_key < key)
            _ppRef = &(pNode->_pRight);
        else _ppRef = &(pNode->_pLeft);
        pNode = *_ppRef; 
    }
    return pNode == nullptr ? nullptr : pNode->_data;
}

void TreeTable::InsRecord(const Key& key, PDatValue value){
    if(IsFull())
        throw "Tree is Full";
    if(FindRecord(key) != nullptr)
        throw "Dublicate";
    _dataCount++;
    *_ppRef = new TreeNode(key, value);
}

Key TreeTable::GetKey() const{
    if(_pCur == nullptr)
        return "";
    return _pCur->_key;
} 

PDatValue TreeTable::GetValue() const{
    if(_pCur == nullptr)
        return nullptr;
    return _pCur->_data;
}

void TreeTable::DelRecord(const Key& key){
    if(FindRecord(key) == nullptr)
        throw "No elewment in Tree";
    PTreeNode pNode = *_ppRef;
    if(pNode->_pRight == nullptr){
        *_ppRef = pNode->_pLeft;
    }
    else{
        if(pNode->_pLeft == nullptr)
            *_ppRef = pNode->_pRight;
        else{                          //у элемента 2 потомка и слева и справа
            PTreeNode pN = pNode->_pLeft;
            PTreeNode* ppR = &pNode->_pLeft;
            while(pN->_pRight){
                ppR = &pN->_pRight;
                pN = *ppR;
            }
            pNode->_data = pN->_data;
            pNode->_key = pN->_key;
            pNode = pN;
            *ppR = pN->_pLeft;
        }
    }
    delete pNode;
}

void TreeTable::DeleteTreeTable(PTreeNode pNode) {
    if (pNode != nullptr) {
        DeleteTreeTable(pNode->GetLeft());
        DeleteTreeTable(pNode->GetRight());
        
        delete pNode;
    }
}

bool TreeTable::Reset(){
    PTreeNode pNode = _pCur = _pRoot;
    while(!_stack.empty()){
        _stack.pop();
    }
    _curPos = 0;
    while (pNode != nullptr){
        _stack.push(pNode);
        _pCur = pNode;
        pNode = pNode->GetLeft();
    }
    return IsTabEnded();
}  

bool TreeTable::IsTabEnded() const{
    return _curPos >= _dataCount;
} 

bool TreeTable::GoNext(){
    if(!IsTabEnded() && _pCur != nullptr){
        _pCur = _pCur -> GetRight();
        PTreeNode pNode = _pCur;
        _stack.pop();
        while(pNode != nullptr){
            _stack.push(pNode);
            _pCur = pNode;
            pNode = pNode->GetLeft();
        }
        if(_pCur == nullptr && _stack.empty()){
            _pCur = _stack.top();
        }
        _curPos++;
    }
    return IsTabEnded();
}

void TreeTable::PrintTreeTable(std::ostream &os, PTreeNode pNode){
    if(pNode != nullptr){
        PrintTreeTable(os, pNode->GetLeft());
        pNode->Print(os);
        std::cout << std::endl;
        PrintTreeTable(os, pNode->GetRight());
    }
}

void TreeTable::DrawTreeTable(PTreeNode pNode, size_t lvl){
    if(pNode != nullptr){
        DrawTreeTable(pNode->GetRight(), lvl + 1);
        for(size_t i = 0; i < 2*lvl;i++){
            std::cout << " ";
        }
        pNode -> Print(std::cout);
        std::cout << std::endl;
        DrawTreeTable(pNode->GetLeft(), lvl + 1);
    }
}

void TreeTable::PutValues(PTreeNode pNode, size_t lvl){
    if(pNode != nullptr && pos < 20){ //нам надо сделать больше 20 самостоятельно
        PutValues(pNode ->GetLeft(), lvl+1);
        _k[pos] = pNode->GetKey();
        _t[pos] = lvl;
        pos++;
        PutValues(pNode ->GetRight(), lvl+1);
    }
}

void TreeTable::Draw(){
    std::cout << "Tree " << std::endl;
    DrawTreeTable(_pRoot, 0);
}

void TreeTable::Show() {
    size_t maxl = 0, i, j, k, pn;
    pos = 0;
    PutValues(_pRoot, 0);
    for(i = 0; i < pos; i++){
        if(maxl < _t[i]){
            maxl = _t[i];
        }
    }
    std::cout << "Tree table visualisation" << std::endl;
    for(i = 0; i < maxl + 1; i++){
        pn = 0;
        for(j = 0; j < pos; j++){
            if(i == _t[j]){
                for(k = 0; k < 2*(j - pn); k++){
                    std::cout << " "; 
                }
                std::cout << _k[j];
                pn = j + 1;
            }
        }
        std::cout << std::endl;
    }
}