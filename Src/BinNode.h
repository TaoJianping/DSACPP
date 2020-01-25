//
// Created by tao on 1/25/20.
//

#ifndef DSACPP_BINNODE_H
#define DSACPP_BINNODE_H

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


    template <typename T> struct BinNode {
    T data;
    BinNodePosi(T) parent;
    BinNodePosi(T) lc;
    BinNodePosi(T) rc;
    int height;
    int npl;
    RBColor color;

    BinNode() :
        parent(nullptr), lc(nullptr), rc(nullptr), height(0), npl(1), color (RB_RED) {};
    explicit BinNode(T e, BinNodePosi(T) p = nullptr, BinNodePosi(T) lc = nullptr, BinNodePosi(T) rc = nullptr,
            int h = 0, int l = 1, RBColor c = RB_RED) :
            data(e), parent(p), lc(lc), rc(rc), height(h), npl(l), color(c) {};
    int size();
    BinNodePosi(T) insertAsLC(T const& d);
    BinNodePosi(T) insertAsRC(T const& d);
    BinNodePosi(T) succ();
    template <typename VST> void travLevel(VST &);
    template <typename VST> void travPre(VST &);
    template <typename VST> void travIn(VST &);
    template <typename VST> void travPost(VST &);
    // 比较器、判断器
    bool operator< (BinNode const& bn) { return data < bn.data; }
    bool operator== (BinNode const& bn) { return data == bn.data; }
};

template<typename T>
int BinNode<T>::size() {
    int size = 1;

    if (lc) size += lc->size();
    if (rc) size += lc->size();

    return size;
}

template<typename T>
BinNode<T> *BinNode<T>::insertAsLC(const T &d) {
    lc = new BinNode<T>(d, this);
    return lc;
}

template<typename T>
BinNode<T> *BinNode<T>::insertAsRC(const T &d) {
    rc = new BinNode<T>(d, this);
    return rc;
}


#endif //DSACPP_BINNODE_H
