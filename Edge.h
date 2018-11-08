#include "Vertex.h"

template <class Nametype, class Data, class Edge_Data> class Edge{
private:
    Vertex<Nametype,Data> *v1;//дескриптор вершины, из которой исходит ребро
    Vertex<Nametype,Data> *v2;//дескриптор вершины, в которую входит ребро
    int w;//вес ребра
    Edge_Data data;//данные, связанные с ребром

public:
    //интерфейсные методы
    Edge(Vertex<Nametype,Data> *ver1, Vertex<Nametype,Data> *ver2);//ver1 - дескриптор вершины, из которой исходит ребро,
    // ver2 - дескриптор вершины, в которую входит ребро
    Edge(Vertex<Nametype,Data> *ver1, Vertex<Nametype,Data> *ver2,int weigth);/*ver1 - дескриптор вершины,из которой
 * исходит ребро, ver2 - дескриптор вершины, в которую входит ребро, weigth - вес ребра*/
    Edge(Vertex<Nametype,Data> *ver1, Vertex<Nametype,Data> *ver2,int weigth, Edge_Data d);/*ver1 - дескриптор вершины,
 * из которой исходит ребро, ver2 - дескриптор вершины, в которую входит ребро, weigth - вес ребра, d - данные,
 * связанные с ребром*/

    Vertex<Nametype,Data>*& V1();//возвращает дескриптор вершины, из которой исходит ребро
    Vertex<Nametype,Data>*& V2();//возвращает дескриптор вершины, из которой исходит ребро
    int getW();//возвращает вес ребра
    void setW(int weigth);//изменение веса ребра
    Edge_Data getData();//возвращает данные, связанные с ребром
    void setData(Edge_Data d);//изменение данных, связанных с ребром
};

template <class Nametype, class Data, class Edge_Data>
Edge<Nametype,Data,Edge_Data>::Edge(Vertex<Nametype, Data> *ver1, Vertex<Nametype, Data> *ver2) {
    v1=ver1;
    v2=ver2;
    w=0;
}

template <class Nametype, class Data, class Edge_Data>
Edge<Nametype,Data,Edge_Data>::Edge(Vertex<Nametype, Data> *ver1, Vertex<Nametype, Data> *ver2, int weigth) {
    v1=ver1;
    v2=ver2;
    w=weigth;
}

template <class Nametype, class Data, class Edge_Data>
Edge<Nametype,Data,Edge_Data>::Edge(Vertex<Nametype, Data> *ver1, Vertex<Nametype, Data> *ver2, int weigth, Edge_Data d) {
    v1=ver1;
    v2=ver2;
    w=weigth;
    data=d;
}

template <class Nametype, class Data, class Edge_Data>
void Edge<Nametype,Data,Edge_Data>::setData(Edge_Data d) {data=d;}

template <class Nametype, class Data, class Edge_Data>
Edge_Data Edge<Nametype,Data,Edge_Data>::getData() { return data;}

template <class Nametype, class Data, class Edge_Data>
int Edge<Nametype,Data,Edge_Data>::getW() { return w;}

template <class Nametype, class Data, class Edge_Data>
void Edge<Nametype,Data,Edge_Data>::setW(int weigth) {w=weigth;}

template <class Nametype, class Data, class Edge_Data>
Vertex<Nametype,Data>*& Edge<Nametype,Data,Edge_Data>::V1() { return v1;}

template <class Nametype, class Data, class Edge_Data>
Vertex<Nametype,Data>*& Edge<Nametype,Data,Edge_Data>::V2() { return v2;}