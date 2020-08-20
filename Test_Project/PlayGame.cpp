#include "PlayGame.h"
#include "Map.h"
#include "Stage_data.h"
#include <Windows.h>
#include <conio.h>
#include <iostream>
#include <iomanip>
#include <mmsystem.h>
#include <cstdlib>
using namespace std;

#pragma comment(lib, "winmm.lib")
#include "Digitalv.h"
#pragma warning (disable: 4244 4800 4311 4312)

using namespace std;
PlayGame::PlayGame()
	:flag(0), dwID(0), rePlay(true)
{
	
}
Map map;
Stage_data stage_data;
void PlayGame::play(int argc, char* argv[])	 {
	
	while (rePlay)
	{
		int is_gameover;
		char keytemp ;

		map.init();
		init();
		enter_game = false;
		system("cls");
		SetColor(WHITE);
		show_menu();

		show_story();
		story_stage1();

		is_gameover = 0;
		startTime = (int)clock();
		int current_time = -1;
		usedBlocks = 0;

		show_total_block(map);
		block_shape = make_new_block(stage_data);
		next_block_shape = make_new_block(stage_data);
		show_next_block(next_block_shape);
		block_start(block_shape, &block_angle, &block_x, &block_y);
		show_cur_block_expected(block_shape, block_angle, block_x, map, true);
		show_cur_block(block_shape, block_angle, block_x, block_y);
		show_gamestat(stage_data);	//block_start���� usedBlocks�� ����ǹǷ� �ļ����� ����

		mciOpen.lpstrElementName = "Ma.mp3"; // ���� ��� �Է�  
		mciOpen.lpstrDeviceType = "mpegvideo";
		mciSendCommand(NULL, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD)(LPVOID)&mciOpen);
		dwID = mciOpen.wDeviceID;
		mciSendCommand(dwID, MCI_PLAY, MCI_DGV_PLAY_REPEAT, (DWORD)(LPVOID)&m_mciPlayParms); // play & repeat 

		PlaySound(TEXT("Hongdae.wav"), NULL, SND_FILENAME | SND_ASYNC);

		voidCursor();
		for (int i = 1; 1; i++)
		{
			if (_kbhit())
			{
				keytemp = _getche();
				if (keytemp == EXT_KEY)
				{
					keytemp = _getche();

					switch (keytemp)
					{
					case KEY_UP:      //ȸ���ϱ�
						if (strike_check(block_shape, (block_angle + 1) % 4, block_x, block_y, map) == 0) {
							erase_cur_block(block_shape, block_angle, block_x, block_y);
							show_cur_block_expected(block_shape, block_angle, block_x, map, false);
							block_angle = (block_angle + 1) % 4;
							show_cur_block_expected(block_shape, block_angle, block_x, map, true);
							show_cur_block(block_shape, block_angle, block_x, block_y);
						}
						break;

					case KEY_LEFT:      //�������� �̵�
						if (block_x > 1)
						{
							erase_cur_block(block_shape, block_angle, block_x, block_y);

							show_cur_block_expected(block_shape, block_angle, block_x, map, false);
							block_x--;

							if (strike_check(block_shape, block_angle, block_x, block_y, map) == 1)
								block_x++;

							show_cur_block_expected(block_shape, block_angle, block_x, map, true);
							show_cur_block(block_shape, block_angle, block_x, block_y);
						}
						break;
					case KEY_RIGHT:      //���������� �̵�
						if (block_x < MAP_COL - 1)
						{
							erase_cur_block(block_shape, block_angle, block_x, block_y);

							show_cur_block_expected(block_shape, block_angle, block_x, map, false);
							block_x++;

							if (strike_check(block_shape, block_angle, block_x, block_y, map) == 1)
								block_x--;

							show_cur_block_expected(block_shape, block_angle, block_x, map, true);
							show_cur_block(block_shape, block_angle, block_x, block_y);
						}
						break;
					case KEY_DOWN:      //�Ʒ��� �̵�
						move_block(&block_shape, &block_angle, &block_x, &block_y, &next_block_shape, stage_data, map);
						is_gameover = check_gameover(map);
						show_cur_block(block_shape, block_angle, block_x, block_y);
						break;
					}
				}
				else if (keytemp == CHANGE_FLAG) {
					show_cur_block_expected(block_shape, block_angle, block_x, map, false);
					flag = 1 - flag;
					show_cur_block_expected(block_shape, block_angle, block_x, map, true);
					show_cur_block(block_shape, block_angle, block_x, block_y);
				}
				if (keytemp == SPACE)   //�����̽��ٸ� ��������
				{
					int check = 0;
					while (check == 0) {
						is_gameover = check_gameover(map);
						check = move_block(&block_shape, &block_angle, &block_x, &block_y, &next_block_shape, stage_data, map);
					}
					show_cur_block_expected(block_shape, block_angle, block_x, map, true);
					show_cur_block(block_shape, block_angle, block_x, block_y);
				}

				if (keytemp == ESC)      //esc ������ ��
				{

					system("pause");

					startTime = clock() - current_time * 1000;

					show_cur_block(block_shape, block_angle, block_x, block_y);

				}

				if (keytemp == '1') {
					if (s_block_shape != -1 || s_block_angle != -1) {
						SetColor(DARK_RED);
						gotoxy(20, 32);
						cout << "    �̹� ����� ����� �����մϴ�    "; //�ȳ�����
					}
					else {
						show_cur_block_expected(block_shape, block_angle, block_x, map, false);
						save_block_item();
					}
				}

				else if (keytemp == '2'&& s_block_shape != -1 && s_block_angle != -1)
				{//��� ��������ۿ��� ����� ����� ����Ҷ� 2�� ������
					map.s_item_check = true;
					gotoxy(20, 32);
					SetColor(WHITE);
					cout << "       ����� ����� �����ɴϴ�      "; //�ȳ�����
					Sleep(300);
					gotoxy(20, 32);
					cout << "                                 "; //�ȳ�����

				}

			}

			if (i % stage_data.getStage(level).getSpeed() == 0) //�ð��� ������ ������;
			{
				move_block(&block_shape, &block_angle, &block_x, &block_y, &next_block_shape, stage_data, map);
				is_gameover = check_gameover(map);
				show_cur_block_expected(block_shape, block_angle, block_x, map, true);
				show_cur_block(block_shape, block_angle, block_x, block_y);
			}

			if (stage_data.getStage(level).getClear_upper_line() == upper_lines &&
				stage_data.getStage(level).getClear_upper_line() == lower_lines)   //Ŭ���� ��������
			{
				score += (level + 2) * (180 - current_time) * (stage_data.getStage(level).getRemain_block_limit() - usedBlocks) / 200;

				level++;

				//���������� ���� �ִϸ��̼� �ٲٱ�
				switch (level)
				{
				case 1: // ȫ���Ա� Ŭ���� ==> ���� // SND_ASYNC
					PlaySound(TEXT("Shinchon.wav"), NULL, SND_FILENAME | SND_ASYNC);
					add_keeping_block(map);
					system("cls");
					story_stage2();
					break;
				case 2: // ���� Ŭ���� ==> ���빮
					PlaySound(TEXT("Dongdaemoon.wav"), NULL, SND_FILENAME | SND_ASYNC);
					add_keeping_block(map);
					system("cls");
					story_stage3();
					break;
				case 3: // ���빮 Ŭ���� ==> �սʸ�
					PlaySound(TEXT("Wangsimni.wav"), NULL, SND_FILENAME | SND_ASYNC);
					add_keeping_block(map);
					system("cls");
					story_stage4();
					break;
				case 4: // �սʸ� Ŭ���� ==> �Ǵ��Ա�(����)
					PlaySound(TEXT("Kondae.wav"), NULL, SND_FILENAME | SND_ASYNC);
					add_keeping_block(map);
					system("cls");
					story_stage5();
					break;
				case 5: // �Ǵ��Ա� Ŭ���� ==> ���
					PlaySound(TEXT("Jamsil1.wav"), NULL, SND_FILENAME | SND_ASYNC);
					mciSendCommandW(dwID, MCI_PAUSE, MCI_NOTIFY, (DWORD)(LPVOID)&m_mciPlayParms); // ������� ���߱�.
					add_keeping_block(map);
					system("cls");
					story_stage5_clear();
					story_stage6();
					mciSendCommandW(dwID, MCI_RESUME, 0, NULL); // ������� �̾ ���
					break;
				case 6: // ��� Ŭ���� ==> ����
					PlaySound(TEXT("Gangbyeon.wav"), NULL, SND_FILENAME | SND_ASYNC);
					add_keeping_block(map);
					system("cls");
					story_stage7();
					break;
				case 7: // ���� Ŭ���� ==> �Ǵ��Ա�
					PlaySound(TEXT("Kondae.wav"), NULL, SND_FILENAME | SND_ASYNC);
					add_keeping_block(map);
					system("cls");
					story_ending();
				default :
					break;
				}
				if (level == 7) {
					gotoxy(20, 10);
					cout << "���� �޴��� ���ư��ðڽ��ϱ�?(y / n) : ";

					char ch;
					cin >> ch;

					if (ch == 'y') {
						fflush(stdin);
						mciSendCommandW(dwID, MCI_CLOSE, 0, NULL); // ������� ����.
						PlaySound(NULL, NULL, NULL);
						SetColor(WHITE);
					}
					else {
						rePlay = false;
					}
					break;
				}
				upper_lines = 0;
				lower_lines = 0;
				show_total_block(map);
				show_next_block(next_block_shape);

				startTime = clock();
				current_time = -1;
				usedBlocks = 0;
				show_gamestat(stage_data);
			}

			if (is_gameover == 1)
			{
				mciSendCommandW(dwID, MCI_CLOSE, 0, NULL); //�뷡���� 
				SetColor(GRAY);
				map.init();
				Sleep(2000);
				system("cls");
				story_gameover();
				gotoxy(30, 17);
				cout << "���� �޴��� ���ư��ðڽ��ϱ�?(y / n) : ";
			
				char ch;
				cin >> ch;

				if (ch == 'y') {
					fflush(stdin);
				}

				else{
					rePlay = false;
				}

				system("cls");
				break;
			}

			if (current_time < (int)((clock() - startTime) / 1000.0))	//���� �ð�(��)�� (���� ���� ƽ-ó�� ƽ)/1000�� �ٸ� �� ==1�ʰ� ����
			{

				current_time++;	//1�ʰ� �������Ƿ�
				gotoxy(2 * (MAP_COL + 1) + ab_x, 21);	//����â ������ ����
				SetColor(GRAY);
				cout << "TIME";	//"�ð�:"

				gotoxy(2 * (MAP_COL + 1) + ab_x, 22);
				cout << setw(10) << 180 - current_time;	//�ð� ���
				SetColor(BLACK);

				if (current_time >= 180) is_gameover = 1;
			}

			if (stage_data.getStage(level).getRemain_block_limit() - usedBlocks < 0) {
				is_gameover = 1;
			}

			gotoxy(77, 23);
			Sleep(15);
			gotoxy(77, 23);

		}
	}
	
}
void PlayGame::voidCursor() {

	static HANDLE hOut;
	CONSOLE_CURSOR_INFO cInfo;

	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	cInfo.dwSize = 0;
	cInfo.bVisible = TRUE;
	SetConsoleCursorInfo(hOut, &cInfo);
}

