#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


typedef int stack_datatype;

typedef struct stack_node_{
    stack_datatype data;
    struct stack_node_ *next;
}stack_node;

static void error(const char *msg){
    fprintf(stderr, "%s\n", msg);
    exit(2);
}

stack_node *stack_push(stack_node *stackNode, stack_datatype *data){
    stack_node *res = calloc(1, sizeof(stack_node));
    res->next = stackNode;
    res->data = *data;
    return res;
}

stack_node *stack_pop(stack_node *stackNode, stack_datatype *data){
    if(stackNode == NULL) return NULL;
    if(data != NULL) *data = stackNode->data;
    stack_node *res = stackNode->next;
    free(stackNode);
    return res;
}

void display_stack_(stack_node *stackNode){
    if(stackNode->next) display_stack_(stackNode->next);
    printf("%d ", stackNode->data);
}

void display_stack(stack_node *stackNode){
    printf("[ ");
    if(stackNode)display_stack_(stackNode);
    printf("]\n");
}

int main(){
    stack_node *stack = NULL, *temp = NULL;
    stack_datatype data;
    int sample_data[] = {67, 91, 101, 25};
    int n = sizeof(sample_data) / sizeof(int);
    for(int i = 0; i < n; i++){
        stack = stack_push(stack, &sample_data[i]);
    }
    printf("Original: ");
    display_stack(stack);
    printf("Temporal: ");
    display_stack(temp);
    puts("");
    while (stack){
        stack = stack_pop(stack, &data);
        while (temp && temp->data > data) {
            stack = stack_push(stack, &temp->data);
            temp = stack_pop(temp, NULL);
        }
        temp = stack_push(temp, &data);
    }
    printf("Original: ");
    display_stack(stack);
    printf("Temporal: ");
    display_stack(temp);
    puts("");
}
