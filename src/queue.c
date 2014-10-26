#include "queue.h"
#include <stdlib.h>
int q_init(queue *q) { /*{{{*/
	if (q == NULL) {
		return -1;
	}
	q->first = NULL;
	q->last = NULL;
	return 0;
} /*}}}*/
int q_post(queue *q, int data0, void *data1) { /*{{{*/
	if (q == NULL) {
		return -1;
	}
	node *n = malloc(sizeof(node));
	if (n == NULL) {
		return -2;
	}
	n->data0 = data0;
	n->data1 = data1;
	n->next = NULL;
	if (q->first == NULL) { /* empty queue */
		q->first = n;
	}
	else { /* nonempty queue */
		q->last->next = n;
	}
	q->last = n;
	return 1;
} /*}}}*/
int q_get(queue *q, int *data0, void **data1) { /*{{{*/
	//*data0 = 0;
	//*data1 = NULL;
	if (q == NULL) {
		return -1;
	}
	node *n = q->first;
	if (n == NULL) {
		return 0;
	}
	if (n == q->last) { /* this was the last node */
		q->last = NULL;
	}
	q->first = n->next;
	*data0 = n->data0;
	*data1 = n->data1;
	free(n);
	return 1;
} /*}}}*/
void just_free(int d0, void *d1, void *d2) { /*{{{*/
	free(d1);
} /*}}}*/
void q_purge(queue *q, void (*free_func)(int, void*, void*), void *d2) { /*{{{*/
	if (free_func == NULL) {
		free_func = &just_free;
	}
	int d0;
	void *d1;
	while (q_get(q, &d0, &d1) == 1) {
		free_func(d0, d1, d2);
	}
} /*}}}*/
