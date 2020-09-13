#include <stdlib.h>
#include <stdio.h>

//Define a LinkedList Queue
typedef struct LLQueue {
	struct Node *head;
	struct Node *tail;
} LLQueue;

//Define a Node
typedef struct Node {
	double data;
	struct Node *next;
} Node;


LLQueue *LLQ_create() {

	LLQueue *LLQ = (LLQueue*)malloc(sizeof(struct LLQueue));

	if (LLQ == NULL) {
		printf("Opertation fails!\n");
		return NULL;
	}
	LLQ->head = NULL;
	LLQ->tail = NULL;
	
	return LLQ;
}


int LLQ_insert(LLQueue *LLQ, double value) {
	//create a new Node
	Node *tmp = (Node*)malloc(sizeof(struct Node));
	tmp->data = value;
	tmp->next = NULL;

	//if queue is empty, add the new node into both queue head and tail
	if (LLQ->head == NULL) {
		LLQ->head = tmp;
		LLQ->tail = tmp;
		return 0;
	}
	//if queue not empty, add the new node at the tail of queue; change tail
	else {
		LLQ->tail->next = tmp;
		LLQ->tail = tmp;
		return 0;
	} 
}


double LLQ_delete(LLQueue* LLQ) {
	if (LLQ->head == NULL) {
		return 0;
	}
	else { //if queue is not null, return the data of head node, remove the head node
		Node* tmp = LLQ->head;

		double value = LLQ->head->data;
		
		LLQ->head = LLQ->head->next;

		free(tmp);
		return value;
	}
}


double *LLQ_Search(LLQueue* LLQ, double value) {
	if (LLQ->head == NULL) {
		printf("Queue is empty!\n");
		return 0;
	}
	//create a pointer *tmp
	Node *tmp = LLQ->head;
	bool flag = false;

	while (tmp != LLQ->tail->next) {
	if (tmp->data == value) {
		flag = true;
		printf("Data %f is found!\n", value);
		return &tmp->data;
		//return tmp->data;
	}
		//move pointer to the next node
		tmp= tmp->next;
	}

	if (!flag) {
		printf("Data %f not found!\n", value);
		return NULL;
	}
	free(tmp);
}


double LLQ_minimum(LLQueue* LLQ) {
	if (LLQ->head == NULL) {
		printf("Queue is empty!\n");
		return 0;
	}
	
	//create a pointer *tmp
	Node* tmp = LLQ->head;
	//create a double min
	Node* min = LLQ->head;
	
	while (tmp != LLQ->tail->next) {
		
		if (tmp->data <= min->data) {
			min = tmp;
		}
		//move pointer to the next node
		tmp = tmp->next;
	}
	return min->data;

	free(tmp), free(min);
}


double LLQ_maximum(LLQueue* LLQ) {
	if (LLQ->head == NULL) {
		printf("Queue is empty!\n");
		return 0;
	}
	
	//create a pointer *tmp
	Node* tmp = LLQ->head;
	//create a double max
	double max = tmp->data;

	while (tmp != LLQ->tail->next) {
		
		if (tmp->data >= max) {
			max = tmp->data;
		}
		//move pointer to the next node
		tmp = tmp->next;
	}
	return max;

	free(tmp);
}


unsigned int LLQ_count(LLQueue* LLQ) {
	int count = 0;
	if (LLQ->head == NULL) {
		return 0;
	}
	//create a pointer *tmp
	Node* tmp = LLQ->head;

	while (tmp != LLQ->tail->next) {

		//move pointer to the next node
		tmp = tmp->next;
		count++;
	}
	free(tmp);
	return count;
}


void LLQ_print(LLQueue* LLQ) {

	if (LLQ->head == NULL) {
		printf("Queue is empty!\n");
		return;
	}
	//create a pointer *tmp
	Node* tmp = LLQ->head;

	while (tmp != LLQ->tail->next) {

		//print data items from head to tail of queue
		printf("\n%f\t", tmp->data);
		//move pointer to the next node
		tmp = tmp->next;
	}
	free(tmp);
}


void LLQ_free(LLQueue* LLQ) {
	free(LLQ);
}
