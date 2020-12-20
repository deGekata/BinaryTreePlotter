#include "RBTree.h"



//RBTreeNode::RBTreeNode() {
//    left = right = parent = nullptr;
//    value = 0;
//    color = BLACK;
//}

void RBTree::initializeNULLNode(RBTreeNode* node, RBTreeNode* parent) {
    node->value = 0;
    node->parent = parent;
    node->left = nullptr;
    node->right = nullptr;
    node->color = BLACK;
}

// Preorder
void RBTree::preOrderHelper(RBTreeNode* node) {
    if (node != TNULL) {
        std::cout << node->value << " ";
        preOrderHelper(node->left);
        preOrderHelper(node->right);
    }
}

// Inorder
void RBTree::inOrderHelper(RBTreeNode* node) {
    if (node != TNULL) {
        inOrderHelper(node->left);
        std::cout << node->value << " ";
        inOrderHelper(node->right);
    }
}

// Post order
void RBTree::postOrderHelper(RBTreeNode* node) {
    if (node != TNULL) {
        postOrderHelper(node->left);
        postOrderHelper(node->right);
        std::cout << node->value << " ";
    }
}

RBTreeNode* RBTree::searchTreeHelper(RBTreeNode* node, int key) {
    if (node == TNULL || key == node->value) {
        return node;
    }

    if (key < node->value) {
        return searchTreeHelper(node->left, key);
    }
    return searchTreeHelper(node->right, key);
}

// For balancing the tree after deletion
void RBTree::deleteFix(RBTreeNode* x) {
    RBTreeNode* s;

    while (x != _root && x->color == BLACK) {
        if (x == x->parent->left) {
            s = x->parent->right;
            if (s->color == RED) {
                s->color = BLACK;
                x->parent->color = RED;
                leftRotate(x->parent);
                s = x->parent->right;
            }

            if (s->left->color == BLACK && s->right->color == BLACK) {
                s->color = RED;
                x = x->parent;
            }
            else {
                if (s->right->color == BLACK) {
                    s->left->color = BLACK;
                    s->color = RED;
                    rightRotate(s);
                    s = x->parent->right;
                }

                s->color = x->parent->color;
                x->parent->color = BLACK;
                s->right->color = BLACK;
                leftRotate(x->parent);
                x = _root;
            }
        }
        else {
            s = x->parent->left;
            if (s->color == RED) {
                s->color = BLACK;
                x->parent->color = RED;
                rightRotate(x->parent);
                s = x->parent->left;
            }

            if (s->right->color == BLACK) {
                s->color = RED;
                x = x->parent;
            }
            else {
                if (s->left->color == BLACK) {
                    s->right->color = BLACK;
                    s->color = RED;
                    leftRotate(s);
                    s = x->parent->left;
                }

                s->color = x->parent->color;
                x->parent->color = BLACK;
                s->left->color = BLACK;
                rightRotate(x->parent);
                x = _root;
            }
        }
    }
    x->color = BLACK;
}

void RBTree::rbTransplant(RBTreeNode* u, RBTreeNode* v) {
    if (u->parent == nullptr) {
        _root = v;
    }
    else if (u == u->parent->left) {
        u->parent->left = v;
    }
    else {
        u->parent->right = v;
    }
    v->parent = u->parent;
}

