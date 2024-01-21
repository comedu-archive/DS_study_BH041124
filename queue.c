#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 노드 정의하기
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// 큐 정의
typedef struct {
    Node* front;
    Node* rear;
} Queue;

// 큐 만들기
Queue* create() {
    Queue* newQueue = (Queue*)malloc(sizeof(Queue));
    if (newQueue == NULL) {
        fprintf(stderr, "메모리 할당 오류\n");
        exit(EXIT_FAILURE);
    }
    newQueue->front = newQueue->rear = NULL;
    return newQueue;
}

// 큐에 머 집어넣기
void enqueue(Queue* queue, int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        fprintf(stderr, "메모리 할당 오류\n");
        exit(EXIT_FAILURE);
    }
    newNode->data = data;
    newNode->next = NULL;

    if (queue->rear == NULL) {
        queue->front = queue->rear = newNode;
    } else {
        queue->rear->next = newNode;
        queue->rear = newNode;
    }
}

// 요소 빼기
void dequeue(Queue* queue) {
    if (queue->front == NULL) {
        fprintf(stderr, "Queue is empty\n");
        exit(EXIT_FAILURE);
    }
    Node* temp = queue->front;
    queue->front = temp->next;

    if (queue->front == NULL) {
        queue->rear = NULL;
    }

    free(temp);
}

//큐 맨 앞 요소 반환
int peek(Queue* queue) {
    if (queue->front == NULL) {
        fprintf(stderr, "Queue is empty\n");
        exit(EXIT_FAILURE);
    }
    return queue->front->data;
}

// 큐 비어있는지 확인
int is_empty(Queue* queue) {
    return queue->front == NULL;
}

// 큐 크기
int size(Queue* queue) {
    int count = 0;
    Node* current = queue->front;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    return count;
}

// 초기화하기
void clear(Queue** queue) {
    while (!is_empty(*queue)) {
        dequeue(*queue);
    }
    free(*queue);
    *queue = NULL;
}

// 출력
void print(Queue* queue) {
    if (is_empty(queue)) {
        printf("Queue is empty\n");
        return;
    }

    Node* current = queue->front;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

// 큐 꽉찼는지 확인
int is_full(Queue* queue) {
    return 0;
}

//메인 함수
int main() {
    Queue* myQueue = create();

    char input[999];

    while (1) {
        printf("Enter command: ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = '\0';

        int data;
        switch (input[0]) {
        case '+':
            enqueue(myQueue, atoi(input + 1));
            break;

        case '-':
            if (!is_empty(myQueue)) {
                printf("Dequeue: %d\n", peek(myQueue));
                dequeue(myQueue);
            } else {
                printf("Queue is empty.\n");
            }
            break;

        case 'P':
            if (!is_empty(myQueue)) {
                printf("Peek: %d\n", peek(myQueue));
            } else {
                printf("Queue is empty.\n");
            }
            break;

        case 'L':
            print(myQueue);
            break;

        case 'F':
            printf("Is Full: %s\n", is_full(myQueue) ? "true" : "false");
            break;

        case 'E':
            printf("Is Empty: %s\n", is_empty(myQueue) ? "true" : "false");
            break;

        case '#':
            printf("Size: %d\n", size(myQueue));
            break;

        case '0':
            printf("Exiting the program.\n");
            clear(&myQueue);
            return 0;

        case 'C':
            clear(&myQueue);
            printf("Queue cleared.\n");
            return 0;

        default:
            printf("Invalid choice! Please enter a valid option.\n");
        }
    }

    return 0;
}