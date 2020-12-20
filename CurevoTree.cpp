#include "CurevoTree.h"

bool CurevoTree::push(int value) {
    //find
    if (find(value)) return false;
    uint32_t hei = engine();
    CurevoTreeNode* node = new CurevoTreeNode(value, hei);
    _root = insert(_root, node);
    return true;
}

void CurevoTree::printTree() {
    printHelper(this->_root, "", true);
}

bool CurevoTree::pop(int value) {
    if (!find(value)) return false;
    _remove(_root, value);
    return true;
}

bool CurevoTree::find(int value) {
    return _find(value) != nullptr;
}

CurevoTreeNode* CurevoTree::_find(int value) {
    CurevoTreeNode* cur_node = _root;
    while (cur_node != nullptr) {
        if (cur_node->_value == value) {
            return cur_node;
        }

        if (value > cur_node->_value) {
            cur_node = cur_node->right;
        } else {
            cur_node = cur_node->left;
        }
    }
    return cur_node;
}

void CurevoTree::_remove(CurevoTreeNode*& node, int item) {
    if (node->_value == item) {
        node = merge(node->left, node->right);
    }
    else {
        _remove(item < node->_value ? node->left : node->right, item);
    }
}

std::pair< CurevoTreeNode *, CurevoTreeNode *> CurevoTree::split(CurevoTreeNode* vertex, int item) {
    if (vertex == nullptr) {
        return { nullptr, nullptr };
    }
    if (vertex->_value < item) {
        auto merge_res = split(vertex->right, item);
        vertex->right = merge_res.first;
        return { vertex, merge_res.second };
    } else {
        auto merge_res = split(vertex->left, item);
        vertex->left = merge_res.second;
        return { merge_res.first, vertex};
    }
}

CurevoTreeNode* CurevoTree::merge(CurevoTreeNode* Lft, CurevoTreeNode* Rht) {
    if (Lft == nullptr) {
        return Rht;
    }
    if (Rht == nullptr) {
        return Lft;
    }

    if (Lft->_y > Rht->_y) {
        Lft->right = merge(Lft->right, Rht);
        return Lft;
    } else {
        Rht->left = merge(Lft, Rht->left);
        return Rht;
    }
}

CurevoTreeNode* CurevoTree::insert(CurevoTreeNode* vertex, CurevoTreeNode* item) {
    if (vertex == nullptr) {
        return item;
    }
    if (item->_y > vertex->_y) {
        auto split_res = split(vertex, item->_value);
        item->right = split_res.second;
        item->left = split_res.first;
        return item;
    }
    else {
        if (item->_value > vertex->_value) {
            vertex->right = insert(vertex->right, item);
        }
        else {
            vertex->left = insert(vertex->left, item);
        }
        return vertex;
    }
}

void CurevoTree::printHelper(CurevoTreeNode* root, std::string indent, bool last) {
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
        std::cout << root->_value << "(" << root->_y << ")" << std::endl;
        printHelper(root->left, indent, false);
        printHelper(root->right, indent, true);
    }
    cur_h--;
}


UnitedVertexForm* CurevoTree::get_unitedTree(){
    UnitedVertexForm* top_node = _get_unitedTree(_root);
    return top_node;
}

UnitedVertexForm*  CurevoTree::_get_unitedTree(CurevoTreeNode* next_node){
    if(next_node == nullptr) return nullptr;
    cur_h++;
    UnitedVertexForm* node = next_node->get_united_form();
    node->hei = cur_h;
    node->left = _get_unitedTree(next_node->left);
    node->right= _get_unitedTree(next_node->right);
    cur_h--;
    return node;
}

