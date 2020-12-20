#pragma once
#include <queue>
#include <QDebug>
class UnitedVertexForm{
public:
    int values = -1;
//    int value_cnt;
    UnitedVertexForm* left = nullptr;
    UnitedVertexForm* right = nullptr;
//    int refs_cnt;
//    int* refs_sizes;
    int color = 0;
    int my_size = 3, leftsize = 0, rightsize = 0;
    int hei = 0;
    void print(){
        qDebug() << "{value: " << values<<  " | color: " << color << " | hei: "
                  << hei << " | mysize: " << my_size << " | leftsize: " << leftsize << " | rightsize: " << rightsize << "}";
    }
    static void prUniTree(UnitedVertexForm* vertex){
        if(vertex != nullptr){
            vertex->print();
            prUniTree(vertex->left);
            prUniTree(vertex->right);
        }
        return;
    }
    static int calc_size(UnitedVertexForm* vertex){
        if(vertex == nullptr){
            return 0;
        }
        vertex->leftsize = calc_size(vertex->left);
        vertex->rightsize = calc_size(vertex->right);
        if(vertex->right == nullptr){
            vertex->rightsize = -1;
        }
        if(vertex->left == nullptr){
            vertex->leftsize = -1;
        }
        int sum_size = vertex->leftsize + vertex->rightsize + 3;
        vertex->my_size = sum_size;
        return sum_size;

    }

};



class TreeNode {
public:
    virtual UnitedVertexForm* get_united_form() = 0;
};

class Tree {
public:
    virtual bool push(int item) = 0;
    virtual bool pop(int item) = 0;
    virtual void clear() = 0;
    //virtual bool find(int item) = 0;
    //virtual TreeNode* head() = 0;
    //virtual ~Tree() {};
   
};

