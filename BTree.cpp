#include "BTree.h"


bool BTreeNode::find(int k) {
    for (int i = 0; i < size; ++i)
        if (keys[i] == k) return true;
    return false;
}

void BTreeNode::swap(int& x, int& y) {
    int r = x;
    x = y;
    y = r;
}

void BTreeNode::sort2(int& x, int& y) {
    if (x > y) swap(x, y);
}

void BTreeNode::sort3(int& x, int& y, int& z) {
    if (x > y) swap(x, y);
    if (x > z) swap(x, z);
    if (y > z) swap(y, z);
}


void BTreeNode::sort() {
    if (size == 1) return;
    if (size == 2) sort2(keys[0], keys[1]);
    if (size == 3) sort3(keys[0], keys[1], keys[2]);
}

void BTreeNode::insert_to_node(int k) {
    keys[size] = k;
    size++;
    sort();
}

void BTreeNode::remove_from_node(int k) { 
    if (size >= 1 && keys[0] == k) {
        keys[0] = keys[1];
        keys[1] = keys[2];
        size--;
    }
    else if (size == 2 && keys[1] == k) {
        keys[1] = keys[2];
        size--;
    }
}

void BTreeNode::become_node2(int k, BTreeNode* first_, BTreeNode* second_) {  
    keys[0] = k;
    left = first_;
    midleft = second_;
    midright = nullptr;
    right = nullptr;
    parent = nullptr;
    size = 1;
}

bool BTreeNode::is_leaf() {
    return (left == nullptr) && (midleft == nullptr) && (midright == nullptr);
}



bool BTree::push(int item) {
    _root = insert(_root, item);
    return false;
}

bool BTree::pop(int item) {
    _root = remove(_root, item);
    return false;
}


void BTree::printHelper(BTreeNode* root, std::string indent, int last) {
    if (root != nullptr) {
        std::cout << indent;
        if (last == 0) {
            std::cout << "L----";
            indent += "   ";
        } else if(last == 1) {
            std::cout << "M/R----";
            indent += "|  ";
        } else if (last == 2) {
            std::cout << "R----";
            indent += "|  ";
        }

        //std::string sColor = root->color ? "RED" : "BLACK";
        if(root->size == 1){
            std::cout << root->keys[0] << "(" << " "<< ")" << std::endl;
        }
        else {
            std::cout << root->keys[0] << ",  " << root->keys[1] << " (" << " " << ")" << std::endl;
        }
        printHelper(root->left, indent, 0);
        printHelper(root->midleft, indent, 1);
        printHelper(root->midright, indent, 2);
    }
}




BTreeNode* BTree::insert(BTreeNode* p, int k) { 
    if (!p) return new BTreeNode(k);

    if (p->is_leaf()) p->insert_to_node(k);
    else if (k <= p->keys[0]) insert(p->left, k);
    else if ((p->size == 1) || ((p->size == 2) && k <= p->keys[1])) insert(p->midleft, k);
    else insert(p->midright, k);

    return split(p);
}


BTreeNode* BTree::split(BTreeNode* item){
    if (item->size < 3) return item;

    BTreeNode*x = new BTreeNode(item->keys[0], item->left, item->midleft, nullptr, nullptr, item->parent);
    BTreeNode*y = new BTreeNode(item->keys[2], item->midright, item->right, nullptr, nullptr, item->parent);
    if (x->left)  x->left->parent = x;
    if (x->midleft) x->midleft->parent = x;
    if (y->left)  y->left->parent = y;
    if (y->midleft) y->midleft->parent = y;

    if (item->parent) {
        item->parent->insert_to_node(item->keys[1]);

        if (item->parent->left == item) item->parent->left = nullptr;
        else if (item->parent->midleft == item) item->parent->midleft = nullptr;
        else if (item->parent->midright == item) item->parent->midright = nullptr;


        if (item->parent->left == nullptr) {
            item->parent->right = item->parent->midright;
            item->parent->midright = item->parent->midleft;
            item->parent->midleft = y;
            item->parent->left = x;
        } else if (item->parent->midleft == nullptr) {
            item->parent->right = item->parent->midright;
            item->parent->midright = y;
            item->parent->midleft = x;
        } else {
            item->parent->right = y;
            item->parent->midright = x;
        }

        BTreeNode*tmp = item->parent;
        delete item;
        return tmp;
    } else {
        x->parent = item;
        y->parent = item;
        item->become_node2(item->keys[1], x, y);
        return item;
    }
}


