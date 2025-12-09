#include <stdio.h>
#define MAX 50
#define RED "\033[1;31m"
#define GREEN "\033[1;32m"
#define YELLOW "\033[1;33m"
#define BLUE "\033[1;34m"
#define MAGENTA "\033[1;35m"
#define CYAN "\033[1;36m"
#define WHITE "\033[1;37m"
#define RESET "\033[0m"

typedef struct {
    int arr[MAX];
    int front, rear;
} Queue;
void init(Queue *q) {
    q->front = q->rear = -1;
}
int isEmpty(Queue *q) {
    return (q->front == -1 || q->front > q->rear);
}
int isFull(Queue *q) {
    return q->rear == MAX - 1;
}
void enqueue(Queue *q, int value) {
    if (isFull(q)) {
        printf("%sQueue is FULL!%s\n", RED, RESET);
        return;
    }
    if (q->front == -1) q->front = 0;
    q->arr[++q->rear] = value;
}
int dequeue(Queue *q) {
    if (isEmpty(q))
        return -1;
    return q->arr[q->front++];
}
void display(Queue *q) {
    if (isEmpty(q)) {
        printf("%s[ empty ]%s\n", CYAN, RESET);
        return;
    }
    for (int i = q->front; i <= q->rear; i++)
        printf("%s%d%s ", MAGENTA, q->arr[i], RESET);
    printf("\n");
}

void displayWaitingTimes(Queue *priorityQ, Queue *normalQ) {
    printf("\n%s========== ESTIMATED WAITING TIME FOR EACH TOKEN ==========%s\n", CYAN, RESET);
    
    int waitTime = 0;
    if (!isEmpty(priorityQ)) {
        printf("%sPRIORITY QUEUE:%s\n", RED, RESET);
        for (int i = priorityQ->front; i <= priorityQ->rear; i++) {
            printf("%sToken %d: %d minutes%s\n", GREEN, priorityQ->arr[i], waitTime, RESET);
            waitTime += 2;
        }
    }
    
    if (!isEmpty(normalQ)) {
        printf("%sNORMAL QUEUE:%s\n", BLUE, RESET);
        for (int i = normalQ->front; i <= normalQ->rear; i++) {
            printf("%sToken %d: %d minutes%s\n", YELLOW, normalQ->arr[i], waitTime, RESET);
            waitTime += 2;
        }
    }
    
    if (isEmpty(priorityQ) && isEmpty(normalQ)) {
        printf("%sNo customers in queue!%s\n", YELLOW, RESET);
    }
}
int queueSize(Queue *q) {
    if (isEmpty(q)) return 0;
    return q->rear - q->front + 1;
}
int estimateTime(int count) {
    return count * 2; 
}
int main() {
    Queue priorityQ, normalQ;
    init(&priorityQ);
    init(&normalQ);
    int choice, type;
    int token = 1;
    while (1) {
        printf("%s\n========== Bank Token Simulation ==========%s\n", CYAN, RESET);
        printf("%s1. Generate Token%s\n", YELLOW, RESET);
        printf("%s2. Serve Customer%s\n", GREEN, RESET);
        printf("%s3. Display Queue%s\n", BLUE, RESET);
        printf("%s4. Estimated Waiting Time%s\n", MAGENTA, RESET);
        printf("%s5. Next Customer%s\n", WHITE, RESET);
        printf("%s6. Exit%s\n", RED, RESET);
        printf("%sEnter your choice: %s", YELLOW, RESET);
        scanf("%d", &choice);
        switch(choice) {
        case 1:
            printf("%sCustomer Type? (1 = Priority, 2 = Normal): %s", CYAN, RESET);
            scanf("%d", &type);
            if (type == 1) {
                enqueue(&priorityQ, token);
                printf("%sPriority Token %d added.%s\n", GREEN, token, RESET);
            } else {
                enqueue(&normalQ, token);
                printf("%sNormal Token %d added.%s\n", BLUE, token, RESET);
            }
            token++;
            break;
        case 2: {
            int served;
            if (!isEmpty(&priorityQ)) {
                served = dequeue(&priorityQ);
                printf("%sServing PRIORITY customer token %d...%s\n", RED, served, RESET);
            }
            else if (!isEmpty(&normalQ)) {
                served = dequeue(&normalQ);
                printf("%sServing NORMAL customer token %d...%s\n", GREEN, served, RESET);
            }
            else {
                printf("%sNo customers to serve!%s\n", YELLOW, RESET);
            }
            break;
        }
        case 3:
            printf("\n%sPriority Queue: %s", MAGENTA, RESET);
            display(&priorityQ);
            printf("%sNormal Queue:   %s", BLUE, RESET);
            display(&normalQ);
            break;
        case 4: {
            displayWaitingTimes(&priorityQ, &normalQ);
            break;
        }
        case 5:
            if (!isEmpty(&priorityQ))
                printf("%sNext customer: Token %d (PRIORITY)%s\n", MAGENTA, priorityQ.arr[priorityQ.front], RESET);
            else if (!isEmpty(&normalQ))
                printf("%sNext customer: Token %d (NORMAL)%s\n", BLUE, normalQ.arr[normalQ.front], RESET);
            else
                printf("%sNo customers waiting.%s\n", YELLOW, RESET);
            break;
        case 6:
            printf("%sGoodbye!%s\n", GREEN, RESET);
            return 0;
        default:
            printf("%sInvalid choice!%s\n", RED, RESET);
        }
    }
}
