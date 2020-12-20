#pragma once
#include "Tree.h"
#include <iostream>

class AVLTreeNode : TreeNode{
public:
    UnitedVertexForm* get_united_form(){
        UnitedVertexForm* vertex = new UnitedVertexForm;
        vertex->color = 2;
        vertex->values = value;
        return vertex;
    };
    AVLTreeNode* left = nullptr;
    AVLTreeNode* right = nullptr;
    AVLTreeNode* parent = nullptr;
    int value;
    int height = 0;
    AVLTreeNode(int _value, int _height, AVLTreeNode* _left, AVLTreeNode* _right, AVLTreeNode* _prev);
};

class AVLTree : public Tree {
public:
    bool push(int value);
    void printTree();
    bool pop(int value);
    void clear();
    ~AVLTree() {};
    int cur_h = 0;
    UnitedVertexForm* get_unitedTree();
    UnitedVertexForm* _get_unitedTree(AVLTreeNode* next_node);
protected:
    void printHelper(AVLTreeNode* root, std::string indent, bool last);
    int height_of(AVLTreeNode* node);
    int diff_of(AVLTreeNode* node);
    void fix_height(AVLTreeNode* node);
    AVLTreeNode* min_way(AVLTreeNode* vertex);
    AVLTreeNode* replace_min(AVLTreeNode* vertex);
    AVLTreeNode* _insert(AVLTreeNode* root, int value);
    AVLTreeNode* _pop(AVLTreeNode* vertex, int value);
    AVLTreeNode* rotate_left(AVLTreeNode* vertex);
    AVLTreeNode* rotate_right(AVLTreeNode* vertex);
    AVLTreeNode* balance(AVLTreeNode* vertex);
    
    AVLTreeNode* _root = nullptr;
};

