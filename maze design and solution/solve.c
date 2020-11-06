#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "solve.h"

//queue
LLQueue* LLQ_create() {

	LLQueue* LLQ = (LLQueue*)malloc(sizeof(struct LLQueue));

	if (LLQ == NULL) {
		printf("Opertation fails!\n");
		return NULL;
	}
	LLQ->head = NULL;
	LLQ->tail = NULL;

	return LLQ;
}


int isEmpty(LLQueue* LLQ) {
	if (LLQ->head == NULL) {
		return 1;
	}
	return 0;
	
}


int LLQ_insert(LLQueue* LLQ, int value, int pred) {
	//create a new Node
	Node* tmp = (Node*)malloc(sizeof(struct Node));
	tmp->index = value;
	tmp->pre = pred;
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



int LLQ_insertHead(LLQueue* LLQ, int value, int pred) {
	//create a new Node
	Node* tmp = (Node*)malloc(sizeof(struct Node));
	tmp->index = value;
	tmp->pre = pred;
	tmp->next = NULL;

	//if queue is empty, add the new node into both queue head and tail
	if (LLQ->head == NULL) {
		LLQ->head = tmp;
		LLQ->tail = tmp;
		return 0;
	}
	//if queue not empty, add the new node at the head of queue; change head
	else {
		tmp->next = LLQ->head;
		LLQ->head = tmp;
		return 0;
	}
}


Node* LLQ_delete(LLQueue *LLQ) {
	if (LLQ->head == NULL) {
		return NULL;
	}
	else { //if queue is not null, return the data of head node, remove the head node
		Node* tmp = LLQ->head;
		LLQ->head = LLQ->head->next;
		return tmp;
	}
}




int LLQ_count(LLQueue* LLQ) {
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
		printf("\nqueue contains vertex: %d\t", tmp->index);
		//move pointer to the next node
		tmp = tmp->next;
	}
	free(tmp);
}


void LLQ_free(LLQueue* LLQ) {
	free(LLQ);
}



//read_adj_list (Reference TA's "graphEx.c" codes!!!!!)

#define LINEBUF_SIZE 1000


// Buffer for holding lines from adjacency list file
static char line_buffer[LINEBUF_SIZE];

int i = 0;

Node* read_adjacencies(FILE* fp)
{
	// Can't read if we've reached end of file
	if (feof(fp))
	{
		return NULL;
	}

	// Read the next line into the buffer. On failure, return null.
	char* line = fgets(line_buffer, LINEBUF_SIZE, fp);
	if (line == NULL)
	{
		return NULL;
	}

	Node *adjacencies = NULL;
	Node *adj_end = NULL;

	size_t line_length = strlen(line);

	// If this line is just too long to parse, fail
	if ((line_length == LINEBUF_SIZE - 1) && (line[LINEBUF_SIZE - 2] != '\n')
		&& (!feof(fp)))
	{
		fprintf(stderr, "Encountered a line longer than max allowed size"
			" (%d).\n", LINEBUF_SIZE - 1);
		return NULL;
	}

	char* endptr = line;

	// Loop through the line until we've read in all present adjacent vertices.
	while (*endptr != '\0')
	{

		// Skip all whitespace
		while (isspace(*endptr) && (*endptr != '\n'))
		{
			endptr++;
		}

		// If we've skipped to the null-byte or a newline character, then we're
		// done parsing this line.
		if ((*endptr == '\n') || (*endptr == '\0'))
		{
			break;
		}

		char* next_num = endptr;

	
		// Parse a number from the current position in the line, which will be our next adjacent vertex.
		int errno = 0;
		int myAdj = strtol(next_num, &endptr, 10);
		if (errno || ((!isspace(*endptr)) && (*endptr != '\0')))
		{
			return NULL;
		}

		// If this is our first adjacent vertex, initialize the linked list.
		// Otherwise, append to the existing linked list.
		if (adjacencies == NULL)
		{
			adjacencies = (Node*)malloc(sizeof(Node));
			Node *head = (Node*)malloc(sizeof(Node));
			adj_end = head;
			adjacencies->next = head;
			head->next = NULL;
			adjacencies->index = i;
			head->index = myAdj;
			i++;
		}
		else
		{
			Node *tmp = (Node*)malloc(sizeof(Node));

			tmp->next = NULL;
			tmp->index = myAdj;
			
			adj_end->next = tmp;
			adj_end = tmp;
		}
		
	}

	return adjacencies;
}



// Frees all nodes in the given linked list.
void freeAll(Node *list)
{
	Node *toFree = list;
	Node *next = NULL;

	while (toFree != NULL)
	{
		next = toFree->next;
		free(toFree);
		toFree = next;
	}
}