BTreeNode* BTree::search(BTreeNode* p, int k) { 
    if (!p) return nullptr;

    if (p->find(k)) return p;
    else if (k < p->keys[0]) return search(p->left, k);
    else if (((p->size == 2) && (k < p->keys[1])) || (p->size == 1)) return search(p->midleft, k);
    else if (p->size == 2) return search(p->midright, k);
//    return  nullptr;
}



BTreeNode* BTree::search_min(BTreeNode* p) {  
    if (!p) return p;
    if (!(p->left)) return p;
    else return search_min(p->left);
}


BTreeNode* BTree::remove(BTreeNode* p, int k) {  
    BTreeNode* item = search(p, k);

    if (!item) return p;

    BTreeNode* min = nullptr;
    if (item->keys[0] == k) min = search_min(item->midleft);
    else min = search_min(item->midright);

    if (min) {
        int& z = (k == item->keys[0] ? item->keys[0] : item->keys[1]);
        item->swap(z, min->keys[0]);
        item = min;
    }

    item->remove_from_node(k);
    return fix(item);
}



BTreeNode* BTree::fix(BTreeNode* leaf) {
    if (leaf->size == 0 && leaf->parent == nullptr) {
        delete leaf;
        return nullptr;
    }
    if (leaf->size != 0) {
        if (leaf->parent) return fix(leaf->parent);
        else return leaf;
    }

    BTreeNode* parent = leaf->parent;
    if (parent->left->size == 2 || parent->midleft->size == 2 || parent->size == 2) leaf = redistribute(leaf);
    else if (parent->size == 2 && parent->midright->size == 2) leaf = redistribute(leaf);
    else leaf = merge(leaf);

    return fix(leaf);
}



