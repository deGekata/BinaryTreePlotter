#pragma once
#include "Tree.h"
#include <utility>
#include <random>
#include <time.h>
#include <iostream>
class CurevoTreeNode : public TreeNode {
public:
    UnitedVertexForm* get_united_form(){
        UnitedVertexForm* vertex = new UnitedVertexForm;
        vertex->color = 3;
        vertex->values = _value;
        return vertex;
    };
    CurevoTreeNode* left = nullptr;
    CurevoTreeNode* right = nullptr;
    int32_t _value;
    uint32_t _y;
    CurevoTreeNode() {};
    //CurevoTreeNode(int value) : _value(value), _y(y) {};
    CurevoTreeNode(int value, int y) : _value(value), _y(y) {};
};


class CurevoTree : public Tree {
public:
    bool push(int value);
    void printTree();
    bool pop(int value);
    bool find(int value);
    void clear() {};
    UnitedVertexForm* get_unitedTree();
    UnitedVertexForm* _get_unitedTree(CurevoTreeNode* next_node);
protected:
    CurevoTreeNode* _find(int value);
    void _remove(CurevoTreeNode*& node, int item);
    std::pair< CurevoTreeNode*, CurevoTreeNode*> split(CurevoTreeNode* vertex, int item);
    CurevoTreeNode* merge(CurevoTreeNode* Lft, CurevoTreeNode* Rht);
    CurevoTreeNode* insert(CurevoTreeNode* vertex, CurevoTreeNode* item);
    void printHelper(CurevoTreeNode* root, std::string indent, bool last);
    int cur_h = 0;

    std::random_device rd{};    
    std::mt19937 engine{rd()};
    CurevoTreeNode* _root = nullptr;
};



