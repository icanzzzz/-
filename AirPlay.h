#include<easyx.h>

//图形窗口大小
#define BGWEIGHT 400	//宽
#define BGHEIGHT 600	//高
//我方飞机的大小
#define myAirWEIHGT 40	//宽
#define myAirHEIGHT 25	//高
//敌机的大小
#define enemyWEIHGT 25	//宽
#define enemyHEIGHT 25	//高
//子弹的大小
#define BulletWEIHGT 16	//宽
#define BulletHEIGHT 16	//高


//1、打开窗口、加载图片、链表结构的实现、变量的定义
//2、升成我方给你、我放飞机的移动
//3、子弹的生成、发射、释放

IMAGE img[9];//图片数组

//初始化函数
void init()
{
	//加载图片
	loadimage(&img[0], _T("res/背景.jpg"), BGWEIGHT, BGHEIGHT);
	loadimage(&img[1], _T("res/飞机.jpg"), myAirWEIHGT, myAirHEIGHT);
	loadimage(&img[2], _T("res/敌机.jpg"), enemyWEIHGT, enemyHEIGHT);
	loadimage(&img[3], _T("res/子弹.jpg"), BulletWEIHGT, BulletHEIGHT);
	loadimage(&img[4], _T("res/敌机子弹.jpg"), BulletWEIHGT, BulletHEIGHT);
	loadimage(&img[5], _T("res/飞机掩码图.jpg"), myAirWEIHGT, myAirHEIGHT);
	loadimage(&img[6], _T("res/敌机掩码图.jpg"), enemyWEIHGT, enemyHEIGHT);
	loadimage(&img[7], _T("res/子弹掩码图.jpg"), BulletWEIHGT, BulletHEIGHT);
	loadimage(&img[8], _T("res/敌机子弹掩码图.jpg"), BulletWEIHGT, BulletHEIGHT);
}

