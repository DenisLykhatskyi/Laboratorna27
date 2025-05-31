#include <stdio.h>
#include <stdlib.h> // For exit()
#include <limits.h> // For INT_MIN

#define MAX_QUEUE_SIZE 10

typedef struct {
    int items[MAX_QUEUE_SIZE];
    int front;
    int rear;
    int count;
} Queue;

void initQueue(Queue *q) {
    q->front = 0;
    q->rear = -1;
    q->count = 0;
}

int isQueueFull(Queue *q) {
    return q->count == MAX_QUEUE_SIZE;
}

int isQueueEmpty(Queue *q) {
    return q->count == 0;
}

void enqueue(Queue *q, int value) {
    if (isQueueFull(q)) {
        fprintf(stderr, "Помилка: Черга повна\n");
        exit(EXIT_FAILURE);
    }
    q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
    q->items[q->rear] = value;
    q->count++;
}

int dequeue(Queue *q) {
    if (isQueueEmpty(q)) {
        fprintf(stderr, "Помилка: Черга порожня (спроба dequeue)\n");
        exit(EXIT_FAILURE);
    }
    int value = q->items[q->front];
    q->front = (q->front + 1) % MAX_QUEUE_SIZE;
    q->count--;
    return value;
}

int main() {
    Queue q1;
    initQueue(&q1);
    int tempStorage[MAX_QUEUE_SIZE];
    int tempCount = 0;

    printf("Введіть 10 цілих чисел для заповнення черги:\n");
    for (int i = 0; i < MAX_QUEUE_SIZE; i++) {
        int num;
        if (scanf("%d", &num) != 1) {
            fprintf(stderr, "Помилка: Некоректне введення.\n");
            return EXIT_FAILURE;
        }
        enqueue(&q1, num);
    }

    if (isQueueEmpty(&q1)) {
        printf("Черга порожня, неможливо знайти максимальний елемент.\n");
        return EXIT_SUCCESS;
    }

    int maxElement = INT_MIN;
    int maxPosition = -1;
    int currentPosition = 0;
    
    while (!isQueueEmpty(&q1)) {
        currentPosition++;
        int val = dequeue(&q1);
        tempStorage[tempCount++] = val;

        if (val > maxElement) {
            maxElement = val;
            maxPosition = currentPosition;
        }
    }

    for (int i = 0; i < tempCount; i++) {
        enqueue(&q1, tempStorage[i]);
    }

    printf("Максимальний елемент у черзі: %d\n", maxElement);
    printf("Його номер (позиція) у черзі: %d\n", maxPosition);

    return EXIT_SUCCESS;
}