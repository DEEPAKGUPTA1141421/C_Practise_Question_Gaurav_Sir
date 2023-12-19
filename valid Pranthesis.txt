typedef struct {
    void** array;   
    size_t capacity;
    size_t size;    
} Stack;

Stack* createStack(size_t capacity) {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->capacity = capacity;
    stack->array = (void**)malloc(capacity * sizeof(void*));
    stack->size = 0;
    return stack;
}
int isEmpty(Stack* stack) {
    return stack->size == 0;
}
int isFull(Stack* stack) {
    return stack->size == stack->capacity;
}
void push(Stack* stack, void* item) {
    if (isFull(stack)) {
        printf("Stack is full but you are special, so I created extra space for you\n");
        stack->array = realloc(stack->array, 2 * stack->capacity * sizeof(void*));
        stack->capacity = 2 * stack->capacity;
    }
    stack->array[stack->size] = malloc(sizeof(char));
    *(char*)(stack->array[stack->size++]) = *(char*)item;
}
void pop(Stack* stack) {
    if (isEmpty(stack)) {
        printf("Stack underflow\n");
        return;
    }
    free(stack->array[--stack->size]);
}
void* peek(Stack* stack) {
    if (isEmpty(stack)) {
        printf("Stack is empty\n");
        return NULL;
    }
    void* result = malloc(sizeof(char));
    *(char*)result = *(char*)stack->array[stack->size - 1];
    return result;
}
void destroyStack(Stack* stack) {
    for (size_t i = 0; i < stack->size; ++i) {
        free(stack->array[i]);
    }
    free(stack->array);
    free(stack);
}

bool isValid(char* s) {
    Stack* stack = createStack(strlen(s));

    for (int i = 0; i < strlen(s); i++) {
        char c = s[i];
        void*ptr=&c;
        if (isEmpty(stack)) {
            push(stack, ptr);
        } else if (c == '(' || c == '{' || c == '[') {
            push(stack, ptr);
        } else {
            if (c == ')') {
                if (*(char*)peek(stack) == '(') {
                    pop(stack);
                } else {
                    return false;
                }
            }
            if (c == '}') {
                if (*(char*)peek(stack) == '{') {
                    pop(stack);
                } else {
                    return false;
                }
            }
            if (c == ']') {
                if (*(char*)peek(stack) == '[') {
                    pop(stack);
                } else {
                    return false;
                }
            }
        }
    }

    if (isEmpty(stack)) {
        destroyStack(stack);
        return true;
    }

    destroyStack(stack);
    return false;
}