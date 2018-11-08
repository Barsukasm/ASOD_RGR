#include "Edge.h"

template <class Nametype, class Data, class Edge_Data> class SimpleGraph{
private:
    bool oriented;//ориентированный граф или нет
    bool l_graph;//является ли L-графом или M-графом
public:
    SimpleGraph();//по умолчанию: создает пустой L-граф с нулевым числом вершин и ребер
    SimpleGraph(int v_num,bool d, bool f);//создает граф с V вершинами, без ребер, типа D
    // (ориентированный / неориентированный), формы представления F (L- граф/M-граф)
    SimpleGraph(int v_num,int e_num,bool d, bool f);/* создает граф с V вершинами, с E случайными ребрами, типа
    D (ориентированный / неориентированный), формы представления F (L- граф/M-граф)*/
    SimpleGraph(SimpleGraph *g);//конструктор копирования
    ~SimpleGraph();//деструктор
    int V();//возвращает число вершин в графе
    int E();//возвращает число ребер в графе
    bool directed();//возвращает тип графа, true - ориентированый, false - неориентированный
    bool dense();//возвращает представление графа, true - L-граф, false - M-граф
    int K();//возвращает коэффициент насыщенности графа
    bool toListGraph();//преобразует граф к L-графу, true - если успех, false - ошибка
    bool toMatrixGraph();//преобразует граф к M-графу, true - если успех, false - ошибка
    Vertex<Nametype,Data>*& insertV();//добавляет вершину к графу и возвращает адрес дескриптора вновь созданной вершины
    bool deleteV(Vertex<Nametype,Data> *&v);//удаляет вершину из графа, заданного адресом дескриптора v
    Edge<Nametype,Data,Edge_Data> insertE(Vertex<Nametype,Data> ver1,Vertex<Nametype,Data> ver2);/*добавляет
 * ребро (v1, v2) к графу, соединяющую вершины, заданные адресами дескрипторов v1 и v2,
 * и возвращает адрес дескриптора вновь созданного ребра - e*/
    bool DeleteE (Vertex<Nametype,Data> *v1, Vertex<Nametype,Data> *v2);/*удаляет ребро, соединяющее вершины,
 * заданные адресами дескрипторов v1 и v2,*/
    Edge<Nametype,Data,Edge_Data>*& GetEdge(Vertex<Nametype,Data> *v1, Vertex<Nametype,Data> *v2);/*возвращает адрес
 * дескриптора ребра соединяющего вершины, заданные дескрипторами v1 и v2*/
};