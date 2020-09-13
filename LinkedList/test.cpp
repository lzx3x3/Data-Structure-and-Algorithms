#include <stdlib.h>
#include <stdio.h>

#include "LLQ.h"

int main() {
	
	LLQueue *q = LLQ_create();  //initialize a queue
	LLQ_insert(q, 1.00);
	LLQ_insert(q, 3.00);
	LLQ_insert(q, 4.00);
	LLQ_insert(q, 2.00);

	printf("Number of queue is: %d\n", LLQ_count(q));
	LLQ_print(q);

	
	printf("\nThe minimum of this queue is: %f\n", LLQ_minimum(q));
	
	printf("\nThe maximum of this queue is: %f\n", LLQ_maximum(q));

	LLQ_Search(q, 1.00);
	LLQ_Search(q, 2.00);
	LLQ_Search(q, 3.00);
	LLQ_Search(q, 5.00);

	LLQ_delete(q);
	LLQ_delete(q);

	printf("Number of queue is: %d\n", LLQ_count(q));
	LLQ_print(q);

	LLQ_delete(q);
	LLQ_delete(q);
	LLQ_delete(q);
	
	LLQ_free(q);
	
}