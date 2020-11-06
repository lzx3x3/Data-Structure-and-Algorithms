//Define a LinkedList Queue
typedef struct LLQueue {
	struct Node* head;
	struct Node* tail;
} LLQueue;

//Define a vertex Node
typedef struct Node {
	int index;
	int pre;
	struct Node* next;
} Node;


LLQueue* LLQ_create();

int isEmpty(LLQueue* LLQ);

int LLQ_insert(LLQueue* LLQ, int value, int pred);

int LLQ_insertHead(LLQueue* LLQ, int value, int pred);

Node* LLQ_delete(LLQueue* LLQ);

int LLQ_count(LLQueue* LLQ);

void LLQ_print(LLQueue* LLQ);

void LLQ_free(LLQueue* LLQ);

Node* read_adjacencies(FILE* fp);

void freeAll(Node *list);
