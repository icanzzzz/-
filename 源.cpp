#include"AirPlay.h"
#include"my_list.h"
#include<conio.h>
#include<iostream>
using namespace std;


// 键盘输入
void keyInput(int* keyStateList){
	ExMessage controlMsg;
	// 判断是否按下按键
	if (peekmessage(&controlMsg, EX_KEY))
	{
		// 判断是按下还是松开
		if (controlMsg.message == WM_KEYDOWN)
			keyStateList[controlMsg.vkcode] = keyStateList[controlMsg.vkcode + 32] = 1;
		if (controlMsg.message == WM_KEYUP)
			keyStateList[controlMsg.vkcode] = keyStateList[controlMsg.vkcode + 32] = 0;
	}
	return;
}

// 控制
void control(int (&keyStateList)[123], Node& player) {
	if (keyStateList['a'] || keyStateList['A'])
		player.x -= player.speed;
	if (keyStateList['d'] || keyStateList['D'])
		player.x += player.speed;
	if (keyStateList['w'] || keyStateList['W'])
		player.y -= player.speed;
	if (keyStateList['s'] || keyStateList['S'])
		player.y += player.speed;

	// 防止越墙
	if (player.x > 360)
		player.x = 360;
	if (player.x < 0)
		player.x = 0;
	if (player.y > 575)
		player.y = 575;
	if (player.y < 0)
		player.y = 0;
}

//打印背景透明图
void putimage(int x, int y, int n){
	putimage(x,y, &img[n+4], SRCAND); // 打印掩码
	putimage(x,y, &img[n], SRCPAINT); // 打印
}

// 绘制
void draw(Node& player, listArray& enemyList, listArray& bulletList)
{
	int currentNode = enemyList.head; // 创建指针用于读取链表

	BeginBatchDraw(); // 开始缓冲
	putimage(0, 0, &img[0]); // 打印背景

	// 打印敌机
	while (currentNode != enemyList.end){
		putimage(enemyList.arrayHead[currentNode]->x, enemyList.arrayHead[currentNode]->y, 2);
		currentNode=listArray_getNextNotNull(enemyList, currentNode);
	}

	// 打印飞机
	putimage(player.x, player.y, 1);

	// 打印子弹
	currentNode = bulletList.head;
	while (!listArray_traverse(bulletList, currentNode)){
		if (bulletList.arrayHead[currentNode]->speed > 0)
			putimage(bulletList.arrayHead[currentNode]->x, bulletList.arrayHead[currentNode]->y, 4); // 打印敌机子弹
		else
			putimage(bulletList.arrayHead[currentNode]->x, bulletList.arrayHead[currentNode]->y, 3); // 打印飞机子弹
		currentNode = listArray_getNextNotNull(bulletList, currentNode);
	}
	EndBatchDraw(); // 结束缓冲
	return;
}

// 敌机坐标生成, 攻击速度生成
void generateEnemyCoordinates(listArray& enemyList, int enemyCount, int enemySpeed){
	Node p; // 定义一个临时节点
	// 生成敌人坐标, 生成攻击速度
	for (int i = 0; i < enemyCount; i++) {
		p = { rand() % 375, rand() % 200 - 100, enemySpeed, rand() % 1000 + 1000 };
		if (listArray_insert(enemyList, p))
			break;
	}
	return;
}

//越界删除
void checkOutOfBounds(listArray& List) {
	if (!listArray_empty(List))
		if (List.arrayHead[List.head]==nullptr||List.arrayHead[List.head]->y > 800 || List.arrayHead[List.head]->y < -100)
			listArray_del(List);
}

// 子弹生成
void generateBulletCoordinates(listArray& enemyList, listArray& bulletList, int bulletSpeed)
{
	clock_t currentTime=NULL;
	Node p; // 定义一个临时节点
	int currentNode = enemyList.head;

	// 生成子弹并随机赋予移动速度
	while (!listArray_traverse(enemyList, currentNode)){
		currentTime = clock();
		if (enemyList.arrayHead[currentNode]->y > 10 && currentTime - enemyList.arrayHead[currentNode]->lastTime > enemyList.arrayHead[currentNode]->attackspeed) {
			p = { enemyList.arrayHead[currentNode]->x + (enemyWIDTH - BulletWIDTH) / 2, enemyList.arrayHead[currentNode]->y + enemyHEIGHT + 2, bulletSpeed, 0 };
			if (listArray_insert(bulletList, p))
				break;
			enemyList.arrayHead[currentNode]->lastTime = currentTime;
		}
		currentNode=listArray_getNextNotNull(enemyList, currentNode);
	}
	return;
}

// 敌机随机移动
void moveEnemies(listArray& enemyList) {
	int currentNode = enemyList.head; // currentNode指向头指针
	Node *p = nullptr; // 临时指针

	while (!listArray_traverse(enemyList, currentNode)) {
		p=enemyList.arrayHead[currentNode];
		p->x += rand() % 3 - 1;
		p->y++;

		// 防止越墙
		if (p->x > 375)
			p->x = 375;
		if (p->x < 0)
			p->x = 0;
		currentNode=listArray_getNextNotNull(enemyList, currentNode);
	}
	return;
}

