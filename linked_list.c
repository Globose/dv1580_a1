#include "linked_list.h"


Node* get_new_node(int data, Node* next){
    Node*new_node = (Node*)mem_alloc(sizeof(Node));
    *new_node = (Node){data,next};
    return new_node;
}

// This function sets up the list and prepares it for operations.
void list_init(Node** head, size_t size){
    mem_init(size);
    *head = NULL;
}

// Adds a new node with the specified data to the linked list. 
void list_insert(Node** head, int data){
    if (head == NULL) return;
    if (*head == NULL){
        *head = get_new_node(data, NULL);
    }
    else{
        Node* node = *head;
        while(node->next != NULL){
            node = node->next;
        } 
        node->next = get_new_node(data, NULL);
    }
}

// Inserts a new node with the specified data immediately after a given node.
void list_insert_after(Node* prev_node, int data){
    Node* new_node = get_new_node(data, prev_node->next);
    prev_node->next = new_node;
}

// Inserts a new node with the specified data immediately before a given node in the list. 
void list_insert_before(Node** head, Node* next_node, int data){
    if (head == NULL) return;
    Node* prev_node = NULL;
    Node* node = *head;
    while(node != NULL){
        if (node == next_node){
            Node* new_node = get_new_node(data, node);
            if (prev_node == NULL){
                *head = new_node;
            }
            else{
                prev_node->next = new_node;
            }
            return;
        }
        else{
            prev_node = node;
            node = node->next;
        }
    } 
}

// Removes a node with the specified data from the linked list.
void list_delete(Node** head, int data){
    if (head == NULL) return;
    Node* prev_node = NULL;
    Node* node = *head;
    while(node != NULL){
        if (node->data == data){
            Node* next = node->next;
            mem_free(node);
            if (prev_node == NULL){
                *head = next;
            }
            else{
                prev_node->next = node;
            }
            node = next;
        }
        else{
            prev_node = node;
            node = node->next;
        }
    } 
}

// Searches for a node with the specified data and returns a pointer to it.
Node* list_search(Node** head, int data){
    if (head == NULL) return NULL;
    Node*node = *head;
    while(node != NULL && node->data != data){
        node = node->next;
    }
    return node;
}

// Prints all the elements in the linked list as a list separated by commas, enclosed in square brackets.
void list_display_range(Node** head, Node* start_node, Node* end_node){
    printf("[");
    if (start_node == NULL) {
        start_node = *head;
    }
    while (start_node != NULL){
        printf("%d", start_node->data);
        if (start_node == end_node) break;
        start_node = start_node->next;
        if (start_node != NULL) printf(", ");
    }
    printf("]");
}

void list_display(Node** head){
    list_display_range(head, *head, NULL);
}

// Returns the count of nodes
int list_count_nodes(Node** head){
    Node* node = *head;
    int counter = 0;
    while (node != NULL){
        node = node->next;
        counter++;
    }
    return counter;
}

// Frees all the nodes in the linked list. Important to prevent memory leaks.
void list_cleanup(Node** head){
    Node* node = *head;
    while (node != NULL){
        Node* old_node = node;
        node = node->next;
        mem_free(old_node);
    }
    *head = NULL;
    mem_deinit();
}