int PlayGame::erase_cur_block(int shape, int angle, int x, int y)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			int curX = (i + x) * 2 + ab_x;
			int curY = j + y + ab_y;

			if ((curX >= 2 * (MAP_COL / 2 - 2) + ab_x && curX <= 2 * (MAP_COL / 2 + 1) + ab_x) && (curY >= MAP_ROW / 2 - 2 + ab_y && curY <= MAP_ROW / 2 + 1 + ab_y))
				SetColor(16 * DARK_RED);
			else
				SetColor(16 * BLACK);

			if (block[shape][angle][j][i] == 1)
			{
				gotoxy((i + x) * 2 + ab_x, j + y + ab_y);
				cout << "  ";
				//break;

			}
		}
	}
	return 0;
}



int PlayGame::show_total_block(Map& map)
{
	for (int i = 0; i < MAP_ROW; i++)
	{
		for (int j = 0; j < MAP_COL; j++)
		{
			if (j == LEFT_WALL || j == RIGHT_WALL || i == UPPER_WALL || i == LOWER_WALL)      //������ ���� �ܺ� ���� ����
			{
				SetColor((level % 6) + 1);
			}
			else {
				SetColor(DARK_GRAY);
			}
			if ((j >= MAP_COL / 2 - 2 && j <= MAP_COL / 2 + 1) && (i >= MAP_ROW / 2 - 2 && i <= MAP_ROW / 2 + 1))
				SetColor(16 * DARK_RED + DARK_GRAY);

			gotoxy((j * 2) + ab_x, i + ab_y);
			if (map.total_block[i][j] == 1)
			{
				cout << "��";
			}
			else if (map.total_block[i][j] == 2) {
				cout << "��";
			}
			else {
				cout << "  ";
			}

		}
	}
	SetColor(BLACK);
	gotoxy(77, 23);
	return 0;
}

