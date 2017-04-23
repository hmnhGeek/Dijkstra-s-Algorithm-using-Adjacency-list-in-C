#include<stdio.h>
#include<stdlib.h>
#define INF 32767

typedef struct edge_node{
    int vertexIndex;
    int dist;
    struct edge_node *next;
}edge;

typedef struct vertex_node{
    int data;
    struct edge_node *next;
}vertex;

vertex graph[10];
int vertexCount = 0;

void insert(int item){
    graph[vertexCount].data = item;
    graph[vertexCount].next = NULL;
    vertexCount +=1;
}

void connect(int vertex1, int vertex2, int distance){
    edge *temp, *edge1, *edge2, *last_temp;

    temp = graph[vertex1].next;
    last_temp = NULL;

    edge1 = (edge *)malloc(sizeof(edge));
    edge1 -> vertexIndex = vertex2;
    edge1 -> dist = distance;
    edge1 -> next = NULL;

    while(temp != NULL){
        last_temp = temp;
        temp = temp -> next;
    }

    if(temp == NULL && last_temp == NULL){
        graph[vertex1].next = edge1;
    }
    else{
        last_temp -> next = edge1;
    }

    temp = graph[vertex2].next;
    last_temp = NULL;

    edge2 = (edge *)malloc(sizeof(edge));
    edge2 -> vertexIndex = vertex1;
    edge2 -> dist = distance;
    edge2 -> next = NULL;

    while(temp != NULL){
        last_temp = temp;
        temp = temp -> next;
    }

    if(temp == NULL && last_temp == NULL){
        graph[vertex2].next = edge2;
    }
    else{
        last_temp -> next = edge2;
    }
}

void print(){
    int i = 0;
    for(i; i<vertexCount; i+=1){
        edge *temp;
        temp = graph[i].next;
        printf("%d(%d)", i, graph[i].data);

        while(temp != NULL){
            printf("-> %d", temp -> vertexIndex);
            temp = temp -> next;
        }
        printf("\n");
    }
}

int edgebw(int u, int v){
    edge *temp = graph[u].next;

    while(temp != NULL){
        if(temp -> vertexIndex == v){
            return temp -> dist;
        }
        temp = temp -> next;
    }
}

int minNode(int dist[], int sptset[]){
    int min = INF;
    int min_index;
    int i = 0;
    for(i; i<vertexCount; i+=1){
        if(sptset[i] == 0 && dist[i] <= min){
            min = dist[i];
            min_index = i;
        }
    }
    return min_index;
}

void printSol(int dist[], int limit){
    int i = 0;
    for(i; i<limit; i+=1){
        printf("%d \t\t %d\n", i, dist[i]);
    }
}

void dijkstra(int source){
    int dist[vertexCount];
    int sptset[vertexCount];

    // Initialise with infinite distance. //
    int i = 0;
    for(i; i<vertexCount; i+=1){
        dist[i] = INF;
        sptset[i] = 0;
    }
    dist[source] = 0;
    sptset[i] = 0;

    // Travrerse the graph. //
    int count = 0;
    int u;
    for(count; count < vertexCount; count +=1){
        u = minNode(dist, sptset);

        sptset[u] = 1;

        int v = 0;
        for(v; v<vertexCount; v+=1){
            if(!sptset[v] && edgebw(u, v) && dist[u] != INF && dist[v] > dist[u] + edgebw(u, v)){
                dist[v] = dist[u] + edgebw(u, v);
            }
        }
    }
    printSol(dist, vertexCount);
}

void main(){
    insert(1);
    insert(2);
    insert(3);
    insert(4);
    insert(5);

    connect(0, 1, 1);
    connect(1, 2, 10);
    connect(2, 3, 11);
    connect(3, 4, 6);
    connect(4, 0, 2);
    connect(4, 1, 5);

    dijkstra(0);

}
