//
// Created by tao on 19-9-14.
//

#ifndef DSACPP_LIST_H
#define DSACPP_LIST_H

#include <initializer_list>
#include <cstdlib>

using Rank = int;
#define Posi(T) ListNode<T>*

template<typename T>
class ListNode {
public:
    T data;
    Posi(T)pred;
    Posi(T)succ;

    ListNode() = default;;

    explicit ListNode(T e, Posi(T)p = nullptr, Posi(T)s = nullptr) :
            data(e), pred(p), succ(s) {}

    Posi(T)insertAsPred(T const &e);

    Posi(T)insertAsSucc(T const &e) {
        auto node = new ListNode(e, this, succ);
        succ->pred = node;
        succ = node;
        return node;
    };

};

template<typename T>
class List {
private:
    int _size;
    Posi(T)header;
    Posi(T)trailer;
protected:
    void init();

    int clear();

    void copyNodes(Posi(T), int);

    void merge(Posi(T)&, int, List<T> &, Posi(T), int);

    void mergeSort(Posi(T)&, int);

    void selectionSort(Posi(T), int);

    void insertionSort(Posi(T), int);

public:
    // constructor function
    List() { init(); }

    List(List<T> const &L);

    List(List<T> const &L, Rank r, int n);

    List(Posi(T)p, int n);

    List(std::initializer_list<T> il) {
        _size = il.size();
        init();
        for (auto item : il) {
            insertAsLast(item);
        }
    }

    // 析构函数
    ~List();

    // readonly function
    Rank size() const { return _size; }

    bool empty() const { return _size <= 0; }

    T &operator[](int r) const;

    Posi(T)first() const { return header->succ; }

    Posi(T)last() const { return trailer->pred; }

    bool valid(Posi(T)p) { return p && (trailer != p) && (header != p); }

    int disordered() const;

    Posi(T) find(T const &e) const { return find(e, _size, trailer); }

    Posi(T) find(T const &e, int n, Posi(T)p) const;

    Posi(T) search(T const &e) const { return search(e, _size, trailer); }

    Posi(T) search(T const &e, int n, Posi(T)p) const;

    Posi(T) selectMax(Posi(T)p, int n);

    Posi(T)selectMax() {
        if (_size == 0)
            return nullptr;
        return selectMax(header->succ, _size);
    }

    Posi(T)insertAsFirst(T const &e);

    Posi(T)insertAsLast(T const &e);

    Posi(T)insertBefore(Posi(T)p, T const &e) {
        _size++;
        return p->insertAsPred(e);
    };

    Posi(T)insertAfter(Posi(T)p, T const &e) {
        _size++;
        return p->insertAsSucc(e);
    };

    T remove(Posi(T)p);

    void merge(List<T> &L) { merge(first(), _size, L, L.first(), L._size); }

    void sort(Posi(T)p, int n);

    void sort() { sort(first(), _size); }

    void selectionSort();

    void insertionSort();

    int deduplicate();

    int uniquify();

    void reverse();

    // traverse
    void traverse(void (*)(T &));

    template<typename VST>
    void traverse(VST &);
};

template<typename T>
void List<T>::init() {
    header = new ListNode<T>();
    trailer = new ListNode<T>();

    header->succ = trailer;
    header->pred = nullptr;

    trailer->pred = header;
    trailer->succ = nullptr;

    _size = 0;
}

template<typename T>
T& List<T>::operator[](int r) const {
    auto node = first();
    while (0 < r--) {
        node = node->succ;
    }
    return node->data;
}

template<typename T>
ListNode<T> *List<T>::find(const T &e, int n, ListNode<T> *p) const {
    auto node = p->pred;
    while (0 < n--) {
        if (e == node->data) {
            return node;
        } else {
            node = node->pred;
        }
    }
    return nullptr;
}

template<typename T>
ListNode<T> * ListNode<T>::insertAsPred(T const &e) {
    Posi(T) node = new ListNode(e, pred, this);     // there is a big performance trouble
    pred->succ = node;
    this->pred = node;
    return node;
}

template<typename T>
ListNode<T> * List<T>::insertAsLast(T const &e) {
    auto node = insertBefore(trailer, e);
    return node;
}

template<typename T>
void List<T>::copyNodes(ListNode<T> * p, int i) {
    init();
    while (i--) {
        insertAsLast(p->data);
        p = p->succ;
    }
}

template<typename T>
List<T>::~List() {
    clear();
    delete header;
    delete trailer;
}

template<typename T>
T List<T>::remove(ListNode<T> *p) {
    // O(1)
    auto e = p->data;
    p->pred->succ = p->succ;
    p->succ->pred = p->pred;
    _size--;
    delete p;
    return e;
}

template<typename T>
int List<T>::clear() {
    int oldSize = _size;
    while (0 < _size) {
        auto node = header->succ;
        remove(node);
    }
    return oldSize;
}

template<typename T>
int List<T>::deduplicate() {
    if (_size < 2) {
        return 0;
    }
    int oldSize = _size;
    auto p = first();
    Rank r = 1;

    while (trailer != (p = p->succ)) {
        auto q = find(p->data, r, p);
        q ? remove(q) : r++;
    }

    return oldSize - _size;
}

template<typename T>
ListNode<T> * List<T>::insertAsFirst(const T & e) {
    auto node = insertAfter(header, e);
    return node;
}

template<typename T>
void List<T>::sort(ListNode<T> *p, int n) {
    switch (random() % 3)
    {
        case 1:
            insertionSort(p, n);
            break;
        case 2:
            selectionSort(p, n);
            break;
        default:
            mergeSort(p, n);
            break;
    }

}

template<typename T>
void List<T>::insertionSort(ListNode<T> * p, int len)
{
    for (int i = 0; i < len; ++i)
    {
        auto nextElem = p->succ;
        auto pos = search(p->data, i, p);
        insertAfter(pos, p->data);
        remove(p);
        p = nextElem;
    }
}

// 在有序列表内节点p（可能是trailer）的n个真前驱中，找到不大于e的最后者
template<typename T>
ListNode<T> *List<T>::search(const T &e, int n, ListNode<T> *p) const
{
    while (n-- >= 0)
    {
        p = p->pred;
        auto data = p->data;

        if ( data <= e)
            break;
    }
    return p;
}

template<typename T>
ListNode<T> *List<T>::selectMax(ListNode<T> *p, int n) {
    auto maxNode = p;
    while (n > 0) {
        p = p->succ;
        if (p->data > maxNode->data) {
            maxNode = p;
        }
        --n;
    }
    return maxNode;
}

template<typename T>
void List<T>::selectionSort(ListNode<T>* p, int n) {
    ListNode<T>* head = p->pred;
    ListNode<T>* tail = p;

    for (int i = 0; i < n; ++i) {
        tail = tail->succ;
    }

    while (n > 0) {
        auto max = selectMax(head->succ, n-1);
        insertBefore(tail, remove(max));
        tail = tail->pred;
        --n;
    }
}

template<typename T>
void List<T>::selectionSort() {
    selectionSort(first(), _size);
}

template<typename T>
void List<T>::insertionSort() {
    insertionSort(first(), _size);
}

#endif //DSACPP_LIST_H