int PlayGame::make_new_block(Stage_data stage_data)
{
	int i = rand() % 100;
	if (i <= stage_data.getStage(level).getStick_rate())      //����� ����Ȯ�� ���
		return 0;                     //����� ������� ����

	int shape = (rand() % 6) + 1;      //shape���� 1~6�� ���� ��
	show_next_block(shape);
	return shape;
}

int PlayGame::strike_check(int shape, int angle, int x, int y, Map& map)
{
	int block_dat;

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (((x + j) == LEFT_WALL) || ((x + j) == RIGHT_WALL))
				block_dat = 1;
			else
				block_dat = map.total_block[y + i][x + j];

			//�������� ��ǥ�� ��������
			if ((block_dat == 1) && (block[shape][angle][i][j] == 1) ||
				(block_dat == 2) && (block[shape][angle][i][j] == 1))
			{
				return 1;
			}
		}
	}
	return 0;
}

int PlayGame::merge_block(int shape, int angle, int x, int y, Stage_data stage_data, Map& map)
{
	PlaySound(TEXT("coin.wav"), NULL, SND_ASYNC | SND_NOSTOP);
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			map.total_block[y + i][x + j] |= block[shape][angle][i][j];
		}
	}
	check_full_line(stage_data, map);
	appear_merchant(map);

	show_total_block(map);

	return 0;
}

