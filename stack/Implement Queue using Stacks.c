#include <stdio.h>
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
        printf("Stack is full but you are special, so I created extra space for you\n");
        stack->array = realloc(stack->array, 2 * stack->capacity * sizeof(int));
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
typedef struct {
    Stack* stack1;
    Stack* stack2;
} MyQueue;
MyQueue* myQueueCreate() {
    MyQueue* queue = (MyQueue*)malloc(sizeof(MyQueue));
    queue->stack1 = createStack(100);
    queue->stack2 = createStack(100);
    return queue;
}
void myQueuePush(MyQueue* obj, int x) {
    push(obj->stack1,x);
}

int myQueuePop(MyQueue* obj) {
    if (isEmpty(obj->stack1)) {
        return -1; 
    }
    while (!isEmpty(obj->stack1)) {
        push(obj->stack2, pop(obj->stack1));
    }
    int a=pop(obj->stack2);
    while (!isEmpty(obj->stack2)) {
        push(obj->stack1, pop(obj->stack2));
    }
    return a;
}

int myQueuePeek(MyQueue* obj) {
    if (isEmpty(obj->stack1)) {
        return -1; 
    }
    while (!isEmpty(obj->stack1)) {
        push(obj->stack2, pop(obj->stack1));
    }
    int a=peek(obj->stack2);
    while (!isEmpty(obj->stack2)) {
        push(obj->stack1, pop(obj->stack2));
    }
    return a;
}

int myQueueEmpty(MyQueue* obj) {
    return isEmpty(obj->stack1);
}

void myQueueFree(MyQueue* obj) {
    destroyStack(obj->stack1);
    destroyStack(obj->stack2);
    free(obj);
}