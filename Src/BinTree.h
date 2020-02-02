//
// Created by tao on 1/25/20.
//

#ifndef DSACPP_BINTREE_H
#define DSACPP_BINTREE_H

#include "BinNode.h"

template <typename T>
class BinTree {
protected:
    int _size;
    BinNodePosi(T) _root;
    virtual int updateHeight(BinNodePosi(T) x);
    void updateHeightAbove(BinNodePosi(T) x);

public:
    // constructor
    BinTree() : _size(0), _root(nullptr) {}
    ~BinTree() {if (0 < _size) this->remove(_root);}

    [[nodiscard]] int size() const { return _size;}
    [[nodiscard]] bool empty() const {return !_root;}
    BinNodePosi(T) root() const {return _root;}

    BinNodePosi(T) insertAsRoot(T const& e);
    BinNodePosi(T) insertAsLC(BinNodePosi(T) x, T const& e);
    BinNodePosi(T) insertAsRC(BinNodePosi(T) x, T const& e);
    BinNodePosi(T) attachAsLC(BinNodePosi(T) x, BinTree<T>* &t);
    BinNodePosi(T) attachAsRC(BinNodePosi(T) x, BinTree<T>* &t);

    int remove(BinNodePosi(T) x);
    BinTree<T>* secede(BinNodePosi(T) x);
    // 遍历
    template <typename VST>
    void travLevel(VST& visit) { if (_root) _root->travLevel(visit);}
    template <typename VST>
    void travPre(VST& visit) {if (_root) _root->travPre(visit);}
    template <typename VST>
    void travIn(VST& visit) { if (_root) _root->travIn(visit);}
    template <typename VST>
    void travPost(VST& visit) {if (_root) _root->travPost(visit);}
    // 比较
    bool operator< (BinTree<T> const& t) {
        return _root && t._root && (_root < t._root);
    }
    bool operator== (BinTree<T> const& t) {
        return _root && t._root && (_root == t._root);
    }
};

template<typename T>
int BinTree<T>::updateHeight(BinNode<T> *x) {
    x->height = 1 + max(stature(x->lc), stature(x->rc));
    return x->height;
}

template<typename T>
void BinTree<T>::updateHeightAbove(BinNode<T> *x) {
    while (x) {
        updateHeight(x);
        x = x->parent;
    }
}

template<typename T>
BinNode<T> *BinTree<T>::insertAsRoot(const T &e) {
    _size = 1;
    _root = new BinNode<T>(e);
    return _root;
}

template<typename T>
BinNode<T> *BinTree<T>::insertAsLC(BinNode<T> *x, const T &e) {
    _size++;
    x->insertAsLC(e);
    updateHeightAbove(x);
    return x->lc;
}

template<typename T>
BinNode<T> *BinTree<T>::insertAsRC(BinNode<T> *x, const T &e) {
    _size++;
    x->insertAsRC(e);
    updateHeightAbove(x);
    return x->rc;
}

#endif //DSACPP_BINTREE_H
