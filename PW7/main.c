/* Author: Abbas Aliyev
 * With great aid of our professor Samir Guliyev
 * */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct Node_ {
    int value;
    int depth;
    bool marked;
    struct Node_* left;
    struct Node_* right;
    struct Node_* parent;
} Node;

Node* add_node(Node* parent, bool position, int value)
{
    Node* node;
    node = calloc(1, sizeof(Node));
    node->value = value;    node->left = NULL;    node->right = NULL;    node->parent = parent;
    if (parent) {
        if (position) {
            parent->right = node;
        } else {
            parent->left = node;
        }
        node->depth = parent->depth + 1;
    } else {
        node->depth = 0;
    }
    return node;
}

Node* find_node(int target, Node* node)
{
    Node* result = NULL;
    if (node->value == target) {
        result = node;
        return result;
    }
    if (node->left) {
        result = find_node(target, node->left);
        if (result) {
            return result;
        }
    }
    if (node->right) {
        result = find_node(target, node->right);
        if (result) {
            return result;
        }
    }
    return result;
}

void traverse_preorder(Node* node)
{
    printf("Node=%d\tDepth=%d\n", node->value, node->depth);
    if (node->left) {
        traverse_preorder(node->left);
    }
    if (node->right) {
        traverse_preorder(node->right);
    }
}

void traverse_inorder(Node* node)
{
    if (node->left) {
        traverse_inorder(node->left);
    }
    printf("Node=%d\tDepth=%d\n", node->value, node->depth);
    if (node->right) {
        traverse_inorder(node->right);
    }
}

void traverse_postorder(Node* node)
{
    if (node->left) {
        traverse_postorder(node->left);
    }
    if (node->right) {
        traverse_postorder(node->right);
    }
    printf("Node=%d\tDepth=%d\n", node->value, node->depth);
}

void traverse_breadthfirst(Node* root)
{
    // variables to manage the circular queue
    const int queue_size = 10;
    Node* queue[10];
    int next = 0;
    int last = 0;
    int count = 0;

    Node* node = root;

    // enqueue the root node
    queue[next] = node;
    next = (next + 1) % queue_size;
    count++;

    // process the queue until it is empty
    while (count) {
        // dequeue the next node
        if (next == last) {
            printf("WARNING: no more items in the circular queue!");
            return;
        }
        node = queue[last];     queue[last] = NULL;
        last = (last + 1) % queue_size;
        count--;

        // process the node
        printf("Node=%d\tDepth=%d\n", node->value, node->depth);

        // enqueue the node's children: first, left child
        if (node->left) {
            if ((next + 1) % queue_size == last) {
                printf("WARNING: no more empty room in the circular queue!");
                return;
            }
            queue[next] = node->left;
            next = (next + 1) % queue_size;
            count++;
        }

        // enqueue the node's children: second, right child
        if (node->right) {
            if ((next + 1) % queue_size == last) {
                printf("WARNING: no more empty room in the circular queue!");
                return;
            }
            queue[next] = node->right;
            next = (next + 1) % queue_size;
            count++;
        }
    }
}

void build_binary_tree(Node* root)
{
    int nValue, pValue, position;
    Node* parent;

    while (true) {
        printf("Enter a positive value (0 - to exit) for the next node: ");
        scanf("%d", &nValue);
        if (nValue <= 0) {
            break;
        }

        printf("Enter the parent's value for the next node: ");
        scanf("%d", &pValue);

        printf("Enter the position for the next node (0 - left, 1 - right): ");
        scanf("%d", &position);

        parent = find_node(pValue, root);
        if (parent) {
            add_node(parent, position, nValue);
        } else {
            printf("WARNING: no parent found for the node!");
            continue;
        }

        printf("\n");
    }
}

/*
 ********************** Binary Search Tree (BST) *********************
 */

void add_sorted_node(Node* node, int target)
{
    Node* cell;

    if (target < node->value) {
        // target is smaller than current node's value: add it to the left subtree
        if (node->left == NULL) {
            cell = calloc(1, sizeof(Node));
            cell->value = target;   cell->left = NULL;  cell->right = NULL;    cell->parent = node;
            node->left = cell;
            return;
        } else {
            add_sorted_node(node->left, target);
        }
    } else {
        // target is not smaller than current node's value: add it to the right subtree
        if (node->right == NULL) {
            cell = calloc(1, sizeof(Node));
            cell->value = target;   cell->left = NULL;  cell->right = NULL;    cell->parent = node;
            node->right = cell;
            return;
        } else {
            add_sorted_node(node->right, target);
        }
    }
}

void build_sorted_binary_tree(Node* root)
{
    int value;

    while (true) {
        printf("Enter a positive value (0 - to exit) for the next node: ");
        scanf("%d", &value);
        if (value <= 0) {
            break;
        }
        add_sorted_node(root, value);
    }
}

