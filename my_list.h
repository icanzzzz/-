// my_list.h

/**
 * @file my_list.h
 * @brief ���Ƕ���Ϸ���ݵĶ���ĳ�ʼ���Ͳ���ͷ�ļ�
 * @author ̫��
 * @date 2025-1-19
 */

#ifndef MY_LIST_H // ��ֹ�ظ������ĺ�
#define MY_LIST_H

#include "ctime"

//ѭ�����нڵ�{x,y,speed,attackspeed,lastTime}
typedef struct NODE
{
	int x=0;//x����
	int y=0;//y����
	int speed=0;//�ƶ��ٶ�
	int attackspeed=0;//�����ٶ�
	clock_t lastTime=NULL;//��¼��һ�θ��µ�ʱ��
	struct NODE* next=nullptr;//ָ�룬����ָ����һ���ڵ�
}Node;

//ѭ�����о��{arrayHead,size,head,end}
struct listArray {
	Node** arrayHead = nullptr;//����ͷָ��
	int size = 0;//�����С
	int head = 0;//���ͷλ��
	int end = 0;//���βλ��
};

/*��ȡѭ��������һ������*/
int listArray_getNext(listArray& list, int p);

/*��ȡѭ��������һ���ǿ�����*/
int listArray_getNextNotNull(listArray& list, int p);

/*��βλ�öԱȡ�����򷵻� true�����򷵻� false*/
bool listArray_traverse(listArray& list,int p);

/*��ͷλ�öԱȡ�����򷵻� true�����򷵻� false*/
bool listArray_reverse_traverse(listArray& list,int p);

/*�ж϶����Ƿ�Ϊ��������Ϊ true ��ʾ����Ϊ��������Ϊ false*/
bool listArray_full(listArray& list);

/*�ж϶����Ƿ�Ϊ�ա�����Ϊ true ��ʾ����Ϊ�գ�����Ϊ false*/
bool listArray_empty(listArray& list);

/*˳������ڵ���뺯����β�巨������Ϊ true ��ʾ����Ϊ��������Ϊ false*/
bool listArray_insert(listArray& list, Node& p);

/*ɾ���ڵ㡣����Ϊ true ��ʾ����Ϊ�գ�����Ϊ false*/
bool listArray_del(listArray& list);

/*ɾ��ָ�������Ľڵ㷵��Ϊ true ��ʾ����Ϊ�գ�����Ϊ false*/
bool listArray_del(listArray& list, int index);

/*�����������Ϊ true ��ʾ����Ϊ��*/
bool listArray_nothing(listArray& list);

#endif // MY_LIST_H