//
// Created by tjp56 on 2019/5/27.
//

#ifndef DSACPP_VECTOR_H
#define DSACPP_VECTOR_H


typedef int Rank;
#define DEFAULT_CAPACITY 3

template<typename T>
class Vector {
private:
    void swap(T &A, T &B);

protected:
    Rank _size{};
    int _capacity{};
    T * _elem;

    void copyFrom(T const *A, Rank lo, Rank hi);    // 复制数组区间

    void expand();

    void shrink();

    Rank bubble(Rank lo, Rank hi);

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

    [[nodiscard]] int disordered() const;

    T get(Rank) const;

    Rank find(T const &e) const { return find(e, 0, (Rank) _size); }

    Rank find(T const &e, Rank lo, Rank hi) const;

    Rank search(T const &e) const;

    Rank search(T const &e, Rank lo, Rank hi) const;

    T &operator[](Rank r) const;

    Vector<T> &operator=(Vector<T> const &) = delete;

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
    if ((_size * 2) < _capacity) {
        return;
    }
    T *old_elem = _elem;
    _capacity = _capacity * 2;
    _elem = new T[_capacity];
    for (int i = 0; i < _size; ++i) {
        _elem[i] = old_elem[i];
    }
    delete[] old_elem;
}

template<typename T>
T Vector<T>::remove(Rank r) {
    T ret = _elem[r];
    remove(r, r + 1);
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
    if (_capacity < DEFAULT_CAPACITY) {
        _capacity = DEFAULT_CAPACITY;
    }
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
T Vector<T>::get(Rank r) const {
    return _elem[r];
}

template<typename T>
void Vector<T>::put(Rank r, const T &e) {
    _elem[r] = e;
}

template<typename T>
int Vector<T>::disordered() const {
    int ret = 0;
    for (int i = 0; i < (_size - 1); ++i) {
        if (_elem[i] > _elem[i + 1]) {
            ret++;
        }
    }
    return ret;
}

template<typename T>
Rank Vector<T>::find(const T &e, Rank lo, Rank hi) const {
    for (int i = lo; i < hi; ++i) {
        if (_elem[i] == e) {
            return i;
        }
    }
    return -1;
}

/*
 * @brief: 删除一定的区间
 * @param: lo 删除的开始位置
 * @param: hi 删除的结束位置
 * @ret: 返回删除的数量
 * */
template<typename T>
int Vector<T>::remove(Rank lo, Rank hi) {
    if (hi > _size) {
        return 0;
    }
    for (int i = 0; i < (_size - hi); ++i) {
        if ((hi + i) <= _size) {
            _elem[lo + i] = _elem[hi + i];
        }
    }
    _size = _size - (hi - lo);
    shrink();
    return lo - hi;
}

template<typename T>
void Vector<T>::sort(Rank lo, Rank hi) {
//    bubbleSort(lo, hi);
    mergeSort(lo, hi);
}

template<typename T>
void Vector<T>::bubbleSort(Rank lo, Rank hi) {
    for (int i = hi; lo < i;) {
        i = bubble(lo, i);
    }
}

// 改进一，当出现整个一次扫描都顺序的时候，直接返回，break掉当前的循环
//template<typename T>
//bool Vector<T>::bubble(Rank lo, Rank hi) {
//    bool is_sorted = true;
//    for (int i = lo; i < (hi-1); ++i) {
//        if (!(_elem[i] <= _elem[i+1])) {
//            is_sorted = false;
//            swap(_elem[i], _elem[i+1]);
//        }
//    }
//    return is_sorted;
//}

template<typename T>
void Vector<T>::swap(T &a, T &b) {
    auto tmp = a;
    a = b;
    b = tmp;
}

// 改进二，取得交换的最后
template<typename T>
Rank Vector<T>::bubble(Rank lo, Rank hi) {
    Rank last = lo;
    for (int i = lo; i < (hi - 1); ++i) {
        if (!(_elem[i] <= _elem[i + 1])) {
            last = i + 1;
            swap(_elem[i], _elem[i + 1]);
        }
    }
    return last;
}

template<typename T>
void Vector<T>::mergeSort(Rank lo, Rank hi) {
    if (hi - lo < 2) {
        return;
    }
    int mid = (lo + hi) / 2;
    mergeSort(lo, mid);
    mergeSort(mid, hi);
    merge(lo, mid, hi);
}

template<typename T>
void Vector<T>::merge(Rank lo, Rank mi, Rank hi) {
    T *A = _elem + lo;     // i
    T *B = new T[hi - lo]();     // j
    for (int i = 0; i < (mi - lo); ++i) {
        B[i] = A[i];
    }
    T *C = _elem + mi;     // k

    auto lb = mi - lo;
    auto lc = hi - mi;

    for (Rank i = 0, j = 0, k = 0; j < lb || k < lc;) {
        if ((j < lb) && (lc <= k || B[j] <= C[k])) A[i++] = B[j++];
        if ((k < lc) && (lb <= j || C[k] < B[j])) A[i++] = C[k++];
    }
    delete[] B;
}

template<typename T>
int Vector<T>::deduplicate() {
    for (int i = 1; i < _size;) {
        auto res = find(_elem[i], 0, i);
        if (res == -1) {
            i++;
        } else {
            remove(i);
        }
    }
    return 0;
}

template<typename T>
template<typename VST>
void Vector<T>::traverse(VST &visit) {
    for (int i = 0; i < _size; ++i) {
        visit(_elem[i]);
    }
}

template<typename T>
void Vector<T>::traverse(void (*visit)(T &)) {
    for (int i = 0; i < _size; ++i) {
        visit(_elem[i]);
    }
}

template<typename T>
int Vector<T>::uniquify() {
    int i;
    int j;
    for (i = 0, j = 1; j < _size;) {
        if (_elem[i] == _elem[j]) {
            ++j;
        } else {
            if ((i+1) == j) {
                ++i;
                ++j;
            } else {
                swap(_elem[i+1], _elem[j]);
                ++i;
                ++j;
            }
        }
    }
    _size = i+1;
    shrink();
    return 0;
}

template<typename T>
Rank Vector<T>::search(const T &e) const {
    return search(e, 0, _size);
}

template<typename T>
Rank Vector<T>::search(const T &e, Rank lo, Rank hi) const {
    while (lo < hi) {
        Rank mi = (lo + hi) / 2;
        (e < _elem[mi]) ? hi = mi : lo = mi + 1;
    }
    return --lo;
}

#endif //DSACPP_VECTOR_H

