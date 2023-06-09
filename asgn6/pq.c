#include "pq.h"
#include "node.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct ListElement ListElement;

struct ListElement {
	Node *tree;
	ListElement *next;
};

struct PriorityQueue {
	ListElement *list;
};

PriorityQueue *pq_create(void){
	PriorityQueue *pq = calloc(1, sizeof(PriorityQueue));
	if (pq == NULL){
		fprintf(stderr, "pq_create");
	}
	return pq;
}

void pq_free(PriorityQueue **q){
	if (q != NULL && *q != NULL){
		free(*q);
	}
	if (q != NULL){
		*q = NULL;
	}
}

bool pq_is_empty(PriorityQueue *q){
	if (q->list == NULL)
		return true;
	return false;
}

bool pq_size_is_1(PriorityQueue *q){
	if (!pq_is_empty(q)){
		if (q->list->next == NULL)
			return true;
	}
	return false;
}
bool pq_less_than(Node *n1, Node *n2){
	if (n1->weight < n2->weight)
		return true;
	if (n1->weight > n2->weight)
		return false;
	return n1->symbol < n2->symbol;
}
void enqueue(PriorityQueue *q, Node *tree){
	ListElement *e = calloc(1, sizeof(ListElement));
	if (e == NULL){
		fprintf(stderr, "enqueue\n");
		exit(1);
	}
	e->tree = tree;
	if (pq_is_empty(q))
		q->list = e;
	else if (pq_less_than(e->tree, q->list->tree)){
		e->next = q->list;
		q->list = e;
	}
	else {
		ListElement *n = q->list;
		while(n != NULL){
			if (n->next == NULL || pq_less_than(e->tree, n->next->tree))
				break;
			n = n->next;
		}
		e->next = n->next;
		n->next = e;
		
	}
}

bool dequeue(PriorityQueue *q, Node **tree){
	if (pq_is_empty(q))
		return false;
	ListElement *d = q->list;
	q->list = q->list->next;
	*tree = d->tree;
	free(d);
	return true;
}

void pq_print(PriorityQueue *q){
	assert(q != NULL);
	ListElement *e = q->list;
	int position = 1;
	
	while (e != NULL) {
	
		if (position++ == 1) {
			printf("=============================================\n");
		} 
		else {
			printf("---------------------------------------------\n");
		}
	
		node_print_tree(e->tree, '<', 2);
		e = e->next;
	}
	
	printf("=============================================\n");
}


