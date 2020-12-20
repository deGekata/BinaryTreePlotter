#pragma once
#include "Tree.h"
#include <string>
#include <iostream>

class BTreeNode : public TreeNode {
public:
    UnitedVertexForm* get_united_form(){ return nullptr;};
    int size;
    int keys[3];
    BTreeNode* left; 
    BTreeNode* midleft;
    BTreeNode* midright;
    BTreeNode* right;  
    BTreeNode* parent;

    BTreeNode(int k) : size(1), keys{ k, 0, 0 }, left(nullptr), midleft(nullptr),
        midright(nullptr), right(nullptr), parent(nullptr) {}

    BTreeNode(int k, BTreeNode* first_, BTreeNode* second_, BTreeNode* third_, BTreeNode* fourth_, BTreeNode* parent_) :
        size(1), keys{ k, 0, 0 }, left(first_), midleft(second_),
        midright(third_), right(fourth_), parent(parent_) {}
private:
    bool find(int k);
    void swap(int& x, int& y);
    void sort2(int& x, int& y);
    void sort();
    void insert_to_node(int k);
    bool is_leaf();
    void become_node2(int k, BTreeNode* first_, BTreeNode* second_);
    void remove_from_node(int k);
    void sort3(int& x, int& y, int& z);
    friend class BTree;

};

class BTree : public Tree {
public:
    bool push(int item);

    bool pop(int data);

    void clear() {};

    void printHelper(BTreeNode* root, std::string indent, int last);
    void printTree() {
        if (_root) {
            printHelper(this->_root, "", 0);
        }
    }
private:
    BTreeNode* insert(BTreeNode* p, int k);
    BTreeNode* split(BTreeNode* p);
    BTreeNode* search(BTreeNode* p, int item);
    BTreeNode* search_min(BTreeNode* p);
    BTreeNode* remove(BTreeNode* p, int k);
    BTreeNode* fix(BTreeNode* leaf);
    BTreeNode* redistribute(BTreeNode* leaf);
    BTreeNode* merge(BTreeNode* leaf);
    
    BTreeNode* _root = nullptr;
};

