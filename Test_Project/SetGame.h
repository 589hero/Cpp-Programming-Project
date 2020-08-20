#pragma once
#include<iostream>
#include <Windows.h>
#include <conio.h>
using namespace std;

#define EXT_KEY			0xffffffe0	//Ȯ��Ű �νİ� 
#define KEY_LEFT		0x4b
#define KEY_RIGHT		0x4d
#define KEY_UP			0x48
#define KEY_DOWN		0x50
#define ENTER			0x0D
#define SPACE			0x20
#define ESC				0x1B
#define MAP_ROW			0x1E // total_map�� ���α���. 10������ 30.
#define MAP_COL			0x10 // total_map�� ���α���. 10������ 16.
#define CHANGE_FLAG		0x61 // 10������ 97. ���ĺ� 'a'�� ��Ÿ��. 

/* �ؿ� �ִ� total_block[][]���� ���ʰ� �Ʒ��� ���� [][]���� ���� ��ȣ�� �ε����� ��Ÿ����,
   ���ʰ� ������ ���� [][]���� ������ ��ȣ�� �ε����� ��Ÿ���ϴ�. ��ǥ�� ���� ��Ÿ���� ���� �ƴմϴ�. */

#define UPPER_WALL		0x00 // 10������ 0.
#define LOWER_WALL		0x1D // 10������ 29.
#define RIGHT_WALL		0x0F // 10������ 15.
#define LEFT_WALL		0x00 // 10������ 0.

class SetGame
{
protected:

	int level;
	int ab_x, ab_y;	//ȭ���� ���� ��Ÿ���� ��ǥ�� ������ġ
	int block_shape, block_angle, block_x, block_y;
	int next_block_shape;
	int score;
	int upper_lines, lower_lines;
	int s_block_shape;//����� �����Ѵ�
	int s_block_angle;//����� ������ ����
	bool enter_game;
	bool timer_flag; // Ÿ�̸Ӱ� ���ư��� ����

	//��� �����
	char block[7][4][4][4] = {
		//������
		1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,	1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,	1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,	1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,

		//�׸���
		1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,	1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,	1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,	1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,

		//'��' ���
		0,1,0,0,1,1,0,0,0,1,0,0,0,0,0,0,	1,1,1,0,0,1,0,0,0,0,0,0,0,0,0,0,	1,0,0,0,1,1,0,0,1,0,0,0,0,0,0,0,	0,1,0,0,1,1,1,0,0,0,0,0,0,0,0,0,

		//'��'���
		1,1,0,0,0,1,0,0,0,1,0,0,0,0,0,0,	1,1,1,0,1,0,0,0,0,0,0,0,0,0,0,0,	1,0,0,0,1,0,0,0,1,1,0,0,0,0,0,0,	0,0,1,0,1,1,1,0,0,0,0,0,0,0,0,0,

		//'��' ���
		1,1,0,0,1,0,0,0,1,0,0,0,0,0,0,0,	1,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,	0,1,0,0,0,1,0,0,1,1,0,0,0,0,0,0,	1,1,1,0,0,0,1,0,0,0,0,0,0,0,0,0,

		//'Z' ���
		1,1,0,0,0,1,1,0,0,0,0,0,0,0,0,0,	0,1,0,0,1,1,0,0,1,0,0,0,0,0,0,0,	1,1,0,0,0,1,1,0,0,0,0,0,0,0,0,0,	0,1,0,0,1,1,0,0,1,0,0,0,0,0,0,0,

		//'S' ���
		0,1,1,0,1,1,0,0,0,0,0,0,0,0,0,0,	1,0,0,0,1,1,0,0,0,1,0,0,0,0,0,0,	0,1,1,0,1,1,0,0,0,0,0,0,0,0,0,0,	1,0,0,0,1,1,0,0,0,1,0,0,0,0,0,0

	};

	//*********************************
	//����ü ����
	//*********************************

	enum {
		BLACK,      /*  0 : ��� */
		DARK_BLUE,    /*  1 : ��ο� �Ķ� */
		DARK_GREEN,    /*  2 : ��ο� �ʷ� */
		DARK_SKY_BLUE,  /*  3 : ��ο� �ϴ� */
		DARK_RED,    /*  4 : ��ο� ���� */
		DARK_VOILET,  /*  5 : ��ο� ���� */
		DARK_YELLOW,  /*  6 : ��ο� ��� */
		GRAY,      /*  7 : ȸ�� */
		DARK_GRAY,    /*  8 : ��ο� ȸ�� */
		BLUE,      /*  9 : �Ķ� */
		GREEN,      /* 10 : �ʷ� */
		SKY_BLUE,    /* 11 : �ϴ� */
		RED,      /* 12 : ���� */
		VOILET,      /* 13 : ���� */
		YELLOW,      /* 14 : ��� */
		WHITE,      /* 15 : �Ͼ� */
	};
public:
	SetGame();
	~SetGame();

	int gotoxy(int x, int y);	//Ŀ���ű��
	void SetColor(int color);	//��ǥ��
	int show_cur_block(int shape, int angle, int x, int y);	//�������� ���� ȭ�鿡 ǥ���Ѵ�
	int init();					//�������� �ʱ�ȭ
	int show_story();
	void show_menu();
	void keyInfo();				//���� ����
	void maker();				//������ ����

	//���丮 ����
	void story_stage1(); // ȫ���Ա�
	void story_stage2(); // ����
	void story_stage3(); // ���빮
	void story_stage4(); // �սʸ�
	void story_stage5(); // �Ǵ��Ա�
	void story_stage5_clear();
	void story_stage6(); // ���
	void story_stage7(); // ����
	void story_ending(); //���� �ȳ���
	void story_gameover();
};

