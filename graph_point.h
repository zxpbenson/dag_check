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

#ifndef DAG_GRAPH_POINT_H
#define DAG_GRAPH_POINT_H

#include "linked_deque.h"

typedef struct point_s {
    int num;
    deque_t *from;//当前点为终点，队列from里的点是起点
    deque_t *to;//当前点为起点，队列to里的点是终点
    int queued; // 0 正常 1 加入待清理队列
} point_t;

//以指定的编号初始化一个点并返回内存地址
point_t *point_init(int num);
//释放指定点p及其占用的内存
int point_free(point_t *p);
//增加一条边，起点from，终点to，两个点双向关联
int point_add_edge(point_t *pa[], int from, int to);
//返回指定点p的入度
int point_in_degree(point_t *p);
//返回指定点p的出度
int point_out_degree(point_t *p);
//找出出度或者入度为0的点加入双端队列q
void point_find_term(point_t *pa[], int len, deque_t *q);
int point_del_rel(point_t *p, deque_t *q);
void point_free_arr(point_t *pa[], int len);

#endif //DAG_GRAPH_POINT_H
