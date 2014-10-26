#include "mqueue.h"
int mq_init(mqueue *q) { /*{{{*/
	q_init(&q->q);
	if (q->flag == 0) {
		pthread_mutex_init(&q->m, NULL);
		pthread_cond_init(&q->c, NULL);
	}
	q->flag = 1;
} /*}}}*/
int mq_post(mqueue *q, int data0, void *data1) { /*{{{*/
	pthread_mutex_lock(&q->m);
	q_post(&q->q, data0, data1);
	pthread_cond_broadcast(&q->c);
	pthread_mutex_unlock(&q->m);
} /*}}}*/
int mq_get(mqueue *q, int *data0, void **data1) { /*{{{*/
	pthread_mutex_lock(&q->m);
	int r = q_get(&q->q, data0, data1);
	pthread_mutex_unlock(&q->m);
	return r;
} /*}}}*/
int mq_get_wait(mqueue *q, int *data0, void **data1) { /*{{{*/
	int r = 0;
	pthread_mutex_lock(&q->m);
	while ((r = q_get(&q->q, data0, data1)) == 0) {
		pthread_cond_wait(&q->c, &q->m);
	}
	pthread_mutex_unlock(&q->m);
	return r;
} /*}}}*/
void mq_purge(mqueue *q, void (*free_func)(int, void*, void*), void* d2) { /*{{{*/
	pthread_mutex_lock(&q->m);
	q_purge(&q->q, free_func, d2);
	pthread_mutex_unlock(&q->m);
} /*}}}*/
void mq_destroy(mqueue *q) { /*{{{*/
	if (q->flag == 0) {
		pthread_mutex_destroy(&q->m);
		pthread_cond_destroy(&q->c);
		q->flag = 1;
	}
} /*}}}*/
