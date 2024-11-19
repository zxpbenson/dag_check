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

#include "graph_point.h"

//以指定的编号初始化一个点并返回内存地址
point_t *point_init(int num) {
    point_t *p = malloc(sizeof(point_t));
    if(p == NULL) {
        return NULL;
    }
    p->queued = 0;
    p->num = num;
    p->from = malloc(sizeof(deque_t));
    p->to = malloc(sizeof(deque_t));
    if(p->from == NULL || p->to == NULL) {//检查是否还有内存
        free(p->from);
        free(p->to);
        free(p);
        return NULL;
    }
    deque_init(p->from);//这一步必须做，否则会有野指针
    deque_init(p->to);//这一步必须做，否则会有野指针
    return p;
}

//释放指定点p及其占用的内存
int point_free(point_t *p) {
    if(p == NULL) {
        return 0;
    }
    deque_free(p->from);
    deque_free(p->to);
    free(p->from);
    free(p->to);
    //free(p);
    return 1;
}

//增加一条边，起点from，终点to，两个点双向关联
int point_add_edge(point_t *pa[], int from, int to) {
    return deque_enqueue(pa[to]->from, (void *)pa[from]) && deque_enqueue(pa[from]->to, (void *)pa[to]);
}

//返回指定点p的入度
int point_in_degree(point_t *p) {
    return p->from->len;
}

//返回指定点p的出度
int point_out_degree(point_t *p) {
    return p->to->len;
}

//找出出度或者入度为0的点加入双端队列q
void point_find_term(point_t *pa[], int len, deque_t *q) {
    int i;
    for(i = 0; i < len; i++) {
        //printf("point %d in_degree %d, out_degree %d\n", pa[i]->num, point_in_degree(pa[i]), point_out_degree(pa[i]));
        if(point_in_degree(pa[i]) == 0 || point_out_degree(pa[i]) == 0) {
            printf("point %d enqueue, wait to clean\n", pa[i]->num);
            deque_enqueue(q, pa[i]);
        }
    }
}


int point_del_rel(point_t *p, deque_t *q) { //删除指定点的关联点对他的关联关系
    if(p == NULL) {
        return 0;
    }
    if(point_in_degree(p) > 0) {//指定点的入度大于0，说明有好多点以此指定点为终点
        point_t *from;
        while(1) {
            from = (point_t *)deque_dequeue(p->from);//遍历以指定点为终点的点
            if(from == NULL) {
                break;
            }
            deque_del(from->to, p);//从以指定点为终点的点中删除和指定点的关联关系
            printf("point %d in_degree %d, out_degree %d\n", from->num, point_in_degree(from), point_out_degree(from));
            if(point_out_degree(from) == 0) {//如果删除关系后这个关联点出度为零，就把这个点加入待清理队列
                if(from->queued == 0) {
                    deque_enqueue(q, from);
                    from->queued = 1;
                    printf("point %d enqueue, wait to clean\n", from->num);
                } else {
                    printf("point %d already in queue\n", from->num);
                }
            }
        }
    }
    if(point_out_degree(p) > 0) {//指定点的出度大于0，说明有好多点以此指定点为起点
        point_t *to;
        while(1) {
            to = (point_t *)deque_dequeue(p->to);//遍历以指定点为起点的点
            if(to == NULL) {
                break;
            }
            deque_del(to->from, p);//从以指定点为起点的点中删除和指定点的关联关系
            printf("point %d in_degree %d, out_degree %d\n", to->num, point_in_degree(to), point_out_degree(to));
            if(point_in_degree(to) == 0) {//如果删除关系后这个关联点入度为零，就把这个点加入待清理队列
                if(to->queued == 0) {
                    deque_enqueue(q, to);
                    to->queued = 1;
                    printf("point %d enqueue, wait to clean\n", to->num);
                } else {
                    printf("point %d already in queue\n", to->num);
                }
            }
        }
    }
    return 1;
}

void point_free_arr(point_t *pa[], int len) {
    int i;
    for(i = 0; i < len; i++) {
        point_free(pa[i]);
        free(pa[i]);
        pa[i] = NULL;
    }
}