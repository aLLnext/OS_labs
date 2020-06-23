/* Example code for Think OS.

Copyright 2015 Allen Downey
License: Creative Commons Attribution-ShareAlike 3.0

*/

#include "utils.h"
#include <assert.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_CHILDREN 2
#define QUEUE_LENGTH 16000

// QUEUE

typedef struct {
  int *array;
  int length;
  int next_in;
  int next_out;
} Queue;

Queue *make_queue(int length) {
  Queue *queue = (Queue *)malloc(sizeof(Queue));
  queue->length = length;
  queue->array = (int *)malloc(length * sizeof(int));
  queue->next_in = 0;
  queue->next_out = 0;
  return queue;
}

int queue_incr(Queue *queue, int i) { return (i + 1) % queue->length; }

int queue_empty(Queue *queue) {
  // queue is empty if next_in and next_out are the same
  return (queue->next_in == queue->next_out);
}

int queue_full(Queue *queue) {
  // queue is full if incrementing next_in lands on next_out
  return (queue_incr(queue, queue->next_in) == queue->next_out);
}

void queue_push(Queue *queue, int item) {
  if (queue_full(queue)) {
    perror_exit("queue is full");
  }

  queue->array[queue->next_in] = item;
  queue->next_in = queue_incr(queue, queue->next_in);
}

int queue_pop(Queue *queue) {
  if (queue_empty(queue)) {
    perror_exit("queue is empty");
  }

  int item = queue->array[queue->next_out];
  queue->next_out = queue_incr(queue, queue->next_out);
  return item;
}

// SHARED

typedef struct {
  Queue *queue;
} Shared;

Shared *make_shared() {
  Shared *shared = check_malloc(sizeof(Shared));
  shared->queue = make_queue(QUEUE_LENGTH);
  return shared;
}

// THREAD

pthread_t make_thread(void *(*entry)(void *), Shared *shared) {
  int ret;
  pthread_t thread;

  ret = pthread_create(&thread, NULL, entry, (void *)shared);
  if (ret != 0) {
    perror_exit("pthread_create failed");
  }
  return thread;
}

void join_thread(pthread_t thread) {
  int ret = pthread_join(thread, NULL);
  if (ret == -1) {
    perror_exit("pthread_join failed");
  }
}

// PRODUCER-CONSUMER

void *producer_entry(void *arg) {
  int i;
  Shared *shared = (Shared *)arg;
  for (i = 0; i < QUEUE_LENGTH - 1; i++) {
    printf("adding item %d\n", i);
    queue_push(shared->queue, i);
  }
  pthread_exit(NULL);
}

void *consumer_entry(void *arg) {
  int i;
  int item;
  Shared *shared = (Shared *)arg;

  for (i = 0; i < QUEUE_LENGTH - 1; i++) {
    item = queue_pop(shared->queue);
    printf("consuming item %d\n", item);
  }
  pthread_exit(NULL);
}

// TEST CODE

void queue_test() {
  int i;
  int item;
  int length = 128;

  Queue *queue = make_queue(length);
  assert(queue_empty(queue));
  for (i = 0; i < length - 1; i++) {
    queue_push(queue, i);
  }
  assert(queue_full(queue));
  for (i = 0; i < 10; i++) {
    item = queue_pop(queue);
    assert(i == item);
  }
  assert(!queue_empty(queue));
  assert(!queue_full(queue));
  for (i = 0; i < 10; i++) {
    queue_push(queue, i);
  }
  assert(queue_full(queue));
  for (i = 0; i < 10; i++) {
    item = queue_pop(queue);
  }
  assert(item == 19);
}

void *test_safety_push(void *arg) {
  Queue *queue = ((Shared *)arg)->queue;
  for (int i = 0; i < (QUEUE_LENGTH - 1) / 2; ++i) {
    queue_push(queue, 1);
  }
  pthread_exit(NULL);
}

void *test_safety_push_2(void *arg) {
  Queue *queue = ((Shared *)arg)->queue;
  for (int i = 0; i < (QUEUE_LENGTH - 1) / 2  + 1; ++i) {
    queue_push(queue, 2);
  }
  pthread_exit(NULL);
}

void *test_empty_sleep(void *arg) {
  Queue *queue = ((Shared *)arg)->queue;
  sleep(1);
  queue_push(queue, 1);
  pthread_exit(NULL);
}

void *test_empty_pop(void *arg) {
  Queue *queue = ((Shared *)arg)->queue;
  queue_pop(queue);
  pthread_exit(NULL);
}

void *test_queue_full(void *arg) {
  Queue *queue = ((Shared *)arg)->queue;
  for (int i = 0; i < QUEUE_LENGTH; ++i) {
    queue_push(queue, 1);
  }
  pthread_exit(NULL);
}

void *test_full_sleep(void *arg) {
  Queue *queue = ((Shared *)arg)->queue;
  sleep(1);
  queue_pop(queue);
  pthread_exit(NULL);
}


int main(int argc, char *argv[]) {
  pthread_t child[NUM_CHILDREN];

  Shared *shared = make_shared();

  if (argc != 2) {
    return EXIT_FAILURE;
  }

  int code = atoi(argv[1]);
  printf("code: %i\n", code);
  switch (code) {
    case 1: {
      for (int i = 0; i < QUEUE_LENGTH; ++i) {
        shared->queue->array[i] = 0;
      }

      child[0] = make_thread(test_safety_push, shared);
      child[1] = make_thread(test_safety_push_2, shared);

      for (int i = 0; i < NUM_CHILDREN; i++) {
        join_thread(child[i]);
      }

      int flag = 2;
      for (int i = 0; i < QUEUE_LENGTH; ++i) {
        if (!(shared->queue->array[i])) {
          flag--;
        }
        assert(flag);
      }

    }
    case 2: {
      child[0] = make_thread(test_empty_sleep, shared);
      child[1] = make_thread(test_empty_pop, shared);

      for (int i = 0; i < NUM_CHILDREN; i++) {
        join_thread(child[i]);
      }
    }
    case 3: {
      child[0] = make_thread(test_full_sleep, shared);
      child[1] = make_thread(test_queue_full, shared);

      for (int i = 0; i < NUM_CHILDREN; i++) {
        join_thread(child[i]);
      }
    }
  }

  return 0;
}
