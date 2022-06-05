#include <stdio.h>
#include <stdlib.h>
#include <time.h>

const int table_size = 11;

int hash(int i, int k) {
    return (2*i + 5) % k;
}

struct node_ {
    int data;
    struct node_ *next, *prev;
};
typedef struct node_ node;

void add_to_beginning(node **l, int data) {
    node *res = calloc(1, sizeof(node));
    res->data = data;
    res->next = *l;
    (*l)->prev = res;
    *l = res;
}

void add_to_end(node **l, int data) {
    node *res = calloc(1, sizeof(node));
    res->data = data;
    node *cur = *l;
    if (cur) {
        while (cur->next) cur = cur->next;
        res->prev = cur;
        cur->next = res;
    } else *l = res;
}

void print_list(node *l) {
    if (l == NULL) {
        printf("NULL");
        return;
    }
    node *cur = l;
    printf("[ ");
    while (cur) {
        printf("%d ", cur->data);
        cur = cur->next;
    }
    printf("]");
}

node *search_list(node *l, int data) {
    node *cur = l;
    while (cur) {
        if (cur->data == data) return cur;
        cur = cur->next;
    }
    return NULL;
}

void remove_node(node **n) {
    if (n == NULL || *n == NULL) return;
    node *cur = *n;
    if (cur->next == NULL && cur->prev == NULL) {
        *n = NULL;
        free(cur);
        return;
    }
    if(cur->prev) cur->prev->next = cur->next;
    if(cur->next) cur->next->prev = cur->prev;
    *n = cur->next;
    free(cur);
}

struct hashtable_chaining_ {
    int size;
    node **data;
};
typedef struct hashtable_chaining_ hashtable_chaining;

hashtable_chaining init_hashtable_chaining(int size) {
    hashtable_chaining res = {0};
    res.size = size;
    res.data = calloc(size, sizeof(node *));
    return res;
}

void print_hashtable_chaining(hashtable_chaining t) {
    puts("===================");
    for (int i = 0; i < t.size; i++) {
        printf("%-3d: ", i);
        print_list(t.data[i]);
        puts("");
    }
    puts("===================");
}

void insert_table_chaining(hashtable_chaining *table, int data) {
    int id = hash(data, table->size);
    add_to_end(&table->data[id], data);
}
node *search_table_chaining(hashtable_chaining table, int data){
    int id = hash(data, table.size);
    return search_list(table.data[id], data);
}
void remove_from_table_chaining(hashtable_chaining *table, int data){
    int id = hash(data, table->size);
    node *temp = search_list(table->data[id], data);
    remove_node(&temp);
}

struct hashtable_probing_{
    int size;
    int **data;
};
typedef struct hashtable_probing_ hashtable_probing;

hashtable_probing init_hashtable_probing(int size){
    hashtable_probing res = {0};
    res.size = size;
    res.data = calloc(size, sizeof (int *));
    return res;
}

void print_hashtable_probing(hashtable_probing t){
    puts("===================");
    for(int i = 0; i < t.size; i++){
        printf("%-3d: ", i);
        if(t.data[i]) printf("%d\n", *(t.data[i]));
        else printf("NULL\n");
    }
    puts("===================");
}

void insert_hashtable_probing(hashtable_probing *t, int data){
    int id = hash(data, t->size);
    while (id < t->size){
        if(t->data[id] == NULL){
            t->data[id] = calloc(1, sizeof (int));
            *t->data[id] = data;
            break;
        }
        id++;
    }
}

int *search_hashtable_probing(hashtable_probing t, int data){
    int id = hash(data, t.size);
    while (id < t.size){
        if(*t.data[id] == data) return t.data[id];
        id++;
    }
    return NULL;
}

void remove_from_hashtable_probing(hashtable_probing *t, int data){
    int id = hash(data, t->size);
    while (id < t->size){
        if(*t->data[id] == data){
            free(t->data[id]);
            t->data[id] = NULL;
            break;
        }
        id++;
    }
}

int hash2(int i, int prime){
    return (prime - i)%prime;
}

const int PRIME = 7;

void insert_hashtable_double_hashing(hashtable_probing *t, int data){
    int id = hash(data, t->size), offset = hash2(data, PRIME);
    while (id < t->size){
        if(t->data[id] == NULL ){
            t->data[id] = calloc(1, sizeof(int));
            *t->data[id] = data;
            break;
        }
        id = (id + offset) % t->size;
    }
}

int *search_hashtable_double_hashing(hashtable_probing t, int data){
    int id = hash(data, t.size), offset = hash2(data, PRIME);
    int first = id;
    do{
        if(*t.data[id] == data)
            return t.data[id];
        id = (id + offset) % t.size;
    } while (id != first);
    return NULL;
}

void remove_from_hashtable_double_hashing(hashtable_probing *t, int data){
    int id = hash(data, t->size), offset = hash2(data, PRIME);
    int first = id;
    do{
        if(*t->data[id] == data){
            //if next one matches, move to the next one
            if(*t->data[(id + offset) % t->size] == data) {
                id = (id + offset) % t->size;
                continue;
            }
            free(t->data[id]);
            t->data[id] = NULL;
        }
        id = (id + offset) % t->size;
    } while (first != id);
}


int main() {
    // no seed for predictable results
    // srand(time(NULL));
    puts("Chaining");
    hashtable_chaining t1 = init_hashtable_chaining(table_size);
    for (int i = 0; i < 77; i++) {
        insert_table_chaining(&t1, rand() % 100);
    }
    print_hashtable_chaining(t1);
    remove_from_table_chaining(&t1, 97);
    print_hashtable_chaining(t1);

    puts("\nProbing");
    hashtable_probing t2 = init_hashtable_probing(11);
    print_hashtable_probing(t2);
    insert_hashtable_probing(&t2, 5);
    insert_hashtable_probing(&t2, 5);
    insert_hashtable_probing(&t2, 5);
    print_hashtable_probing(t2);

}


