#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *next;
};

int main() {
    struct Node *head = NULL, *newNode, *temp;
    int n, i, value;

    // Take number of elements
    printf("Enter the number of elements: ");
    scanf("%d", &n);

    // Create circular linked list
    for (i = 0; i < n; i++) {
        newNode = (struct Node *)malloc(sizeof(struct Node));

        printf("Enter element %d: ", i + 1);
        scanf("%d", &value);

        newNode->data = value;

        if (head == NULL) {
            // First node
            head = newNode;
            newNode->next = head;
        } 
        else {
            // Insert at the end
            temp = head;

            while (temp->next != head) {
                temp = temp->next;
            }

            temp->next = newNode;
            newNode->next = head;
        }
    }

    // Display the circular linked list
    printf("\nCircular Linked List: ");

    if (head != NULL) {
        temp = head;

        do {
            printf("%d -> ", temp->data);
            temp = temp->next;
        } while (temp != head);

        printf("(back to head)");
    }

    return 0;
}