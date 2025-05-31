#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 15

typedef struct {
    int items[MAX_SIZE];
    int top;
} Stack;

void initStack(Stack *s) {
    s->top = -1;
}

int isFull(Stack *s) {
    return s->top == MAX_SIZE - 1;
}

int isEmpty(Stack *s) {
    return s->top == -1;
}

void push(Stack *s, int value) {
    if (isFull(s)) {
        fprintf(stderr, "Помилка: Стек переповнений\n");
        exit(EXIT_FAILURE);
    }
    s->items[++(s->top)] = value;
}

int pop(Stack *s) {
    if (isEmpty(s)) {
        fprintf(stderr, "Помилка: Стек порожній (спроба pop)\n");
        exit(EXIT_FAILURE);
    }
    return s->items[(s->top)--];
}

void printAndRestoreStack(Stack *s, const char *name) {
    if (isEmpty(s)) {
        printf("Стек %s порожній.\n", name);
        printf("----\n");
        return;
    }

    Stack tempPrintStack;
    initStack(&tempPrintStack);

    printf("Вміст стека %s (з вершини до низу):\n", name);
    
    while (!isEmpty(s)) {
        int val = pop(s);
        printf("%d\n", val);
        push(&tempPrintStack, val);
    }

    while (!isEmpty(&tempPrintStack)) {
        push(s, pop(&tempPrintStack));
    }
    printf("----\n");
}

int main() {
    Stack s1, s2, tempStack;

    initStack(&s1);
    initStack(&s2);
    initStack(&tempStack);

    printf("Введіть 15 цілих чисел:\n");
    for (int i = 0; i < MAX_SIZE; i++) {
        int num;
        // printf("Число %d: ", i + 1); // Можна розкоментувати для нумерації вводу
        if (scanf("%d", &num) != 1) {
            fprintf(stderr, "Помилка: Некоректне введення\n");
            return EXIT_FAILURE;
        }
        push(&s1, num);
    }

    printf("\nПочатковий вигляд стека S1:\n");
    printAndRestoreStack(&s1, "S1 (Початковий)");

    while (!isEmpty(&s1)) {
        push(&tempStack, pop(&s1));
    }

    while (!isEmpty(&tempStack)) {
        int value = pop(&tempStack);
        push(&s1, value); 
        if (value < 0) {
            push(&s2, 0);
        } else {
            push(&s2, value);
        }
    }
    
    printf("\nСтек S1 після всіх операцій (має бути збережений):\n");
    printAndRestoreStack(&s1, "S1 (Після операцій)");

    printf("\nСформований стек S2 (від'ємні елементи замінено на 0):\n");
    printAndRestoreStack(&s2, "S2 (Результат)");
    
    printf("\nУсі операції завершено успішно.\n");
    printf("Стек S1 було сформовано, використано для створення S2 та збережено.\n");
    printf("Стек S2 було сформовано зі стека S1 із заміною від'ємних елементів на 0.\n");

    return EXIT_SUCCESS;
}