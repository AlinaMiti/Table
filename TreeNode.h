#include "TabRecord.h"

using PTreeNode = TreeNode*;

class TreeNode : public TabRecord{
protected:
    PTreeNode _pLeft;
    PTreeNode _pRight;
public:
    TreeNode(Key key = "", PDatValue data = nullptr, PTreeNode pLeft = nullptr, PTreeNode pRight = nullptr) 
    : TabRecord(key, data){
        _pLeft = pLeft;
        _pRight = pRight;
    }

    PTreeNode GetLeft() const {
        return _pLeft;
    }
    PTreeNode GetRight() const {
        return _pRight;
    }

    virtual PDatValue GetCopy(){
        PTreeNode copeTree = new TreeNode(_key, _data);
        return copeTree;
    }

    friend class TreeTable;
    friend class BalencedTreeTable;
};