int PlayGame::block_start(int shape, int* angle, int* x, int* y)
{
	usedBlocks += 4;
	*x = (MAP_COL / 2 - 2);
	*y = (MAP_ROW / 2 - 2);
	*angle = 0;
	flag = rand() % 2; // ó���� ����� ���� �������� �Ʒ��� �������� �������� ����.
	return 0;
}


int PlayGame::move_block(int* shape, int* angle, int* x, int* y, int* next_shape, Stage_data stage_data, Map& map)
{
	erase_cur_block(*shape, *angle, *x, *y);
	if (flag == 0) {
		(*y)++;   //���� ��ĭ �Ʒ��� ����
	}
	else if (flag == 1) {
		(*y)--; //���� ��ĭ ���� �ø� 
	}

	if (strike_check(*shape, *angle, *x, *y, map) == 1)
	{
		if (flag == 0) {
			(*y)--;   //���� ��ĭ �Ʒ��� ����
		}
		else if (flag == 1) {
			(*y)++; //���� ��ĭ ���� �ø� 
		}
		//(*y)--;      // ?

		merge_block(*shape, *angle, *x, *y, stage_data, map);
		if (!map.s_item_check)   //����� ���� �ȵǾ������
		{
			*shape = *next_shape;
			*next_shape = make_new_block(stage_data);
		}
		else  //����� ����Ǿ������
		{
			*shape = s_block_shape;
			*angle = s_block_angle;      //������Ͽ� ����� ����� �������� �Ѵ�. 
			s_block_shape = -1;   //������ ����� �ٽ� �ʱ�ȭ
			s_block_angle = -1;
			map.s_item_check = false; //��� ���� ���θ� Ȯ���ϴ� ������ �ٽ� false�� �ʱ�ȭ

			for (int i = 1; i < 7; i++)
			{
				gotoxy(38, i + 24);
				for (int j = 0; j < 6; j++)      //����� ����� �����־��� ĭ�� ���ش�
				{
					cout << "  ";
				}
			}
			gotoxy(20, 22);
			cout << "                                     "; //��� ���� ������ ���� ����
		}
		/**shape = *next_shape;
		*next_shape = make_new_block(stage_data);*/

		block_start(*shape, angle, x, y);   //angle,x,y�� ��������
		show_next_block(*next_shape);
		show_gamestat(stage_data);
		return 2;
	}
	return 0;
}

