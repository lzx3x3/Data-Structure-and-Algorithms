#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "solve.h"


void bfs(Node** adj_list, int start, int end, int n_vertices);

int main(int argc, char** argv) {

	if (2 != argc) {
		printf("Please input the name of the input grid!\n");
		return 1;
	}
	FILE* inputMaze = fopen(argv[1], "r");
	if (inputMaze == NULL) {
		fprintf(stderr, "Could not open the file:\t%s\n", argv[1]);
		perror("Failed to open grid");
		return 2;
	}

	int row, col;
	int readIn = fscanf(inputMaze, "%d %d", &row, &col);
	int* maze = (int*)malloc(row * col * sizeof(int));

	int start, end;
	readIn = fscanf(inputMaze, "%d %d", &start, &end);
	printf("row: %d\ncol: %d\nstart: %d\nend:%d\n", row, col, start, end);
	
	int n_vertices = row*col;
	printf("Reading adjacency list in inputMaze for %d vertices:\n", n_vertices);


	Node **adj_list = (Node**)malloc(n_vertices * sizeof(Node*));
	for (int i = -1; i < n_vertices; i++)
	{
		*(adj_list + i) = NULL;
		*(adj_list + i) = read_adjacencies(inputMaze);	
		
	}

		
	// Print out the adjacency list we read in
	for (int i = 0; i < n_vertices; i++)
	{
		Node *adj = *(adj_list + i);
		
		printf("Vertex %d is adjacent to:  ",i);
		
		while (adj != NULL)
			{
			adj->pre = i;
			printf("%d", adj->index);
			printf("[%d], ", adj->pre);
			
			adj = adj->next;
			}
			printf("\n");
	}
			

	fclose(inputMaze);

	printf("\n\n");
	bfs(adj_list, start, end, n_vertices);

	freeAll(*adj_list);

	return 0;
}


void bfs(Node **adj_list, int start, int end, int n_vertices) {
	int i = start;
	int flag = 0;
	int visit[n_vertices]; //use an array to indicate a vertex has been visited or not
	         
	for (int j = 0; j < n_vertices; j++) {
		visit[j] = 0;
	}
	
	printf("maze solution is: ");

	LLQueue* queue = LLQ_create();  //initialize a queue to store vertex unexplored
	LLQ_insert(queue, i, i);
	//LLQ_print(queue);

	int pred = start;
	while (!isEmpty(queue) && !flag) {
		
		Node* tmp = LLQ_delete(queue); //pop the first vertex (FIFO)
		i = tmp->index;
		
		visit[i] = 1;
		
		//printf("queue delete vertex: %d\n", i);
		printf("Vertex %d[%d] -> ", tmp->index, tmp->pre);
		pred = tmp->index;

		free(tmp);

		Node* adj = *(adj_list + i);
		adj->pre = pred;

		//printf("Vertex %d[%d](%d) -> ", adj->index, adj->pre, visit[adj->index]);
				
		
		while(adj->next != NULL) {
			if (adj->index == end) {
				visit[adj->index] = 1;
				flag = 1;
				printf("Vertex %d[%d], end!\n", adj->index, adj->pre);
				break;
			}
			//printf("Vertex %d[%d](%d) -> ", adj->index, adj->pre, adj->visit);
			
			adj = adj->next;
			
			if (visit[adj->index] == 0) {
				LLQ_insert(queue, adj->index, pred);
				//LLQ_print(queue);
			}
			
		}
	}
	if (!flag) {
		printf("No maze solution!\n");
	}
	LLQ_free(queue);
	//freeAll(adj_list);
}