Node* find_sorted_node(Node* node, int target)
{
    if (node->value == target) {
        return node;
    }
    if (node->value > target) {
        // search in the left subtree
        if (node->left == NULL) {
            return NULL;
        } else {
            return find_sorted_node(node->left, target);
        }
    } else {
        // search in the right subtree
        if (node->right == NULL) {
            return NULL;
        } else {
            return find_sorted_node(node->right, target);
        }
    }
}

void delete_sorted_node(Node* root, int target)
{
    Node* parent;
    Node* node;

    node = find_sorted_node(root, target);
    if (node == NULL) {
        printf("\nCell %d not found: nothing to delete!\n", target);
        return;
    }

    // target is a leaf
    if (node->left == NULL && node->right == NULL) {
        parent = node->parent;
        if (parent->left == node) {
            parent->left = NULL;
        } else {
            parent->right = NULL;
        }
        free(node);
        return;
    }

    // target is not a leaf and has only one child
    if (node->left == NULL || node->right == NULL) {
        parent = node->parent;
        if (parent->left == node) {
            if (node->left) {
                parent->left = node->left;
            } else {
                parent->left = node->right;
            }
        } else {
            if (node->left) {
                parent->right = node->left;
            } else {
                parent->right = node->right;
            }
        }
        return;
    }

    // target is not a leaf and has both children
    if (node->left && node->right) {
        parent = node->parent;
        // case 1: target node's left child has no right child
        if (node->left->right == NULL) {
            node->left->right = node->right;
            if (parent->left == node) {
                parent->left = node->left;
            } else {
                parent->right = node->left;
            }
            return;
        }
        // case 2: target node's left child has a right child
        if (node->left->right) {
            Node* rnode = node->left;
            while (rnode->right) {
                rnode = rnode->right;
            }
            if (rnode->left == NULL && rnode->right == NULL) {
                rnode->parent->right = NULL;
                rnode->left = node->left;
                rnode->right = node->right;
                if (parent->left == node) {
                    parent->left = rnode;
                } else {
                    parent->right = rnode;
                }
                return;
            }
            if (rnode->left) {
                rnode->parent->right = rnode->left;
                rnode->left = node->left;
                rnode->right = node->right;
                if (parent->left == node) {
                    parent->left = rnode;
                } else {
                    parent->right = rnode;
                }
                return;
            }
        }
    }
}

Node* lowest_common_ancestor_sorted(Node* node, int value1, int value2)
{
    Node* result = NULL;
    // check if both nodes belong down the left child branch.
    if ((value1 < node->value) && (value2 < node->value)) {
        result = lowest_common_ancestor_sorted(node->left, value1, value2);
        if (result) {
            return result;
        }
    }

    // check if both nodes belong down the right child branch.
    if ((value1 >= node->value) && (value2 >= node->value)) {
        result = lowest_common_ancestor_sorted(node->right, value1, value2);
        if (result) {
            return result;
        }
    }

    // if we ever reach this point, then the current node is the LCA.
    result = node;
    return result;
}

Node* lowest_common_ancestor_parent_pointers(Node* node1, Node* node2)
{
    Node* lca;
    Node* node;
    // mark nodes above node1
    node = node1;
    while (node != NULL) {
        node->marked = true;
        node = node->parent;
    }

    // search nodes above node2 until we find a marked node
    lca = NULL;
    node = node2;
    while (node != NULL) {
        if (node->marked) {
            lca = node;
            break;
        }
        node = node->parent;
    }

    // unmark nodes above node1
    node = node1;
    while (node != NULL) {
        node->marked = false;
        node = node->parent;
    }

    // return the lowest common ancestor
    return lca;
}

Node* lowest_common_ancestor_parent_depth(Node* node1, Node* node2)
{
    // climb up the tree until the nodes have the same depth
    while (node1->depth > node2->depth) {
        node1 = node1->parent;
    }
    while (node2->depth > node1->depth) {
        node2 = node2->parent;
    }

    // climb up the tree until the nodes match
    while (node1 != node2) {
        node1 = node1->parent;
        node2 = node2->parent;
    }

    // return the lowest common ancestor
    return node1;
}