BTreeNode* BTree::redistribute(BTreeNode* leaf) {
    BTreeNode* parent = leaf->parent;
    BTreeNode* left = parent->left;
    BTreeNode* midleft = parent->midleft;
    BTreeNode* midright = parent->midright;

    if ((parent->size == 2) && (left->size < 2) && (midleft->size < 2) && (midright->size < 2)) {
        if (left == leaf) {
            parent->left = parent->midleft;
            parent->midleft = parent->midright;
            parent->midright = nullptr;
            parent->left->insert_to_node(parent->keys[0]);
            parent->left->midright = parent->left->midleft;
            parent->left->midleft = parent->left->left;

            if (leaf->left != nullptr) parent->left->left = leaf->left;
            else if (leaf->midleft != nullptr) parent->left->left = leaf->midleft;

            if (parent->left->left != nullptr) parent->left->left->parent = parent->left;

            parent->remove_from_node(parent->keys[0]);
            delete left;
        }
        else if (midleft == leaf) {
            left->insert_to_node(parent->keys[0]);
            parent->remove_from_node(parent->keys[0]);
            if (leaf->left != nullptr) left->midright = leaf->left;
            else if (leaf->midleft != nullptr) left->midright = leaf->midleft;

            if (left->midright != nullptr) left->midright->parent = left;

            parent->midleft = parent->midright;
            parent->midright = nullptr;

            delete midleft;
        }
        else if (midright == leaf) {
            midleft->insert_to_node(parent->keys[1]);
            parent->midright = nullptr;
            parent->remove_from_node(parent->keys[1]);
            if (leaf->left != nullptr) midleft->midright = leaf->left;
            else if (leaf->midleft != nullptr) midleft->midright = leaf->midleft;

            if (midleft->midright != nullptr)  midleft->midright->parent = midleft;

            delete midright;
        }
    }
    else if ((parent->size == 2) && ((left->size == 2) || (midleft->size == 2) || (midright->size == 2))) {
        if (midright == leaf) {
            if (leaf->left != nullptr) {
                leaf->midleft = leaf->left;
                leaf->left = nullptr;
            }

            leaf->insert_to_node(parent->keys[1]);
            if (midleft->size == 2) {
                parent->keys[1] = midleft->keys[1];
                midleft->remove_from_node(midleft->keys[1]);
                leaf->left = midleft->midright;
                midleft->midright = nullptr;
                if (leaf->left != nullptr) leaf->left->parent = leaf;
            }
            else if (left->size == 2) {
                parent->keys[1] = midleft->keys[0];
                leaf->left = midleft->midleft;
                midleft->midleft = midleft->left;
                if (leaf->left != nullptr) leaf->left->parent = leaf;

                midleft->keys[0] = parent->keys[0];
                parent->keys[0] = left->keys[1];
                left->remove_from_node(left->keys[1]);
                midleft->left = left->midright;
                if (midleft->left != nullptr) midleft->left->parent = midleft;
                left->midright = nullptr;
            }
        }
        else if (midleft == leaf) {
            if (midright->size == 2) {
                if (leaf->left == nullptr) {
                    leaf->left = leaf->midleft;
                    leaf->midleft = nullptr;
                }
                midleft->insert_to_node(parent->keys[1]);
                parent->keys[1] = midright->keys[0];
                midright->remove_from_node(midright->keys[0]);
                midleft->midleft = midright->left;
                if (midleft->midleft != nullptr) midleft->midleft->parent = midleft;
                midright->left = midright->midleft;
                midright->midleft = midright->midright;
                midright->midright = nullptr;
            }
            else if (left->size == 2) {
                if (leaf->midleft == nullptr) {
                    leaf->midleft = leaf->left;
                    leaf->left = nullptr;
                }
                midleft->insert_to_node(parent->keys[0]);
                parent->keys[0] = left->keys[1];
                left->remove_from_node(left->keys[1]);
                midleft->left = left->midright;
                if (midleft->left != nullptr) midleft->left->parent = midleft;
                left->midright = nullptr;
            }
        }
        else if (left == leaf) {
            if (leaf->left == nullptr) {
                leaf->left = leaf->midleft;
                leaf->midleft = nullptr;
            }
            left->insert_to_node(parent->keys[0]);
            if (midleft->size == 2) {
                parent->keys[0] = midleft->keys[0];
                midleft->remove_from_node(midleft->keys[0]);
                left->midleft = midleft->left;
                if (left->midleft != nullptr) left->midleft->parent = left;
                midleft->left = midleft->midleft;
                midleft->midleft = midleft->midright;
                midleft->midright = nullptr;
            }
            else if (midright->size == 2) {
                parent->keys[0] = midleft->keys[0];
                midleft->keys[0] = parent->keys[1];
                parent->keys[1] = midright->keys[0];
                midright->remove_from_node(midright->keys[0]);
                left->midleft = midleft->left;
                if (left->midleft != nullptr) left->midleft->parent = left;
                midleft->left = midleft->midleft;
                midleft->midleft = midright->left;
                if (midleft->midleft != nullptr) midleft->midleft->parent = midleft;
                midright->left = midright->midleft;
                midright->midleft = midright->midright;
                midright->midright = nullptr;
            }
        }
    }
    else if (parent->size == 1) {
        leaf->insert_to_node(parent->keys[0]);

        if (left == leaf && midleft->size == 2) {
            parent->keys[0] = midleft->keys[0];
            midleft->remove_from_node(midleft->keys[0]);

            if (leaf->left == nullptr) leaf->left = leaf->midleft;

            leaf->midleft = midleft->left;
            midleft->left = midleft->midleft;
            midleft->midleft = midleft->midright;
            midleft->midright = nullptr;
            if (leaf->midleft != nullptr) leaf->midleft->parent = leaf;
        }
        else if (midleft == leaf && left->size == 2) {
            parent->keys[0] = left->keys[1];
            left->remove_from_node(left->keys[1]);

            if (leaf->midleft == nullptr) leaf->midleft = leaf->left;

            leaf->left = left->midright;
            left->midright = nullptr;
            if (leaf->left != nullptr) leaf->left->parent = leaf;
        }
    }
    return parent;
}


BTreeNode* BTree::merge(BTreeNode* leaf) {
    BTreeNode* parent = leaf->parent;

    if (parent->left == leaf) {
        parent->midleft->insert_to_node(parent->keys[0]);
        parent->midleft->midright = parent->midleft->midleft;
        parent->midleft->midleft = parent->midleft->left;

        if (leaf->left != nullptr) parent->midleft->left = leaf->left;
        else if (leaf->midleft != nullptr) parent->midleft->left = leaf->midleft;

        if (parent->midleft->left != nullptr) parent->midleft->left->parent = parent->midleft;

        parent->remove_from_node(parent->keys[0]);
        delete parent->left;
        parent->left = nullptr;
    }
    else if (parent->midleft == leaf) {
        parent->left->insert_to_node(parent->keys[0]);

        if (leaf->left != nullptr) parent->left->midright = leaf->left;
        else if (leaf->midleft != nullptr) parent->left->midright = leaf->midleft;

        if (parent->left->midright != nullptr) parent->left->midright->parent = parent->left;

        parent->remove_from_node(parent->keys[0]);
        delete parent->midleft;
        parent->midleft = nullptr;
    }

    if (parent->parent == nullptr) {
        BTreeNode* tmp = nullptr;
        if (parent->left != nullptr) tmp = parent->left;
        else tmp = parent->midleft;
        tmp->parent = nullptr;
        delete parent;
        return tmp;
    }
    return parent;
}
