#include <stdio.h>
#include <stdbool.h>
typedef struct {
    int size;
    int capacity;
    int front;
    int rear;
    int*array;
} MyCircularQueue;


MyCircularQueue* myCircularQueueCreate(int k) {
    MyCircularQueue*queue=(MyCircularQueue*)malloc(sizeof(MyCircularQueue));
    queue->array=(int*)malloc(k*sizeof(int));
    queue->capacity=k;
    queue->front=0;
    queue->rear=0;
    queue->size=0;
    return queue;
}

bool myCircularQueueEnQueue(MyCircularQueue* obj, int value) {
    if(obj->capacity==obj->size){
        return false;
    }
    obj->array[obj->rear]=value;
    obj->size+=1;
    obj->rear+=1;
    obj->rear=obj->rear%obj->capacity;
    return true;
}

bool myCircularQueueDeQueue(MyCircularQueue* obj) {
    if(obj->size==0){
        return false;
    }
    obj->front+=1;
    obj->front=obj->front%obj->capacity;
    obj->size-=1;
    return true;
}

int myCircularQueueFront(MyCircularQueue* obj) {
     if(obj->size==0){
        return -1;
    }
    return obj->array[obj->front];
}

int myCircularQueueRear(MyCircularQueue* obj) {
    if (obj->size == 0) {
        return -1;
    }
    int rearIndex = (obj->rear - 1 + obj->capacity) % obj->capacity;
    return obj->array[rearIndex];
}

bool myCircularQueueIsEmpty(MyCircularQueue* obj) {
    if(obj->size==0){
        return true;
    }
    return false;
}

bool myCircularQueueIsFull(MyCircularQueue* obj) {
    if(obj->capacity==obj->size){
        return true;
    }
    return false;
}

void myCircularQueueFree(MyCircularQueue* obj) {
    free(obj->array);
    free(obj);
}

/**
 * Your MyCircularQueue struct will be instantiated and called as such:
 * MyCircularQueue* obj = myCircularQueueCreate(k);
 * bool param_1 = myCircularQueueEnQueue(obj, value);
 
 * bool param_2 = myCircularQueueDeQueue(obj);
 
 * int param_3 = myCircularQueueFront(obj);
 
 * int param_4 = myCircularQueueRear(obj);
 
 * bool param_5 = myCircularQueueIsEmpty(obj);
 
 * bool param_6 = myCircularQueueIsFull(obj);
 
 * myCircularQueueFree(obj);
*/