// 子弹移动
void moveBullets(listArray& bulletList){
	int currentNode = bulletList.head;

	while (!listArray_traverse(bulletList, currentNode)){
		bulletList.arrayHead[currentNode]->y += bulletList.arrayHead[currentNode]->speed;
		currentNode=listArray_getNextNotNull(bulletList, currentNode);
	}
	return;
}



// 子弹飞机碰撞判定,若我方飞机与子弹碰撞则返回true
bool checkCollisions(Node& player, listArray& bulletList, listArray& enemyList){
	int bulletNode = bulletList.head; // 首先对子弹链表进行一级遍历
	int enemyNode = NULL; 
	Node* Bullet= NULL;
	Node* Enemy = NULL;

	//没有到达链表尾部就一直遍历
	while (!listArray_traverse(bulletList, bulletNode)){
		enemyNode = enemyList.head; // 对敌人列表进行二级遍历
		Bullet = bulletList.arrayHead[bulletNode];
		//敌机与子弹判定
		if (Bullet->speed < 0) {
			//没有到达链表尾部就一直遍历
			while (!listArray_traverse(enemyList, enemyNode)) {
				Enemy = enemyList.arrayHead[enemyNode];
				if ((Bullet->x < Enemy->x + enemyWIDTH - 5) && (Enemy->x - BulletWIDTH + 5 < Bullet->x) && (Bullet->y < Enemy->y) && (Enemy->y < Bullet->y + enemyHEIGHT)) {
					listArray_del(bulletList, bulletNode); // 删除子弹
					listArray_del(enemyList, enemyNode); // 删除敌机
					break;
				}
				enemyNode = listArray_getNextNotNull(enemyList, enemyNode);
			}
		}
		//我方飞机与子弹判定
		else if ((Bullet->x < player.x+ myAirWIDTH) && (player.x - BulletWIDTH < Bullet->x) && (Bullet->y < player.y + myAirHEIGHT) && (player.y - BulletHEIGHT < Bullet->y)){
			listArray_del(bulletList, bulletNode); // 删除子弹
			return true;
		}
		
		bulletNode = listArray_getNextNotNull(bulletList, bulletNode);
	}
	return false;
}
int main()
{
	int running = 1; // 游戏运行状态
	clock_t currentTime;

	init(); // 初始化资源
	initgraph(BGWEIGHT, BGHEIGHT);

	//资源声明和初始化
	const int bulletMaxCount = 1000; // 子弹最大数量
	const int enemyMaxCount = 5; // 敌机最大数量
	Node *bulletlist[bulletMaxCount]= {nullptr};// 创建子弹数组
	Node *enemylist[enemyMaxCount] = {nullptr}; // 创建敌机数组
	listArray bulletArray = { bulletlist,bulletMaxCount }; // 创建子弹句柄，并初始化
	listArray enemyArray = { enemylist,enemyMaxCount }; // 创建敌机句柄，并初始化
	int  airplaneSpeed = 3, enemySpeed = 2; //飞机速度，敌机速度
	int airplaneX = 200, airplaneY = 500; // 飞机坐标

	while (running)
	{
		bool gamePlaying = false;
		int tickInterval = 10, keyStateList[123]={0};
		Node airplane = { airplaneX,airplaneY,airplaneSpeed,0,clock() }; // 定义飞机坐标
		listArray_nothing(bulletArray); // 清空子弹数组
		listArray_nothing(enemyArray); // 清空敌机数组

		int currentNode = NULL; // 工具指针用于遍历列表
		clock_t lastBulletTime= clock();

		Node p; // 定义一个临时节点,用于队列添加初始化
		// 游戏主体
		while (!gamePlaying)
		{
			draw(airplane, enemyArray, bulletArray); // 绘制游戏画面

			// 获取控制
			keyInput(keyStateList);

			generateEnemyCoordinates(enemyArray, 5, enemySpeed); // 发送需要生成的敌机数量生成敌机
			generateBulletCoordinates(enemyArray, bulletArray, 4); // 生成敌机子弹

			currentTime = clock();
			// 物体坐标更新
			if (currentTime - airplane.lastTime > tickInterval) {
				airplane.lastTime = currentTime;
				moveEnemies(enemyArray); // 敌机移动
				control(keyStateList, airplane); // 我方飞机移动

				currentTime = clock();
				// 判断飞机生成子弹是否符合条件
				if (currentTime - lastBulletTime > 300) {
					lastBulletTime = currentTime;
					p = { airplane.x + (myAirWIDTH - BulletWIDTH) / 2, airplane.y - BulletHEIGHT - 2, -5 };
					listArray_insert(bulletArray, p); // 生成我方子弹
				}

				moveBullets(bulletArray); // 子弹坐标更新
				gamePlaying = checkCollisions(airplane,bulletArray, enemyArray); // 敌机与子弹碰撞判定，若我方飞机与子弹碰撞则返回true，游戏结束
				checkOutOfBounds(enemyArray); // 敌机越界删除
				checkOutOfBounds(bulletArray); // 子弹越界删除
			}
		}
	}
	closegraph();
	return 0;
}
