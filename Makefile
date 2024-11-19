#
# Copyright (C) 2024 张懿曦(Zhang Yixi)
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.
#

# 目标文件
OBJS = linked_deque.o graph_point.o dag_check.o

# 编译器
CC = gcc

# 编译选项
CFLAGS = -Wall -g

# 生成可执行文件
TARGET = dag_check

default: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

# 生成目标文件规则
linked_deque.o: linked_deque.c linked_deque.h
	$(CC) $(CFLAGS) -c linked_deque.c

graph_point.o: graph_point.c graph_point.h linked_deque.h
	$(CC) $(CFLAGS) -c graph_point.c

dag_check.o: dag_check.c graph_point.h linked_deque.h
	$(CC) $(CFLAGS) -c dag_check.c

# 清理规则
clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: default clean
