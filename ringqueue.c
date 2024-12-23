// A simple fifo queue (or ring buffer) in c.
// This implementation \should be\ "thread safe" for single producer/consumer with atomic writes of size_t.
// This is because the head and tail "pointers" are only written by the producer and consumer respectively.
// Demonstrated with void pointers and no memory management.
// Note that empty is head==tail, thus only QUEUE_SIZE-1 entries may be used.

#include <stdlib.h>
#include <assert.h>
#include <ringqueue.h>

size_t queue_count(queue_t *queue) {
  return queue->head - queue->tail;
}

uint8_t queue_read(queue_t *queue) {
    if (queue->tail == queue->head) {
        return 0xff;
    }
    uint8_t handle = queue->data[queue->tail];
    // queue->data[queue->tail] = NULL;
    queue->tail = (queue->tail + 1) % queue->size;
    return handle;
}

int queue_write(queue_t *queue, uint8_t handle) {
    if (((queue->head + 1) % queue->size) == queue->tail) {
        return -1;
    }
    queue->data[queue->head] = handle;
    queue->head = (queue->head + 1) % queue->size;
    return 0;
}