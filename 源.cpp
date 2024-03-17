#include"AirPlay.h"
#include"list.h"
#include<conio.h>

//飞机控制
void ctrl(int* ctrlList)
{
	ExMessage ctrlmsg;
	//判断是否按下按键
	if (peekmessage(&ctrlmsg, EX_KEY))
	{
		//判断是按下还是松开
		if (ctrlmsg.message == WM_KEYDOWN)
			*(ctrlList + ctrlmsg.vkcode) = *(ctrlList + ctrlmsg.vkcode + 32) = 1;
		if (ctrlmsg.message == WM_KEYUP)
			*(ctrlList + ctrlmsg.vkcode) = *(ctrlList + ctrlmsg.vkcode + 32) = 0;
	}
	return;
}

//绘制
void draw(int Airplane_x,int Airplane_y,Play *ListCoordinateEnemy,Play* ListCoordinateBullet)
{
	Node* p = NULL;//创建指针p用于读取链表
	BeginBatchDraw();//开始缓冲
	putimage(0, 0,&img[0]);//打印背景
	//打印敌机
	p = ListCoordinateEnemy->head;//将头节点赋予p
	while (p != NULL)
	{
		putimage(p->x, p->y, &img[6],SRCAND);//打印敌机掩码
		putimage(p->x, p->y, &img[2],SRCPAINT);//打印敌机
		p = p->next;
	}
	//打印飞机
	putimage(Airplane_x, Airplane_y, &img[5], SRCAND);//打印飞机掩码
	putimage(Airplane_x, Airplane_y, &img[1], SRCPAINT);//打印飞机
	//打印子弹
	p = ListCoordinateBullet->head;
	while (p != NULL)
	{
		if (p->speed > 0)
		{
			putimage(p->x, p->y, &img[8], SRCAND);//打印敌机子弹掩码
			putimage(p->x, p->y, &img[4], SRCPAINT);//打印敌机子弹
		}
		else
		{
			putimage(p->x, p->y, &img[7], SRCAND);//打印飞机子弹掩码
			putimage(p->x, p->y, &img[3], SRCPAINT);//打印飞机子弹
		}
		p = p->next;
	}
	EndBatchDraw();//结束缓冲
	return;
}

//敌机坐标生成,攻击速度生成
void CoordinateEnemy(Play* ListCoordinateEnemy,int enemynum,int enemyspeed)
{
	int n = 0;//创建n用于循环计数
	Node* p = NULL;//创建p用于循环检索敌机数量
	p = ListCoordinateEnemy->head;
	//检索敌机数量
	for (;p!=NULL;n++)
	{
		p = p->next;
	}
	if (n <= enemynum)
	{
		//生成敌人坐标,生成攻击速度
		for (; n < enemynum; n++)
		{
			LinkList_insert(ListCoordinateEnemy, rand() % 375, rand() % 200 - 100, enemyspeed, rand() % 1000 + 1000);
		}
	}
	p = NULL;
	return;
}

//敌机随机移动
void MoveEnemy(Play* ListCoordinateEnemy)
{
	Node* p = NULL, * pn = NULL;//创建p指针用于遍历链表。pn用于删除p节点时失去指向的空间，即pn指向原p->next
	p = ListCoordinateEnemy->head;//p指向头指针
	while (p != NULL)
	{
		p->x += rand() % 3 - 1;
		p->y++;
		//防越墙
		if (p->x > 375)
			p->x = 375;
		if (p->x < 0)
			p->x = 0;
		pn = p->next;//保存p->next防止删除p节点后丢失目标
		//敌机超出屏幕消失删除节点
		if (p->y > 600)
		{
			LinkList_del(ListCoordinateEnemy, p);
		}
		p = pn;//更新指针
	}
	return;
}

