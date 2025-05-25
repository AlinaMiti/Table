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

//
void TreeTable::DeleteTreeTable(PTreeNode pNode) {
    if (pNode != nullptr) {
        DeleteTreeTable(pNode->GetLeft());
        DeleteTreeTable(pNode->GetRight());
        
        delete pNode;
    }
}