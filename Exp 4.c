#include <stdio.h>
#include <stdlib.h>

#define MAX 5  // Maximum size of the circular queue

// Circular Queue structure definition
struct CircularQueue {
    int items[MAX];
    int front;
    int rear;
};

// Function to initialize the circular queue
void initQueue(struct CircularQueue* q) {
    q->front = -1;
    q->rear = -1;
}

// Function to check if the queue is full
int isFull(struct CircularQueue* q) {
    return (q->front == 0 && q->rear == MAX - 1) || (q->rear == (q->front - 1) % (MAX - 1));
}

// Function to check if the queue is empty
int isEmpty(struct CircularQueue* q) {
    return q->front == -1;
}

// Function to add an element to the circular queue (enqueue operation)
void enqueue(struct CircularQueue* q, int value) {
    if (isFull(q)) {
        printf("Queue is full! Cannot enqueue %d.\n", value);
        return;
    }

    if (isEmpty(q)) {  // First element to be enqueued
        q->front = 0;
        q->rear = 0;
    } else if (q->rear == MAX - 1 && q->front != 0) {  // Wrap around
        q->rear = 0;
    } else {  // Regular increment
        q->rear++;
    }

    q->items[q->rear] = value;
    printf("Enqueued %d to queue.\n", value);
}

// Function to remove and return an element from the circular queue (dequeue operation)
int dequeue(struct CircularQueue* q) {
    if (isEmpty(q)) {
        printf("Queue is empty! Cannot dequeue element.\n");
        return -1;  // Return -1 as an error code for underflow
    }

    int dequeued_value = q->items[q->front];

    if (q->front == q->rear) {  // Queue has only one element, so reset after dequeuing
        q->front = -1;
        q->rear = -1;
    } else if (q->front == MAX - 1) {  // Wrap around the front
        q->front = 0;
    } else {  // Regular increment
        q->front++;
    }

    printf("Dequeued %d from queue.\n", dequeued_value);
    return dequeued_value;
}

// Function to return the front element of the circular queue without removing it (peek operation)
int peek(struct CircularQueue* q) {
    if (isEmpty(q)) {
        printf("Queue is empty! Cannot peek.\n");
        return -1;
    } else {
        return q->items[q->front];
    }
}

// Function to display the elements of the circular queue
void display(struct CircularQueue* q) {
    if (isEmpty(q)) {
        printf("Queue is empty.\n");
        return;
    }

    printf("Queue elements: ");
    if (q->rear >= q->front) {
        for (int i = q->front; i <= q->rear; i++) {
            printf("%d ", q->items[i]);
        }
    } else {
        for (int i = q->front; i < MAX; i++) {
            printf("%d ", q->items[i]);
        }
        for (int i = 0; i <= q->rear; i++) {
            printf("%d ", q->items[i]);
        }
    }
    printf("\n");
}

// Main function to demonstrate circular queue operations
int main() {
    struct CircularQueue q;
    initQueue(&q);  // Initialize the queue

    // Demonstrate enqueue operation
    enqueue(&q, 10);
    enqueue(&q, 20);
    enqueue(&q, 30);
    enqueue(&q, 40);
    enqueue(&q, 50);
    enqueue(&q, 60);  // This should cause queue to be full

    // Display queue elements
    display(&q);

    // Demonstrate dequeue operation
    dequeue(&q);
    dequeue(&q);

    // Display queue elements after dequeuing
    display(&q);

    // Demonstrate enqueue after wrap around
    enqueue(&q, 60);
    display(&q);

    return 0;
}