Node* lowest_common_ancestor_exhaustive_search(Node* root, int value1, int value2)
{
    // variables to manage the circular queue
    const int size = 10;
    Node* queue[10];
    int next = 0;
    int last = 0;
    int count = 0;

    // variables to manage the stack
    Node* path1[10]; int top1 = -1;
    Node* path2[10]; int top2 = -1;

    // variables to manage lca
    Node* node1 = NULL;
    Node* node2 = NULL;
    Node* node = root;

    // enqueue the root node
    queue[next] = node;
    next = (next + 1) % size;
    count++;

    // process the queue until it is empty
    while (count) {
        // dequeue the next node
        if (next == last) {
            printf("WARNING: no more items in the circular queue!");
            return NULL;
        }
        node = queue[last];     queue[last] = NULL;
        last = (last + 1) % size;
        count--;

        // process the current node
        if (node->value == value1 && node1 == NULL) {
            printf("First node found = %d\tDepth = %d\n", node->value, node->depth);
            node1 = node;
            // climb up the tree till the root to build the path
            top1++;
            path1[top1] = node1;
            while (node1->parent) {
                node1 = node1->parent;
                top1++;
                if (top1 == size) {
                    printf("WARNING: no more empty room in the stack(1)!");
                    return NULL;
                }
                path1[top1] = node1;
            }
            printf("First path complete.\n");
        }

        if (node->value == value2 && node2 == NULL) {
            printf("Second node found = %d\tDepth = %d\n", node->value, node->depth);
            node2 = node;
            // climb up the tree till the root to build the path
            top2++;
            path2[top2] = node2;
            while (node2->parent) {
                node2 = node2->parent;
                top2++;
                if (top2 == size) {
                    printf("WARNING: no more empty room in the stack(2)!");
                    return NULL;
                }
                path2[top2] = node2;
            }
            printf("Second path complete.\n");
        }

        if (node1 && node2) {
            printf("Leaving the breadth-first traversal.\n");
            break;
        }

        // enqueue the node's children: first, left child
        if (node->left) {
            if ((next + 1) % size == last) {
                printf("WARNING: no more empty room in the circular queue!");
                return NULL;
            }
            queue[next] = node->left;
            next = (next + 1) % size;
            count++;
        }

        // enqueue the node's children: second, right child
        if (node->right) {
            if ((next + 1) % size == last) {
                printf("WARNING: no more empty room in the circular queue!");
                return NULL;
            }
            queue[next] = node->right;
            next = (next + 1) % size;
            count++;
        }
    }

    // find the lca of two nodes
    node = NULL;
    while (top1 >=0 && top2 >= 0) {
        node1 = path1[top1];
        node2 = path2[top2];
        if (node1 != node2) {
            node = path1[top1 + 1];
            break;
        } else {
            top1--; top2--;
        }
    }
    return node;
}

int main(int argc, char* argv[])
{
    Node* node; Node* node1; Node* node2;
    Node* root;

    // building an unsorted binary tree
    root = add_node(NULL, true, 17);
    build_binary_tree(root);

    /*
    // building a sorted binary tree
    root = add_node(NULL, true, 17);
    build_sorted_binary_tree(root);
    */

    // traversing a binary tree
    printf("\nTree Traversal (Preorder):\n");
    traverse_preorder(root);

    printf("\nTree Traversal (Inorder):\n");
    traverse_inorder(root);

    printf("\nTree Traversal (Postorder):\n");
    traverse_postorder(root);

    printf("\nTree Traversal (Breadth-First):\n");
    traverse_breadthfirst(root);

    /*
    // finding a node in a tree
    int value = 12;
    node = find_sorted_node(root, value);
    if (node) {
        printf("\nCell %d found;  Parent: %d\n", node->value, node->parent->value);
    } else {
        printf("\nCell %d not found!\n", value);
    }
    */

    /*
    // deleting a node from a tree
    value = 35;
    delete_sorted_node(root, value);

    printf("\nTree Traversal (Sorted):\n");
    traverse_inorder(root);
    */

    /*
    // finding a lowest common ancestor of two nodes in a sorted binary tree
    node = find_sorted_node(root, 2);
    if (node == NULL) {
        printf("WARNING: no such target value in the tree!\n");
        return EXIT_FAILURE;
    }
    node = find_sorted_node(root, 5);
    if (node == NULL) {
        printf("WARNING: no such target value in the tree!\n");
        return EXIT_FAILURE;
    }
    node = lowest_common_ancestor_sorted(root, 2, 5);
    if (node) {
        printf("\n Lowest Common Ancestor is %d\n", node->value);
    } else {
        printf("ERROR: Lowest Common Ancestor not found!\n");
    }
    */

    // finding a lowest common ancestor of two nodes in an unsorted binary tree
    node1 = find_node(3, root);
    if (node1 == NULL) {
        printf("WARNING: no such target value in the tree!\n");
        return EXIT_FAILURE;
    }
    node2 = find_node(7, root);
    if (node2 == NULL) {
        printf("WARNING: no such target value in the tree!\n");
        return EXIT_FAILURE;
    }
    // node = lowest_common_ancestor_parent_pointers(node1, node2);
    // node = lowest_common_ancestor_parent_depth(node1, node2);
    node = lowest_common_ancestor_exhaustive_search(root, 3, 7);
    if (node) {
        printf("\n Lowest Common Ancestor is %d\n", node->value);
    } else {
        printf("ERROR: Lowest Common Ancestor not found!\n");
    }

    return EXIT_SUCCESS;
}