int PlayGame::check_full_line(Stage_data stage_data, Map& map)
{
	int j;
	for (int i = 13; i > UPPER_WALL; i--) // ���� ��� �˻�. ���� �˻����.
	{
		for (j = (LEFT_WALL + 1); j < RIGHT_WALL; j++)
		{
			if (map.total_block[i][j] == 0)
				break;
		}
		if (j == RIGHT_WALL)   //������ �� ä������
		{
			if (upper_lines < stage_data.getStage(level).getClear_upper_line()) {
				upper_lines++;
			}
			show_total_block(map);
			SetColor(BLUE);
			gotoxy(1 * 2 + ab_x, i + ab_y);
			for (j = (LEFT_WALL + 1); j < RIGHT_WALL; j++)
			{
				cout << "��";
				Sleep(10);
			}
			gotoxy(1 * 2 + ab_x, i + ab_y);
			for (j = (LEFT_WALL + 1); j < RIGHT_WALL; j++)
			{
				cout << "  ";
				Sleep(10);
			}

			i++;
			for (int k = i; k < 14; k++) {
				for (int j = (LEFT_WALL + 1); j < RIGHT_WALL; j++) {
					if (k != (UPPER_WALL + 1)) {
						map.total_block[k - 1][j] = map.total_block[k][j]; //��ĭ�� �÷��ִ� �κ� 
					}
				}
			}
			
			show_gamestat(stage_data);
		}
	}

	for (int i = 14; i < LOWER_WALL; i++) // �Ʒ��� ��� �˻�. ���� �˻� ����.
	{
		for (j = (LEFT_WALL + 1); j < RIGHT_WALL; j++)
		{
			if (map.total_block[i][j] == 0)
				break;
		}
		if (j == RIGHT_WALL)   //������ �� ä������
		{
			if (lower_lines < stage_data.getStage(level).getClear_lower_line()) {
				lower_lines++;
			}
			show_total_block(map);
			SetColor(BLUE);
			gotoxy(1 * 2 + ab_x, i + ab_y);
			for (j = (LEFT_WALL + 1); j < RIGHT_WALL; j++)
			{
				cout << "��";
				Sleep(10);
			}
			gotoxy(1 * 2 + ab_x, i + ab_y);
			for (j = (LEFT_WALL + 1); j < RIGHT_WALL; j++)
			{
				cout << "  ";
				Sleep(10);
			}


			for (int k = i; k > 14; k--)
			{
				for (j = (LEFT_WALL + 1); j < RIGHT_WALL; j++) {
					if (k != (UPPER_WALL + 1)) {
						map.total_block[k][j] = map.total_block[k - 1][j]; //��ĭ�� �����ִ� �κ� 
					}
				}
			}
			show_gamestat(stage_data);

		}
	}
	return 0;
}

int PlayGame::check_gameover(Map & map)	//4*4�� ���� �������� 1�� ��ȯ�ϴ� �Լ�
{
	for (int j = MAP_ROW / 2 - 2; j <= MAP_ROW / 2 + 1; j++) {
		for (int i = MAP_COL / 2 - 2; i <= MAP_COL / 2 + 1; i++) {
			if (map.total_block[j][i] == 1)
				return 1;
		}
	}
	return 0;
}

