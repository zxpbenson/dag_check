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

#include "linked_deque.h"

// 初始化队列
void deque_init(deque_t *q) {
    q->front = NULL;
    q->rear = NULL;
    q->len = 0;
}

int deque_free(deque_t *q) {
    if(q == NULL) {
        return 0;
    }
    while(1) {
        if(deque_dequeue(q) == NULL) break;
    }
    //free(q);
    return 1;
}

// 判断队列是否为空
int deque_empty(deque_t *q) {
    return q->len == 0;
}

// 入队
int deque_enqueue(deque_t *q, void *val) {
    if(val == NULL) return 0;//不接受NULL值
    if (q->len == MAX_LEN) return 0;//队列为空
    item_t *new_item = malloc(sizeof(item_t));
    if(new_item == NULL) {//申请不到内存
        return -1;
    }
    new_item->val = val;
    new_item->next = NULL;

    if(q->len == 0) {
        new_item->prev = NULL;
        q->front = new_item;
        q->rear = new_item;
        q->len++;
        return 1;
    }

    q->rear->next = new_item;
    new_item->prev = q->rear;
    q->rear = new_item;
    q->len++;
    return 1;
}

// 出队
void *deque_dequeue(deque_t *q) {
    if (deque_empty(q)) return NULL;
    item_t *front = q->front;
    void *val = front->val;
    q->len--;
    if(deque_empty(q)) {
        q->front = NULL;
        q->rear = NULL;
    } else {
        q->front = front->next;;
    }
    free(front);
    printf("deque len : %d, front address : %p, rear address %p\n", q->len, q->front, q->rear);
    return val;
}

//删除指定元素
int deque_del(deque_t *q, void *val) {
    if(q == NULL || val == NULL) {
        return 0;
    }
    if(deque_empty(q)) {
        return 0;
    }
    if(q->front->val == val) {//对，你没看错，就是地址比较
        deque_first(q);
        return 1;
    }
    if(q->rear->val == val) {
        deque_last(q);
        return 1;
    }
    item_t *cur = q->front->next;//front前面已经比较过了
    while(1) {
        if(cur->val == val) {
            cur->prev->next = cur->next;
            cur->next->prev = cur->prev;
            free(cur);
            return 1;
        }
        cur = cur->next;
        if(cur == NULL) {
            break;
        }
    }
    return 0;
}

//弹出头部值 即出队操作
void *deque_first(deque_t *q) {
    return deque_dequeue(q);
}

//弹出尾部值
void *deque_last(deque_t *q) {
    if (deque_empty(q)) return NULL;
    item_t *item = q->rear;
    void *val = item->val;
    q->rear = item->prev;
    free(item);
    q->len--;
    if(deque_empty(q)) {
        q->front = NULL;//队列空时不需要对头字段rear置NULL，因为前面已经对rear置过尾部节点的prev的值，所以如果没有上一个节点，rear的值一定是NULL
    } else {
        q->rear->next = NULL;
    }
    return val;
}

