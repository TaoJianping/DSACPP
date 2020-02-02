//
// Created by tao on 2/1/20.
//

#ifndef DSACPP_PQ_COMPLHEAP_H
#define DSACPP_PQ_COMPLHEAP_H

#include "PriorityQueue.h"
#include "vector.h"

#define InHeap(n, i) ((( -1 ) < ( i )) && (( i ) < ( n )))
#define Parent(i) (( i - 1) >> 1)
#define LastInternal(n) Parent( n - 1 )
#define LChild(i) ( 1 + ( ( i ) << 1 ) )
#define RChild(i) ( ( 1 + ( i ) ) << 1 )
#define ParentValid(i) ( 0 < i )
#define LChildValid(n, i) InHeap( n, LChild( i ))
#define RChildValid(n, i) InHeap( n, RChild( i ))
#define Bigger(PQ, i, j) ((PQ[i] < PQ[j]) ? j : i)
#define ProperParent(PQ, n, i)      \
        ( RChildValid(n, i) ? Bigger(PQ, Bigger(PQ, i, LChild(i)), RChild(i)) : \
        ( LChildValid(n, i) ? Bigger(PQ, i, LChild(i)) : i) \
        )

template<typename T>
class PQ_CompleteHeap : public PQ<T>, public Vector<T>
{
protected:
	Rank percolateDown(Rank n, Rank i);     // 下滤
	Rank percolateUp(Rank i);               // 上滤
	void heapify(Rank n);                   // Floyd建堆算法
	void heapify_bad(Rank n);               // 蛮力算法
public:
	PQ_CompleteHeap(T* A, Rank n)
	{
		copyFrom(A, 0, n);
		heapify(n);
	}

	PQ_CompleteHeap() = default;

	void insert(T data) override;

	T getMax() override;

	T delMax() override;
};

template<typename T>
T PQ_CompleteHeap<T>::getMax()
{
	return this->_elem[0];
}

template<typename T>
void PQ_CompleteHeap<T>::insert(T data)
{
	Vector<T>::insert(data);
	percolateUp(this->_size - 1);
}

template<typename T>
Rank PQ_CompleteHeap<T>::percolateUp(Rank i)
{
	while (ParentValid(i))
	{
		auto pi = Parent(i);
		if (this->_elem[pi] < this->_elem[i])
		{
			this->swap(this->_elem[pi], this->_elem[i]);
			i = pi;
		}
		else
		{
			break;
		}
	}
	return i;
}

template<typename T>
T PQ_CompleteHeap<T>::delMax()
{
	auto ret = this->_elem[0];
	this->swap(this->_elem[0], this->_elem[this->_size - 1]);
	this->remove(this->_size - 1);
	percolateDown(this->_size, 0);
	return ret;
}

/*
 * i: 你要下滤的元素
 * */
template<typename T>
Rank PQ_CompleteHeap<T>::percolateDown(Rank n, Rank i)
{
	while (auto p = ProperParent(this->_elem, n, i))
	{
		if (p == i)
			break;

		this->swap(this->_elem[p], this->_elem[i]);
		i = p;
	}

	return i;
}

template<typename T>
void PQ_CompleteHeap<T>::heapify(Rank n)
{
	for (int i = LastInternal(n); InHeap(n, i); i--)
	{
		percolateDown(n, i);
	}
}

/*
 * 蛮力算法
 * */
template<typename T>
void PQ_CompleteHeap<T>::heapify_bad(Rank n)
{
	for (int i = 1; i < n; ++i)
	{
		this->percolateUp(i);
	}
}


#endif //DSACPP_PQ_COMPLHEAP_H
