//
// Created by tao on 1/29/20.
//

#ifndef DSACPP_GRAPHMATRIX_H
#define DSACPP_GRAPHMATRIX_H

#include "Graph.h"
#include "vector.h"

template <typename Tv>
struct Vertex
{
    Tv data;
    int inDegree;
    int outDegree;

    VStatus status;

    int dTime;
    int fTime;

    int parent;
    int priority;

    explicit Vertex(Tv const& d = (Tv) 0) :
            data(d), inDegree(0), outDegree(0), status(UNDISCOVERED),
            dTime(-1), fTime(-1), parent(-1), priority(INT_MAX) {}
};


template <typename Te>
struct Edge
{
    Te data;
    int weight;
    EStatus status;
    Edge(Te const & d, int w) :
        data(d), weight(w), status(UNDETERMINED) {}
};


template <typename Tv, typename Te>
class GraphMatrix : public Graph<Tv, Te>{
private:
    Vector<Vertex<Tv>> V;
    Vector<Vector<Edge<Te>*>> E;
public:
    GraphMatrix() {this->n = this->e = 0;}
    ~GraphMatrix() {
        for (int j = 0; j < this->n; ++j) {
            for (int k = 0; k < this->n; ++k) {
                delete E[j][k];
            }
        }
    }
    // 顶点的基本操作：查询第i个顶点（0 <= i < n）
    virtual Tv& vertex(int i) { return V[i].data; }
    virtual int inDegree(int i) { return V[i].inDegree; }
    virtual int outDegree(int i) { return V[i].outDegree; }
    VStatus & status(int i) { return V[i].status;}
    int & dTime(int i) { return V[i].dTime;}
    int & fTime(int i) { return V[i].fTime;}
    int & parent(int i) { return V[i].parent;}
    int & priority(int i) { return V[i].priority;}

    virtual int firstNbr(int i);
    virtual int nextNbr(int i, int j);

    // 顶点的动态操作
    virtual int insert (Tv const& vertex);
    virtual Tv remove(int i);

    // 边的确认操作
    virtual bool exists(int i, int j);
    // 边的基本操作
    virtual EType& type(int i, int j) { return E[i][j]->status; }
    virtual Te& edge(int i, int j) { return E[i][j]->data; }
    virtual int& weight(int i, int j) { return E[i][j]->weight; }
    // 边的动态操作
    virtual void insert(Te const& edge, int w, int i, int j);
    virtual Te remove(int i, int j);
};

template<typename Tv, typename Te>
bool GraphMatrix<Tv, Te>::exists(int i, int j) {
    return (0 <= i < this->n) && (0 <= j < this->n) && E[i][j] != nullptr;
}

template<typename Tv, typename Te>
void GraphMatrix<Tv, Te>::insert(const Te &edge, int w, int i, int j)
{
    if (exists(i, j))
        return;
    E[i][j] = new Edge<Te>(edge, w);

    ++this->e;
    V[i].outDegree++;
    V[j].inDegree++;
}

template<typename Tv, typename Te>
Te GraphMatrix<Tv, Te>::remove(int i, int j)
{
    if (!exists(i, j))
        return nullptr;
    Te d = edge(i, j);
    delete E[i][j];
    E[i][j] = nullptr;
    --this->e;
    V[i].outDegree--;
    V[j].inDegree--;
    return d;
}

template<typename Tv, typename Te>
int GraphMatrix<Tv, Te>::firstNbr(int i)
{
    return nextNbr(i, this->n);
}

template<typename Tv, typename Te>
int GraphMatrix<Tv, Te>::nextNbr(int i, int j)
{
    while (-1 < j && !exists(i, --j));
    return j;
}

template<typename Tv, typename Te>
int GraphMatrix<Tv, Te>::insert(const Tv &vertex) {
    for (int j = 0; j < this->n; ++j)
    {
        E[j].insert(nullptr);
    }
    this->n++;
    E.insert(Vector<Edge<Te>*>(this->n, this->n, nullptr));
    return V.insert(Vertex<Tv>(vertex));
}

template<typename Tv, typename Te>
Tv GraphMatrix<Tv, Te>::remove(int i)
{
    for (int j = 0; j < this->n; ++j) {
        if (exists(i, j))
        {
            delete E[i][j];
            V[j].inDegree--;
        }
    }
    this->n--;
    E.remove(i);

    Tv vBak = vertex(i);
    V.remove(i);

    for (int j = 0; j < this->n; ++j)
    {
        if (auto e = E[j].remove(i))
        {
            delete e;
            V[j].outDegree--;
        }
    }

    return vBak;
}


#endif //DSACPP_GRAPHMATRIX_H
