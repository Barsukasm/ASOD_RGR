//
// Created by nikolay on 20.12.18.
//

#ifndef ASOD_RGR_TASK1_H
#define ASOD_RGR_TASK1_H

#include "Graph.h"
#include <stack>

typedef Vertex<string, int> VertexSample;
typedef Edge<string, int, int> EdgeSample;
typedef Graph<VertexSample, EdgeSample> GraphSample;

template <class Graph> class Task1{
private:
    GraphSample *graph;
    vector<VertexSample*> res;
    stack<int> r;
    vector<int> color;

public:

    Task1(GraphSample &g){
        graph=&g;
        graph->toListGraph();
        color.clear();
        color.resize(graph->V());
        res.clear();
        restart();
    }

    Task1(Task1 &t){
        graph=&t.graph;
        graph->toListGraph();
        color = &t.color;
        r=&t.r;
        res=&t.res;
        restart();
    }

    void set(GraphSample &g){
        graph=&g;
        graph->toListGraph();
        res.clear();
        while(!r.empty()){
            r.pop();
        }
        color.clear();
        color.resize(graph->V());
    }

    bool restart(){
        if(!graph->directed())
            return false;
        bool cycle;
        //обход в глубину
        for(int i=0;i<graph->V();i++){
            cycle=dfs(i);
            if(cycle) return false;
        }
        //Преобразование из стека индексов вершин в упорядоченный вектор дескрипторов вершин
        while(!r.empty()){
            res.push_back(graph->getVertex(r.top()));
            r.pop();
        }
        return true;
    }

    vector<VertexSample*> result(){
        return res;
    }

private:
    bool dfs(int v){
        if(color[v]==1) return true;//Если вершина серая, то был обнаружен цикл. Завершаем обработку алгоритма.
        if(color[v]==2) return false;//Если вершина черная, то заканчиваем её обработку.
        color[v]=1;
        //Обработка смежных вершин
        GraphSample::OuterEdgeIterator *it=new GraphSample::OuterEdgeIterator(*graph,v);
        if(it->begin()){
            bool ok=true;
            while (it->inGraph()&&ok){
                if(dfs(it->curV2)) return true;
                ok=it->operator++();
            }
        }
        delete it;
        //добавление в стек и покраска
        r.push(v);
        color[v]=2;
        return false;
    }
};


#endif //ASOD_RGR_TASK1_H
