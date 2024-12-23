/*
 * Copyright 2024, Steve Calfee. All rights reserved.
 * SPDX-License-Identifier: BSD-3-Clause
 * Idea spawned from circular_buffer app
 */
#ifndef _RING_QUEUE_H_
#define _RING_QUEUE_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    size_t head;
    size_t tail;
    size_t size;
    uint8_t *data;
} queue_t;

uint8_t queue_read(queue_t *queue);
int queue_write(queue_t *queue, uint8_t handle);
size_t queue_count(queue_t *queue);
#endif
