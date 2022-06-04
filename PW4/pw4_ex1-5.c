#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>


typedef struct list_node_{
    int data;
    struct list_node_ *next;
}list_node;

/*! \struct list_
 * wrapper of linked list. Stores number of nodes, first and last node
 */
typedef struct list_{
    int size;
    list_node *first, *last;
} list;

// My approach to the problem
list init_list();
void free_list(list *l);
void add_to_beginning(list *l, int data);
void add_to_end(list *l, int data);
void print_list(list l);
void print_named_list(list l, const char *name);
list copy_list(list l);
/// returns array of 2 list
list *split_list(list l);
list sorted_merge(list l1, list l2);
list merge_sort(list l);

// Intended approach (geekfor...)
void PushToBeginning(list_node **node, int data);
void PrintList(list_node *node);
void PrintNamedList(list_node *node, const char *name);
void FrontBackSplit(list_node *source, list_node **half1, list_node **half2);
list_node *SortedMerge(list_node *l1, list_node *l2);
void MergeSort(list_node **head);
void RemoveDuplicates(list_node *l);
void ReverseLinkedList(list_node **l);

int main(){
    srand(time(NULL));
    int step = 10;
    list my_list = init_list();
    for(int i = 0; i < 5; i++){
        int item = rand()%step;
        add_to_end(&my_list, item);
    }
    puts("my approach");
    print_named_list(my_list, "my_list");
    list sorted = merge_sort(my_list);
    print_named_list(sorted, "sorted");
    puts("suggested approach");
    list_node *l_copy = copy_list(my_list).first;
    PrintNamedList(l_copy, "l_copy");
    MergeSort(&l_copy);
    PrintNamedList(l_copy, "sorted");
    RemoveDuplicates(l_copy);
    PrintNamedList(l_copy, "reduced");
    ReverseLinkedList(&l_copy);
    PrintNamedList(l_copy, "reversed");
}

// My approach to the problem
list init_list(){
    return (list){0,NULL, NULL};
}
void free_list(list *l){
    list_node *n = l->first, *p;
    while (n){
        p = n;
        n = n->next;
        free(p);
    }
    l->first = NULL;
    l->last = NULL;
}
void add_to_beginning(list *l, int data){
    l->size++;
    if(l->first == NULL && l->last == NULL){
        l->first = malloc(sizeof(list_node));
        l->first->data = data;
        l->first->next = NULL;
        l->last = l->first;
    }else{
        list_node *node = malloc(sizeof(list_node));
        node->data = data;
        node->next = l->first;
        l->first = node;
    }
}
void add_to_end(list *l, int data){
    l->size++;
    if(l->first == NULL && l->last == NULL){
        l->first = malloc(sizeof(list_node));
        l->first->data = data;
        l->first->next = NULL;
        l->last = l->first;
    }
    else{
        l->last->next = malloc(sizeof(list_node));
        l->last = l->last->next;
        l->last->data = data;
        l->last->next = NULL;
    }
}
void print_list(list l){
#ifdef DEBUG
    printf("{first: %p, last: %p, size: %d}", l.first, l.last, l.size);
#endif
    printf("[ ");
    if(!(l.first == NULL && l.last == NULL)){
        list_node *n = l.first, *p = NULL;
        while (p != l.last) {
            printf("%d", n->data);
#ifdef DEBUG
            printf("(%p)\n", n);
#endif
            printf(" ");

            p = n;
            n = n->next;
        }
    }
    printf("]");
}
void print_named_list(list l, const char *name){
    printf("%10s: ", name);
    print_list(l);
    puts("");
}
list copy_list(list l){
    list res = init_list();
    if(!(l.first == NULL && l.last == NULL)){
        for (list_node *n = l.first; n; n = n->next) {
            add_to_end(&res, n->data);
        }
    }
    return res;
}
list *split_list(list l){
    list *res = calloc(2, sizeof(list));
    res[0] = init_list(); res[1] = init_list();
    list_node *t = l.first;

    for(int i = 0; i < l.size; i++){
        if(i < (l.size + 1)/2) add_to_end(&res[0], t->data);
        else add_to_end(&res[1], t->data);
        t = t->next;
    }

    return res;
}
list sorted_merge(list l1, list l2){
    list res = init_list();
    // tracker1 and tracker2
    list_node *t1 = l1.first, *t2 = l2.first;
    while (t1 && t2){
        if(t1->data <= t2->data){
            add_to_end(&res, t1->data);
            t1 = t1->next;
        } else{
            add_to_end(&res, t2->data);
            t2 = t2->next;
        }
    }
    while (t1){
        add_to_end(&res, t1->data);
        t1 = t1->next;
    }
    while (t2){
        add_to_end(&res, t2->data);
        t2 = t2->next;
    }

    return res;
}
list merge_sort(list l){
    list res;
    if(l.size > 1){
        list *halfs = split_list(l), h1, h2;
        h1 = merge_sort(halfs[0]);
        h2 = merge_sort(halfs[1]);
        res = sorted_merge(h1, h2);
        //free(halfs);
        //free_list(&h1);
        //free_list(&h2);
    } else res = l;
    return res;
}


// Intended approach (geekfor..)
void PushToBeginning(list_node **node, int data){
    list_node *t = malloc(sizeof(list_node));
    t->data = data; t->next = *node;
    *node = t;
}
void PrintList(list_node *node){
    printf("[ ");
    while (node != NULL){
        printf("%d", node->data);
#ifdef DEBUG
        printf("(%p)\n", node);
#endif
        printf(" ");
        node = node->next;
    }
    printf("]");
}
void PrintNamedList(list_node *node, const char *name){
    printf("%10s: ",name);
    PrintList(node);
    puts("");
}
void FrontBackSplit(list_node *source, list_node **half1, list_node **half2){
    if(source == NULL){ *half1 = NULL; *half2 = NULL; return;}
    if(source->next == NULL){*half1 = source; *half2 = NULL; return;}
    list_node *slow = source, *fast = source->next;
    while (fast != NULL){
        fast = fast->next;
        if(fast != NULL){
            slow = slow->next;
            fast = fast->next;
        }
    }
    *half1 = source;
    *half2 = slow->next;
    slow->next = NULL;
}
list_node *SortedMerge(list_node *l1, list_node *l2){
    list_node *result = NULL;
    if(l1 == NULL) return l2;
    if(l2 == NULL) return l1;

    if (l1->data <= l2->data) {
        result = l1;
        result->next = SortedMerge(l1->next, l2);
    } else {
        result = l2;
        result->next = SortedMerge(l1, l2->next);
    }
    return result;
}
void MergeSort(list_node **l){
    list_node *head = *l, *h1, *h2;
    if(head == NULL ||  head->next == NULL) return;

    FrontBackSplit(head, &h1, &h2);
    MergeSort(&h1);
    MergeSort(&h2);

    *l = SortedMerge(h1, h2);
}
void RemoveDuplicates(list_node *l){
    list_node *current, *next, *dup;
    current = l;
    next = current->next;
    while (next){
        if(current->data == next->data){
            dup = next;
            current->next = next->next;
            next = current->next;
            free(dup);
        }else{
            current = next;
            next = current->next;
        }
    }
}

void ReverseLinkedList(list_node **l){
    list_node *current = *l, *prev = NULL, *next = NULL;
    while (current != NULL){
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    *l = prev;
}