#include <iostream>

using namespace std;
#pragma once

struct Key
{
    int key;
    string path;
    // var record
    Key() : key(0), path("") {}
    Key(int xkey, string xpath) : key(xkey), path(xpath) {}
};

class BTreeNode {
public:
    Key* keys;
    int t;
    BTreeNode** C;
    int n;
    bool leaf;

    BTreeNode(int _t, bool _leaf);

    void traverse();
    int findKey(int k);
    void insertNonFull(Key k);
    void splitChild(int i, BTreeNode* y);
    void deletion(int k);
    void removeFromLeaf(int idx);
    void removeFromNonLeaf(int idx);
    int getPredecessor(int idx);
    int getSuccessor(int idx);
    void fill(int idx);
    void borrowFromPrev(int idx);
    void borrowFromNext(int idx);
    void merge(int idx);
    int returnkeys();
    void returnkeys(Key* k, int x, int limit);




    BTreeNode* search(int k);
    // Getter and Setter methods
    int getKeyAtIndex(int index) const;
    void setKeyAtIndex(int index, Key value);
    BTreeNode* getChildAtIndex(int index) const;
    void setChildAtIndex(int index, BTreeNode* child);
    int getNumKeys() const;
    bool isLeaf() const;
};

class BTree {
public:
    BTreeNode* root;
    int t;
    int totalkeys;

    BTree(int temp);
    void insertion(int k);
    int getTotalKeys() { return totalkeys; }
    void traverse();
    BTreeNode* search(int k);
    void insertion(Key k);
    void deletion(int k);
    void deleteTree(BTreeNode* node);
    Key returnkeys();
    void returnkeys(Key* k, int limit);

    // Getter and Setter methods
    int getDegree() const;
    void setDegree(int temp);
};

// Implementation of BTreeNode member functions
BTreeNode::BTreeNode(int t1, bool leaf1) {
    t = t1;
    leaf = leaf1;

    keys = new Key[2 * t - 1];
    C = new BTreeNode * [2 * t];

    n = 0;
}


void BTree::returnkeys(Key* k, int limit)
{
    int i = 0;
    if (root != nullptr)
        root->returnkeys(k, i, limit);
}

int BTreeNode::getKeyAtIndex(int index) const {
    return keys[index].key;
}

void BTreeNode::setKeyAtIndex(int index, Key value) {
    keys[index] = value;
}

BTreeNode* BTreeNode::getChildAtIndex(int index) const {
    return C[index];
}

void BTreeNode::setChildAtIndex(int index, BTreeNode* child) {
    C[index] = child;
}

int BTreeNode::getNumKeys() const {
    return n;
}

bool BTreeNode::isLeaf() const {
    return leaf;
}

void BTreeNode::traverse() {
    int i;
    for (i = 0; i < n; i++) {
        if (!leaf)
            C[i]->traverse();
        cout << " " << keys[i].key;
    }

    if (!leaf)
        C[i]->traverse();
}

int BTreeNode::returnkeys()
{
    int i;
    for (i = 0; i < n; i++) {
        if (!leaf)
            C[i]->traverse();
        return keys[i].key;
    }

    if (!leaf)
        C[i]->traverse();

}
int BTreeNode::findKey(int k) {
    int idx = 0;
    while (idx < n && keys[idx].key < k)
        ++idx;
    return idx;
}

void BTreeNode::insertNonFull(Key k) {
    int i = n - 1;

    if (leaf) {
        while (i >= 0 && keys[i].key > k.key) {
            keys[i + 1] = keys[i];
            i--;
        }

        keys[i + 1] = k;
        n = n + 1;
    }
    else {
        while (i >= 0 && keys[i].key > k.key)
            i--;

        if (C[i + 1]->n == 2 * t - 1) {
            splitChild(i + 1, C[i + 1]);

            if (keys[i + 1].key < k.key)
                i++;
        }
        C[i + 1]->insertNonFull(k);
    }
}

void BTreeNode::splitChild(int i, BTreeNode* y)
{
    BTreeNode* z = new BTreeNode(y->t, y->leaf);
    z->n = t - 1;

    for (int j = 0; j < t - 1; j++)
        z->keys[j] = y->keys[j + t];

    if (y->leaf == false) {
        for (int j = 0; j < t; j++)
            z->C[j] = y->C[j + t];
    }

    y->n = t - 1;

    for (int j = n; j >= i + 1; j--)
        C[j + 1] = C[j];

    C[i + 1] = z;

    for (int j = n - 1; j >= i; j--)
        keys[j + 1] = keys[j];

    keys[i] = y->keys[t - 1];

    n = n + 1;
}

void BTreeNode::deletion(int k) {
    int idx = findKey(k);

    if (idx < n && keys[idx].key == k) {
        if (leaf)
            removeFromLeaf(idx);
        else
            removeFromNonLeaf(idx);
    }
    else {
        if (leaf) {
            cout << "The key " << k << " does not exist in the tree\n";
            return;
        }

        bool flag = ((idx == n) ? true : false);

        if (C[idx]->n < t)
            fill(idx);

        if (flag && idx > n)
            C[idx - 1]->deletion(k);
        else
            C[idx]->deletion(k);
    }
    return;
}

void BTreeNode::removeFromLeaf(int idx) {
    for (int i = idx + 1; i < n; ++i)
        keys[i - 1] = keys[i];

    n--;

    return;
}

