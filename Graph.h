#ifndef GRAPH_H
#define GRAPH_H
#include <vector>
#include <string>
#include <time.h>
#include <iostream>
#include <iomanip>
#include "Edge.h"
#include "Form.h"

using namespace std;

template <class Vertex, class Edge> class Graph{
private:
    vector<Vertex*> vertexVector; //Вектор вершин графа
    GraphForm<Edge> *data; //
    bool oriented;//ориентированный граф или нет
    bool l_graph;//является ли L-графом или M-графом
    int edgeCount;//число ребер в графе
    int sN;
public:
//Конструкторы
    Graph();//по умолчанию: создает пустой L-граф с нулевым числом вершин и ребер
    Graph(int v_num,bool directed, bool dense);//создает граф с V вершинами, без ребер, типа D
    // (ориентированный / неориентированный), формы представления F (L- граф/M-граф)
    Graph(int v_num,int e_num,bool directed, bool dense);/* создает граф с V вершинами, с E случайными ребрами, типа
    D (ориентированный / неориентированный), формы представления F (L- граф/M-граф)*/
    Graph(Graph &g);//конструктор копирования
    ~Graph();//деструктор

//функции АТД
    int V();//возвращает число вершин в графе
    int E();//возвращает число ребер в графе
    bool directed();//возвращает тип графа, true - ориентированый, false - неориентированный
    bool dense();//возвращает представление графа, false - L-граф, true - M-граф
    double K();//возвращает коэффициент насыщенности графа
    bool toListGraph();//преобразует граф к L-графу, true - если успех, false - ошибка
    bool toMatrixGraph();//преобразует граф к M-графу, true - если успех, false - ошибка
    Vertex* insertV();//добавляет вершину к графу и возвращает адрес дескриптора вновь созданной вершины
    bool deleteV(Vertex *v);//удаляет вершину из графа, заданного адресом дескриптора v
    bool deleteV(int index);//удаление вершины по индексу
    Edge* insertE(Vertex *ver1,Vertex *ver2);/*добавляет
 * ребро (v1, v2) к графу, соединяющую вершины, заданные адресами дескрипторов v1 и v2,
 * и возвращает адрес дескриптора вновь созданного ребра - e*/
    bool DeleteE (Vertex *v1, Vertex *v2);/*удаляет ребро, соединяющее вершины,
 * заданные адресами дескрипторов v1 и v2,*/
    Edge* GetEdge(Vertex *v1, Vertex *v2);/*возвращает адрес
 * дескриптора ребра соединяющего вершины, заданные дескрипторами v1 и v2*/

 //Вспомогательные функции
    void print();//печать графа
    int getIndex(Vertex *v);//определить индекс дескриптора в векторе вершин графа
    Vertex* getVertex(int index);//получить вершину по индексу
    Vertex* getVertex(string name);//получить вершину по имени

    //итератор вершин графа
    class VertexIterator{
    private:
        Graph<Vertex, Edge> *graph; //привязанный граф
        bool end; //признак нахождения итератора в пределах графа
        int cur; //текущее положение
    public:
        VertexIterator(Graph<Vertex, Edge> &g){
            graph = &g;
            end=true;
        }

        bool begin(){
            if(graph->vertexVector.size()==0){
                end = true;
                return false;
            }
            cur = 0;
            end = false;
            return true;
        }

        bool operator++(){
            if(end) return false;
            cur++;
            if(cur == graph->vertexVector.size()-1) end = true;
            return true;
        }

        bool toEnd(){
            end = true;
            cur = graph->vertexVector.size()-1;
            if(cur<0) return false;
            return true;
        }

        bool inGraph(){ return !end;} //Возвращает true - если в графе, false - в противном случае

        Vertex* operator*(){
            if(cur>=graph->vertexVector.size()||cur<0) throw "Out of range";
            return graph->vertexVector[cur];
        }
    };

    //Итератор ребер
    class EdgeIterator{
        Graph<Vertex, Edge> *graph; //привязанный граф
        bool end;
    public:
        int curV1, curV2;

        EdgeIterator(Graph<Vertex, Edge> &g){graph = &g;}

        bool begin(){
            if(graph->vertexVector.size()==0||graph->edgeCount==0){
                end = true;
                return false;
            }
            //перебираем пары вершин пока не найдем ребро/не просмотрим все вершины
            bool k = false;
            if(graph->directed()){
                for(curV1=0;curV1<graph->vertexVector.size();curV1++){
                    for(curV2=0;curV2<graph->vertexVector.size();curV2++){
                        if(graph->data->hasEdge(curV1,curV2)) {
                            k=true;
                            break;
                        }
                    }
                    if(k) break;
                }
            } else{
                //оптимизация под неориентированный граф
                for(curV1=0;curV1<graph->vertexVector.size()-1;curV1++){
                    for(curV2=curV1+1;curV2<graph->vertexVector.size();curV2++){
                        if(graph->data->hasEdge(curV1,curV2)) {
                            k= true;
                            break;
                        }
                    }
                    if(k) break;
                }
            }
            if(graph->data->hasEdge(curV1,curV2)){
                end= false;
                return true;
            }
            end = true;
            return false;
        }

        bool operator++(){
            if(end) return false;

            bool k = false;
            if(graph->directed()){
                for(;curV1<graph->vertexVector.size();curV1++){
                    for(curV2+=1;curV2<graph->vertexVector.size();curV2++){
                        if(graph->data->hasEdge(curV1,curV2)) {
                            k=true;
                            break;
                        }
                    }
                    if(k) break;
                    curV2=-1;
                }
            } else{
                //оптимизация под неориентированный граф
                for(;curV1<graph->vertexVector.size()-1;curV1++){
                    for(curV2+=1;curV2<graph->vertexVector.size();curV2++){
                        if(graph->data->hasEdge(curV1,curV2)) {
                            k=true;
                            break;
                        }
                    }
                    if(k) break;
                    curV2=curV1+1;
                }
            }
            if (graph->data->hasEdge(curV1,curV2)){
                return true;
            } else{
                end = true;
                return false;
            };
        }

        bool toEnd(){
            end = true;
            if(graph->vertexVector.size()==0||graph->edgeCount==0){
                return false;
            }
            bool k = false;
            if(graph->directed()){
                for(curV1=graph->vertexVector.size()-1;curV1>=0;curV1--){
                    for(curV2=graph->vertexVector.size()-1;curV2>=0;curV2--){
                        if(graph->data->hasEdge(curV1,curV2)) {
                            k=true;
                            break;
                        }
                    }
                    if(k) break;
                }
            } else{
                //оптимизация под неориентированный граф
                for(curV1=graph->vertexVector.size()-1;curV1>=0;curV1--){
                    for(curV2=curV1-1;curV2>=0;curV2--){
                        if(graph->data->hasEdge(curV1,curV2)) {
                            k = true;
                            break;
                        }
                    }
                    if(k) break;
                }
            }
            return graph->data->hasEdge(curV1,curV2);
        }

        bool inGraph(){ return !end;} //Возвращает true - если в графе, false - в противном случае

        Edge* operator*(){
            if(graph->vertexVector.size()==0||graph->edgeCount==0) throw "Out of range";
            return graph->data->getEdge(curV1,curV2);
        }
    };

    //Итератор исходящих ребер
    class OuterEdgeIterator{
        Graph<Vertex, Edge> *graph; //привязанный граф
        bool end;
    public:
        int cur; //обрабатываемая вершина
        int curV2; //вершина, в которую входит ребро

        OuterEdgeIterator(Graph<Vertex, Edge> &g, Vertex &v){
            graph=&g;
            cur=graph->getIndex(&v);
        }

        OuterEdgeIterator(Graph<Vertex, Edge> &g, int index){
            graph=&g;
            cur=index;
        }

        bool begin(){
            if(graph->vertexVector.size()==0||graph->edgeCount==0){
                end = true;
                return false;
            }

            for(curV2=0;curV2<graph->vertexVector.size();curV2++){
                if(graph->data->hasEdge(cur,curV2)) break;
            }
            return graph->data->hasEdge(cur,curV2);
        }

        bool operator++(){
            if(end) return false;
            for(curV2+=1;curV2<graph->vertexVector.size();curV2++){
                if(graph->data->hasEdge(cur,curV2)) break;
            }
            return graph->data->hasEdge(cur,curV2);
        }

        bool toEnd(){
            end = true;
            if(graph->vertexVector.size()==0||graph->edgeCount==0){
                return false;
            }
            for(curV2=graph->vertexVector.size()-1;curV2>=0;curV2--){
                if(graph->data->hasEdge(cur,curV2)) break;
            }
            return graph->data->hasEdge(cur,curV2);
        }

        bool inGraph(){ return !end;} //Возвращает true - если в графе, false - в противном случае

        Edge* operator*(){
            if(graph->vertexVector.size()==0||graph->edgeCount==0) throw "Out of range";
            return graph->data->getEdge(cur,curV2);
        }
    };
};

