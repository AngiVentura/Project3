#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

typedef struct node
{
	unsigned int data;
	struct node* next;
}NODE;


typedef struct Queue
{
	NODE* head;
	NODE* tail;
} QUEUE;

int dequeue(QUEUE* q);
void enqueue(QUEUE* q, int data);
int isEmpty(QUEUE* q);
void initQueue(QUEUE* q);
void rotate(QUEUE* s);
int countQueue(QUEUE* s);
void cutAndReplace(QUEUE* s);
void reverseQueue(QUEUE* q);
int minQueue(QUEUE* s);
void sort(QUEUE* s);


void main()
{
	QUEUE Q;
	NODE* head = (NODE*)malloc(10 * sizeof(NODE));
	NODE* two = (NODE*)malloc(10 * sizeof(NODE));
	NODE* three = (NODE*)malloc(10 * sizeof(NODE));
	NODE* four = (NODE*)malloc(10 * sizeof(NODE));
	NODE* tail = (NODE*)malloc(10 * sizeof(NODE));

	Q.head = head;
	Q.tail = tail;
	head->next = two;
	two->next = three;
	three->next = four;
	four->next = tail;
	tail->next = NULL;


	head->data = 1;
	two->data = 2;
	three->data = 3;
	four->data = 4;
	tail->data = 5;

	sort(&Q);
	rotate(&Q);
	cutAndReplace(&Q);
}

void cutAndReplace(QUEUE* s)
{
	QUEUE q;
	initQueue(&q);
	int length = countQueue(s);

	if (length % 2)
	{
		enqueue(s, average(s));
		length++;
	}


	for (int i = 0; i < length / 2; i++)
		enqueue(&q, dequeue(s));


	reverseQueue(s);

	for (int i = 0; i < length / 2; i++)
		enqueue(s, dequeue(&q));
}

int average(QUEUE* s)
{
	int length = countQueue(s), sum = 0, res;
	QUEUE q;
	initQueue(&q);

	for (int i = 0; i < length; i++)
	{
		res = dequeue(s);
		sum += res;
		enqueue(&q, res);
	}

	for (int i = 0; i < length; i++)
	{
		res = dequeue(&q);
		enqueue(s, res);
	}
	return sum / length;
}


void rotate(QUEUE* s)
{
	int count = countQueue(s);
	int begin, end, res;
	QUEUE q1;
	q1.head = NULL;
	q1.tail = NULL;

	if (isEmpty(s))
		return;

	for (int i = 0; i < count - 1; i++)
	{
		res = dequeue(s);
		enqueue(&q1, res);
	}

	end = dequeue(s);

	enqueue(s, end);

	for (int i = 0; i < count - 1; i++)
		enqueue(s, dequeue(&q1));

}

int countQueue(QUEUE* s)
{
	QUEUE res;
	int resNum, count = 0;
	initQueue(&res);

	while (s->head != NULL)
	{
		resNum = dequeue(s);
		enqueue(&res, resNum);
		count++;
	}

	while (res.head != NULL)
	{
		resNum = dequeue(&res);
		enqueue(s, resNum);
	}
	return count;
}

int dequeue(QUEUE* q)
{
	if (isEmpty(q))
	{
		printf("empty!");
		return -1;
	}

	NODE* temp = q->head;
	int data = temp->data;
	q->head = q->head->next;
	if (q->head == NULL)
		q->tail = NULL;

	free(temp);
	return data;
}

void enqueue(QUEUE* q, int data)
{
	NODE* newNode = (NODE*)calloc(1, sizeof(NODE));
	newNode->data = data;

	if (!isEmpty(q)) {
		q->tail->next = newNode;
		q->tail = newNode;
		return;
	}
	q->head = q->tail = newNode;
}

int isEmpty(QUEUE* q)
{
	return q->head == NULL && q->tail == NULL;
}

void initQueue(QUEUE* q)
{
	q->head = q->tail = NULL;
}

void reverseQueue(QUEUE* q)
{
	QUEUE helper1, helper2;
	initQueue(&helper1); initQueue(&helper2);
	while (!isEmpty(q)) {
		while (!isEmpty(&helper1)) {
			enqueue(&helper2, dequeue(&helper1));
		}
		enqueue(&helper1, dequeue(q));
		while (!isEmpty(&helper2)) {
			enqueue(&helper1, dequeue(&helper2));
		}
	}
	while (!isEmpty(&helper1)) {
		enqueue(q, dequeue(&helper1));
	}
}

void sort(QUEUE* s)
{
	QUEUE q;
	initQueue(&q);
	int count = countQueue(s), min;

	for (int i = 0; i < count; i++)
	{
		min = minQueue(s);
		enqueue(&q, min);
	}

	for (int i = 0; i < count; i++)
		enqueue(s, dequeue(&q));
}

int minQueue(QUEUE* s)
{
	QUEUE q1, q2;
	initQueue(&q1); initQueue(&q2);
	int res, min = s->head->data;

	while (s->head != NULL)
	{
		res = dequeue(s);
		if (min > res)
			min = res;
		enqueue(&q1, res);
	}

	while (q1.head != NULL)
	{
		if (min == q1.head->data)
			dequeue(&q1);

		else
			enqueue(&q2, dequeue(&q1));
	}

	while (q2.head != NULL)
		enqueue(s, dequeue(&q2));

	return min;
}