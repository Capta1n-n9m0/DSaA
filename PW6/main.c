#include <stdio.h>
#include <stdlib.h>
#include <time.h>

const int table_size = 11;

int hash(int i, int k) {
    return i % k;
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

struct hash_table_ {
    int size;
    node **data;
};
typedef struct hash_table_ hash_table;

hash_table init_table(int size) {
    hash_table res = {0};
    res.size = size;
    res.data = calloc(size, sizeof(node *));
    return res;
}

void print_hash_table(hash_table t) {
    puts("===================");
    for (int i = 0; i < t.size; i++) {
        printf("%-3d: ", i);
        print_list(t.data[i]);
        puts("");
    }
    puts("===================");
}

void insert_table(hash_table *table, int data) {
    int id = hash(data, table->size);
    add_to_end(&table->data[id], data);
}
node *search_table(hash_table table, int data){
    int id = hash(data, table.size);
    return search_list(table.data[id], data);
}
void remove_from_table(hash_table *table, int data){
    int id = hash(data, table->size);
    node *temp = search_list(table->data[id], data);
    remove_node(&temp);
}

int main() {
    hash_table t1 = init_table(table_size);
    for (int i = 0; i < 77; i++) {
        insert_table(&t1, rand() % 100);
    }
    print_hash_table(t1);
    remove_from_table(&t1, 97);
    print_hash_table(t1);

}


