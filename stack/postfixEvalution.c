#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    int* array;
    int capacity;
    int size;
} Stack;

Stack* createStack(size_t capacity) {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->capacity = capacity;
    stack->array = (int*)malloc(capacity * sizeof(int));
    stack->size = 0;
    return stack;
}

int isEmpty(Stack* stack) {
    return stack->size == 0;
}

int isFull(Stack* stack) {
    return stack->size == stack->capacity;
}

void push(Stack* stack, int item) {
    if (isFull(stack)) {
        int* temp = realloc(stack->array, 2 * stack->capacity * sizeof(int));

        if (temp == NULL) {
            printf("Memory reallocation failed\n");
            return;
        }

        stack->array = temp;
        stack->capacity = 2 * stack->capacity;
    }

    stack->array[stack->size++] = item;
}

int pop(Stack* stack) {
    if (isEmpty(stack)) {
        printf("Stack underflow\n");
        return -1;
    }
    return stack->array[--stack->size];
}

int peek(Stack* stack) {
    if (isEmpty(stack)) {
        return -1;
    }
    return stack->array[stack->size - 1];
}

void destroyStack(Stack* stack) {
    free(stack->array);
    free(stack);
}

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        char s[100];
        scanf(" %[^\n]s", s);
        int length = strlen(s);
        Stack* stack = createStack(length);
        int i = 0;
        
        while (s[i] != '?') {
            if (s[i] == ' ') {
                i++;
                continue;
            }

            if (s[i] >= '0' && s[i] <= '9') {
                int num = 0;
                while (s[i] >= '0' && s[i] <= '9') {
                    num = num * 10 + (s[i] - '0');
                    i++;
                }
                push(stack, num);
            } else {
                int a = peek(stack);
                pop(stack);
                int b = peek(stack);
                pop(stack);
                int evaluate;
                if (s[i] == '+') {
                    evaluate = a + b;
                } else if (s[i] == '-') {
                    evaluate = b - a;  
                } else if (s[i] == '*') {
                    evaluate = a * b;
                } else if (s[i] == '/') {
                    if (a != 0) {
                        evaluate = b / a;  
                    } else {
                        return -1;
                    }
                }
                push(stack, evaluate);
            }
            i++;
        }

        printf("%d\n", peek(stack));
        destroyStack(stack);
    }

    return 0;
}
