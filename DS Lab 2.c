#include <stdio.h>

#define SIZE 5

int queue[SIZE];
int front = -1;
int rear = -1;

// Check if queue is full
int isFull() {
    return (front == (rear + 1) % SIZE);
}

// Check if queue is empty
int isEmpty() {
    return (front == -1);
}

// Insert an element
void enqueue(int value) {
    if (isFull()) {
        printf("Queue is full\n");
        return;
    }

    // First element
    if (front == -1) {
        front = 0;
    }

    rear = (rear + 1) % SIZE;
    queue[rear] = value;

    printf("%d inserted\n", value);
}

// Remove an element
void dequeue() {
    if (isEmpty()) {
        printf("Queue is empty\n");
        return;
    }

    printf("%d deleted\n", queue[front]);

    // If only one element is present
    if (front == rear) {
        front = -1;
        rear = -1;
    } else {
        front = (front + 1) % SIZE;
    }
}

// Display the queue
void display() {
    if (isEmpty()) {
        printf("Queue is empty\n");
        return;
    }

    int i = front;

    printf("Circular Queue: ");

    while (1) {
        printf("%d ", queue[i]);

        if (i == rear)
            break;

        i = (i + 1) % SIZE;
    }

    printf("\n");
}

int main() {
    enqueue(10);
    enqueue(20);
    enqueue(30);
    enqueue(40);
    enqueue(50);

    display();

    dequeue();
    dequeue();

    display();

    enqueue(60);
    enqueue(70);

    display();

    return 0;
}