void BTreeNode::removeFromNonLeaf(int idx) {
    int k = keys[idx].key;

    if (C[idx]->n >= t) {
        int pred = getPredecessor(idx);
        keys[idx].key = pred;
        C[idx]->deletion(pred);
    }

    else if (C[idx + 1]->n >= t) {
        int succ = getSuccessor(idx);
        keys[idx].key = succ;
        C[idx + 1]->deletion(succ);
    }

    else {
        merge(idx);
        C[idx]->deletion(k);
    }
    return;
}

int BTreeNode::getPredecessor(int idx) {
    BTreeNode* cur = C[idx];
    while (!cur->leaf)
        cur = cur->C[cur->n];

    return cur->keys[cur->n - 1].key;
}

int BTreeNode::getSuccessor(int idx) {
    BTreeNode* cur = C[idx + 1];
    while (!cur->leaf)
        cur = cur->C[0];

    return cur->keys[0].key;
}

void BTreeNode::fill(int idx) {
    if (idx != 0 && C[idx - 1]->n >= t)
        borrowFromPrev(idx);

    else if (idx != n && C[idx + 1]->n >= t)
        borrowFromNext(idx);

    else {
        if (idx != n)
            merge(idx);
        else
            merge(idx - 1);
    }
    return;
}

void BTreeNode::borrowFromPrev(int idx) {
    BTreeNode* child = C[idx];
    BTreeNode* sibling = C[idx - 1];

    for (int i = child->n - 1; i >= 0; --i)
        child->keys[i + 1] = child->keys[i];

    if (!child->leaf) {
        for (int i = child->n; i >= 0; --i)
            child->C[i + 1] = child->C[i];
    }

    child->keys[0] = keys[idx - 1];

    if (!child->leaf)
        child->C[0] = sibling->C[sibling->n];

    keys[idx - 1] = sibling->keys[sibling->n - 1];

    child->n += 1;
    sibling->n -= 1;

    return;
}

void BTreeNode::borrowFromNext(int idx) {
    BTreeNode* child = C[idx];
    BTreeNode* sibling = C[idx + 1];

    child->keys[(child->n)] = keys[idx];

    if (!(child->leaf))
        child->C[(child->n) + 1] = sibling->C[0];

    keys[idx] = sibling->keys[0];

    for (int i = 1; i < sibling->n; ++i)
        sibling->keys[i - 1] = sibling->keys[i];

    if (!sibling->leaf) {
        for (int i = 1; i <= sibling->n; ++i)
            sibling->C[i - 1] = sibling->C[i];
    }

    child->n += 1;
    sibling->n -= 1;

    return;
}

void BTreeNode::merge(int idx) {
    BTreeNode* child = C[idx];
    BTreeNode* sibling = C[idx + 1];

    child->keys[t - 1] = keys[idx];

    for (int i = 0; i < sibling->n; ++i)
        child->keys[i + t] = sibling->keys[i];

    if (!child->leaf) {
        for (int i = 0; i <= sibling->n; ++i)
            child->C[i + t] = sibling->C[i];
    }

    for (int i = idx + 1; i < n; ++i)
        keys[i - 1] = keys[i];

    for (int i = idx + 2; i <= n; ++i)
        C[i - 1] = C[i];

    child->n += sibling->n + 1;
    n--;

    delete (sibling);
    return;
}

BTreeNode* BTreeNode::search(int k) {
    int i = 0;
    while (i < n && k > keys[i].key)
        i++;

    if (keys[i].key == k)
        return this;

    if (leaf == true)
        return NULL;

    return C[i]->search(k);
}

// Implementation of BTree member functions
BTree::BTree(int temp) {
    root = nullptr;
    t = temp;
    totalkeys = 0;
}

int BTree::getDegree() const {
    return t;
}

void BTree::setDegree(int temp) {
    t = temp;
}

void BTree::traverse() {
    if (root != nullptr)
        root->traverse();
}

BTreeNode* BTree::search(int k) {
    return (root == nullptr) ? nullptr : root->search(k);
}

void BTree::insertion(Key k) {
    if (root == nullptr) {
        root = new BTreeNode(t, true);
        root->setKeyAtIndex(0, k);
        root->n = 1;
    }
    else {
        if (root->n == 2 * t - 1) {
            BTreeNode* s = new BTreeNode(t, false);

            s->setChildAtIndex(0, root);

            s->splitChild(0, root);

            int i = 0;
            if (s->getKeyAtIndex(0) < k.key)
                i++;
            s->getChildAtIndex(i)->insertNonFull(k);

            root = s;
        }
        else
            root->insertNonFull(k);
    }
    totalkeys++;

}



void BTree::deletion(int k)
{
    if (!root) {
        cout << "The tree is empty\n";
        return;
    }

    root->deletion(k);

    if (root->n == 0) {
        BTreeNode* tmp = root;
        if (root->isLeaf())
            root = nullptr;
        else
            root = root->getChildAtIndex(0);

        delete tmp;
    }
    totalkeys--;
    return;
}

void BTree::deleteTree(BTreeNode* node)
{
    if (node != nullptr) {
        for (int i = 0; i < node->n + 1; ++i) {
            deleteTree(node->C[i]);
        }
        delete node;
    }
}



void BTreeNode::returnkeys(Key* k, int x, int limit)
{


    int i;
    for (i = 0; i < n; i++) {
        if (x == limit)
            return;

        if (!leaf)
            C[i]->traverse();
        k[x] = keys[i];
        x++;

    }

    if (!leaf)
        C[i]->traverse();
}