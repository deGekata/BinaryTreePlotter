#include "AVLTree.h"

AVLTreeNode::AVLTreeNode(int _value, int _height = 1, AVLTreeNode* _left = nullptr, AVLTreeNode* _right = nullptr, AVLTreeNode* _parent = nullptr) {
    value = _value;
    height = _height;
    left = _left;
    right = _right;
    parent = _parent;
}

bool AVLTree::push(int value) {

    _root = _insert(_root, value);
    return false;
}

void AVLTree::printTree() {
    printHelper(this->_root, "", true);
}

UnitedVertexForm* AVLTree::get_unitedTree(){
    UnitedVertexForm* top_node = _get_unitedTree(_root);
    return top_node;
}

UnitedVertexForm*  AVLTree::_get_unitedTree(AVLTreeNode* next_node){
    if(next_node == nullptr) return nullptr;
    cur_h++;
    UnitedVertexForm* node = next_node->get_united_form();
    node->hei = cur_h;
    node->left = _get_unitedTree(next_node->left);
    node->right= _get_unitedTree(next_node->right);
    cur_h--;
    return node;
}


void AVLTree::printHelper(AVLTreeNode* root, std::string indent, bool last) {
    cur_h++;
    if (root != nullptr) {
        std::cout << indent;
        if (last) {
            std::cout << "R----";
            indent += "   ";
        }
        else {
            std::cout << "L----";
            indent += "|  ";
        }

        //std::string sColor = root-> ? "RED" : "BLACK";
        std::cout << root->value << "(" << cur_h << ")" << std::endl;
        printHelper(root->left, indent, false);
        printHelper(root->right, indent, true);
    }
        cur_h--;
}


bool AVLTree::pop(int value) {
    _root = _pop(_root, value);
    return false;
}

void AVLTree::clear() {
}

int AVLTree::height_of(AVLTreeNode* node) {
    return node == nullptr ? 0 : node->height;
}

int AVLTree::diff_of(AVLTreeNode* node) {
    return height_of(node->right) - height_of(node->left);
}

void AVLTree::fix_height(AVLTreeNode* node) {
    int l_h = height_of(node->left);
    int r_h = height_of(node->right);
    node->height = (l_h > r_h ? l_h : r_h) + 1;
    return;
}

AVLTreeNode* AVLTree::min_way(AVLTreeNode* vertex) {
    return vertex->left == nullptr ? vertex : min_way(vertex->left);
}

AVLTreeNode* AVLTree::replace_min(AVLTreeNode* vertex) {
    if (vertex->left == nullptr) {
        return vertex->right;
    }

    vertex->left = replace_min(vertex->left);
    return balance(vertex);
}



AVLTreeNode* AVLTree::_insert(AVLTreeNode* vert, int value) {
    if (vert == nullptr) {
        return new AVLTreeNode(value);
    }

    if (value < vert->value) {
        vert->left =  _insert(vert->left, value);
    } else {
        vert->right = _insert(vert->right, value);
    }

    return balance(vert);
    //return nullptr;
}

AVLTreeNode* AVLTree::_pop(AVLTreeNode* vertex, int value) {
    if (vertex == nullptr) {
        return nullptr;
    }

    if (value < vertex->value) {
        vertex->left = _pop(vertex->left, value);
    } else if (value > vertex->value) {
        vertex->right = _pop(vertex->right, value);
    } else {
        AVLTreeNode* left = vertex->left;
        AVLTreeNode* right = vertex->right;
        delete vertex;
        if (right == nullptr) return left;
        AVLTreeNode* min = min_way(right);
        min->right = replace_min(right);
        min->left = left;
        return balance(min);
    }
    
    return balance(vertex);
}

AVLTreeNode* AVLTree::rotate_left(AVLTreeNode* q) {
    AVLTreeNode* p = q->right;
    q->right = p->left;
    p->left = q;
    fix_height(q);
    fix_height(p);
    return p;
}

AVLTreeNode* AVLTree::rotate_right(AVLTreeNode* p) {
    AVLTreeNode* q = p->left;
    p->left = q->right;
    q->right= p;
    fix_height(p);
    fix_height(q);
    return q;
}

AVLTreeNode* AVLTree::balance(AVLTreeNode* vertex) {
    fix_height(vertex);

    if (diff_of(vertex) == 2) {
        if (diff_of(vertex->right) < 0) {
            vertex->right = rotate_right(vertex->right);
        }
        return rotate_left(vertex);
    }

    if (diff_of(vertex) == -2) {
        if (diff_of(vertex->left) > 0) {
            vertex->left = rotate_left(vertex->left);
        }
        return rotate_right(vertex);
    }
    
    return vertex;
}