//子弹生成
void CoordinateBullet(Play* ListCoordinateEnemy,Play* ListCoordinateBullet,int speedbullet)
{
	Node* p = NULL;//创建指针p读取敌机链表
	clock_t nowTime;
	p = ListCoordinateEnemy->head;
	//生成子弹并随机赋予移动速度
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

//子弹移动
void MoveBullet(Play* ListCoordinateBullet)
{
	Node* p = NULL,*pn;//创建p指针遍历子弹列表,pn用于删除p节点时失去指向的空间，即pn指向原p->next
	p = ListCoordinateBullet->head;
	while (p != NULL)
	{
		pn = p->next;//保存指向下一节点的指针
		p->y += p->speed;
		if (p->y > 600 || p->y < -20)
			LinkList_del(ListCoordinateBullet, p);
		p = pn;
	}
	return;
}

//子弹敌机飞机碰撞判定
void BengBeng(Play* ListCoordinateBullet, Play* ListCoordinateEnemy)
{
	Node* p = NULL, * pn = NULL, * q = NULL, * qn = NULL;//创建p,q指针遍历列表,pn\qn用于删除p\q节点时失去指向的空间，即pn指向原p->next
	p = ListCoordinateBullet->head;//首先对子弹链表进行一级遍历
	while (p != NULL)
	{
		pn = p->next;//保存指向节点的指针
		q = ListCoordinateEnemy->head;//对敌人列表进行二级遍历
		while (q != NULL)
		{
			qn = q->next;//保存指向节点的指针
			if ((p->speed < 0) && (p->x < q->x + enemyWEIHGT - 5) && (q->x - BulletWEIHGT + 5 < p->x) && (p->y < q->y) && (q->y < p->y + enemyHEIGHT))
			{
				LinkList_del(ListCoordinateBullet, p);//删除子弹
				LinkList_del(ListCoordinateEnemy, q);//删除敌机
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
	int game = 1;//开始初始化
	clock_t nowTime;
	init();//初始化资源
	initgraph(BGWEIGHT,BGHEIGHT);
	while (game)
	{
		static int play = 0;
		int Tick = 10, speed = 3, speedenemy = 2, Airplane[2], ctrlList[123], ctrlList_n = 0;
		Node* p = NULL, * pn = NULL;//工具p用于遍历列表
		Airplane[0] = 200;//重置飞机横坐标
		Airplane[1] = 500;//重置飞机纵坐标
		//重置控件
		for (; ctrlList_n < 122; ctrlList_n++)
		{
			ctrlList[ctrlList_n] = 0;
		}

		 static Play ListCoordinateEnemy;//创建敌机链表
		 static Play ListCoordinateBullet;//创建子弹链表
		 LinkList_nothing(&ListCoordinateEnemy);//清空敌机链表
		 LinkList_nothing(&ListCoordinateBullet);//清空子弹链表
		 play = 1;// 启动游戏
		//游戏主体
		while (play)
		{
			static clock_t TimeStart = clock();
			static clock_t TimeLast = clock();
			static clock_t TimeBulletLast = clock();
			draw(Airplane[0], Airplane[1], &ListCoordinateEnemy,&ListCoordinateBullet);
			//获取控制
			ctrl(ctrlList);

			CoordinateEnemy(&ListCoordinateEnemy, 5, speedenemy);//发送需要生成的敌机数量生成敌机
			//生成敌机子弹
			CoordinateBullet(&ListCoordinateEnemy, &ListCoordinateBullet, 4);

			//物体坐标更新
			nowTime = clock();
			if (nowTime - TimeLast > Tick)
			{
				TimeLast = nowTime;
				MoveEnemy(&ListCoordinateEnemy);//敌机移动
				if (ctrlList['a'] || ctrlList['A'])
					Airplane[0]-=speed;
				if (ctrlList['d'] || ctrlList['D'])
					Airplane[0]+= speed;
				if (ctrlList['w'] || ctrlList['W'])
					Airplane[1]-= speed;
				if (ctrlList['s'] || ctrlList['S'])
					Airplane[1]+= speed;
				nowTime = clock();
				//生成飞机子弹
				if (nowTime - TimeBulletLast > 300)//判断飞机生成子弹是否符合条件
				{
					TimeBulletLast = nowTime;
					LinkList_insert(&ListCoordinateBullet, Airplane[0] + (myAirWEIHGT - BulletWEIHGT) / 2, Airplane[1] - BulletHEIGHT - 2, -5, 0);//生成我方子弹
				}
				
				//子弹坐标更新
				MoveBullet(&ListCoordinateBullet);

				//敌机与子弹碰撞判定
				BengBeng(&ListCoordinateBullet, &ListCoordinateEnemy);
				
				//飞机与子弹判定
				p = ListCoordinateBullet.head;//将子弹链表头节点赋予p
				while (p != NULL)
				{
					pn = p->next;//保存节点
					if ((p->speed > 0) && (p->x < Airplane[0] + myAirWEIHGT) && (Airplane[0] - BulletWEIHGT < p->x) && (p->y < Airplane[1] + myAirHEIGHT) && (Airplane[1] - BulletHEIGHT < p->y))
					{
						LinkList_del(&ListCoordinateBullet, p);//删除子弹
						play = 0;
					}
					p = pn;
				}

			}

			//防越墙
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