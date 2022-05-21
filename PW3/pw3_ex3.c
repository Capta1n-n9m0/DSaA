#include <stdlib.h>
#include <stdio.h>

typedef struct queue_node_ {
    int data;
    struct queue_node_ *next;
} queue_node;

typedef struct queue_ {
    queue_node *rear, *front;
} queue;


queue create_queue() {
    queue res;
    res.front = NULL;
    res.rear = NULL;
    return res;
}

void push_to_queue(queue *q, int item) {
    queue_node *n = calloc(1, sizeof(queue_node));
    n->data = item;
    n->next = NULL;
    if ((q->rear == NULL) && (q->front == NULL)) {
        q->rear = n;
        q->front = n;
        q->rear->next = q->front;
    } else {
        q->rear->next = n;
        q->rear = n;
        n->next = q->front;
    }
}

int pop_from_queue(queue *q) {
    queue_node *t;
    int res;
    t = q->front;
    if ((q->front == NULL) && (q->rear == NULL)) {
        fprintf(stderr, "Reading from empty queue.\n");
        exit(2);
    } else if (q->rear == q->front) {
        res = t->data;
        q->front = NULL;
        q->rear = NULL;
        free(t);
    } else {
        res = t->data;
        q->front = q->front->next;
        q->rear->next = q->front;
        free(t);
    }
    return res;
}

void print_queue(queue q) {
    queue_node *t;
    t = q.front;
    printf("[ ");
    if (!((q.front == NULL) && (q.rear == NULL))) {
        do {
            printf("%d ", t->data);
            t = t->next;
        } while (t != q.front);
    }
    printf("]");
}

void print_named_queue(queue q, const char *name) {
    printf("%s: ", name);
    print_queue(q);
    puts("");
}

int main() {
    queue q1 = create_queue();
    queue q2 = create_queue();
    int data1, data2;
    print_named_queue(q1, "q1");
    print_named_queue(q2, "q2");
    for (int i = 0; i < 10; ++i) {
        push_to_queue(&q1, 10 + i);
        push_to_queue(&q2, 20 + i);
        print_named_queue(q1, "q1");
        print_named_queue(q2, "q2");
        puts("");
    }
    print_named_queue(q1, "q1");
    print_named_queue(q2, "q2");
    for(int i = 0; i < 10; ++i){
        data1 = pop_from_queue(&q1);
        data2 = pop_from_queue(&q2);
        print_named_queue(q1, "q1");
        printf("popped from q1: %d\n", data1);
        print_named_queue(q2, "q2");
        printf("popped from q2: %d\n", data2);
        puts("");
    }
    print_named_queue(q1, "q1");
    print_named_queue(q2, "q2");
}











