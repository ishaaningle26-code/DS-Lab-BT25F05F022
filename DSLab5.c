#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *prev;
    struct Node *next;
};

struct Node *head = NULL;

// Function to insert a node
void insert() {
    struct Node *newNode, *temp;
    int value, position, i;

    newNode = (struct Node *)malloc(sizeof(struct Node));

    printf("Enter value: ");
    scanf("%d", &value);

    printf("Enter position: ");
    scanf("%d", &position);

    newNode->data = value;
    newNode->prev = NULL;
    newNode->next = NULL;

    // Insert at beginning
    if (position == 1) {
        newNode->next = head;

        if (head != NULL) {
            head->prev = newNode;
        }

        head = newNode;
        printf("Node inserted successfully.\n");
        return;
    }

    // Find the node before the required position
    temp = head;

    for (i = 1; i < position - 1 && temp != NULL; i++) {
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Invalid position!\n");
        free(newNode);
        return;
    }

    newNode->next = temp->next;
    newNode->prev = temp;

    if (temp->next != NULL) {
        temp->next->prev = newNode;
    }

    temp->next = newNode;

    printf("Node inserted successfully.\n");
}

// Function to delete a node
void deleteNode() {
    struct Node *temp;
    int position, i;

    if (head == NULL) {
        printf("List is empty!\n");
        return;
    }

    printf("Enter position to delete: ");
    scanf("%d", &position);

    temp = head;

    // Delete first node
    if (position == 1) {
        head = head->next;

        if (head != NULL) {
            head->prev = NULL;
        }

        free(temp);

        printf("Node deleted successfully.\n");
        return;
    }

    // Find the node to delete
    for (i = 1; i < position && temp != NULL; i++) {
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Invalid position!\n");
        return;
    }

    // Connect previous node to next node
    temp->prev->next = temp->next;

    // Connect next node to previous node
    if (temp->next != NULL) {
        temp->next->prev = temp->prev;
    }

    free(temp);

    printf("Node deleted successfully.\n");
}

// Display in forward direction
void displayForward() {
    struct Node *temp;

    if (head == NULL) {
        printf("List is empty!\n");
        return;
    }

    temp = head;

    printf("Forward: ");

    while (temp != NULL) {
        printf("%d <-> ", temp->data);
        temp = temp->next;
    }

    printf("NULL\n");
}

// Display in reverse direction
void displayReverse() {
    struct Node *temp;

    if (head == NULL) {
        printf("List is empty!\n");
        return;
    }

    temp = head;

    // Move to last node
    while (temp->next != NULL) {
        temp = temp->next;
    }

    printf("Reverse: ");

    while (temp != NULL) {
        printf("%d <-> ", temp->data);
        temp = temp->prev;
    }

    printf("NULL\n");
}

// Main function
int main() {
    int choice, n, i, value;

    printf("Enter the number of elements initially: ");
    scanf("%d", &n);

    // Create initial list
    for (i = 1; i <= n; i++) {
        struct Node *newNode, *temp;

        newNode = (struct Node *)malloc(sizeof(struct Node));

        printf("Enter element %d: ", i);
        scanf("%d", &value);

        newNode->data = value;
        newNode->prev = NULL;
        newNode->next = NULL;

        if (head == NULL) {
            head = newNode;
        }
        else {
            temp = head;

            while (temp->next != NULL) {
                temp = temp->next;
            }

            temp->next = newNode;
            newNode->prev = temp;
        }
    }

    // Menu
    do {
        printf("\n===== DOUBLY LINKED LIST =====\n");
        printf("1. Insertion\n");
        printf("2. Deletion\n");
        printf("3. Display Forward\n");
        printf("4. Display Reverse\n");
        printf("5. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                insert();
                break;

            case 2:
                deleteNode();
                break;

            case 3:
                displayForward();
                break;

            case 4:
                displayReverse();
                break;

            case 5:
                printf("Exiting program...\n");
                break;

            default:
                printf("Invalid choice!\n");
        }

    } while (choice != 5);

    return 0;
}