#include "Edge.h"
#include "Form.h"
#include <vector>

using namespace std;

template <class Vertex, class Edge> class Graph{
private:
    vector<Vertex*> vertexVector; //Вектор вершин графа
    GraphForm<Edge> *data; //
    bool oriented;//ориентированный граф или нет
    bool l_graph;//является ли L-графом или M-графом
    int edgeCount;//число ребер в графе
public:
//Конструкторы
    Graph();//по умолчанию: создает пустой L-граф с нулевым числом вершин и ребер
    Graph(int v_num,bool directed, bool dense);//создает граф с V вершинами, без ребер, типа D
    // (ориентированный / неориентированный), формы представления F (L- граф/M-граф)
    Graph(int v_num,int e_num,bool directed, bool dense);/* создает граф с V вершинами, с E случайными ребрами, типа
    D (ориентированный / неориентированный), формы представления F (L- граф/M-граф)*/
    Graph(Graph *g);//конструктор копирования
    ~Graph();//деструктор

//функции АТД
    int V();//возвращает число вершин в графе
    int E();//возвращает число ребер в графе
    bool directed();//возвращает тип графа, true - ориентированый, false - неориентированный
    bool dense();//возвращает представление графа, true - L-граф, false - M-граф
    int K();//возвращает коэффициент насыщенности графа
    bool toListGraph();//преобразует граф к L-графу, true - если успех, false - ошибка
    bool toMatrixGraph();//преобразует граф к M-графу, true - если успех, false - ошибка
    Vertex* insertV();//добавляет вершину к графу и возвращает адрес дескриптора вновь созданной вершины
    bool deleteV(Vertex *v);//удаляет вершину из графа, заданного адресом дескриптора v
    bool deleteV(int index);//удаление вершины по индексу
    Edge insertE(Vertex *ver1,Vertex *ver2);/*добавляет
 * ребро (v1, v2) к графу, соединяющую вершины, заданные адресами дескрипторов v1 и v2,
 * и возвращает адрес дескриптора вновь созданного ребра - e*/
    bool DeleteE (Vertex *v1, Vertex *v2);/*удаляет ребро, соединяющее вершины,
 * заданные адресами дескрипторов v1 и v2,*/
    Edge* GetEdge(Vertex *v1, Vertex *v2);/*возвращает адрес
 * дескриптора ребра соединяющего вершины, заданные дескрипторами v1 и v2*/

 //Вспомогательные функции
    void print();//печать графа

    //итератор вершин
    class VertexIterator{
    private:
        Graph<Vertex, Edge> *graph; //граф, к которому привязан итератор
        bool out=false;//true, если итератор вышел за пределы графа
        int cur;//Текущий индекс вершины

    public:
        VertexIterator(Graph &g){graph=&g;}

        //Установить итератор на первую вершину графа
        bool begin(){
            if(graph->vertexVector.size()==0){
                out= true;
                return false;
            }
            cur=0;
            out=false;
            return true;
        }

        //переход к следующей вершине
        bool operator++(){
            if(out){
                cur=-1;
                return false;
            }
            cur++;
            if(graph->vertexVector.size()-1==cur){
                out=true;
            }
            return true;
        }

        //Установка итератора на последнюю вершину графа
        bool end(){
            out = true;
            cur = graph->vertexVector.size()-1;
            if (cur < 0)
                return false;
            else
                return true;

        }

        //возвращает дескриптор вершины графа, на которую указывает итератор
        Vertex* operator*(){
            if(cur>=graph->vertexVector.size()||cur==-1){
                throw "out of graph";
            }
        }
    };

    //Итератор ребер
    class EdgeIterator{
    private:
        Graph<Vertex,Edge> *graph; //граф, к которому привязан итератор
        typename MatrixForm<Edge>::EdgeIterator *mIt;

    };

};