void RBTree::deleteNodeHelper(RBTreeNode* node, int key) {
    RBTreeNode* z = TNULL;
    RBTreeNode* x;
    RBTreeNode* y;
    while (node != TNULL) {
        if (node->value == key) {
            z = node;
        }

        if (node->value <= key) {
            node = node->right;
        }
        else {
            node = node->left;
        }
    }

    if (z == TNULL) {
        std::cout << "Key not found in the tree" << std::endl;
        return;
    }

    y = z;
    int y_original_color = y->color;
    if (z->left == TNULL) {
        x = z->right;
        rbTransplant(z, z->right);
    }
    else if (z->right == TNULL) {
        x = z->left;
        rbTransplant(z, z->left);
    }
    else {
        y = minimum(z->right);
        y_original_color = y->color;
        x = y->right;
        if (y->parent == z) {
            x->parent = y;
        }
        else {
            rbTransplant(y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }

        rbTransplant(z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }
    delete z;
    if (y_original_color == BLACK) {
        deleteFix(x);
    }
}

// For balancing the tree after insertion
void RBTree::insertFix(RBTreeNode* k) {
    RBTreeNode* u;
    while (k->parent->color == RED) {
        if (k->parent == k->parent->parent->right) {
            u = k->parent->parent->left;
            if (u->color == RED) {
                u->color = BLACK;
                k->parent->color = BLACK;
                k->parent->parent->color = RED;
                k = k->parent->parent;
            }
            else {
                if (k == k->parent->left) {
                    k = k->parent;
                    rightRotate(k);
                }
                k->parent->color = BLACK;
                k->parent->parent->color = RED;
                leftRotate(k->parent->parent);
            }
        }
        else {
            u = k->parent->parent->right;

            if (u->color == RED) {
                u->color = BLACK;
                k->parent->color = BLACK;
                k->parent->parent->color = RED;
                k = k->parent->parent;
            }
            else {
                if (k == k->parent->right) {
                    k = k->parent;
                    leftRotate(k);
                }
                k->parent->color = BLACK;
                k->parent->parent->color = RED;
                rightRotate(k->parent->parent);
            }
        }
        if (k == _root) {
            break;
        }
    }
    _root->color = BLACK;
}

void RBTree::printHelper(RBTreeNode* root, std::string indent, bool last) {
    if (root != TNULL) {
        std::cout << indent;
        if (last) {
            std::cout << "R----";
            indent += "   ";
        } else {
            std::cout << "L----";
            indent += "|  ";
        }

        std::string sColor = root->color ? "RED" : "BLACK";
        std::cout << root->value << "(" << sColor << ")" << std::endl;
        printHelper(root->left, indent, false);
        printHelper(root->right, indent, true);
    }
}

RBTree::RBTree() {
        TNULL = new RBTreeNode;
        TNULL->color = BLACK;
        TNULL->left = nullptr;
        TNULL->right = nullptr;
        _root = TNULL;
}

void RBTree::preorder() {
        preOrderHelper(this->_root);
    }

void RBTree::inorder() {
        inOrderHelper(this->_root);
    }

void RBTree::postorder() {
        postOrderHelper(this->_root);
    }

RBTreeNode* RBTree::searchTree(int k) {
        return searchTreeHelper(this->_root, k);
    }

RBTreeNode* RBTree::minimum(RBTreeNode* node) {
        while (node->left != TNULL) {
            node = node->left;
        }
        return node;
    }

RBTreeNode* RBTree::maximum(RBTreeNode* node) {
        while (node->right != TNULL) {
            node = node->right;
        }
        return node;
    }

RBTreeNode* RBTree::successor(RBTreeNode* x) {
        if (x->right != TNULL) {
            return minimum(x->right);
        }

        RBTreeNode* y = x->parent;
        while (y != TNULL && x == y->right) {
            x = y;
            y = y->parent;
        }
        return y;
    }

RBTreeNode* RBTree::predecessor(RBTreeNode* x) {
        if (x->left != TNULL) {
            return maximum(x->left);
        }

        RBTreeNode* y = x->parent;
        while (y != TNULL && x == y->left) {
            x = y;
            y = y->parent;
        }

        return y;
    }

void RBTree::leftRotate(RBTreeNode* x) {
        RBTreeNode* y = x->right;
        x->right = y->left;
        if (y->left != TNULL) {
            y->left->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nullptr) {
            this->_root = y;
        }
        else if (x == x->parent->left) {
            x->parent->left = y;
        }
        else {
            x->parent->right = y;
        }
        y->left = x;
        x->parent = y;
    }

void RBTree::rightRotate(RBTreeNode* x) {
        RBTreeNode* y = x->left;
        x->left = y->right;
        if (y->right != TNULL) {
            y->right->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nullptr) {
            this->_root = y;
        }
        else if (x == x->parent->right) {
            x->parent->right = y;
        }
        else {
            x->parent->left = y;
        }
        y->right = x;
        x->parent = y;
    }

    // Inserting a node
bool RBTree::push(int key) {
        RBTreeNode* node = new RBTreeNode;
        node->parent = nullptr;
        node->value = key;
        node->left = TNULL;
        node->right = TNULL;
        node->color = RED;

        RBTreeNode* y = nullptr;
        RBTreeNode* x = this->_root;

        while (x != TNULL) {
            y = x;
            if (node->value < x->value) {
                x = x->left;
            }
            else {
                x = x->right;
            }
        }

        node->parent = y;
        if (y == nullptr) {
            _root = node;
        }
        else if (node->value < y->value) {
            y->left = node;
        }
        else {
            y->right = node;
        }

        if (node->parent == nullptr) {
            node->color = BLACK;
            return false;
        }

        if (node->parent->parent == nullptr) {
            return false;
        }

        insertFix(node);
        return false;
    }

RBTreeNode* RBTree::getRoot() {
        return this->_root;
    }

bool RBTree::pop(int data) {
    deleteNodeHelper(this->_root, data);
    return false;
}

void RBTree::printTree() {
        if (_root) {
            printHelper(this->_root, "", true);
        }
}



UnitedVertexForm* RBTree::get_unitedTree(){
    UnitedVertexForm* top_node = _get_unitedTree(_root);
    return top_node;
}

UnitedVertexForm*  RBTree::_get_unitedTree(RBTreeNode* next_node){
    if(next_node == nullptr || next_node == TNULL) return nullptr;
    cur_h++;
    UnitedVertexForm* node = next_node->get_united_form();
    node->hei = cur_h;
    node->left = _get_unitedTree(next_node->left);
    node->right= _get_unitedTree(next_node->right);
    cur_h--;
    return node;
}
