#include "Graph.h"
#include <iostream>

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
    cout<<"47. Task 1"<<endl; //in progress
    cout<<"48. Task 2"<<endl; //in progress
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

    bool exit=false;
    int choice;
    draw_menu();
    while (!exit){
        cin>>choice;
        if(graph==NULL&&choice>3&&choice<=48){
            cout<<"Graph does not initialised"<<endl;
            continue;
        }
        if(oIt==NULL&&choice>=38&&choice<=48){
            cout<<"Outer iterator does not initialised"<<endl;
            continue;
        }
        switch (choice){
            case 1:{
                clearGraph(graph,vIt,eIt,oIt);
                graph=new GraphSample();
                vIt=new GraphSample::VertexIterator(*graph);
                eIt=new GraphSample::EdgeIterator(*graph);
                cout<<"Created"<<endl;
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
                cout<<"Created"<<endl;
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
                cout<<"Created"<<endl;
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

    return 0;
}