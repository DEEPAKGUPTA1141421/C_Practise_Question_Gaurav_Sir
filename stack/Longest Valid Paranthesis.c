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
        
        // Use a temporary pointer to store the result of realloc
        int* temp = realloc(stack->array, 2 * stack->capacity * sizeof(int));

        if (temp == NULL) {
            printf("Memory reallocation failed\n");
            return;
        }

        // Update the stack's array and capacity
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
int max(int a, int b) {
    return (a > b) ? a : b;
}
int longestValidParentheses(char* s) {
     int n=strlen(s);
     Stack*stack=createStack(n);
     push(stack,-1);
     int cnt = 0;
     for(int i=0;i<n;i++){
         char c = s[i];
         if(c == '(')
             push(stack,i);
         else{
             if(isEmpty(stack)!=1){
                 pop(stack);
             }
             if(isEmpty(stack)!=1){
                 cnt = max(cnt , i - peek(stack));
             }
             else 
                 push(stack,i);
         }
     }
     return cnt;
}
