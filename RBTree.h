#pragma once
#include "Tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <iostream>



/* Red-Black tree description */
typedef enum { BLACK, RED } nodeColor;


class RBTreeNode : TreeNode{
public:
    UnitedVertexForm* get_united_form(){
        UnitedVertexForm* vertex = new UnitedVertexForm;
        vertex->color = color;
        vertex->values = value;
        return vertex;
    };
    RBTreeNode* left;
    RBTreeNode* right;
    RBTreeNode* parent;
    nodeColor color;        
    int value;
} ;


class RBTree : Tree {
private:
    RBTreeNode* _root;
    RBTreeNode* TNULL;

    void initializeNULLNode(RBTreeNode* node, RBTreeNode* parent);


    void preOrderHelper(RBTreeNode* node);


    void inOrderHelper(RBTreeNode* node);


    void postOrderHelper(RBTreeNode* node);

    RBTreeNode* searchTreeHelper(RBTreeNode* node, int key);


    void deleteFix(RBTreeNode* x);

    void rbTransplant(RBTreeNode* u, RBTreeNode* v);

    void deleteNodeHelper(RBTreeNode* node, int key);


    void insertFix(RBTreeNode* k);

    void printHelper(RBTreeNode* _root, std::string indent, bool last);

    RBTreeNode* getRoot();

    void preorder();

    void inorder();

    void postorder();

    RBTreeNode* searchTree(int k);

    RBTreeNode* minimum(RBTreeNode* node);

    RBTreeNode* maximum(RBTreeNode* node);

    RBTreeNode* successor(RBTreeNode* x);

    RBTreeNode* predecessor(RBTreeNode* x);

    void leftRotate(RBTreeNode* x);

    void rightRotate(RBTreeNode* x);
    int cur_h = 0;
public:
    UnitedVertexForm* get_unitedTree();
    UnitedVertexForm* _get_unitedTree(RBTreeNode* next_node);
    RBTree();

    bool push(int key);

    bool pop(int data);

    void clear() {};

    void printTree();
};





