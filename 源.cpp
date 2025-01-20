#include"AirPlay.h"
#include"my_list.h"
#include<conio.h>
#include<iostream>
using namespace std;


// ��������
void keyInput(int* keyStateList){
	ExMessage controlMsg;
	// �ж��Ƿ��°���
	if (peekmessage(&controlMsg, EX_KEY))
	{
		// �ж��ǰ��»����ɿ�
		if (controlMsg.message == WM_KEYDOWN)
			keyStateList[controlMsg.vkcode] = keyStateList[controlMsg.vkcode + 32] = 1;
		if (controlMsg.message == WM_KEYUP)
			keyStateList[controlMsg.vkcode] = keyStateList[controlMsg.vkcode + 32] = 0;
	}
	return;
}

// ����
void control(int (&keyStateList)[123], Node& player) {
	if (keyStateList['a'] || keyStateList['A'])
		player.x -= player.speed;
	if (keyStateList['d'] || keyStateList['D'])
		player.x += player.speed;
	if (keyStateList['w'] || keyStateList['W'])
		player.y -= player.speed;
	if (keyStateList['s'] || keyStateList['S'])
		player.y += player.speed;

	// ��ֹԽǽ
	if (player.x > 360)
		player.x = 360;
	if (player.x < 0)
		player.x = 0;
	if (player.y > 575)
		player.y = 575;
	if (player.y < 0)
		player.y = 0;
}

//��ӡ����͸��ͼ
void putimage(int x, int y, int n){
	putimage(x,y, &img[n+4], SRCAND); // ��ӡ����
	putimage(x,y, &img[n], SRCPAINT); // ��ӡ
}

// ����
void draw(Node& player, listArray& enemyList, listArray& bulletList)
{
	int currentNode = enemyList.head; // ����ָ�����ڶ�ȡ����

	BeginBatchDraw(); // ��ʼ����
	putimage(0, 0, &img[0]); // ��ӡ����

	// ��ӡ�л�
	while (currentNode != enemyList.end){
		putimage(enemyList.arrayHead[currentNode]->x, enemyList.arrayHead[currentNode]->y, 2);
		currentNode=listArray_getNextNotNull(enemyList, currentNode);
	}

	// ��ӡ�ɻ�
	putimage(player.x, player.y, 1);

	// ��ӡ�ӵ�
	currentNode = bulletList.head;
	while (!listArray_traverse(bulletList, currentNode)){
		if (bulletList.arrayHead[currentNode]->speed > 0)
			putimage(bulletList.arrayHead[currentNode]->x, bulletList.arrayHead[currentNode]->y, 4); // ��ӡ�л��ӵ�
		else
			putimage(bulletList.arrayHead[currentNode]->x, bulletList.arrayHead[currentNode]->y, 3); // ��ӡ�ɻ��ӵ�
		currentNode = listArray_getNextNotNull(bulletList, currentNode);
	}
	EndBatchDraw(); // ��������
	return;
}

// �л���������, �����ٶ�����
void generateEnemyCoordinates(listArray& enemyList, int enemyCount, int enemySpeed){
	Node p; // ����һ����ʱ�ڵ�
	// ���ɵ�������, ���ɹ����ٶ�
	for (int i = 0; i < enemyCount; i++) {
		p = { rand() % 375, rand() % 200 - 100, enemySpeed, rand() % 1000 + 1000 };
		if (listArray_insert(enemyList, p))
			break;
	}
	return;
}

//Խ��ɾ��
void checkOutOfBounds(listArray& List) {
	if (!listArray_empty(List))
		if (List.arrayHead[List.head]==nullptr||List.arrayHead[List.head]->y > 800 || List.arrayHead[List.head]->y < -100)
			listArray_del(List);
}

