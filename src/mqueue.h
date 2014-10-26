#ifndef __MQUEUE_H__
#define __MQUEUE_H__

#include "queue.h"
#include <pthread.h>

typedef struct {
	queue q;
	int flag;
	pthread_mutex_t m;
	pthread_cond_t c;
} mqueue;

int mq_init(mqueue *q);
int mq_post(mqueue *q, int data0, void *data1);
int mq_get(mqueue *q, int *data0, void **data1);
int mq_get_wait(mqueue *q, int *data0, void **data1);
void mq_purge(mqueue *q, void (*free_func)(int, void*, void*), void* d2);
void mq_destroy(mqueue *q);

#endif

