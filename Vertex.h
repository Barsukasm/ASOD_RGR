#ifndef VERTEX_H
#define VERTEX_H
template<class NameType, class Data> class Vertex{
private:
     NameType name;//имя вершины
     Data data;//данные, связанные с вершиной

public:
     int index;//индекс вершины в структуре графа или -1

     //интерфейсные методы
     Vertex();//Конструктор по умолчанию
     Vertex(NameType n, Data d);//Конструктор, n - имя вершины, d - данные, связанные с вершиной
     NameType getName();//возвращает имя вершины
     Data getData();//возвращает данные, связанные с вершиной
     void setName(NameType n);//задает имя вершины
     void setData(Data d);//записывает данные d в дескриптор вершины
};

template <class NameType,class Data>
Vertex<NameType,Data>::Vertex() {
    index=-1;
}

template <class NameType,class Data>
Vertex<NameType,Data>::Vertex(NameType n, Data d) {
    name=n;
    data=d;
    index=-1;
}

template <class NameType,class Data>
Data Vertex<NameType,Data>::getData() {return data;}

template <class NameType,class Data>
NameType Vertex<NameType,Data>::getName() { return name;}

template <class NameType,class Data>
void Vertex<NameType,Data>::setData(Data d) {data=d;}

template <class NameType,class Data>
void Vertex<NameType,Data>::setName(NameType n) {name=n;}

#endif