//конструкторы
//пустой граф
template<class Vertex, class Edge> Graph<Vertex, Edge>::Graph() {
    sN = 0;
    data = new ListForm<Edge>(false);
    oriented = false;
    l_graph=true;
    edgeCount=0;
}

template<class Vertex, class Edge> Graph<Vertex, Edge>::Graph(Graph &g) {
    sN = g.sN;
    delete data;
    if(g->dense()){
        data = new MatrixForm<Edge>(*(g.data));
    } else{
        data = new ListForm<Edge>(*(g.data));
    }
    vertexVector = new vector<Vertex*>(g.vertexVector);
    oriented = g.oriented;
    l_graph=g.l_graph;
    edgeCount = g.edgeCount;
}

template<class Vertex, class Edge> Graph<Vertex, Edge>::Graph(int v_num, bool directed, bool dense) {
    sN=0;
    if(dense){
        data = new MatrixForm<Edge>(directed);
    } else{
        data = new ListForm<Edge>(directed);
    }
    //создаем вершины
    for(int i=0;i<v_num;i++){
        Vertex *v = new Vertex;
        v->setName(to_string(sN));
        sN++;
        vertexVector.push_back(v);
        data->InsertV(i);
    }
    oriented=directed;
    l_graph=!dense;
    edgeCount = 0;
}

