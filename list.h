//��¼�ɻ����ӵ����������
#include<stdlib.h>
#include<assert.h>
#include<time.h>

//����ڵ�Ľṹ�壨�����;����ҷ��ɻ����л����ӵ������ͣ�
typedef struct NODE
{
	int x;//x����
	int y;//y����
	int speed;//�ƶ��ٶ�
	int attackspeed;//�����ٶ�
	clock_t lastTime;//��¼��һ�θ��µ�ʱ��
	struct NODE* next;//ָ�룬����ָ����һ���ڵ�
}Node;

//����ṹ�Ľڵ�
typedef struct LinkList
{
	struct NODE* head = NULL;//ͷָ��
	struct NODE* end = NULL;//βָ��
}Play;

//��������ڵ㺯��
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

//������ڵ���뺯����β�巨
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
		list->end = list->end->next;//����βָ��
	}
}

//ɾ������ڵ�
void LinkList_del(Play* list,Node* p)
{
	Node* q=NULL;//����ָ��q����Ѱ��p�ڵ����һ��
	if (list->head == NULL)
		return;
	//ɾ��ͷ�ڵ�
	if (list->head == p)
	{
		list->head = p->next;//��ͷָ����ڶ��ڵ�����
	}
	//ɾ�������ڵ�
	else
	{
		q = list->head;
		while (q->next != p)
		{
			q = q->next;
		}
		//ɾ��β���
		if (list->end == p)
		{
			list->end = q;//����һ��Ҫ����β��㣬����ͻ�����޷����·ɻ����ӵ�����������ַɻ����ܷ����ӵ����л�����ȴ���������������bug�صúܵײ㣬���������˺ܾò��ҵ��ǵײ��߼�����.����д����һ��Ҫд�����ײ������Ĺ��ܣ�������������
			q->next = NULL;
		}
		//ɾ���м�ڵ�
		else
		{
			q->next = p->next;
		}
	}
	free(p);//�ͷ���Ҫɾ���Ľڵ��ڴ�
}

//�������
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