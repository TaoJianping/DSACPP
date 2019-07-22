//
// Created by tjp56 on 2019/5/27.
//

#ifndef DSACPP_VECTOR_H
#define DSACPP_VECTOR_H

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

    void shrink();

    bool bubble(Rank lo, Rank hi);

    void bubbleSort(Rank lo, Rank hi); //起泡排序算法
    Rank max(Rank lo, Rank hi); //选取最大元素
    void selectionSort(Rank lo, Rank hi); //选择排序算法
    void merge(Rank lo, Rank mi, Rank hi); //归并算法
    void mergeSort(Rank lo, Rank hi); //归并排序算法
    Rank partition(Rank lo, Rank hi); //轴点极造算法
    void quickSort(Rank lo, Rank hi); //快速排序算法
    void heapSort(Rank lo, Rank hi); //堆排序
public:
    // 构造函数
    Vector(int c = DEFAULT_CAPACITY, int s = 0, T v = 0) //容量为c、规模为s、所有元素初始为v
    {
        _elem = new T[_capacity = c];
        for (_size = 0; _size < s; _elem[_size++] = v);
    } //s <= c
    Vector(T const *A, Rank lo, Rank hi) { copyFrom(A, lo, hi); } //数组区间赋值
    Vector(T const *A, Rank n) { copyFrom(A, 0, n); } //数组整体复制
    Vector(Vector<T> const &V, Rank lo, Rank hi) { copyFrom(V._elem, lo, hi); } //向量区间复制
    Vector(Vector<T> const &V) { copyFrom(V._elem, 0, V._size); } //向量整体复制
    // 析构函数
    ~Vector() { delete[] _elem; } //释放内部空间
    // 只读访问接口
    Rank size() const { return _size; } //觃模
    bool empty() const { return !_size; } //刞空
    int disordered() const; //刞断向量是否已排序
    Rank find(T const &e) const { return find(e, 0, (Rank) _size); } //无序向量整体查找
    Rank find(T const &e, Rank lo, Rank hi) const; //无序向量匙间查找
    Rank search(T const &e) const //有序向量整体查找
    { return (0 >= _size) ? -1 : search(e, (Rank) 0, (Rank) _size); }

    Rank search(T const &e, Rank lo, Rank hi) const; //有序向量匙间查找
    // 可写讵问接口
    T &operator[](Rank r) const; //重载下标操作符，可以类似亍数组形式引用各元素
    Vector<T> &operator=(Vector<T> const &); //重载赋值操作符，以便直接克隆向量
    T remove(Rank r); //初除秩为r癿元素
    int remove(Rank lo, Rank hi); //初除秩在匙间[lo, hi)乀内癿元素
    Rank insert(Rank r, T const &e); //揑入元素
    Rank insert(T const &e) { return insert(_size, e); } //默讣作为末元素揑入
    void sort(Rank lo, Rank hi); //对[lo, hi)排序
    void sort() { sort(0, _size); } //整体排序
    void unsort(Rank lo, Rank hi); //对[lo, hi)置乱
    void unsort() { unsort(0, _size); } //整体置乱
    int deduplicate(); //无序去重
    int uniquify(); //有序去重
    // 遍历
    void traverse(void (*)(T &)); //遍历（使用函数指针，叧读戒尿部性修改）
    template<typename VST>
    void traverse(VST &); //遍历（使用函数对象，可全尿性修改）
}; //Vector


template<typename T>
void Vector<T>::expand() {
    // 尚未满员时，不必扩容
    if (_size < _capacity) {
        return;
    }
    // 不低于最小容量
    T *new_elem = new T[_capacity * 2];
    // 容量加倍

    // 复制原向量内容
    for (int i = 0; i < _size; ++i) {
        new_elem[i] = _elem[i];
    }

    _elem = new_elem;
    // 释放原空间
    delete _elem;
}


template<typename T>
void Vector<T>::copyFrom(T const *A, Rank lo, Rank hi) {
    _capacity = 2 * (hi - lo);
    _elem = new T[_capacity];
    _size = 0;

    while (lo < hi) {
        _elem[_size++] = A[lo++];
    }
}


template<typename T>
void Vector<T>::shrink() {
    if (_capacity < DEFAULT_CAPACITY) {
        return;
    }
    if (_size * 4  > _capacity) {
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
T& Vector<T>::operator[](Rank r) const {

    _elem = 0;
    return _elem[r];
}



#endif //DSACPP_VECTOR_H

