//
// Created by tjp56 on 2019/5/27.
//

#ifndef DSACPP_VECTOR_H
#define DSACPP_VECTOR_H

#include <iostream>

using namespace std;

typedef int Rank;
#define DEFAULT_CAPACITY 3

template<typename T>
class Vector {
protected:
    Rank _size;
    int _capacity;
    T *_elem;

    void copyFrom(T const *A, Rank lo, Rank hi);    // 复制数组区间

    void expand();
    void ExpandWhatever();

    void shrink();

    bool bubble(Rank lo, Rank hi);
    void bubbleSort(Rank lo, Rank hi);
    Rank max(Rank lo, Rank hi);
    void selectionSort(Rank lo, Rank hi);
    void merge(Rank lo, Rank mi, Rank hi);
    void mergeSort(Rank lo, Rank hi);
    Rank partition(Rank lo, Rank hi);
    void quickSort(Rank lo, Rank hi);
    void heapSort(Rank lo, Rank hi);
public:
    // 构造函数
    explicit Vector(int c = DEFAULT_CAPACITY, int s = 0, T v = 0); //容量为c、规模为s、所有元素初始为v
    Vector(T const *A, Rank lo, Rank hi) { copyFrom(A, lo, hi); } //数组区间赋值
    Vector(T const *A, Rank n) { copyFrom(A, 0, n); } //数组整体复制
    Vector(Vector<T> const &V, Rank lo, Rank hi) { copyFrom(V._elem, lo, hi); } //向量区间复制
    Vector(Vector<T> const &V) { copyFrom(V._elem, 0, V._size); } //向量整体复制
    // 析构函数
    ~Vector() { delete[] _elem; } //释放内部空间
    // 只读访问接口
    [[nodiscard]] Rank size() const { return _size; }
    [[nodiscard]] bool empty() const { return !_size; }
    int disordered() const;
    T get(Rank) const ;
    Rank find(T const &e) const { return find(e, 0, (Rank) _size); }
    Rank find(T const &e, Rank lo, Rank hi) const;
    Rank search(T const &e) const;
    Rank search(T const &e, Rank lo, Rank hi) const;

    T &operator[](Rank r) const;
    Vector<T> &operator=(Vector<T> const &);
    T remove(Rank r);
    int remove(Rank lo, Rank hi);
    void insert(Rank r, T const &e);
    void put(Rank r, T const &e);
    Rank insert(T const &e) { return insert(_size, e); }
    void sort(Rank lo, Rank hi);
    void sort() { sort(0, _size); }
    void unsort(Rank lo, Rank hi);
    void unsort() { unsort(0, _size); }
    int deduplicate();
    int uniquify();
    void traverse(void (*)(T &));
    template<typename VST>
    void traverse(VST &);

};


template<typename T>
void Vector<T>::expand() {
    // 尚未满员时，不必扩容
    if (_size < _capacity) {
        return;
    }

    int new_size = _capacity * 2;
    // 不低于最小容量
    T *new_elem = new T[new_size];
    // 容量加倍
    _capacity = new_size;
    // 复制原向量内容
    for (int i = 0; i < _size; ++i) {
        new_elem[i] = _elem[i];
    }

    // 释放原空间
    // 释放指针的时候，如果他是数组，要像下面这么写
    delete []_elem;

    _elem = new_elem;
}

template<typename T>
T Vector<T>::remove(Rank r) {
    T ret = _elem[r];
    for (int i = r; i < _size; ++i) {
        _elem[i] = _elem[i+1];
    }
    return ret;
}


template<typename T>
void Vector<T>::shrink() {
    if (_capacity < DEFAULT_CAPACITY) {
        return;
    }
    if (_size * 4 > _capacity) {
        return;
    }

    T *tmp = _elem;
    int new_volume = _capacity / 4;
    _elem = new T[new_volume];
    for (int i = 0; i < _size; ++i) {
        _elem[i] = tmp[i];
    }
}


template<typename T>
T &Vector<T>::operator[](Rank r) const {
//    _elem = 0;
    return _elem[r];
}


template<typename T>
void Vector<T>::copyFrom(T const *A, Rank lo, Rank hi) {
    _capacity = (hi - lo) * 2;
    // 加不加括号有什么区别？
    _elem = new T[_capacity]();
    for (_size = 0; (lo + _size) < hi; ++_size) {
        _elem[_size] = A[_size + lo];
    }
}


template<typename T>
Vector<T>::Vector(int c, int s, T v) {
    _elem = new T[_capacity = c];
    for (_size = 0; _size < s; _elem[_size++] = v);
}


template<typename T>
void Vector<T>::insert(Rank r, const T &e) {
    // Todo r > _capacity???
    expand();
    for (int i = _size; i >= r; --i) {
        _elem[i + 1] = _elem[i];
    }
    _size++;
    _elem[r] = e;
}

template<typename T>
void Vector<T>::ExpandWhatever() {
    T *new_elem = new T[_capacity * 2];
    for (int i = 0; i < _size; ++i) {
        new_elem[i] = _elem[i];
    }
    _elem = new_elem;
    delete _elem;
}

template<typename T>
T Vector<T>::get(Rank r) const {
    return _elem[r];
}

template<typename T>
void Vector<T>::put(Rank r, const T &e) {
    _elem[r] = e;
}


#endif //DSACPP_VECTOR_H

