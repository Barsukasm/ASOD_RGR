#include "Graph.h"
#include <iostream>
#include "Task1.h"

typedef Vertex<string, int> VertexSample;
typedef Edge<string, int, int> EdgeSample;
typedef Graph<VertexSample, EdgeSample> GraphSample;

using namespace std;

void draw_menu(){
    cout<<"Graph creation"<<endl;
    cout<<"1. Create empty L-graph"<<endl;
    cout<<"2. Create custom graph without edges"<<endl;
    cout<<"3. Create fully custom graph"<<endl;
    cout<<endl;
    cout<<"Graph manipulation"<<endl;
    cout<<"4. Print graph"<<endl;
    cout<<"5. Vertex count"<<endl;
    cout<<"6. Edge count"<<endl;
    cout<<"7. Is dense?"<<endl;
    cout<<"8. Is directed"<<endl;
    cout<<"9. Density coefficient"<<endl;
    cout<<"10. To L-form"<<endl;
    cout<<"11. To M-form"<<endl;
    cout<<"12. Add vertex"<<endl;
    cout<<"13. Delete vertex"<<endl;
    cout<<"14. Add edge"<<endl;
    cout<<"15. Delete edge"<<endl;
    cout<<endl;
    cout<<"Vertex manipulation"<<endl;
    cout<<"16. Read vertex data"<<endl;
    cout<<"17. Write vertex data"<<endl;
    cout<<"18. Rewrite vertex name"<<endl;
    cout<<endl;
    cout<<"Edge manipulation"<<endl;
    cout<<"19. Read edge weight"<<endl;
    cout<<"20. Write edge weight"<<endl;
    cout<<"21. Read edge data"<<endl;
    cout<<"22. Write edge data"<<endl;
    cout<<endl;
    cout<<"Vertex iterator"<<endl;
    cout<<"23. To first vertex"<<endl;
    cout<<"24. To last vertex"<<endl;
    cout<<"25. Next vertex"<<endl;
    cout<<"26. Read data"<<endl;
    cout<<"27. Change data"<<endl;
    cout<<"28. Show vertex name"<<endl;
    cout<<"29. Rewrite vertex name"<<endl;
    cout<<endl;
    cout<<"Edge iterator"<<endl;
    cout<<"30. To first edge"<<endl;
    cout<<"31. To last edge"<<endl;
    cout<<"32. Next edge"<<endl;
    cout<<"33. Read data"<<endl;
    cout<<"34. Change data"<<endl;
    cout<<"35. Show edge weight"<<endl;
    cout<<"36. Rewrite edge weight"<<endl;
    cout<<"37. Show edge ends"<<endl;
    cout<<endl;
    cout<<"Outer edges iterator"<<endl;
    cout<<"38. Create iterator"<<endl;
    cout<<"39. To first edge"<<endl;
    cout<<"40. To last edge"<<endl;
    cout<<"41. Next edge"<<endl;
    cout<<"42. Read data"<<endl;
    cout<<"43. Change data"<<endl;
    cout<<"44. Show edge weight"<<endl;
    cout<<"45. Rewrite edge weight"<<endl;
    cout<<"46. Show edge ends"<<endl;
    cout<<endl;
    cout<<"47. GetEdge()"<<endl;
    cout<<"48. Task 1"<<endl;
    cout<<"49. Task 2 (WIP)"<<endl; //in progress
    cout<<"0. Exit"<<endl;
}

void clearGraph(GraphSample *&graph, GraphSample::VertexIterator *&vIt, GraphSample::EdgeIterator *&eIt, GraphSample::OuterEdgeIterator *&oIt){
    delete graph;
    delete vIt;
    delete eIt;
    delete oIt;
    graph = NULL;
    vIt = NULL;
    eIt = NULL;
    oIt = NULL;
}

