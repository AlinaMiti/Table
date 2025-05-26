#pragma once
#include "Table.h"
#include "TreeNode.h"
#include <stack>
#include <string>


class TreeTable : public Table{
protected:
    PTreeNode _pRoot;  //вершина дерева
    PTreeNode _pCur;  //
    PTreeNode *_ppRef;    //адрес указателя на вершину дерева
    std::stack<PTreeNode> _stack; 
    //std::stack<PTreeNode> _stack = ;
    size_t _curPos;   //текущая позиция в дереве
    void PrintTreeTable(std::ostream &os, PTreeNode pNode);
    void DrawTreeTable(PTreeNode pNode, size_t lvl); //печать таблицы с ярусами, типа граф
    void DeleteTreeTable(PTreeNode pNode);
    //поля для отрисовки
    std::string _k[20];
    size_t _t[20];
    size_t pos;
    void PutValues(PTreeNode pNode, size_t t);
public:
    TreeTable() : Table(){
        _pRoot = nullptr;
        _pCur = nullptr;
        _ppRef = nullptr;
        _curPos = 0;
    };
    ~TreeTable(){
        DeleteTreeTable(_pRoot);
    }

    bool IsFull() const{
        try{
            PTreeNode a = new TreeNode();
        }
        catch(const char*){
            return true;
        }
        return false;
    }

    PDatValue FindRecord(const Key& key) override;
    void InsRecord(const Key& key, PDatValue value) override; 
    void DelRecord(const Key& key) override;
    
    bool Reset() override;  //сброс текущего положения на начало
    bool IsTabEnded() const override;  //дошли ли до последней записи
    bool GoNext() override;  //переместиться на следщ запись

    Key GetKey() const override;   //значение для текущей записи
    PDatValue GetValue() const override; 

    void Draw();
    void Show();

    friend std::ostream& operator <<(std::ostream &os, TreeTable &table){
        std::cout << "Print table" << std::endl;
        table.PrintTreeTable(os, table._pRoot);
        return os;
    }

};