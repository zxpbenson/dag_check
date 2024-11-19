/*
 * Copyright (C) 2024 张懿曦(Zhang Yixi)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef DAG_LINKED_DEQUE_H
#define DAG_LINKED_DEQUE_H
#include <stdio.h>
#include <stdlib.h>
#define MAX_LEN 1000

typedef struct item_s{
    void *val;
    struct item_s *prev;
    struct item_s *next;
} item_t;

// 队列操作
typedef struct deque_s {
    item_t *front;
    item_t *rear;
    int len;
} deque_t;

void  deque_init(deque_t *);
int   deque_free(deque_t *);
int   deque_empty(deque_t *);
int   deque_enqueue(deque_t *, void *);
void *deque_dequeue(deque_t *);
int   deque_del(deque_t *, void *);
void *deque_first(deque_t *);
void *deque_last(deque_t *);

#endif //DAG_LINKED_DEQUE_H