void PlayGame::show_cur_block_expected(int shape, int angle, int x, Map & map, bool is_draw_mode)	//���� ������ ��ġ�� ������ִ� �Լ�
{
	if (flag == 0) {
		for (int y = block_y;; y++) {
			int check = strike_check(shape, angle, x, y, map);

			if (check == 1) {
				y--;
				int curX, curY;
				int exist_background;
				for (int i = 0; i < 4; i++)
				{
					for (int j = 0; j < 4; j++)
					{
						curX = (i + x) * 2 + ab_x;
						curY = j + y + ab_y;

						if ((curX >= 2*(MAP_COL/2 -2) + ab_x && curX <= 2 * (MAP_COL / 2 + 1) + ab_x) && (curY >= MAP_ROW/2-2+ab_y && curY <= MAP_ROW / 2 + 1 + ab_y))
							exist_background = 1;
						else
							exist_background = 0;

						switch (shape)
						{
						case 0:
							SetColor(exist_background * 16 * DARK_RED + RED);
							break;
						case 1:
							SetColor(exist_background * 16 * DARK_RED + BLUE);
							break;
						case 2:
							SetColor(exist_background * 16 * DARK_RED + SKY_BLUE);
							break;
						case 3:
							SetColor(exist_background * 16 * DARK_RED + WHITE);
							break;
						case 4:
							SetColor(exist_background * 16 * DARK_RED + YELLOW);
							break;
						case 5:
							SetColor(exist_background * 16 * DARK_RED + VOILET);
							break;
						case 6:
							SetColor(exist_background * 16 * DARK_RED + GREEN);
							break;
						}
						if ((j + y) < 0)
							continue;

						if (block[shape][angle][j][i] == 1)
						{
							gotoxy((i + x) * 2 + ab_x, j + y + ab_y);
							if (is_draw_mode) cout << "��";
							else cout << "  ";
						}
					}
				}
				SetColor(BLACK);
				gotoxy(77, 23);
				break;
			}
		}
	}
	else {
		for (int y = block_y;; y--) {
			int check = strike_check(shape, angle, x, y, map);

			if (check == 1) {
				y++;
				int curX, curY;
				int exist_background;
				for (int i = 0; i < 4; i++)
				{
					for (int j = 0; j < 4; j++)
					{
						curX = (i + x) * 2 + ab_x;
						curY = j + y + ab_y;

						if ((curX >= 2 * (MAP_COL / 2 - 2) + ab_x && curX <= 2 * (MAP_COL / 2 + 1) + ab_x) && (curY >= MAP_ROW / 2 - 2 + ab_y && curY <= MAP_ROW / 2 + 1 + ab_y))
							exist_background = 1;
						else
							exist_background = 0;

						switch (shape)
						{
						case 0:
							SetColor(exist_background * 16 * DARK_RED + RED);
							break;
						case 1:
							SetColor(exist_background * 16 * DARK_RED + BLUE);
							break;
						case 2:
							SetColor(exist_background * 16 * DARK_RED + SKY_BLUE);
							break;
						case 3:
							SetColor(exist_background * 16 * DARK_RED + WHITE);
							break;
						case 4:
							SetColor(exist_background * 16 * DARK_RED + YELLOW);
							break;
						case 5:
							SetColor(exist_background * 16 * DARK_RED + VOILET);
							break;
						case 6:
							SetColor(exist_background * 16 * DARK_RED + GREEN);
							break;
						}
						if ((j + y) < 0)
							continue;

						if (block[shape][angle][j][i] == 1)
						{
							gotoxy((i + x) * 2 + ab_x, j + y + ab_y);
							if (is_draw_mode) cout << "��";
							else cout << "  ";

						}
					}
				}
				SetColor(BLACK);
				gotoxy(77, 23);
				break;
			}
		}
	}
}

