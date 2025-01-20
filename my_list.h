// my_list.h

/**
 * @file my_list.h
 * @brief 这是对游戏数据的定义的初始化和操作头文件
 * @author 太白
 * @date 2025-1-19
 */

#ifndef MY_LIST_H // 防止重复包含的宏
#define MY_LIST_H

#include "ctime"

//循环队列节点{x,y,speed,attackspeed,lastTime}
typedef struct NODE
{
	int x=0;//x坐标
	int y=0;//y坐标
	int speed=0;//移动速度
	int attackspeed=0;//攻击速度
	clock_t lastTime=NULL;//记录上一次更新的时间
	struct NODE* next=nullptr;//指针，用来指向下一个节点
}Node;

//循环队列句柄{arrayHead,size,head,end}
struct listArray {
	Node** arrayHead = nullptr;//数组头指针
	int size = 0;//数组大小
	int head = 0;//结点头位置
	int end = 0;//结点尾位置
};

/*获取循环队列下一个索引*/
int listArray_getNext(listArray& list, int p);

/*获取循环队列下一个非空索引*/
int listArray_getNextNotNull(listArray& list, int p);

/*与尾位置对比。相等则返回 true，否则返回 false*/
bool listArray_traverse(listArray& list,int p);

/*与头位置对比。相等则返回 true，否则返回 false*/
bool listArray_reverse_traverse(listArray& list,int p);

/*判断队列是否为满。返回为 true 表示队列为满，否则为 false*/
bool listArray_full(listArray& list);

/*判断队列是否为空。返回为 true 表示队列为空，否则为 false*/
bool listArray_empty(listArray& list);

/*顺序链表节点插入函数、尾插法。返回为 true 表示队列为满，否则为 false*/
bool listArray_insert(listArray& list, Node& p);

/*删除节点。返回为 true 表示队列为空，否则为 false*/
bool listArray_del(listArray& list);

/*删除指定索引的节点返回为 true 表示队列为空，否则为 false*/
bool listArray_del(listArray& list, int index);

/*清空链表。返回为 true 表示队列为空*/
bool listArray_nothing(listArray& list);

#endif // MY_LIST_H