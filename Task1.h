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
    stack<VertexSample> *res;

public:

    Task1(GraphSample &g){
        graph=&g;
        restart();
    }

    Task1(Task1 &t){
        graph=&t.graph;
    }

    void set(GraphSample &g){
        graph=&g;
    }

    void restart(){

    }

    stack<VertexSample>* result(){
        return res;
    }
};


#endif //ASOD_RGR_TASK1_H