int PlayGame::add_keeping_block(Map & map)
{
	show_total_block(map);
	// �������� Ŭ���� �� ������ ���Ʒ� 1�پ� �߰�.
	int empty1, empty2; // �������� Ŭ����� ���� ��Ͽ��� ������ ���� ����� x��ǥ. 

	// ���� ��� �ױ�. 
	for (int i = 15; i > UPPER_WALL; i--) {
		for (int j = (LEFT_WALL + 1); j < RIGHT_WALL; j++) {
			map.total_block[i + 1][j] = map.total_block[i][j];
		}
	}

	for (int i = 17; i < LOWER_WALL; i++) {
		for (int j = (LEFT_WALL + 1); j < RIGHT_WALL; j++) {
			map.total_block[i - 1][j] = map.total_block[i][j];
		}
	}

	for (int i = (LEFT_WALL + 1); i < RIGHT_WALL; i++) {
		map.total_block[UPPER_WALL + 1][i] = 0;
		map.total_block[LOWER_WALL - 1][i] = 0;
	}

	switch (level) {
	case 1 : // ȫ���Ա� Ŭ���� ==> ����
		Sleep(6800);
		break;
	case 2 : // ���� Ŭ���� ==> ���빮
		Sleep(9500);
		break;
	case 3 : // ���빮 Ŭ���� ==> �սʸ�
		Sleep(6600);
		break;
	case 4 : // �սʸ� Ŭ���� ==> �Ǵ��Ա�(����)
		Sleep(8000);
		break;
	case 5 : // �Ǵ��Ա� ==> ���
		Sleep(7000);
		break;
	case 6 : // ��� Ŭ���� ==> ����
		Sleep(8000);
		break;
	case 7 : // ���� Ŭ���� ==> �Ǵ��Ա�
		Sleep(8000);
		break;
	}
	
	// ���Ʒ� ���Թ� ����.
	show_total_block(map);
	map.total_block[UPPER_WALL + 1][RIGHT_WALL] = 0;
	map.total_block[LOWER_WALL - 1][RIGHT_WALL] = 0;

	show_total_block(map);
	Sleep(1000);

	// ������� ���Ʒ��� Ÿ�� ����� ��Ÿ��.
	while (true) {

		empty1 = rand() % (RIGHT_WALL - 1) + 1; // 1 ~ 14
		empty2 = rand() % (RIGHT_WALL - 1) + 1; // 1 ~ 14

		if (empty1 != empty2) {

			for (int i = (RIGHT_WALL - 1); i > LEFT_WALL; i--) { // i : 14 ~ 1
				if (i != empty1 && i != empty2) {
					map.total_block[UPPER_WALL + 1][i] = 1;
					Sleep(50);
					show_total_block(map);
				}
			}
			break;
		}
	}

	while (true) {

		empty1 = rand() % (RIGHT_WALL - 1) + 1; // 1 ~ 14
		empty2 = rand() % (RIGHT_WALL - 1) + 1; // 1 ~ 14

		if (empty1 != empty2) {

			for (int i = (RIGHT_WALL - 1); i > LEFT_WALL; i--) {
				if (i != empty1 && i != empty2) {
					map.total_block[LOWER_WALL - 1][i] = 1;
					Sleep(50);
					show_total_block(map);
				}
			}
			break;
		}
	}

	// ���Թ� ����.
	Sleep(3000);
	map.total_block[UPPER_WALL + 1][RIGHT_WALL] = 1;
	map.total_block[LOWER_WALL - 1][RIGHT_WALL] = 1;
	show_total_block(map);
	Sleep(4500);

	return 0;
}

int PlayGame::appear_merchant(Map & map)
{
	int upper_merchant1, upper_merchant2;
	int lower_merchant1, lower_merchant2;

	if ((rand() % 40) == 0) { // ����� ���϶����� 2.5%�� Ȯ���� ����� ����.

		while (true) {
			upper_merchant1 = rand() % 10 + 1; // 1 ~ 13 ==> 1 ~ 10�� �ٲٱ�
			upper_merchant2 = rand() % 10 + 1;

			// ��� ������ġ�� �������� ���ʿ� ����� �ϳ�(��� �ϳ�) ����.

			if (map.total_block[upper_merchant1][upper_merchant2] != 1 &&
				map.total_block[upper_merchant1][upper_merchant2] != 2) {
				map.total_block[upper_merchant1][upper_merchant2] = 2;
				break;
			}
		}

		// ��� ������ġ�� �������� �Ʒ��ʿ� ����� �ϳ�(��� �ϳ�) ����.

		while (true) {
			lower_merchant1 = LOWER_WALL - (rand() % 10 + 1); // 28 ~ 15 ==> 28(29 - 1) ~ 19(29 - 10)�� �ϱ� 
			lower_merchant2 = rand() % 10 + 1;

			if (map.total_block[lower_merchant1][lower_merchant2] != 1 &&
				map.total_block[lower_merchant1][lower_merchant2] != 2) {
				map.total_block[lower_merchant1][lower_merchant2] = 2;
				break;
			}
		}
	}
	return 0;
}

