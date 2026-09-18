#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *prev;
    struct Node *next;
};

int main() {
    struct Node *head = NULL, *newNode, *temp;
    int n, i, value;

    // Take number of elements
    printf("Enter the number of elements: ");
    scanf("%d", &n);

    // Create doubly linked list
    for (i = 0; i < n; i++) {
        newNode = (struct Node *)malloc(sizeof(struct Node));

        printf("Enter element %d: ", i + 1);
        scanf("%d", &value);

        newNode->data = value;
        newNode->prev = NULL;
        newNode->next = NULL;

        if (head == NULL) {
            // First node
            head = newNode;
        }
        else {
            // Insert at the end
            temp = head;

            while (temp->next != NULL) {
                temp = temp->next;
            }

            temp->next = newNode;
            newNode->prev = temp;
        }
    }

    // Display in forward direction
    printf("\nDoubly Linked List (Forward): ");

    temp = head;

    while (temp != NULL) {
        printf("%d <-> ", temp->data);
        temp = temp->next;
    }

    printf("NULL");

    // Display in reverse direction
    printf("\nDoubly Linked List (Reverse): ");

    temp = head;

    // Move to the last node
    if (temp != NULL) {
        while (temp->next != NULL) {
            temp = temp->next;
        }
    }

    // Traverse backwards
    while (temp != NULL) {
        printf("%d <-> ", temp->data);
        temp = temp->prev;
    }

    printf("NULL");

    return 0;
}