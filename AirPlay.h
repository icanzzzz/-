//AirPlay.h
//用于定义窗口大小、图片大小、变量、链表结构等
//作者：太白
//日期：2025-1-20
//版本：v1.1

#include<easyx.h>

//图形窗口大小
const int BGWEIGHT = 400;	//宽
const int BGHEIGHT = 600;	//高

// 我方飞机的大小
const int myAirWIDTH = 40;  // 宽
const int myAirHEIGHT = 25; // 高

// 敌机的大小
const int enemyWIDTH = 25;  // 宽
const int enemyHEIGHT = 25; // 高

// 子弹的大小
const int BulletWIDTH = 16;  // 宽
const int BulletHEIGHT = 16; // 高



//1、打开窗口、加载图片、链表结构的实现、变量的定义
//2、升成我方给你、我放飞机的移动
//3、子弹的生成、发射、释放

IMAGE img[9];//图片数组

//初始化函数
void init()
{
	//加载图片
	loadimage(&img[0], _T("res/背景.jpg"), BGWEIGHT, BGHEIGHT);
	loadimage(&img[1], _T("res/飞机.jpg"), myAirWIDTH, myAirHEIGHT);
	loadimage(&img[2], _T("res/敌机.jpg"), enemyWIDTH, enemyHEIGHT);
	loadimage(&img[3], _T("res/子弹.jpg"), BulletWIDTH, BulletHEIGHT);
	loadimage(&img[4], _T("res/敌机子弹.jpg"), BulletWIDTH, BulletHEIGHT);
	loadimage(&img[5], _T("res/飞机掩码图.jpg"), myAirWIDTH, myAirHEIGHT);
	loadimage(&img[6], _T("res/敌机掩码图.jpg"), enemyWIDTH, enemyHEIGHT);
	loadimage(&img[7], _T("res/子弹掩码图.jpg"), BulletWIDTH, BulletHEIGHT);
	loadimage(&img[8], _T("res/敌机子弹掩码图.jpg"), BulletWIDTH, BulletHEIGHT);
}

