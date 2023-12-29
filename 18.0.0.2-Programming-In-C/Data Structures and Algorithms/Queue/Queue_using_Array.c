#include <stdio.h>
#include <stdlib.h>

struct queue{
    int size;
    int f;
    int r;
    int *arr;
};

int isEmpty(struct queue* q){
    if(q->r == q->f){
        return 1;
    }
    return 0;
}

int isFull(struct queue* q){
    if(q->r == q->size-1){
        return 1;
    }
    return 0;
}

//INSERTION || PUSH
void enqueue(struct queue *q, int value){
    if(isFull(q)){
        printf("Queue is Full \n");
    }
    else{
        q->r++;
        q->arr[q->r] = value; // arr[rear] = value
        printf("Enqued element: %d\n", value);
    }
}

int dequeue(struct queue *q){
    int a = -1;
    if(isEmpty(q)){
        printf("Queue is empty \n");
    }
    else{
        q->f++;
        a = q->arr[q->f];
    }
    return a;
}


int main(){
    struct queue q;

    q.size = 4;
    q.f = q.r = 0;
    q.arr = (int*) malloc(q.size * sizeof(int));

    enqueue(&q, 10);
    enqueue(&q, 20);
    enqueue(&q, 30);

    printf("Dequeueing element %d\n",dequeue(&q));
    printf("Dequeueing element %d\n",dequeue(&q));
    printf("Dequeueing element %d\n",dequeue(&q));

    enqueue(&q, 40);
    enqueue(&q, 50);
    enqueue(&q, 60);

    if(isEmpty(&q)){
        printf("Queue is Empty\n");
    }
    if(isFull(&q)){
        printf("Queue is Full\n");
    }

    return 0;
}