int PlayGame::show_next_block(int shape)
{
	SetColor((level + 1) % 6 + 1);
	for (int i = 1; i < 7; i++)
	{
		gotoxy(2 * (MAP_COL + 1) + ab_x, i);
		for (int j = 0; j < 6; j++)
		{
			if (i == 1 || i == 6 || j == 0 || j == 5)
			{
				cout << "��";
			}
			else {
				cout << "  ";
			}

		}
	}
	show_cur_block(shape, 0, 18, 1);
	return 0;
}

int PlayGame::show_gamestat(Stage_data stage_data)
{
	static int printed_text = 0;
	SetColor(GRAY);
	if (printed_text == 0)
	{
		gotoxy(2 * (MAP_COL + 1) + ab_x, 7);
		cout << "STAGE";

		gotoxy(2 * (MAP_COL + 1) + ab_x, 9);
		cout << "SCORE";

		gotoxy(2 * (MAP_COL + 1) + ab_x, 12);
		cout << "UPPER";
		gotoxy(2 * (MAP_COL + 1) + ab_x, 13);
		cout << "LINES";

		gotoxy(2 * (MAP_COL + 1) + ab_x, 15);
		cout << "LOWER";
		gotoxy(2 * (MAP_COL + 1) + ab_x, 16);
		cout << "LINES";

		gotoxy(2 * (MAP_COL + 1) + ab_x, 18);
		cout << "REMAIN";
		gotoxy(2 * (MAP_COL + 1) + ab_x, 19);
		cout << "BLOCK";
	}
	gotoxy(2 * (MAP_COL + 1) + ab_x + 6, 7);
	cout << stage_data.getStage(level).getStation_name() << "            ";
	gotoxy(2 * (MAP_COL + 1) + ab_x, 10);
	cout << setw(10) << score;
	gotoxy(2 * (MAP_COL + 1) + ab_x, 14);
	cout << setw(10) << stage_data.getStage(level).getClear_upper_line() - upper_lines;
	gotoxy(2 * (MAP_COL + 1) + ab_x, 17);
	cout << setw(10) << stage_data.getStage(level).getClear_lower_line() - lower_lines;
	gotoxy(2 * (MAP_COL + 1) + ab_x, 20);
	cout << setw(10) << stage_data.getStage(level).getRemain_block_limit() - usedBlocks;
	return 0;
}

PlayGame::~PlayGame()
{
}
void PlayGame::save_block_item() //���� ��� ���� ������
{

	SetColor((level + 2) % 6 + 1);
	int i, j;
	for (i = 1; i < 7; i++)
	{
		gotoxy(2 * (MAP_COL + 1) + ab_x, i + 24);
		for (j = 0; j < 6; j++)   //����� ����� �� ĭ�� �����
		{
			if (i == 1 || i == 6 || j == 0 || j == 5)
			{
				cout << "��";
			}
			else {
				cout << "  ";
			}

		}
	}
	
	gotoxy(20, 32);
	SetColor(WHITE);
	cout << "����� �ҷ������� '2' Ű�� �����ּ���"; //��� �ȳ�����

	show_cur_block(block_shape, block_angle, 18, 25);//1�� ������ ����� ����� ǥ���Ѵ�, 1/2����
	s_block_shape = block_shape; //����� �����Ѵ�
	s_block_angle = block_angle;

	block_shape = next_block_shape;
	next_block_shape = make_new_block(stage_data);
	erase_cur_block(s_block_shape, s_block_angle, block_x, block_y); //����� ����� �÷����ϴ� ȭ�鿡�� �����
	block_start(block_shape, &block_angle, &block_x, &block_y);

}