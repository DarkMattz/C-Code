#include <stdio.h>
#include <stdlib.h>


struct Edge{
    int src, dest;
};

struct Graph{
    int vertices, totalEdges;

    Edge *edge;
};

Graph *createGraph(int vertices, int totalEdges){
    Graph *temp = (Graph *) malloc(sizeof(Graph));
    temp->totalEdges = totalEdges;
    temp->vertices = vertices;
    
    temp->edge = (Edge *) malloc(sizeof(Edge) * totalEdges);

    return temp;
}

int find(int parent[], int i){
    if(parent[i] == -1){
        return i;
    } else {
        return find(parent, parent[i]);
    }
}

bool isCycle(Graph *graph){
    int parent[graph->vertices];

    for(int i = 0; i < graph->vertices; i++){
        parent[i] = -1;
    }

    for(int i = 0; i < graph->totalEdges; i++){
        int srcParent = find(parent, graph->edge[i].src);
        int destParent = find(parent, graph->edge[i].dest);

        if(srcParent == destParent){
            return true;
        } else {
            parent[srcParent] = destParent;
        }

    }

    return false;
}

int main(){
    int vetices = 4;
    int totalEdges = 4;

    Graph *graph = createGraph(vetices, totalEdges);

    graph->edge[0].src = 0;
    graph->edge[0].dest = 1;

    graph->edge[1].src = 1;
    graph->edge[1].dest = 2;

    graph->edge[2].src = 2;
    graph->edge[2].dest = 3;

    graph->edge[3].src = 3;
    graph->edge[3].dest = 4;

    if(isCycle(graph)){
        printf("Graf siklik");
    } else {
        printf("Graf nonsiklik");
    }

}