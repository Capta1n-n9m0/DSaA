#include <stdio.h>
#include <malloc.h>
#include <stdbool.h>


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

void printList(struct node *n) {
    printf("[ ");
    while (n) {
        printf("%d ", n->data);
        n = n->next;
    }
    printf("]");
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

void reverse(struct node **n) {
    struct node *temp = NULL, *current = *n;
    while (current) {
        temp = current->previous;
        current->previous = current->next; //this is the required line
        current->next = temp;
        current = current->previous;
    }
    if (temp != NULL) *n = temp->previous; //for short lists
}

void reverse_sl(struct node **n) {
    // reverse but for simply linked list
    struct node *current = *n, *prev = NULL, *next = NULL;
    while (current) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    *n = prev;
}


bool isPalindrome_sl(struct node *n) {
    struct node *slow = n, *fast = n;
    struct node *half, *prev_slow = n;
    struct node *mid = NULL;
    bool res = true;
    while (fast && fast->next) {
        fast = fast->next->next;
        prev_slow = slow;
        slow = slow->next;
    }

    if (fast) {
        mid = slow;
        slow = slow->next;
    }

    half = slow;
    prev_slow->next = NULL;
    reverse_sl(&half);
    struct node *t1 = n, *t2 = half;
    while (t1 && t2){
        if(t1->data != t2->data){
            res = false;
            break;
        }
        t1 = t1->next;
        t2 = t2->next;
    }

    reverse_sl(&half);
    if(mid){
        prev_slow->next = mid;
        mid->next = half;
    } else prev_slow->next = half;


    return res;
}

int main() {
    addNode(5);
    addNode(7);
    addNode(9);
    addNode(1);
    addNode(2);
    addNode(1);
    addNode(9);
    addNode(7);
    addNode(5);
    printList(head);
    puts("");

    printf("Minimum value node in the list: %d\n", minimumNode());
    printf("Maximum value node in the list: %d\n", maximumNode());
    printf("Is palindrome? ");
    if (isPalindrome(head)) printf("true\n");
    else printf("false\n");
    printf("Is palindrome as simply linked list? ");
    if (isPalindrome_sl(head)) printf("true\n");
    else printf("false\n");
    addNode(8);
    printList(head);
    puts("");
    printf("Is palindrome now? ");
    if (isPalindrome(head)) printf("true\n");
    else printf("false\n");
    printf("Is palindrome as simply linked list now? ");
    if (isPalindrome_sl(head)) printf("true\n");
    else printf("false\n");
    reverse(&head);
    printList(head);

    return 0;
}