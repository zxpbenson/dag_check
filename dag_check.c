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

#include <stdio.h>
#include <stdlib.h>
#include "graph_point.h"
#define MAX_LEN 1000

void init_dag_pa(point_t *pa[], int len) {
	pa[0] = point_init(0);
	pa[1] = point_init(1);
	pa[2] = point_init(2);
	pa[3] = point_init(3);
	pa[4] = point_init(4);
	pa[5] = point_init(5);
	pa[6] = point_init(6);

    point_add_edge(pa, 1, 2);
    point_add_edge(pa, 2, 3);
    point_add_edge(pa, 2, 4);
    point_add_edge(pa, 4, 3);
    point_add_edge(pa, 3, 5);
}

void init_dcg_pa(point_t *pa[], int len) {
	pa[0] = point_init(0);
	pa[1] = point_init(1);
	pa[2] = point_init(2);
	pa[3] = point_init(3);
	pa[4] = point_init(4);
	pa[5] = point_init(5);
	pa[6] = point_init(6);

    point_add_edge(pa, 1, 2);
    point_add_edge(pa, 2, 3);
    point_add_edge(pa, 4, 2);
    point_add_edge(pa, 3, 4);
    point_add_edge(pa, 3, 5);
}

int check_dag(point_t *pa[], int len) {
	deque_t q;
	deque_init(&q);//创建并初始化一个队列
    point_find_term(pa, len, &q);//找到出度和入度至少有一个是0的节点
    printf("find_term_point done\n");

	//找到起始点或者终点(入度为0的点是起始点，出度为0的点是终点)，并在这个点的关联点中删除和这个点的关联关系
	point_t *p;
	while(1) {
		p = deque_dequeue(&q);//从待处理队列取出节点并逐个处理
        printf("point address : %p\n", p);
		if(p == NULL) {
			break;
		}
        printf("clean point %d\n", p->num);
		if(point_del_rel(p, &q)) {//删除边缘节点或者孤立节点的关联数据，并检查关联节点的出入度变化，如果出入度降为0，也要加入待处理队列
			pa[p->num] = NULL;
			printf("point %d delete relation ok\n", p->num);
			point_free(p);
            free(p);
            p = NULL;
		} else {
			printf("point %d delete relation fail\n", p->num);
			exit(1);
		}
	}

	int i;
	for(i = 0; i < len; i++) {
		if(pa[i] != NULL) {
			return 1;// DCG
		}
	}	
	return 0;// DAG
}

int main() {

	point_t *pa[7];

	init_dag_pa(pa, 7);

	// 检查图是否为DAG
	if (check_dag(pa, 7)) {
		printf("This graph is a Directed Cyclic Graph (DCG).\n");
	} else {
		printf("This graph is a Directed Acyclic Graph (DAG).\n");
	}
    point_free_arr(pa, 7);


	 init_dcg_pa(pa, 7);
	 // 检查图是否为DAG
	 if (check_dag(pa, 7)) {
	 	printf("This graph is a Directed Cyclic Graph (DCG).\n");
	 } else {
	 	printf("This graph is a Directed Acyclic Graph (DAG).\n");
	 }
    point_free_arr(pa, 7);

	return 0;
}
