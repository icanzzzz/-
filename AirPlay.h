//AirPlay.h
//���ڶ��崰�ڴ�С��ͼƬ��С������������ṹ��
//���ߣ�̫��
//���ڣ�2025-1-20
//�汾��v1.1

#include<easyx.h>

//ͼ�δ��ڴ�С
const int BGWEIGHT = 400;	//��
const int BGHEIGHT = 600;	//��

// �ҷ��ɻ��Ĵ�С
const int myAirWIDTH = 40;  // ��
const int myAirHEIGHT = 25; // ��

// �л��Ĵ�С
const int enemyWIDTH = 25;  // ��
const int enemyHEIGHT = 25; // ��

// �ӵ��Ĵ�С
const int BulletWIDTH = 16;  // ��
const int BulletHEIGHT = 16; // ��



//1���򿪴��ڡ�����ͼƬ������ṹ��ʵ�֡������Ķ���
//2�������ҷ����㡢�ҷŷɻ����ƶ�
//3���ӵ������ɡ����䡢�ͷ�

IMAGE img[9];//ͼƬ����

//��ʼ������
void init()
{
	//����ͼƬ
	loadimage(&img[0], _T("res/����.jpg"), BGWEIGHT, BGHEIGHT);
	loadimage(&img[1], _T("res/�ɻ�.jpg"), myAirWIDTH, myAirHEIGHT);
	loadimage(&img[2], _T("res/�л�.jpg"), enemyWIDTH, enemyHEIGHT);
	loadimage(&img[3], _T("res/�ӵ�.jpg"), BulletWIDTH, BulletHEIGHT);
	loadimage(&img[4], _T("res/�л��ӵ�.jpg"), BulletWIDTH, BulletHEIGHT);
	loadimage(&img[5], _T("res/�ɻ�����ͼ.jpg"), myAirWIDTH, myAirHEIGHT);
	loadimage(&img[6], _T("res/�л�����ͼ.jpg"), enemyWIDTH, enemyHEIGHT);
	loadimage(&img[7], _T("res/�ӵ�����ͼ.jpg"), BulletWIDTH, BulletHEIGHT);
	loadimage(&img[8], _T("res/�л��ӵ�����ͼ.jpg"), BulletWIDTH, BulletHEIGHT);
}

