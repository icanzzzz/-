#include"AirPlay.h"
#include"list.h"
#include<conio.h>

//�ɻ�����
void ctrl(int* ctrlList)
{
	ExMessage ctrlmsg;
	//�ж��Ƿ��°���
	if (peekmessage(&ctrlmsg, EX_KEY))
	{
		//�ж��ǰ��»����ɿ�
		if (ctrlmsg.message == WM_KEYDOWN)
			*(ctrlList + ctrlmsg.vkcode) = *(ctrlList + ctrlmsg.vkcode + 32) = 1;
		if (ctrlmsg.message == WM_KEYUP)
			*(ctrlList + ctrlmsg.vkcode) = *(ctrlList + ctrlmsg.vkcode + 32) = 0;
	}
	return;
}

//����
void draw(int Airplane_x,int Airplane_y,Play *ListCoordinateEnemy,Play* ListCoordinateBullet)
{
	Node* p = NULL;//����ָ��p���ڶ�ȡ����
	BeginBatchDraw();//��ʼ����
	putimage(0, 0,&img[0]);//��ӡ����
	//��ӡ�л�
	p = ListCoordinateEnemy->head;//��ͷ�ڵ㸳��p
	while (p != NULL)
	{
		putimage(p->x, p->y, &img[6],SRCAND);//��ӡ�л�����
		putimage(p->x, p->y, &img[2],SRCPAINT);//��ӡ�л�
		p = p->next;
	}
	//��ӡ�ɻ�
	putimage(Airplane_x, Airplane_y, &img[5], SRCAND);//��ӡ�ɻ�����
	putimage(Airplane_x, Airplane_y, &img[1], SRCPAINT);//��ӡ�ɻ�
	//��ӡ�ӵ�
	p = ListCoordinateBullet->head;
	while (p != NULL)
	{
		if (p->speed > 0)
		{
			putimage(p->x, p->y, &img[8], SRCAND);//��ӡ�л��ӵ�����
			putimage(p->x, p->y, &img[4], SRCPAINT);//��ӡ�л��ӵ�
		}
		else
		{
			putimage(p->x, p->y, &img[7], SRCAND);//��ӡ�ɻ��ӵ�����
			putimage(p->x, p->y, &img[3], SRCPAINT);//��ӡ�ɻ��ӵ�
		}
		p = p->next;
	}
	EndBatchDraw();//��������
	return;
}

//�л���������,�����ٶ�����
void CoordinateEnemy(Play* ListCoordinateEnemy,int enemynum,int enemyspeed)
{
	int n = 0;//����n����ѭ������
	Node* p = NULL;//����p����ѭ�������л�����
	p = ListCoordinateEnemy->head;
	//�����л�����
	for (;p!=NULL;n++)
	{
		p = p->next;
	}
	if (n <= enemynum)
	{
		//���ɵ�������,���ɹ����ٶ�
		for (; n < enemynum; n++)
		{
			LinkList_insert(ListCoordinateEnemy, rand() % 375, rand() % 200 - 100, enemyspeed, rand() % 1000 + 1000);
		}
	}
	p = NULL;
	return;
}

//�л�����ƶ�
void MoveEnemy(Play* ListCoordinateEnemy)
{
	Node* p = NULL, * pn = NULL;//����pָ�����ڱ�������pn����ɾ��p�ڵ�ʱʧȥָ��Ŀռ䣬��pnָ��ԭp->next
	p = ListCoordinateEnemy->head;//pָ��ͷָ��
	while (p != NULL)
	{
		p->x += rand() % 3 - 1;
		p->y++;
		//��Խǽ
		if (p->x > 375)
			p->x = 375;
		if (p->x < 0)
			p->x = 0;
		pn = p->next;//����p->next��ֹɾ��p�ڵ��ʧĿ��
		//�л�������Ļ��ʧɾ���ڵ�
		if (p->y > 600)
		{
			LinkList_del(ListCoordinateEnemy, p);
		}
		p = pn;//����ָ��
	}
	return;
}

//�ӵ�����
void CoordinateBullet(Play* ListCoordinateEnemy,Play* ListCoordinateBullet,int speedbullet)
{
	Node* p = NULL;//����ָ��p��ȡ�л�����
	clock_t nowTime;
	p = ListCoordinateEnemy->head;
	//�����ӵ�����������ƶ��ٶ�
	while (p != NULL) 
	{
		nowTime = clock();
		if (p->y > 10 && nowTime - p->lastTime > p->attackspeed)
		{
			LinkList_insert(ListCoordinateBullet, p->x + (enemyWEIHGT - BulletWEIHGT) / 2, p->y + enemyHEIGHT + 2, speedbullet, 0);
			p->lastTime = nowTime;
			
		}
		p = p->next;
	}
	p = NULL;
	return;
}

//�ӵ��ƶ�
void MoveBullet(Play* ListCoordinateBullet)
{
	Node* p = NULL,*pn;//����pָ������ӵ��б�,pn����ɾ��p�ڵ�ʱʧȥָ��Ŀռ䣬��pnָ��ԭp->next
	p = ListCoordinateBullet->head;
	while (p != NULL)
	{
		pn = p->next;//����ָ����һ�ڵ��ָ��
		p->y += p->speed;
		if (p->y > 600 || p->y < -20)
			LinkList_del(ListCoordinateBullet, p);
		p = pn;
	}
	return;
}