template<class Vertex, class Edge> Graph<Vertex, Edge>::Graph(int v_num, int e_num, bool directed, bool dense){
    sN=0;
    if(dense){
        data = new MatrixForm<Edge>(directed);
    } else{
        data = new ListForm<Edge>(directed);
    }
    //создаем вершины
    for(int i=0;i<v_num;i++){
        Vertex *v = new Vertex;
        v->setName(to_string(sN));
        sN++;
        vertexVector.push_back(v);
        data->InsertV(i);
    }
    oriented=directed;
    l_graph=!dense;
    edgeCount = 0;
    //вставка ребер
    if(e_num<=0) return;
    //корректировка ребер
    if(directed){
        if(e_num > v_num*(v_num-1)){
            e_num = v_num*(v_num-1);
        }
    } else {
        if(e_num > ((v_num)*(v_num-1))/2){
            e_num = ((v_num)*(v_num-1))/2;
        }
    }

    //непосредственно вставка
    int v1, v2;
    srand((unsigned)time(NULL));
    while (edgeCount<e_num){
        v1 = rand() % v_num;
        v2 = rand() % v_num;
        //если вершины совпали или между ними уже было вставлено ребро, то переходим к следующей итерации
        if(v1 == v2) continue;
        if(data->hasEdge(v1,v2)) continue;
        Edge *e = new Edge(vertexVector[v1], vertexVector[v2]);
        data->InsertE(v1, v2, e);
        e->setW((rand()%9)+1);
        if(!directed){
            data->InsertE(v2, v1, e);
        }
        edgeCount++;
    }
}

//деструктор
template<class Vertex, class Edge> Graph<Vertex, Edge>::~Graph(){
    while (vertexVector.size()!=0){
        deleteV(0);
    }
    delete data;
}


//методы

template<class Vertex, class Edge> int Graph<Vertex, Edge>::V(){
    return vertexVector.size();
}

template<class Vertex, class Edge> int Graph<Vertex, Edge>::E(){
    return edgeCount;
}

template<class Vertex,class Edge> bool Graph<Vertex,Edge>::directed(){
    return oriented;
}

template<class Vertex,class Edge> bool Graph<Vertex,Edge>::dense(){
    return !l_graph;
}

template<class Vertex, class Edge> double Graph<Vertex, Edge>::K(){
    return (double)2*edgeCount/vertexVector.size();
}

//переход к L-графу
template<class Vertex,class Edge> bool Graph<Vertex,Edge>::toListGraph(){
    //если граф уже является L-графом, то ничего не меняем, просто возвращаем true
    if(l_graph)
        return true;
    //создаем структуру, которая заменит текущую
    GraphForm<Edge> *newData = new ListForm<Edge>(this->oriented);

    //создаем копии вершин в новой форме
    for(int i=0; i<vertexVector.size();i++){
        newData->InsertV(i);
    }

    //перенос ребер
    for(int i=0; i<vertexVector.size();i++) {
        for (int j = 0; j < vertexVector.size(); j++) {
            if (data->hasEdge(i, j)) newData->InsertE(i, j, data->getEdge(i, j));
        }
    }
    delete data;
    data = newData;
    l_graph= true;
    return true;
}

