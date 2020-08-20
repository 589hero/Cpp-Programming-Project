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
	int erase_cur_block(int shape, int angle, int x, int y);	//�� ������ �ܻ��� ����� ���� �Լ�
	int show_next_block(int shape);
	int make_new_block(Stage_data stage_data);	//return������ block�� ����ȣ�� �˷���
	int block_start(int shape, int* angle, int* x, int* y);	//���� ó�� ���ö� ��ġ�� ����� �˷���

	int show_total_block(Map& map);	//�׿����ִ� ���� ȭ�鿡 ǥ���Ѵ�.
	int strike_check(int shape, int angle, int x, int y, Map& map);	//���� ȭ�� �� �Ʒ��� �δ��ƴ��� �˻� �δ�ġ�� 1������ �ƴϸ� 0����
	int merge_block(int shape, int angle, int x, int y, Stage_data stage_data, Map& map);	//���� �ٴڿ� ������� �������� ���� �׾��� ���� ��ħ
	int move_block(int* shape, int* angle, int* x, int* y, int* next_shape, Stage_data stage_data, Map& map);	//���ӿ����� 1������ �ٴڿ� ���� ������ 2�� ����
	int check_full_line(Stage_data stage_data, Map& map);

	int add_keeping_block(Map& map);
	int appear_merchant(Map& map);

	int check_gameover(Map& map);
	void show_cur_block_expected(int shape, int angle, int x, Map& map, bool is_erase_mode);

	int show_gamestat(Stage_data stage_data);	//����, ���� �� ���
};

