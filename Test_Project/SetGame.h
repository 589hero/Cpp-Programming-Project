#pragma once
#include<iostream>
#include <Windows.h>
#include <conio.h>
using namespace std;

#define EXT_KEY			0xffffffe0	//확장키 인식값 
#define KEY_LEFT		0x4b
#define KEY_RIGHT		0x4d
#define KEY_UP			0x48
#define KEY_DOWN		0x50
#define ENTER			0x0D
#define SPACE			0x20
#define ESC				0x1B
#define MAP_ROW			0x1E // total_map의 세로길이. 10진수로 30.
#define MAP_COL			0x10 // total_map의 가로길이. 10진수로 16.
#define CHANGE_FLAG		0x61 // 10진수로 97. 알파벳 'a'를 나타냄. 

/* 밑에 있는 total_block[][]에서 위쪽과 아래쪽 벽은 [][]에서 왼쪽 괄호의 인덱스를 나타내고,
   왼쪽과 오른쪽 벽은 [][]에서 오른쪽 괄호의 인덱스를 나타냅니다. 좌표의 값을 나타내는 것이 아닙니다. */

#define UPPER_WALL		0x00 // 10진수로 0.
#define LOWER_WALL		0x1D // 10진수로 29.
#define RIGHT_WALL		0x0F // 10진수로 15.
#define LEFT_WALL		0x00 // 10진수로 0.

class SetGame
{
protected:

	int level;
	int ab_x, ab_y;	//화면중 블럭이 나타나는 좌표의 절대위치
	int block_shape, block_angle, block_x, block_y;
	int next_block_shape;
	int score;
	int upper_lines, lower_lines;
	int s_block_shape;//블록을 저장한다
	int s_block_angle;//블록의 각도를 저장
	bool enter_game;
	bool timer_flag; // 타이머가 돌아가는 조건

	//블록 만들기
	char block[7][4][4][4] = {
		//막대모양
		1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,	1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,	1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,	1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,

		//네모모양
		1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,	1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,	1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,	1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,

		//'ㅓ' 모양
		0,1,0,0,1,1,0,0,0,1,0,0,0,0,0,0,	1,1,1,0,0,1,0,0,0,0,0,0,0,0,0,0,	1,0,0,0,1,1,0,0,1,0,0,0,0,0,0,0,	0,1,0,0,1,1,1,0,0,0,0,0,0,0,0,0,

		//'ㄱ'모양
		1,1,0,0,0,1,0,0,0,1,0,0,0,0,0,0,	1,1,1,0,1,0,0,0,0,0,0,0,0,0,0,0,	1,0,0,0,1,0,0,0,1,1,0,0,0,0,0,0,	0,0,1,0,1,1,1,0,0,0,0,0,0,0,0,0,

		//'ㄴ' 모양
		1,1,0,0,1,0,0,0,1,0,0,0,0,0,0,0,	1,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,	0,1,0,0,0,1,0,0,1,1,0,0,0,0,0,0,	1,1,1,0,0,0,1,0,0,0,0,0,0,0,0,0,

		//'Z' 모양
		1,1,0,0,0,1,1,0,0,0,0,0,0,0,0,0,	0,1,0,0,1,1,0,0,1,0,0,0,0,0,0,0,	1,1,0,0,0,1,1,0,0,0,0,0,0,0,0,0,	0,1,0,0,1,1,0,0,1,0,0,0,0,0,0,0,

		//'S' 모양
		0,1,1,0,1,1,0,0,0,0,0,0,0,0,0,0,	1,0,0,0,1,1,0,0,0,1,0,0,0,0,0,0,	0,1,1,0,1,1,0,0,0,0,0,0,0,0,0,0,	1,0,0,0,1,1,0,0,0,1,0,0,0,0,0,0

	};

	//*********************************
	//구조체 선언
	//*********************************

	enum {
		BLACK,      /*  0 : 까망 */
		DARK_BLUE,    /*  1 : 어두운 파랑 */
		DARK_GREEN,    /*  2 : 어두운 초록 */
		DARK_SKY_BLUE,  /*  3 : 어두운 하늘 */
		DARK_RED,    /*  4 : 어두운 빨강 */
		DARK_VOILET,  /*  5 : 어두운 보라 */
		DARK_YELLOW,  /*  6 : 어두운 노랑 */
		GRAY,      /*  7 : 회색 */
		DARK_GRAY,    /*  8 : 어두운 회색 */
		BLUE,      /*  9 : 파랑 */
		GREEN,      /* 10 : 초록 */
		SKY_BLUE,    /* 11 : 하늘 */
		RED,      /* 12 : 빨강 */
		VOILET,      /* 13 : 보라 */
		YELLOW,      /* 14 : 노랑 */
		WHITE,      /* 15 : 하양 */
	};
public:
	SetGame();
	~SetGame();

	int gotoxy(int x, int y);	//커서옮기기
	void SetColor(int color);	//색표현
	int show_cur_block(int shape, int angle, int x, int y);	//진행중인 블럭을 화면에 표시한다
	int init();					//각종변수 초기화
	int show_story();
	void show_menu();
	void keyInfo();				//조작 설명
	void maker();				//제작자 정보

	//스토리 설명
	void story_stage1(); // 홍대입구
	void story_stage2(); // 신촌
	void story_stage3(); // 동대문
	void story_stage4(); // 왕십리
	void story_stage5(); // 건대입구
	void story_stage5_clear();
	void story_stage6(); // 잠실
	void story_stage7(); // 강변
	void story_ending(); //아직 안넣음
	void story_gameover();
};

