#pragma once
#include "Map.h"
#include "Stage_data.h"
#include "SetGame.h"
#include <ctime>
class PlayGame	
	:SetGame
{
private:
	int flag;
	int dwID;
	int startTime;
	int usedBlocks;
	bool rePlay;
	MCI_OPEN_PARMS m_mciOpenParms;
	MCI_PLAY_PARMS m_mciPlayParms;
	DWORD m_dwDeviceID;
	MCI_OPEN_PARMS mciOpen;
	MCI_PLAY_PARMS mciPlay;
public:
	PlayGame();
	~PlayGame();
	void save_block_item();
	void play(int argc, char* argv[]);
	void voidCursor();
	int erase_cur_block(int shape, int angle, int x, int y);	//블럭 진행의 잔상을 지우기 위한 함수
	int show_next_block(int shape);
	int make_new_block(Stage_data stage_data);	//return값으로 block의 모양번호를 알려줌
	int block_start(int shape, int* angle, int* x, int* y);	//블럭이 처음 나올때 위치와 모양을 알려줌

	int show_total_block(Map& map);	//쌓여져있는 블럭을 화면에 표시한다.
	int strike_check(int shape, int angle, int x, int y, Map& map);	//블럭이 화면 맨 아래에 부닥쳤는지 검사 부닥치면 1을리턴 아니면 0리턴
	int merge_block(int shape, int angle, int x, int y, Stage_data stage_data, Map& map);	//블럭이 바닥에 닿았을때 진행중인 블럭과 쌓아진 블럭을 합침
	int move_block(int* shape, int* angle, int* x, int* y, int* next_shape, Stage_data stage_data, Map& map);	//게임오버는 1을리턴 바닥에 블럭이 닿으면 2를 리턴
	int check_full_line(Stage_data stage_data, Map& map);

	int add_keeping_block(Map& map);
	int appear_merchant(Map& map);

	int check_gameover(Map& map);
	void show_cur_block_expected(int shape, int angle, int x, Map& map, bool is_erase_mode);

	int show_gamestat(Stage_data stage_data);	//점수, 남은 줄 출력
};

