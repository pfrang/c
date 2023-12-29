#include <stdio.h>
#include <stdlib.h>

#define SIZE 10

struct queue{
    int items[SIZE];
    int front;
    int rear;
};

struct queue* createQueue();
void enqueue(struct queue*q, int);
int dequeue(struct queue*q);
int isEmpty(struct queue*q);
void printQueue(struct queue*q);

//CREATING A GRAPH NODE/VERTEX 
struct node{
    int data;
    struct node* next;
};

struct node* createNode(int);

struct Graph{
    int numVertices;
    struct node** adjList;
    int* visited;
};

void BFS(struct Graph* graph, int source){
    struct queue*q = createQueue();
    graph->visited[source] = 1;
    enqueue(q,source);

    while(!isEmpty(q)){
        printQueue(q);
        int currentNode = dequeue(q);
        printf("Visited Node is: %d\n", currentNode);
        struct node* temp = graph->adjList[currentNode];
        while(temp){
            int adjVertex = temp->data;
            if(graph->visited[adjVertex] == 0){
                graph->visited[adjVertex] = 1;
                enqueue(q,adjVertex);
            }
            temp = temp->next;
        }
    }
}

struct node* createNode(int v){
    struct node*newnode = malloc(sizeof(struct node));
    newnode->data = v;
    newnode->next = NULL;
    return newnode;
}

struct Graph* createGraph(int vertices){
    struct Graph* graph = malloc(sizeof(struct Graph));
    graph->numVertices = vertices;
    graph->adjList = malloc(vertices* sizeof(struct node*));
    graph->visited = malloc(vertices* sizeof(int));
    int i;
    for(i=0;i<vertices;i++){
        graph->adjList[i] = NULL;
        graph->visited[i] = 0;
    }
    return graph;
}

void AddEdge(struct Graph* graph, int source, int destination){
    struct node* newnode = createNode(destination);
    newnode->next = graph->adjList[source];
    graph->adjList[source] = newnode;

    newnode = createNode(source);
    newnode->next = graph->adjList[destination];
    graph->adjList[destination] = newnode;
}

struct queue* createQueue(){
    struct queue* q = malloc(sizeof(struct queue));
    q->front = -1;
    q->rear = -1;
    return q;
}

int isEmpty(struct queue*q){
    if(q->rear == -1){
        return 1;
    }
    else{
        return 0;
    }
}

void enqueue(struct queue*q, int value){
    if(q->rear == SIZE-1){
        printf("Queue is Full\n");
    }
    else{
        if(q->front == -1){
            q->front = 0;
        }
        q->rear++;
        q->items[q->rear] == value;
    }
}

int dequeue(struct queue *q){
    int item;
    if(isEmpty(q)){
        printf("Queue is empty\n");
        item = -1;
    }
    else{
        item = q->items[q->front];
        q->front++;
        if(q->front > q->rear){
            printf("Resetting the Queue\n");
            q->front = q->rear = -1;
        }
    }
    return item;
}

void printQueue(struct queue*q){
    int i = q->front;
    if(isEmpty(q)){
        printf("Queue is empty\n");
    }
    else{
        printf("Queue contains: \n");
        for(i=q->front; i<q->rear+1; i++){
            printf("%d ", q->items[i]);
        }
    }
}

int main(){
    struct Graph* graph = createGraph(6);
    AddEdge(graph, 0, 1);
    AddEdge(graph, 0, 2);
    AddEdge(graph, 1, 2);
    AddEdge(graph, 1, 4);
    AddEdge(graph, 1, 3);
    AddEdge(graph, 2, 4);
    AddEdge(graph, 3, 4);

    BFS(graph,0);

    return 0;
}