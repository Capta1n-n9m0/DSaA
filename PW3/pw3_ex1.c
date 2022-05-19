#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

const int default_stack_size = 256;

typedef char stack_datatype;

typedef struct stack_{
    int size, cursor;
    stack_datatype *data;
}stack;

static void error(const char *msg){
    fprintf(stderr, "%s\n", msg);
    exit(2);
}

stack create_new_stack(int size){
    stack res;
    res.size = size;
    res.cursor = 0;
    res.data = calloc(size, sizeof(stack_datatype));
    return res;
}

void free_stack(stack *stack1){
    stack1->size = 0;
    stack1->cursor = 0;
    free(stack1->data);
}

stack_datatype *stack_push(stack *s, stack_datatype item){
    if(s->cursor < s->size){
        s->data[s->cursor++] = item;
        return s->data+s->cursor;
    }return NULL;
}

stack_datatype *stack_pop(stack *s){
    if(s->cursor > 0){
        return &s->data[--s->cursor];
    }return NULL;
}

bool if_brackets_are_balanced(const char *string){
    stack res = create_new_stack(default_stack_size);
    for(int i = 0; string[i]; i++){
        char c = string[i];
        char *state = NULL;
        if(c == '('){
            if((state = stack_push(&res, c)) == NULL) error("Stack overflow");
        } else if(c == ')'){
            if((state = stack_pop(&res)) == NULL) error("Stack overflow");
            else if (*state != '(') return false;
        } else if(c == '{'){
            if((state = stack_push(&res, c)) == NULL) error("Stack overflow");
        } else if(c == '}'){
            if((state = stack_pop(&res)) == NULL) error("Stack overflow");
            else if (*state != '{') return false;
        } else if(c == '['){
            if((state = stack_push(&res, c)) == NULL) error("Stack overflow");
        } else if(c == ']'){
            if((state = stack_pop(&res)) == NULL) error("Stack overflow");
            else if (*state != '[') return false;
        }
//        else{
//            free_stack(&res);
//            return false;
//        }
    }
    free_stack(&res);
    return true;
}

int main() {
    char *strings[64] = {
            "(()){}[()]",
            "()[]{(}[]",
            NULL
    };
    for(int i = 0; strings[i]; i++){
        if(if_brackets_are_balanced(strings[i]))
            puts("Balanced");
        else
            puts("Unbalanced");

    }
    return 0;
}