int main() {
    GraphSample *graph = NULL;
    GraphSample::VertexIterator *vIt=NULL;
    GraphSample::EdgeIterator *eIt=NULL;
    GraphSample::OuterEdgeIterator *oIt=NULL;
    Task1<GraphSample> *tsk=NULL;

    bool exit=false;
    int choice;
    draw_menu();
    while (!exit){
        cin>>choice;
        if(graph==NULL&&choice>3&&choice<=49){
            cout<<"Graph does not initialised"<<endl;
            continue;
        }
        if(oIt==NULL&&choice>38&&choice<=46){
            cout<<"Outer iterator does not initialised"<<endl;
            continue;
        }
        switch (choice){
            //создание графа
            case 1:{
                clearGraph(graph,vIt,eIt,oIt);
                graph=new GraphSample();
                vIt=new GraphSample::VertexIterator(*graph);
                eIt=new GraphSample::EdgeIterator(*graph);
                //cout<<"Created"<<endl;
                break;
            }
            case 2:{
                int v_num;
                bool dense, directed;
                cout<<"Vertex amount:"<<endl;
                cin>>v_num;
                cout<<"Dense? (1 - true, 2 - false)"<<endl;
                int ch=0;
                while(ch!=1&&ch!=2){
                    cin>>ch;
                    if(ch!=1&&ch!=2){
                        cout<<"Incorrect answer"<<endl;
                    }
                }
                if(ch == 1) {dense=true;}
                else { dense= false;}
                cout<<"Directed? (1 - true, 2 - false)"<<endl;
                ch=0;
                while(ch!=1&&ch!=2){
                    cin>>ch;
                    if(ch!=1&&ch!=2){
                        cout<<"Incorrect answer"<<endl;
                    }
                }
                if(ch == 1) {directed=true;}
                else { directed= false;}
                clearGraph(graph,vIt,eIt,oIt);
                graph=new GraphSample(v_num,directed,dense);
                vIt=new GraphSample::VertexIterator(*graph);
                eIt=new GraphSample::EdgeIterator(*graph);
                //cout<<"Created"<<endl;
                break;
            }
            case 3:{
                int v_num, e_num;
                bool dense, directed;
                cout<<"Vertex amount:"<<endl;
                cin>>v_num;
                cout<<"Edges amount:"<<endl;
                cin>>e_num;
                cout<<"Dense? (1 - true, 2 - false)"<<endl;
                int ch=0;
                while(ch!=1&&ch!=2){
                    cin>>ch;
                    if(ch!=1&&ch!=2){
                        cout<<"Incorrect answer"<<endl;
                    }
                }
                if(ch == 1) {dense=true;}
                else { dense= false;}
                cout<<"Directed? (1 - true, 2 - false)"<<endl;
                ch=0;
                while(ch!=1&&ch!=2){
                    cin>>ch;
                    if(ch!=1&&ch!=2){
                        cout<<"Incorrect answer"<<endl;
                    }
                }
                if(ch == 1) {directed=true;}
                else { directed= false;}
                clearGraph(graph,vIt,eIt,oIt);
                graph=new GraphSample(v_num,e_num,directed,dense);
                vIt=new GraphSample::VertexIterator(*graph);
                eIt=new GraphSample::EdgeIterator(*graph);
                //cout<<"Created"<<endl;
                break;
            }

            //общие операции над графом
            case 4:{
                graph->print();
                break;
            }

            case 5:{
                cout<<graph->V()<<endl;
                break;
            }

            case 6:{
                cout<<graph->E()<<endl;
                break;
            }

            case 7:{
                cout<<graph->dense()<<endl;
                break;
            }

            case 8:{
                cout<<graph->directed()<<endl;
                break;
            }

            case 9:{
                cout<<graph->K()<<endl;
                break;
            }

            case 10:{
                cout<<graph->toListGraph()<<endl;
                break;
            }

            case 11:{
                cout<<graph->toMatrixGraph()<<endl;
                break;
            }

            case 12:{
                if(graph->insertV()) /*cout<<"done"<<endl*/;
                else cout<<"error"<<endl;
                break;
            }

            case 13:{
                cout<<"Insert vertex name:"<<endl;
                string name;
                cin>>name;
                cout<<graph->deleteV(graph->getVertex(name))<<endl;
                break;
            }

            case 14:{
                string v1, v2;
                cout<<"Insert vertex from:"<<endl;
                cin>>v1;
                cout<<"Insert vertex to:"<<endl;
                cin>>v2;
                try {
                    graph->insertE(graph->getVertex(v1), graph->getVertex(v2));
                    //cout<<"done"<<endl;
                }catch (...){
                    cout<<"error"<<endl;
                }
                break;
            }

            case 15:{
                string v1, v2;
                cout<<"Insert vertex from:"<<endl;
                cin>>v1;
                cout<<"Insert vertex to:"<<endl;
                cin>>v2;
                try {
                    graph->DeleteE(graph->getVertex(v1), graph->getVertex(v2));
                    //cout<<"done"<<endl;
                }catch (...){
                    cout<<"error"<<endl;
                }
                break;
            }

            //работа с вершинами
            case 16:{
                cout<<"Insert vertex name:"<<endl;
                string str;
                cin>>str;
                try {
                    cout<<graph->getVertex(str)->getData()<<endl;
                }catch (...){
                    cout<<"Vertex not found"<<endl;
                }
                break;
            }

            case 17:{
                string v;
                int data;
                cout<<"Insert vertex name:"<<endl;
                cin>>v;
                cout<<"Insert new data:"<<endl;
                cin>>data;
                try {
                    graph->getVertex(v)->setData(data);
                    //cout<<"done"<<endl;
                }catch (...){
                    cout<<"Vertex not found"<<endl;
                }
                break;
            }

            case 18:{
                string v, name;
                cout<<"Insert vertex name:"<<endl;
                cin>>v;
                cout<<"Insert new name:"<<endl;
                cin>>name;
                try {
                    graph->getVertex(v)->setName(name);
                    //cout<<"done"<<endl;
                }catch (...){
                    cout<<"Vertex not found"<<endl;
                }
                break;
            }

            //манипуляции с ребрами
            case 19:{
                string v1, v2;
                cout<<"Insert vertex from:"<<endl;
                cin>>v1;
                cout<<"Insert vertex to:"<<endl;
                cin>>v2;
                try {
                    cout<<graph->GetEdge(graph->getVertex(v1),graph->getVertex(v2))->getW()<<endl;
                }catch (...){
                    cout<<"Edge not found"<<endl;
                }
                break;
            }

            case 20:{
                string v1, v2;
                cout<<"Insert vertex from:"<<endl;
                cin>>v1;
                cout<<"Insert vertex to:"<<endl;
                cin>>v2;
                cout<<"Insert new weight:"<<endl;
                int w;
                cin>>w;
                try {
                    graph->GetEdge(graph->getVertex(v1),graph->getVertex(v2))->setW(w);
                    //cout<<"done"<<endl;
                }catch (...){
                    cout<<"Edge not found"<<endl;
                }
                break;
            }

            case 21:{
                string v1, v2;
                cout<<"Insert vertex from:"<<endl;
                cin>>v1;
                cout<<"Insert vertex to:"<<endl;
                cin>>v2;
                try {
                    cout<<graph->GetEdge(graph->getVertex(v1),graph->getVertex(v2))->getData()<<endl;
                }catch (...){
                    cout<<"Edge not found"<<endl;
                }
                break;
            }

            case 22:{
                string v1, v2;
                cout<<"Insert vertex from:"<<endl;
                cin>>v1;
                cout<<"Insert vertex to:"<<endl;
                cin>>v2;
                cout<<"Insert new data:"<<endl;
                int data;
                cin>>data;
                try {
                    graph->GetEdge(graph->getVertex(v1),graph->getVertex(v2))->setData(data);
                    //cout<<"done"<<endl;
                }catch (...){
                    cout<<"Edge not found"<<endl;
                }
                break;
            }

            //итератор вершин
            case 23:{
                cout<<vIt->begin()<<endl;
                break;
            }

            case 24:{
                cout<<vIt->toEnd()<<endl;
                break;
            }

            case 25:{
                cout<<vIt->operator++()<<endl;
                break;
            }

            case 26:{
                try {
                    cout<<vIt->operator*()->getData()<<endl;
                }catch (...){
                    cout<<"Out of range"<<endl;
                }
                break;
            }

            case 27:{
                int data;
                cout<<"Insert new data:"<<endl;
                cin>>data;
                try {
                    vIt->operator*()->setData(data);
                }catch (...){
                    cout<<"Out of range"<<endl;
                }
                break;
            }

            case 28:{
                try {
                    cout<<vIt->operator*()->getName()<<endl;
                }catch (...){
                    cout<<"Out of range"<<endl;
                }
                break;
            }

            case 29:{
                string name;
                cout<<"Insert new name:"<<endl;
                cin>>name;
                try {
                    vIt->operator*()->setName(name);
                }catch (...){
                    cout<<"Out of range"<<endl;
                }
                break;
            }

            //Итератор ребер
            case 30:{
                cout<<eIt->begin()<<endl;
                break;
            }

            case 31:{
                cout<<eIt->toEnd()<<endl;
                break;
            }

            case 32:{
                cout<<eIt->operator++()<<endl;
                break;
            }

            case 33:{
                try {
                    cout<<eIt->operator*()->getData()<<endl;
                }catch (...){
                    cout<<"Out of range"<<endl;
                }
                break;
            }

            case 34:{
                int data;
                cout<<"Insert new data:"<<endl;
                cin>>data;
                try {
                    eIt->operator*()->setData(data);
                }catch (...){
                    cout<<"Out of range"<<endl;
                }
                break;
            }

            case 35:{
                try {
                    cout<<eIt->operator*()->getW()<<endl;
                }catch (...){
                    cout<<"Out of range"<<endl;
                }
                break;
            }

            case 36:{
                int weight;
                cout<<"Insert new weight:"<<endl;
                cin>>weight;
                try {
                    eIt->operator*()->setW(weight);
                }catch (...){
                    cout<<"Out of range"<<endl;
                }
                break;
            }

            case 37:{
                try {
                    cout<<eIt->operator*()->V1()->getName()<<" - "<<eIt->operator*()->V2()->getName()<<endl;
                }catch (...){
                    cout<<"Out of range"<<endl;
                }
                break;
            }

            //Итератор исходящих вершин

            case 38:{
                string v1;
                delete oIt;
                oIt = NULL;
                cout<<"Input name of vertex, whose outer edges you want to iterate:"<<endl;
                cin>>v1;
                oIt=new GraphSample::OuterEdgeIterator(*graph,*graph->getVertex(v1));
                break;
            }

            case 39:{
                cout<<oIt->begin()<<endl;
                break;
            }

            case 40:{
                cout<<oIt->toEnd()<<endl;
                break;
            }

            case 41:{
                cout<<oIt->operator++()<<endl;
                break;
            }

            case 42:{
                try {
                    cout<<oIt->operator*()->getData()<<endl;
                }catch (...){
                    cout<<"Out of range"<<endl;
                }
                break;
            }

            case 43:{
                int data;
                cout<<"Insert new data:"<<endl;
                cin>>data;
                try {
                    oIt->operator*()->setData(data);
                }catch (...){
                    cout<<"Out of range"<<endl;
                }
                break;
            }

            case 44:{
                try {
                    cout<<oIt->operator*()->getW()<<endl;
                }catch (...){
                    cout<<"Out of range"<<endl;
                }
                break;
            }

            case 45:{
                int weight;
                cout<<"Insert new weight:"<<endl;
                cin>>weight;
                try {
                    oIt->operator*()->setW(weight);
                }catch (...){
                    cout<<"Out of range"<<endl;
                }
                break;
            }

            case 46:{
                try {
                    cout<<oIt->operator*()->V1()->getName()<<" - "<<oIt->operator*()->V2()->getName()<<endl;
                }catch (...){
                    cout<<"Out of range"<<endl;
                }
                break;
            }




            case 47:{
                string v1, v2;
                cout<<"Insert vertex from:"<<endl;
                cin>>v1;
                cout<<"Insert vertex to:"<<endl;
                cin>>v2;
                try {
                    if(graph->GetEdge(graph->getVertex(v1),graph->getVertex(v2))) cout<< true<<endl;
                    else cout<< false<<endl;
                    //cout<<"done"<<endl;
                }catch (...){
                    cout<<"Edge not found"<<endl;
                }
                break;
            }

                //Индивидуальные задания (в процессе)

            case 48:{
                tsk=new Task1<GraphSample>(*graph);
                vector<VertexSample*> res=tsk->result();
                if(tsk->restart()){
                    for(int i=0;i<res.size();i++){
                        cout<<res[i]->getName();
                        if(i<res.size()-1) cout<<" -> ";
                    }
                } else cout<<false;
                cout<<endl;
                break;
            }

            case 0:{
                exit= true;
                break;
            }
            case -1:{
                draw_menu();
                break;
            }
            default:{
                cout<<"Wrong command. To see list of available commands type -1."<<endl;
                break;
            }
        }
    }
    clearGraph(graph,vIt,eIt,oIt);
    return 0;
}