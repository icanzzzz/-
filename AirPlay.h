#include<easyx.h>

//ͼ�δ��ڴ�С
#define BGWEIGHT 400	//��
#define BGHEIGHT 600	//��
//�ҷ��ɻ��Ĵ�С
#define myAirWEIHGT 40	//��
#define myAirHEIGHT 25	//��
//�л��Ĵ�С
#define enemyWEIHGT 25	//��
#define enemyHEIGHT 25	//��
//�ӵ��Ĵ�С
#define BulletWEIHGT 16	//��
#define BulletHEIGHT 16	//��


//1���򿪴��ڡ�����ͼƬ������ṹ��ʵ�֡������Ķ���
//2�������ҷ����㡢�ҷŷɻ����ƶ�
//3���ӵ������ɡ����䡢�ͷ�

IMAGE img[9];//ͼƬ����

//��ʼ������
void init()
{
	//����ͼƬ
	loadimage(&img[0], _T("res/����.jpg"), BGWEIGHT, BGHEIGHT);
	loadimage(&img[1], _T("res/�ɻ�.jpg"), myAirWEIHGT, myAirHEIGHT);
	loadimage(&img[2], _T("res/�л�.jpg"), enemyWEIHGT, enemyHEIGHT);
	loadimage(&img[3], _T("res/�ӵ�.jpg"), BulletWEIHGT, BulletHEIGHT);
	loadimage(&img[4], _T("res/�л��ӵ�.jpg"), BulletWEIHGT, BulletHEIGHT);
	loadimage(&img[5], _T("res/�ɻ�����ͼ.jpg"), myAirWEIHGT, myAirHEIGHT);
	loadimage(&img[6], _T("res/�л�����ͼ.jpg"), enemyWEIHGT, enemyHEIGHT);
	loadimage(&img[7], _T("res/�ӵ�����ͼ.jpg"), BulletWEIHGT, BulletHEIGHT);
	loadimage(&img[8], _T("res/�л��ӵ�����ͼ.jpg"), BulletWEIHGT, BulletHEIGHT);
}

