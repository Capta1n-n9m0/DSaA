#include <stdlib.h>
#include <stdio.h>

typedef struct queue_node_{
    int data;
    struct queue_node_ *next;
}queue_node;

typedef struct queue_{
    queue_node *rear, *front;
}queue;


queue create_queue(){
    queue res;
    res.front = NULL; res.rear = NULL;
    return res;
}

void push(queue *q, int item){
    queue_node *n = calloc(1, sizeof(queue_node));
    n->data = item;
    n->next = NULL;
    if((q->rear == NULL) && (q->front == NULL)){
        q->rear = n;
        q->front = n;
        q->rear->next = q->front;
    } else{
        q->rear->next = n;
        q->rear = n;
        n->next = q->front;
    }
}

int pop(queue *q){
    queue_node *t;
    int res;
    t = q->front;
    if((q->front == NULL) && (q->rear == NULL)){
        fprintf(stderr, "Reading from empty queue.\n");
        exit(2);
    } else if(q->rear == q->front){
        q->front = NULL;
        q->rear = NULL;
        free(t);
    }
}