//переход к M-графу
template<class Vertex,class Edge> bool Graph<Vertex,Edge>::toMatrixGraph(){
    //создаем структуру, которая заменит текущую
    GraphForm<Edge> *newData = new MatrixForm<Edge>(this->oriented);

    //создаем вершины
    for(int i=0; i<vertexVector.size();i++){
        newData->InsertV(i);
    }
    for(int i=0; i<vertexVector.size();i++) {
        for (int j = 0; j < vertexVector.size(); j++) {
            if (data->hasEdge(i, j)) newData->InsertE(i, j, data->getEdge(i, j));
        }
    }
    delete data;
    data = newData;
    l_graph= false;
    //переносим ребра
    return true;
}
//вставка вершины в граф
template<class Vertex, class Edge> Vertex* Graph<Vertex, Edge>::insertV() {
    Vertex *v = new Vertex();
    if(!data->InsertV(vertexVector.size())){
        throw 1;
    }
    v->setName(to_string(sN));
    sN++;
    vertexVector.push_back(v);
    return v;
}


//удаление вершины по индексу
template<class Vertex,class Edge> bool Graph<Vertex,Edge>::deleteV(int index) {
    edgeCount-=data->deleteEdges(index, oriented);
    if(data->DeleteV(index)){
        vertexVector.erase(vertexVector.begin()+index);
        return true;
    }
    return false;
}


//удаление вершины по адресу дескриптора
template<class Vertex,class Edge> bool Graph<Vertex,Edge>::deleteV(Vertex *v) {
    int index = getIndex(v);
    edgeCount-=data->deleteEdges(index, oriented);
    if(data->DeleteV(index)){
        vertexVector.erase(vertexVector.begin()+index);
        return true;
    }
    return false;
}


//добавить ребро
template<class Vertex,class Edge> Edge* Graph<Vertex,Edge>::insertE(Vertex *ver1, Vertex *ver2) {
    Edge *e = new Edge(ver1, ver2);
    if(!data->InsertE(getIndex(ver1),getIndex(ver2),e)) throw "insert exception";

    if(!oriented){
        data->InsertE(getIndex(ver2),getIndex(ver1),e);
    }
    edgeCount++;
    return e;
}

//удалить ребро
template<class Vertex,class Edge> bool Graph<Vertex,Edge>::DeleteE(Vertex *v1, Vertex *v2) {
    if(data->DeleteE(getIndex(v1),getIndex(v2))){
        edgeCount--;
        if(!oriented){
            data->DeleteE(getIndex(v2), getIndex(v1));
        }
        return true;
    }
    return false;
}


//получить адрес дескриптора ребра
template<class Vertex,class Edge> Edge* Graph<Vertex,Edge>::GetEdge(Vertex *v1, Vertex *v2) {
    Edge *e;
    try{
        e = data->getEdge(getIndex(v1), getIndex(v2));
    }catch (int){
        throw "edge not found";
    }
    return e;
}


//распечатка графа
template<class Vertex,class Edge> void Graph<Vertex,Edge>::print() {
    int i,j;
    Vertex *v;
    Edge *e;

    if(dense()){
        cout<<setw(5)<< " ";
        for(i=0;i<V();i++){
            v = vertexVector[i];
            cout << setw(4)<<v->getName();
        }
        cout<<endl;
        for(i=0; i<5*V() + 4; i++)
            cout<<"_";
        cout << endl;
        for (i=0; i<V(); i++)
        {
            v=vertexVector[i];
            cout<<setw(4)<<v->getName()<<"|";
            for (j=0; j<V(); j++)
                if (data->hasEdge(i,j))
                {
                    e=data->getEdge(i,j);
                    cout<<setw(4)<<e->getW();
                }
                else
                    cout << setw(4) << "-";
            cout << endl;
        }
    }
    else
    {
        for (i=0; i<V(); i++){
            v = vertexVector[i];
            cout << v->getName() << ": ";
            for (j=0; j < V(); j++){
                v = vertexVector[j];
                if (data->hasEdge(i, j))
                    cout << v->getName() << "; ";
            }
            cout << endl;
        }
    }


}

//поиск индекса
template<class Vertex,class Edge> int Graph<Vertex,Edge>::getIndex(Vertex *v) {
    int index;
    for (index=0; index<vertexVector.size();index++){
        if(vertexVector[index]==v) break;
    }
    if(index==vertexVector.size()) throw "vertex not found";
    return index;
}

template<class Vertex,class Edge> Vertex* Graph<Vertex,Edge>::getVertex(int index) {
    if(index==vertexVector.size()) throw "vertex not found";
    return vertexVector[index];
}

template<class Vertex,class Edge> Vertex* Graph<Vertex,Edge>::getVertex(string name) {
    int index;
    for (index=0; index<vertexVector.size();index++){
        if(vertexVector[index]->getName()==name) break;
    }
    if(index==vertexVector.size()) throw "vertex not found";
    return vertexVector[index];
}

#endif