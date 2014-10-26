#ifndef __QUEUE_H__
#define __QUEUE_H__

typedef struct queue_n {
	int data0;
	void *data1;
	struct queue_n *next;
} node;

typedef struct {
	node *first;
	node *last;
} queue;

typedef struct {
	void (*ff)(void*,void*);
	void *ud;
} ffs_data;

int q_init(queue *q);
int q_post(queue *q, int data0, void *data1);
int q_get(queue *q, int *data0, void **data1);
void q_purge(queue *q, void (*free_func)(int, void*, void*), void* d2);

#endif
