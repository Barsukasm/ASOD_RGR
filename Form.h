#include <vector>
#include <list>
#include "Graph.h"

//Абстрактный класс формы представления
using namespace std;

template <class Edge> class GraphForm{
public:
    //Вставка и удаление вершин
    virtual bool InsertV(int index) = 0;
    virtual bool DeleteV(int index) = 0;
    virtual bool InsertE(int v1, int v2, Edge *t) = 0;
    virtual bool DeleteE(int v1, int v2) = 0;
    virtual Edge* getEdge(int v1, int v2) = 0;
};


template <class Edge> class MatrixForm : public GraphForm<Edge>{
    friend class EdgeIterator;
private:
    bool directed; //флаг ориентированности

public:
    vector<vector<Edge*>> matrix; //матрица смежности

    MatrixForm(bool dir){directed=dir;}

    //Вставка вершины
    bool InsertV(int index){
        int size = matrix.size(); //Число вершин
        //Неверный номер вершины
        if (index < 0 || index > size) return false;
        //Создаём новую пустую строку
        vector<Edge*> newLine;
        newLine.assign(size, NULL);
        //Вставляем новую строку:
        matrix.insert(matrix.begin() + index, newLine);
        ++size;
        //Вставляем новый столбец:
        for (int i = 0; i < size; ++i)
            matrix[i].insert(matrix[i].begin() + index, (Edge*)NULL);
        return true;

    }


    //Удаление вершины
    bool DeleteV(int index){
        int size = matrix.size(); //Число вершин
        //Неверный номер вершины
        if (index < 0 || index >= size)
            return false;
        //Удаляем строку:
        matrix.erase(matrix.begin() + index);
        --size;
        //Удаляем столбец:
        for (int i = 0; i < size; i++)
            matrix[i].erase(matrix[i].begin() + index);
        return true;

    }

    //Вставка ребра
    bool InsertE(int v1, int v2, Edge *t){
        int size = matrix.size(); //Число вершин
        //Неверный номер вершины
        if (v1 < 0 || v2 < 0 || v1 >= size || v2 >= size) return false;
        //Петля или ребро уже есть
        if (v1 == v2 || matrix[v1][v2] != NULL) return false;
        //Вставляем ребро
        matrix[v1][v2] = t;
        return true;
    }

    //Удаление ребра
    bool DeleteE(int v1, int v2){
        int size = matrix.size(); //Число вершин
        //Неверный номер вершины
        if (v1 < 0 || v2 < 0 || v1 >= size || v2 >= size) return false;
        //Ребра нет
        if (v1 == v2 || matrix[v1][v2] == NULL) return false;
        matrix[v1][v2] = NULL;
        return true;
    }

    //Получение адреса дескриптора ребра
    Edge* getEdge(int v1, int v2)
    {
        int size = matrix.size(); //Число вершин
        //Неверный номер вершины
        if (v1 < 0 || v2 < 0 || v1 >= size || v2 >= size)
            throw 1;
        if (v1 == v2 || matrix[v1][v2] == NULL)//Петля
            throw 1;
        return matrix[v1][v2];
    }

};

template <class Edge> class ListForm : public GraphForm<Edge>{
    class Node{
    public:
        Edge *edge; //ребро
        int v2; //номер вершины
    };
    bool directed;
    vector<list<Node>> adjList;//списки смежности

public:
    ListForm(bool dir){directed=dir;}

    //Вставка вершины
    bool InsertV(int index){
        int size = adjList.size(); //Число вершин
        if (index < 0 || index > size) //Неверный номер вершины
            return false;
        //Создаём новый список смежности
        list<Node> newList;
        //Вставляем
        adjList.insert(adjList.begin() + index, newList);
        ++size;
        //Обновляем дескрипторы
        for (int i = 0; i < size; ++i)
            for (typename list<Node>::iterator j = adjList[i].begin(); j != adjList[i].end(); ++j)
                if ((*j).v2 >= index)//если текущая вершина имеет больший номер, чем вставляемая,
                    ++((*j).v2);//то увеличиваем этот номер
        return true;
    }

    //Удаление вершины
    bool DeleteV(int index){
        int size = adjList.size(); //Число вершин
        if (index < 0 || index >= size)  //Неверный номер вершины
            return false;
        //Удаляем из списков записи о рёбрах
        for (int i = 0; i < size; ++i)
            for (typename list<Node>::iterator j = adjList[i].begin(); j != adjList[i].end(); ++j)
                if ((*j).v2 == index)
                {
                    adjList[i].erase(j);
                    break;
                }
        //Удаляем список смежности
        adjList.erase(adjList.begin() + index);//
        --size;//
        //Обновляем дескрипторы
        for (int i = 0; i < size; ++i)//
            for (typename list<Node>::iterator j = adjList[i].begin(); j != adjList[i].end(); ++j)//
                if ((*j).v2 > index)//если текущая вершина имеет больший номер, чем удаляемая,//
                    --((*j).v2);//то уменьшить этот номер//
        return true;
    }

    //Вставка ребра
    bool InsertE(int v1, int v2, Edge *t){
        int size = adjList.size(); //Число вершин
        if (v1 < 0 || v2 < 0 || v1 >= size || v2 >= size)//Неверный номер вершины
            return false;
        if (v1 == v2 || adjList(v1, v2))  //Петля или ребро уже есть
            return false;
        //Вставляем ребро
        Node node;
        node.edge = t;
        node.v2 = v2;
        adjList[v1].push_front(node);
        return true;
    }

    //Удаление ребра
    bool DeleteE(int v1, int v2){
        int size = adjList.size(); //Число вершин
        //Неверный номер вершины
        if (v1 < 0 || v2 < 0 || v1 >= size || v2 >= size)
            return false;
        //Ребра нет
        if (v1 == v2 || adjList(v1, v2) == false)
            return false;
        //Удаляем ребро
        for (typename list<Node>::iterator j = adjList[v1].begin(); j != adjList[v1].end(); ++j)
            if ((*j).v2 == v2) {
                adjList[v1].erase(j);
                break;
            }
        return true;
    }

    //Получение дескриптора ребра
    Edge* getEdge(int v1, int v2)
    {
        int size = adjList.size(); //Число вершин
        //Неверный номер вершины
        if (v1 < 0 || v2 < 0 || v1 >= size || v2 >= size)
            throw 1;
        //Петля
        if (v1 == v2)
            throw 1;
        for (typename list<Node>::iterator j = adjList[v1].begin(); j != adjList[v1].end(); ++j)
            if ((*j).v2 == v2)
                return (*j).edge;
        throw 1;
    }

};