// �ӵ�����
void generateBulletCoordinates(listArray& enemyList, listArray& bulletList, int bulletSpeed)
{
	clock_t currentTime=NULL;
	Node p; // ����һ����ʱ�ڵ�
	int currentNode = enemyList.head;

	// �����ӵ�����������ƶ��ٶ�
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

// �л�����ƶ�
void moveEnemies(listArray& enemyList) {
	int currentNode = enemyList.head; // currentNodeָ��ͷָ��
	Node *p = nullptr; // ��ʱָ��

	while (!listArray_traverse(enemyList, currentNode)) {
		p=enemyList.arrayHead[currentNode];
		p->x += rand() % 3 - 1;
		p->y++;

		// ��ֹԽǽ
		if (p->x > 375)
			p->x = 375;
		if (p->x < 0)
			p->x = 0;
		currentNode=listArray_getNextNotNull(enemyList, currentNode);
	}
	return;
}

// �ӵ��ƶ�
void moveBullets(listArray& bulletList){
	int currentNode = bulletList.head;

	while (!listArray_traverse(bulletList, currentNode)){
		bulletList.arrayHead[currentNode]->y += bulletList.arrayHead[currentNode]->speed;
		currentNode=listArray_getNextNotNull(bulletList, currentNode);
	}
	return;
}



// �ӵ��ɻ���ײ�ж�,���ҷ��ɻ����ӵ���ײ�򷵻�true
bool checkCollisions(Node& player, listArray& bulletList, listArray& enemyList){
	int bulletNode = bulletList.head; // ���ȶ��ӵ��������һ������
	int enemyNode = NULL; 
	Node* Bullet= NULL;
	Node* Enemy = NULL;

	//û�е�������β����һֱ����
	while (!listArray_traverse(bulletList, bulletNode)){
		enemyNode = enemyList.head; // �Ե����б���ж�������
		Bullet = bulletList.arrayHead[bulletNode];
		//�л����ӵ��ж�
		if (Bullet->speed < 0) {
			//û�е�������β����һֱ����
			while (!listArray_traverse(enemyList, enemyNode)) {
				Enemy = enemyList.arrayHead[enemyNode];
				if ((Bullet->x < Enemy->x + enemyWIDTH - 5) && (Enemy->x - BulletWIDTH + 5 < Bullet->x) && (Bullet->y < Enemy->y) && (Enemy->y < Bullet->y + enemyHEIGHT)) {
					listArray_del(bulletList, bulletNode); // ɾ���ӵ�
					listArray_del(enemyList, enemyNode); // ɾ���л�
					break;
				}
				enemyNode = listArray_getNextNotNull(enemyList, enemyNode);
			}
		}
		//�ҷ��ɻ����ӵ��ж�
		else if ((Bullet->x < player.x+ myAirWIDTH) && (player.x - BulletWIDTH < Bullet->x) && (Bullet->y < player.y + myAirHEIGHT) && (player.y - BulletHEIGHT < Bullet->y)){
			listArray_del(bulletList, bulletNode); // ɾ���ӵ�
			return true;
		}
		
		bulletNode = listArray_getNextNotNull(bulletList, bulletNode);
	}
	return false;
}
int main()
{
	int running = 1; // ��Ϸ����״̬
	clock_t currentTime;

	init(); // ��ʼ����Դ
	initgraph(BGWEIGHT, BGHEIGHT);

	//��Դ�����ͳ�ʼ��
	const int bulletMaxCount = 1000; // �ӵ��������
	const int enemyMaxCount = 5; // �л��������
	Node *bulletlist[bulletMaxCount]= {nullptr};// �����ӵ�����
	Node *enemylist[enemyMaxCount] = {nullptr}; // �����л�����
	listArray bulletArray = { bulletlist,bulletMaxCount }; // �����ӵ����������ʼ��
	listArray enemyArray = { enemylist,enemyMaxCount }; // �����л����������ʼ��
	int  airplaneSpeed = 3, enemySpeed = 2; //�ɻ��ٶȣ��л��ٶ�
	int airplaneX = 200, airplaneY = 500; // �ɻ�����

	while (running)
	{
		bool gamePlaying = false;
		int tickInterval = 10, keyStateList[123]={0};
		Node airplane = { airplaneX,airplaneY,airplaneSpeed,0,clock() }; // ����ɻ�����
		listArray_nothing(bulletArray); // ����ӵ�����
		listArray_nothing(enemyArray); // ��յл�����

		int currentNode = NULL; // ����ָ�����ڱ����б�
		clock_t lastBulletTime= clock();

		Node p; // ����һ����ʱ�ڵ�,���ڶ�����ӳ�ʼ��
		// ��Ϸ����
		while (!gamePlaying)
		{
			draw(airplane, enemyArray, bulletArray); // ������Ϸ����

			// ��ȡ����
			keyInput(keyStateList);

			generateEnemyCoordinates(enemyArray, 5, enemySpeed); // ������Ҫ���ɵĵл��������ɵл�
			generateBulletCoordinates(enemyArray, bulletArray, 4); // ���ɵл��ӵ�

			currentTime = clock();
			// �����������
			if (currentTime - airplane.lastTime > tickInterval) {
				airplane.lastTime = currentTime;
				moveEnemies(enemyArray); // �л��ƶ�
				control(keyStateList, airplane); // �ҷ��ɻ��ƶ�

				currentTime = clock();
				// �жϷɻ������ӵ��Ƿ��������
				if (currentTime - lastBulletTime > 300) {
					lastBulletTime = currentTime;
					p = { airplane.x + (myAirWIDTH - BulletWIDTH) / 2, airplane.y - BulletHEIGHT - 2, -5 };
					listArray_insert(bulletArray, p); // �����ҷ��ӵ�
				}

				moveBullets(bulletArray); // �ӵ��������
				gamePlaying = checkCollisions(airplane,bulletArray, enemyArray); // �л����ӵ���ײ�ж������ҷ��ɻ����ӵ���ײ�򷵻�true����Ϸ����
				checkOutOfBounds(enemyArray); // �л�Խ��ɾ��
				checkOutOfBounds(bulletArray); // �ӵ�Խ��ɾ��
			}
		}
	}
	closegraph();
	return 0;
}
