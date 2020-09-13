#ifndef LLQueue_H
#define LLQueue_H

typedef struct LLQueue LLQueue;
typedef struct Node Node;

LLQueue *LLQ_create();

int LLQ_insert(LLQueue* LLQ, double data);
double LLQ_delete(LLQueue* LLQ);
double* LLQ_Search(LLQueue* LLQ, double data);
double LLQ_minimum(LLQueue* LLQ);
double LLQ_maximum(LLQueue* LLQ);
unsigned int LLQ_count(LLQueue* LLQ);
void LLQ_print(LLQueue* LLQ);
void LLQ_free(LLQueue* LLQ);

#endif
