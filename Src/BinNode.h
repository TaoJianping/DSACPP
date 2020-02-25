//
// Created by tao on 1/25/20.
//

#ifndef DSACPP_BINNODE_H
#define DSACPP_BINNODE_H

#include "Stack.h"

#define BinNodePosi(T) BinNode<T>*
#define stature(p) ((p) ? (p) -> height : -1)
typedef enum {RB_RED, RB_BLACK} RBColor;

#define IsRoot(x) (!((x).parent))
#define IsLChild(x) (! IsRoot(x) && (& (x) == (x).parent->lc))
#define IsRChild(x) (! IsRoot(x) && (& (x) == (x).parent->rc))
#define HasParent(x) (! IsRoot(x))
#define HasLChild(x) ((x).lc)
#define HasRChild(x) ((x).rc)
#define HasChild(x) (HasLChild(x) || HasRChild(x))
#define HasBothChild(x) (HasLChild(x) && HasRChild(x))
#define IsLeaf(x) (! HasChild(x))
#define sibling(p)  \
    (IsLChild(*(p))) ? (p)->parent->rc : (p)->parent->lc)

#define uncle(x)    \
    (IsLChild(*((x)->parent)) ? (x)->parent-parent->rc : (x)->parent->parent->lc)

#define FromParentTo(x)     \
    (IsRoot(x) ? _root : (IsLChild(x) ? (x).parent->lc : (x).parent->rc))


template <typename T>
struct BinNode {
    T data;
    BinNodePosi(T) parent;
    BinNodePosi(T) lChild;
    BinNodePosi(T) rChild;
    int height;
    int npl;
    RBColor color;
    // init
    BinNode() : parent(nullptr), lChild(nullptr), rChild(nullptr), height(0), npl(1), color (RB_RED) {};
    explicit BinNode(T e, BinNodePosi(T) p = nullptr, BinNodePosi(T) lc = nullptr, BinNodePosi(T) rc = nullptr,
            int h = 0, int l = 1, RBColor c = RB_RED) :
            data(e), parent(p), lChild(lc), rChild(rc), height(h), npl(l), color(c) {};
    // functions
    int size();
    BinNodePosi(T) insertAsLC(T const& d);
    BinNodePosi(T) insertAsRC(T const& d);
    BinNodePosi(T) succ();                              // 中序遍历意义下的当前节点的直接后继
    // enumerate
    template <typename VST> void travLevel(VST &);      // 子树层次遍历
    // 子树先序遍历
    template <typename VST> void travPre(VST &);
    // 先序遍历-> 递归
    template <typename VST> void travPre_R(BinNodePosi(T) node, VST &func);
    // 先序遍历-> 迭代1
    template <typename VST> void travPre_I_1(BinNodePosi(T) node, VST &func);
    // 先序遍历-> 迭代2
    template <typename VST> void travPre_I_2(BinNodePosi(T) node, VST &func);
    template <typename VST> void visitAlongLeftBranch(BinNodePosi(T) node, VST &func, Stack<BinNodePosi(T)> & S);

    // 子树中序遍历
    template <typename VST> void travIn(VST &);
    // 中序遍历-> 递归
    template <typename VST> void travIn_R(BinNodePosi(T) node, VST &func);
    // 中序遍历-> 迭代1
    template <typename VST> void travIn_I_1(BinNodePosi(T) node, VST &func);
    static void goAlongLeftBranch(BinNodePosi(T) node, Stack<BinNodePosi(T)> &S);

    // 子树后序遍历
    template <typename VST> void travPost(VST &);
    // 比较器、判断器
    bool operator< (BinNode const& bn) { return this->data < bn.data; }
    bool operator== (BinNode const& bn) { return this->data == bn.data; }
};

template<typename T>
int BinNode<T>::size() {
    int size = 1;

    if (lChild) size += lChild->size();
    if (rChild) size += lChild->size();

    return size;
}

template<typename T>
BinNode<T> *BinNode<T>::insertAsLC(const T &d) {
    lChild = new BinNode<T>(d, this);
    return lChild;
}

template<typename T>
BinNode<T> *BinNode<T>::insertAsRC(const T &d) {
    rChild = new BinNode<T>(d, this);
    return rChild;
}

template<typename T>
template<typename VST>
void BinNode<T>::travPre(VST &) {

}

template<typename T>
template<typename VST>
void BinNode<T>::travPre_R(BinNode<T> *node, VST &func) {
    if (!node)
        return;
    func(node->data);
    travPre_R(node->lChild, func);
    travPre_R(node->rChild, func);
}

template<typename T>
template<typename VST>
void BinNode<T>::travPre_I_1(BinNode<T> *node, VST &func) {
    if (!node)
        return;

    auto stack = new Stack<BinNode<T> *>();
    stack->push(node);
    while (!stack->empty()) {
        auto n = stack->pop();
        if (n)
        {
            func(n->data);
            if (n->rChild)
            {
                stack->push(n->rChild);
            }
            if (n->lChild)
            {
                stack->push(n->lChild);
            }
        }
    }

}

template<typename T>
template<typename VST>
void BinNode<T>::travPre_I_2(BinNode<T> *node, VST &func) {
    if (!node)
        return;

    auto stack = new Stack<BinNode<T> *>();
    while (true)
    {
        visitAlongLeftBranch(node, func, stack);
        if (stack->empty())
            break;
        node = stack->pop();
    }
    delete stack;
}

template<typename T>
template<typename VST>
void BinNode<T>::visitAlongLeftBranch(BinNode<T> *node, VST &func, Stack<BinNode<T> *> &S) {
    while (node)
    {
        func(node->data);
        if (node->rChild)
        {
            S.push(node->rChild);
        }
        node = node->lChild;
    }
}

template<typename T>
template<typename VST>
void BinNode<T>::travIn_R(BinNode<T> *node, VST &func) {
    if (node == nullptr)
        return;

    travIn_R(node->lChild, func);
    func(node->data);
    travIn_R(node->rChild, func);
}

template<typename T>
template<typename VST>
void BinNode<T>::travIn_I_1(BinNode<T> *node, VST &func) {
    auto stack = new Stack<BinNode<T>*>();
    while (true)
    {
        goAlongLeftBranch(node, stack);
        if (stack->empty())
            break;
        node = stack->pop();
        func(node->data);
        node = node->rChild;
    }
}

template<typename T>
void BinNode<T>::goAlongLeftBranch(BinNode<T> *node, Stack<BinNode<T> *> &S) {
    while (node) {
        S.push(node);
        node = node->lChild;
    }
}


#endif //DSACPP_BINNODE_H
