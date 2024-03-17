//记录飞机、子弹的相关数据
#include<stdlib.h>
#include<assert.h>
#include<time.h>

//链表节点的结构体（这类型就是我方飞机、敌机、子弹的类型）
typedef struct NODE
{
	int x;//x坐标
	int y;//y坐标
	int speed;//移动速度
	int attackspeed;//攻击速度
	clock_t lastTime;//记录上一次更新的时间
	struct NODE* next;//指针，用来指向下一个节点
}Node;

//链表结构的节点
typedef struct LinkList
{
	struct NODE* head = NULL;//头指针
	struct NODE* end = NULL;//尾指针
}Play;

//创建链表节点函数
Node* Node_init(int x, int y,int speed,int attackspeed)
{
	Node* temp = (Node*)malloc(sizeof(Node));
	assert(temp);
	temp->x = x;
	temp->y = y;
	temp->speed = speed;
	temp->attackspeed = attackspeed;
	temp->lastTime = clock();
	temp->next = NULL;
	return temp;
}

//单链表节点插入函数、尾插法
void LinkList_insert(Play* list, int x, int y, int speed, int attackspeed)
{
	if (list == NULL)
	{
		return;
	}
	if (list->head == NULL)
	{
		list->head = list->end = Node_init(x, y, speed, attackspeed);
	}
	else
	{
		list->end->next = Node_init(x, y, speed, attackspeed);
		list->end = list->end->next;//更新尾指针
	}
}

//删除链表节点
void LinkList_del(Play* list,Node* p)
{
	Node* q=NULL;//建立指针q用来寻找p节点的上一节
	if (list->head == NULL)
		return;
	//删除头节点
	if (list->head == p)
	{
		list->head = p->next;//将头指针与第二节点连接
	}
	//删除其他节点
	else
	{
		q = list->head;
		while (q->next != p)
		{
			q = q->next;
		}
		//删除尾结点
		if (list->end == p)
		{
			list->end = q;//这里一定要更新尾结点，否则就会出现无法更新飞机和子弹的情况，出现飞机不能发射子弹，敌机减少却不更新数量。这个bug藏得很底层，导致我找了很久才找到是底层逻辑问题.所以写代码一定要写完整底层代码组的功能！！！！！！！
			q->next = NULL;
		}
		//删除中间节点
		else
		{
			q->next = p->next;
		}
	}
	free(p);//释放需要删除的节点内存
}

//清空链表
void LinkList_nothing(Play* list)
{
	Node* p, * pn;
	p = list->head;
	list->head = list->end = NULL;
	while (p != NULL)
	{
		pn = p->next;
		free(p);
		p = pn;
	}
}