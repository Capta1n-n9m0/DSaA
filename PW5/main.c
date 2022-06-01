#include <stdio.h>
#include <malloc.h>


struct node {
    int data;
    struct node *previous;
    struct node *next;
};

struct node *head, *tail = NULL;

void addNode(int data) {
    struct node *newNode = (struct node *) malloc(sizeof(struct node));
    newNode->data = data;
    if (head == NULL) {
        head = tail = newNode;
        head->previous = NULL;
        tail->next = NULL;
    } else {
        tail->next = newNode;
        newNode->previous = tail;
        tail = newNode;
        tail->next = NULL;
    }
}


int minimumNode() {
    //Node current will point to head
    struct node *current = head;
    int min;
    if (head == NULL) {
        printf("List is empty\n");
        return 0;
    } else {
        min = head->data;
        while (current != NULL) {
            if (min > current->data)
                min = current->data;
            current = current->next;
        }
    }
    return min;
}

int maximumNode() {
    struct node *current = head;
    int max;
    if (head == NULL) {
        printf("List is empty\n");
        return 0;
    } else {
        max = head->data;
        while (current != NULL) {
            if (current->data > max)
                max = current->data;
            current = current->next;
        }
    }
    return max;
}

int isPalindrome(struct node *left) {
    if (left == NULL)
        return 1;

    struct node *right = left;
    while (right->next != NULL)
        right = right->next;

    while (left != right) {
        if (left->data != right->data)
            return 0;

        left = left->next;
        right = right->previous;
    }

    return 1;
}

int main() {
    addNode(5);
    addNode(7);
    addNode(9);
    addNode(1);
    addNode(2);

    printf("Minimum value node in the list: %d\n", minimumNode());
    printf("Maximum value node in the list: %d", maximumNode());

    return 0;
}