//�ӵ��л��ɻ���ײ�ж�
void BengBeng(Play* ListCoordinateBullet, Play* ListCoordinateEnemy)
{
	Node* p = NULL, * pn = NULL, * q = NULL, * qn = NULL;//����p,qָ������б�,pn\qn����ɾ��p\q�ڵ�ʱʧȥָ��Ŀռ䣬��pnָ��ԭp->next
	p = ListCoordinateBullet->head;//���ȶ��ӵ��������һ������
	while (p != NULL)
	{
		pn = p->next;//����ָ��ڵ��ָ��
		q = ListCoordinateEnemy->head;//�Ե����б���ж�������
		while (q != NULL)
		{
			qn = q->next;//����ָ��ڵ��ָ��
			if ((p->speed < 0) && (p->x < q->x + enemyWEIHGT - 5) && (q->x - BulletWEIHGT + 5 < p->x) && (p->y < q->y) && (q->y < p->y + enemyHEIGHT))
			{
				LinkList_del(ListCoordinateBullet, p);//ɾ���ӵ�
				LinkList_del(ListCoordinateEnemy, q);//ɾ���л�
				break;
			}
			q = qn;
		}
		p = pn;
	}
	return;
}

int main()
{
	int game = 1;//��ʼ��ʼ��
	clock_t nowTime;
	init();//��ʼ����Դ
	initgraph(BGWEIGHT,BGHEIGHT);
	while (game)
	{
		static int play = 0;
		int Tick = 10, speed = 3, speedenemy = 2, Airplane[2], ctrlList[123], ctrlList_n = 0;
		Node* p = NULL, * pn = NULL;//����p���ڱ����б�
		Airplane[0] = 200;//���÷ɻ�������
		Airplane[1] = 500;//���÷ɻ�������
		//���ÿؼ�
		for (; ctrlList_n < 122; ctrlList_n++)
		{
			ctrlList[ctrlList_n] = 0;
		}

		 static Play ListCoordinateEnemy;//�����л�����
		 static Play ListCoordinateBullet;//�����ӵ�����
		 LinkList_nothing(&ListCoordinateEnemy);//��յл�����
		 LinkList_nothing(&ListCoordinateBullet);//����ӵ�����
		 play = 1;// ������Ϸ
		//��Ϸ����
		while (play)
		{
			static clock_t TimeStart = clock();
			static clock_t TimeLast = clock();
			static clock_t TimeBulletLast = clock();
			draw(Airplane[0], Airplane[1], &ListCoordinateEnemy,&ListCoordinateBullet);
			//��ȡ����
			ctrl(ctrlList);

			CoordinateEnemy(&ListCoordinateEnemy, 5, speedenemy);//������Ҫ���ɵĵл��������ɵл�
			//���ɵл��ӵ�
			CoordinateBullet(&ListCoordinateEnemy, &ListCoordinateBullet, 4);

			//�����������
			nowTime = clock();
			if (nowTime - TimeLast > Tick)
			{
				TimeLast = nowTime;
				MoveEnemy(&ListCoordinateEnemy);//�л��ƶ�
				if (ctrlList['a'] || ctrlList['A'])
					Airplane[0]-=speed;
				if (ctrlList['d'] || ctrlList['D'])
					Airplane[0]+= speed;
				if (ctrlList['w'] || ctrlList['W'])
					Airplane[1]-= speed;
				if (ctrlList['s'] || ctrlList['S'])
					Airplane[1]+= speed;
				nowTime = clock();
				//���ɷɻ��ӵ�
				if (nowTime - TimeBulletLast > 300)//�жϷɻ������ӵ��Ƿ��������
				{
					TimeBulletLast = nowTime;
					LinkList_insert(&ListCoordinateBullet, Airplane[0] + (myAirWEIHGT - BulletWEIHGT) / 2, Airplane[1] - BulletHEIGHT - 2, -5, 0);//�����ҷ��ӵ�
				}
				
				//�ӵ��������
				MoveBullet(&ListCoordinateBullet);

				//�л����ӵ���ײ�ж�
				BengBeng(&ListCoordinateBullet, &ListCoordinateEnemy);
				
				//�ɻ����ӵ��ж�
				p = ListCoordinateBullet.head;//���ӵ�����ͷ�ڵ㸳��p
				while (p != NULL)
				{
					pn = p->next;//����ڵ�
					if ((p->speed > 0) && (p->x < Airplane[0] + myAirWEIHGT) && (Airplane[0] - BulletWEIHGT < p->x) && (p->y < Airplane[1] + myAirHEIGHT) && (Airplane[1] - BulletHEIGHT < p->y))
					{
						LinkList_del(&ListCoordinateBullet, p);//ɾ���ӵ�
						play = 0;
					}
					p = pn;
				}

			}

			//��Խǽ
			if (Airplane[0] > 360)
				Airplane[0] = 360;
			if (Airplane[0] < 0)
				Airplane[0] = 0;
			if (Airplane[1] > 575)
				Airplane[1] = 575;
			if (Airplane[1] < 0)
				Airplane[1] = 0;
		}

	}
	closegraph();
	return 0;
}