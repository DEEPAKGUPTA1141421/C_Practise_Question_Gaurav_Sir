#include<stdio.h>
#include<limits.h>
#include<stdlib.h>
typedef struct {
    char* array;
    int capacity;
    int size;
} Stack;

Stack* createStack(size_t capacity) {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->capacity = capacity;
    stack->array = (char*)malloc(capacity * sizeof(char));
    stack->size = 0;
    return stack;
}

int isEmpty(Stack* stack) {
    return stack->size == 0;
}

int isFull(Stack* stack) {
    return stack->size == stack->capacity;
}

void push(Stack* stack, char item) {
    if (isFull(stack)) {
        printf("Stack is full but you are special, so I created extra space for you\n");
        stack->array = realloc(stack->array, 2 * stack->capacity * sizeof(char));
        stack->capacity = 2 * stack->capacity;
    }
    stack->array[stack->size++]=item;
    // stack->array[stack->size] = malloc(sizeof(char));
    // *(char*)(stack->array[stack->size++]) = *(char*)item;
}

void pop(Stack* stack) {
    
    if (isEmpty(stack)) {
        printf("Stack underflow\n");
        return;
    }
    stack->size--;
}

char peek(Stack* stack) {
    if (isEmpty(stack)) {
        printf("Stack is empty\n");
        return NULL;
    }

    // Allocate memory for the result
    return stack->array[stack->size-1];
}

void destroyStack(Stack* stack) {
    free(stack->array);
    free(stack);
}

char* removeDuplicateLetters(char* s) {
    int n = strlen(s);
    Stack* stack = createStack(n);
    int arr[26];
    for(int i=0;i<26;i++){
        arr[i]=0;
    }
    for (int i = 0; i < n; i++) {
        arr[s[i] - 'a'] = i;
    }
    for(int i=0;i<26;i++){
        printf("%d ",arr[i]);
    }
    for (int i = 0; i < n; i++) {
        char c = s[i];
        if (isEmpty(stack)) {
            printf("1 ");
            push(stack,c);
        } else if (peek(stack) > c && arr[peek(stack) - 'a'] > i) {
            printf("2 ");
            while (isEmpty(stack) != 1 && peek(stack) > c && arr[peek(stack) - 'a'] > i) {
                printf("3 ");
                pop(stack);
            }
            push(stack,c);
        } else {
            printf("4 ");
            push(stack,c);
        }
    }
    printf("size of stack is %d",stack->size);
    char* ans = (char*)malloc((stack->size + 1) * sizeof(char));
    int i = stack->size - 1;
    while (isEmpty(stack) != 1) {
        printf("inside ");
        ans[i] = peek(stack);
        printf("%c",ans[i]);
        pop(stack);
        i--;
    }
    printf("\n");
    printf("%s",ans);
    ans[stack->size] = '\0';
    destroyStack(stack);
    return ans;
}


