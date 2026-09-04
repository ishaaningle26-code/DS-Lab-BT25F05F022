#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *next;
};

struct Node *head = NULL;

// Insert a node at the end
void insert(int value) {
    struct Node *newNode = malloc(sizeof(struct Node));

    if (newNode == NULL) {
        printf("Memory allocation failed\n");
        return;
    }

    newNode->data = value;
    newNode->next = NULL;

    // If list is empty
    if (head == NULL) {
        head = newNode;
        return;
    }

    // Find the last node
    struct Node *temp = head;

    while (temp->next != NULL) {
        temp = temp->next;
    }

    temp->next = newNode;
}

// Display the list
void display() {
    struct Node *temp = head;

    if (head == NULL) {
        printf("List is empty\n");
        return;
    }

    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }

    printf("NULL\n");
}

// Delete the first node
void deleteFirst() {
    if (head == NULL) {
        printf("List is empty\n");
        return;
    }

    struct Node *temp = head;
    head = head->next;

    free(temp);
}

int main() {
    insert(10);
    insert(20);
    insert(30);
    insert(40);

    printf("Singly Linked List:\n");
    display();

    deleteFirst();

    printf("After deleting first node:\n");
    display();

    return 0;
}
