#include "SetGame.h"



SetGame::SetGame()
	: score(0), enter_game(false)
{
}

int SetGame::gotoxy(int x, int y)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.Y = y;
	pos.X = x;
	SetConsoleCursorPosition(hConsole, pos);
	return 0;
}

void SetGame::SetColor(int color)
{
	static HANDLE std_output_handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(std_output_handle, color);
}

int SetGame::init()
{
	//전역변수 초기화
	level = 0;
	upper_lines = 0;
	lower_lines = 0;
	ab_x = 5;
	ab_y = 1;
	s_block_angle = -1;
	s_block_shape = -1;
	timer_flag = true;
	return 0;
}

void SetGame::show_menu()
{
	PlaySound(TEXT("Menubgm.wav"), NULL, SND_FILENAME | SND_ASYNC);

	gotoxy(10, 2); Sleep(10);  cout << "          BBBBBBBBBBBBBBBBB 	   ";
	gotoxy(10, 3); Sleep(10);  cout << "      BBBBBBBB        BBBBBBBB     ";
	gotoxy(10, 4); Sleep(10);  cout << "     BBBBBBBBB        BBBBBBBBB    ";
	gotoxy(10, 5); Sleep(10);  cout << "    BBBBBBBBBBBBBBBBBBBBBBBBBBBB   ";
	gotoxy(10, 6); Sleep(10);  cout << "    BB          ... .        BBB   ";
	gotoxy(10, 7); Sleep(10);  cout << "    BB                       BBB   ";
	gotoxy(10, 8); Sleep(10);  cout << "    BB  . . ... ... . . ...  BBB   ";
	gotoxy(10, 9); Sleep(10);  cout << "    BB  ...................  BBB   ";
	gotoxy(10, 10);Sleep(10);  cout << "    BB  ... ............. .  BBB   ";
	gotoxy(10, 11); Sleep(10); cout << "    BB   . . . .   .   . .   BBB   ";
	gotoxy(10, 12); Sleep(10); cout << "    BB                       BBB   ";
	gotoxy(10, 13); Sleep(10); cout << "    BBBBBBBBBBBBBBBBBBBBBBBBBBBB   ";
	gotoxy(10, 14); Sleep(10); cout << "    BBBBBBBBBBBBBBBBBBBBBBBBBBBB   ";
	gotoxy(10, 15); Sleep(10); cout << "    BBB      BBBBBBBBBB     BBBB   ";
	gotoxy(10, 16); Sleep(10); cout << "     BBBB   BBBBBBBBBBBB   BBBB    ";
	gotoxy(10, 17); Sleep(10); cout << "      BBBBBBBBBBBBBBBBBBBBBBB      ";
	gotoxy(10, 18); Sleep(10); cout << "        BBBBBBBBBBBBBBBBBBB        ";
	gotoxy(10, 19); Sleep(10); cout << "       BBBBBBBBBBBBBBBBBBBBBB      ";
	gotoxy(10, 20); Sleep(10); cout << "     BBBBB                BBBB     ";
	gotoxy(10, 21); Sleep(10); cout << "    BBBB                   BBBB    ";

	gotoxy(50, 2); Sleep(10);  cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@";
	gotoxy(50, 3); Sleep(10);  cout << "@                                                          @";
	gotoxy(50, 4); Sleep(10);  cout << "@          BB      BB                                      @";
	gotoxy(50, 5); Sleep(10);  cout << "@         BBB     BBB           BBB                        @";
	gotoxy(50, 6); Sleep(10);  cout << "@         BBBBB BBBBB   BBBBB  BBBBB  BBBBBB  BBBBB        @";
	gotoxy(50, 7); Sleep(10);  cout << "@         BB BB BB BB  BB   BB  BBB   BBBB   BB   BB       @";
	gotoxy(50, 8); Sleep(10);  cout << "@         BB  BBB  BB  BBBBBBB  BBB   BBB    BB   BB       @";
	gotoxy(50, 9); Sleep(10);  cout << "@         BB  BBB  BB  BBB      BBB   BBB    BB   BB       @";
	gotoxy(50, 10); Sleep(10); cout << "@         BB   B   BB   BBBBB   BBBB  BBB     BBBBB        @";
	gotoxy(50, 11); Sleep(10); cout << "@                                                          @";
	gotoxy(50, 12); Sleep(10); cout << "@                                                          @";
	gotoxy(50, 13); Sleep(10); cout << "@                                                          @";
	gotoxy(50, 14); Sleep(10); cout << "@       BBBBBBB BBBBBBB BBBBBBB BBBBBBB  BBB  BBBBBB       @";
	gotoxy(50, 15); Sleep(10); cout << "@         BBB   BBB       BBB   BB   BB  BBB  BBB          @";
	gotoxy(50, 16); Sleep(10); cout << "@         BBB   BBBBBB    BBB   BB   BB  BBB  BBBB         @";
	gotoxy(50, 17); Sleep(10); cout << "@         BBB   BBBBBB    BBB   BBBBBBB  BBB    BBBB       @";
	gotoxy(50, 18); Sleep(10); cout << "@         BBB   BBB       BBB   BB   BB  BBB      BBB      @";
	gotoxy(50, 19); Sleep(10); cout << "@         BBB   BBBBBBB   BBB   BB    BB BBB  BBBBBBB      @";
	gotoxy(50, 20); Sleep(10); cout << "@                                                          @";
	gotoxy(50, 21); Sleep(10); cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@";
	
	gotoxy(42, 23); Sleep(10); cout << "① ||  게임시작  ||";
	gotoxy(42, 25); Sleep(10); cout << "② ||   조작키   ||";
	gotoxy(42, 27); Sleep(10); cout << "③ ||   제작자   ||";
	gotoxy(42, 29); Sleep(10); cout << "④ ||  게임종료  ||";
	// 메뉴의 화면입니다.
	int x = 37, y = 23;
	char keytemp2;
	
	gotoxy(x, y); cout << "▶\b";
	
	while (enter_game == false) { // enter_game이 true가 되면 menu()를 빠져나옵니다.

		keytemp2 = _getch();

		if (keytemp2 == EXT_KEY) {

			keytemp2 = _getch();

			switch (keytemp2) {
			case KEY_DOWN:
				if (y < 29) {
					gotoxy(x, y); cout << " "; // 현재 위치에 있는 ▶을 지워줍니다.
					y += 2;
					gotoxy(x, y); cout << "▶\b";
				}

				else { // y의 좌표가 21일 때, 즉 메뉴항목의 맨 밑을 가리키고 있는 경우에는 ▶가 움직이지 않습니다.
					gotoxy(x, 29); cout << "▶\b";
				}
				break;

			case KEY_UP:
				if (y > 23) {
					gotoxy(x, y); cout << " "; // 현재 위치에 있는 ▶을 지워줍니다.
					y -= 2;
					gotoxy(x, y); cout << "▶\b";
				}
				else { // y의 좌표가 23일 때, 즉 메뉴항목의 맨 위를 가리키고 있는 경우에는 ▶가 움직이지 않습니다.
					gotoxy(x, 23); cout << "▶\b";
				}
				break;
			}
		}

		else if (keytemp2 == ENTER) {
			if (y == 23) { // 게임 시작
				system("cls");
				enter_game = true; // 게임 시작을 누르면 enter_game의 값이 되어 menu()함수를 빠져나오도록 합니다.
			}

			else if (y == 25) { // 게임 설명
				cout << "\b "; // ▶을 지워줍니다.
				system("cls");
				keyInfo();
			}

			else if (y == 27) { // 제작자
				cout << "\b "; // ▶을 지워줍니다.
				system("cls");
				maker();
			}

			else if (y == 29) { // 게임종료
				system("cls");
				exit(0);
			}
		}
	}
	

	system("cls");
}

int SetGame::show_story()
{
	char arr1[100] = "동훈이는 오늘 아침 1교시 수업이있다. 현재시각 8시 20분 동훈은 꿀잠중...";
	gotoxy(13, 3);
	for (int i = 0; i < sizeof(arr1); i++) { // SND_ASYNC
		PlaySound(TEXT("Typesound.wav"), NULL, SND_FILENAME | SND_ASYNC);
		cout << arr1[i];
		Sleep(15);
		if (arr1[i] == NULL) {
			break;
		}
	}
	PlaySound(NULL, NULL, NULL);

	char arr2[100] = "동훈이는 잘 자다가 갑자기 쎄한 느낌이 든다... 너무 잘 잔거 같다...";
	gotoxy(13, 5);
	for (int i = 0; i < sizeof(arr2); i++) {
		PlaySound(TEXT("Typesound.wav"), NULL, SND_FILENAME | SND_ASYNC);
		cout << arr2[i];
		Sleep(15);
		if (arr2[i] == NULL) {
			break;
		}
	}
	PlaySound(NULL, NULL, NULL);

	char arr3[100] = "눈이 번쩍 뜬 동훈은 얼른 시계를 본다.";
	gotoxy(13, 7);
	for (int i = 0; i < sizeof(arr3); i++) {
		PlaySound(TEXT("Typesound.wav"), NULL, SND_FILENAME | SND_ASYNC);
		cout << arr3[i];
		Sleep(15);
		if (arr3[i] == NULL) {
			break;
		}
	}
	PlaySound(NULL, NULL, NULL);
	Sleep(600);

	system("cls");
	char arr4[100] = "깜짝 놀라 잠이 달아난 동훈은 얼른 일어나 지하철을 타러간다.";
	gotoxy(13, 3);
	for (int i = 0; i < sizeof(arr4); i++) {
		PlaySound(TEXT("Typesound.wav"), NULL, SND_FILENAME | SND_ASYNC);
		cout << arr4[i];
		Sleep(15);
		if (arr4[i] == NULL) {
			break;
		}
	}
	PlaySound(NULL, NULL, NULL);

	char arr5[100] = "동훈의 집은 홍대입구역 근처";
	gotoxy(13, 5);
	for (int i = 0; i < sizeof(arr5); i++) {
		PlaySound(TEXT("Typesound.wav"), NULL, SND_FILENAME | SND_ASYNC);
		cout << arr5[i];
		Sleep(15);
		if (arr5[i] == NULL) {
			break;
		}
	}
	PlaySound(NULL, NULL, NULL);

	char arr6[100] = "동훈이는 과연 1교시 수업에 늦지 않게 건대입구역에 도착할 수 있을까?";
	gotoxy(13, 7);
	for (int i = 0; i < sizeof(arr6); i++) {
		PlaySound(TEXT("Typesound.wav"), NULL, SND_FILENAME | SND_ASYNC);
		cout << arr6[i];
		Sleep(15);
		if (arr6[i] == NULL) {
			break;
		}
	}
	PlaySound(NULL, NULL, NULL);
	Sleep(600);

	system("cls");
	char arr7[100] = "지하철 열차칸을 시간 제한 이내에 채워서 열차를 출발시켜라!!!";
	gotoxy(13, 5);
	for (int i = 0; i < sizeof(arr7); i++) {
		PlaySound(TEXT("Typesound.wav"), NULL, SND_FILENAME | SND_ASYNC);
		cout << arr7[i];
		Sleep(15);
		if (arr7[i] == NULL) {
			break;
		}
	}
	PlaySound(NULL, NULL, NULL);
	Sleep(400);

	system("cls");

	gotoxy(20, 10);
	cout << "아무키를 누르면 게임이 시작됩니다.";
	while (true) {
		if (_kbhit())
			break;
	}
	_getche();

	// level = 0;
	system("cls");

	return 0;
}

void SetGame::keyInfo()
{
	SetColor(GRAY);

	gotoxy(30, 4); cout << "■■■■■■<GAME KEY>■■■■■■";
	Sleep(10);
	gotoxy(30, 5); cout << "■                              ■";
	Sleep(10);
	gotoxy(30, 6); cout << "■  UP   : Rotate Block         ■";
	Sleep(10);
	gotoxy(30, 7); cout << "■                              ■";
	Sleep(10);
	gotoxy(30, 8); cout << "■  DOWN : Move One-Step Down   ■";
	Sleep(10);
	gotoxy(30, 9); cout << "■                              ■";
	Sleep(10);
	gotoxy(30, 10);cout << "■  SPACE: Move Bottom Down     ■";
	Sleep(10);
	gotoxy(30, 11);cout << "■                              ■";
	Sleep(10);
	gotoxy(30, 12);cout << "■  LEFT : Move Left            ■";
	Sleep(10);
	gotoxy(30, 13);cout << "■                              ■";
	Sleep(10);
	gotoxy(30, 14);cout << "■  RIGHT: Move Right           ■";
	Sleep(10);
	gotoxy(30, 15);cout << "■                              ■";
	Sleep(10);
	gotoxy(30, 16);cout << "■   a   : 위아래 변환          ■";
	Sleep(10);
	gotoxy(30, 17);cout << "■                              ■";
	Sleep(10);
	gotoxy(30, 18);cout << "■   1   : 현재블록저장         ■";
	Sleep(10);
	gotoxy(30, 19);cout << "■                              ■";
	Sleep(10);
	gotoxy(30, 20);cout << "■   2   : 저장블록 호출        ■";
	Sleep(10);
	gotoxy(30, 21);cout << "■                              ■";
	Sleep(10);
	gotoxy(30, 22);cout << "■   ESC : 일시정지             ■";
	Sleep(10);
	gotoxy(30, 23);cout << "■                              ■";
	Sleep(10);
	gotoxy(30, 24);cout << "■■■■■■■■■■■■■■■■■";

	gotoxy(28, 27);
	cout << "||  'q'를 누르면 메뉴로 돌아갑니다.  || ";

	char ch = _getch();

	if (ch == 'q') {
		system("cls");
		show_menu();
	}
	else {
		keyInfo();
	}


}
void SetGame::maker()
{
	SetColor(GRAY);

	gotoxy(30, 7);
	cout << "■■■■■■■■< Credit >■■■■■■■■";
	Sleep(10);
	gotoxy(30, 8);
	cout << "■                                      ■";
	Sleep(10);
	gotoxy(30, 9);
	cout << "■        팀장 : 201811186 백동훈       ■";
	Sleep(10);
	gotoxy(30, 10);
	cout << "■                                      ■";
	Sleep(10);
	gotoxy(30, 11);
	cout << "■        팀원 : 201411196 김영현       ■";
	Sleep(10);
	gotoxy(30, 12);
	cout << "■                                      ■";
	Sleep(10);
	gotoxy(30, 13);
	cout << "■        팀원 : 201811169 김재현       ■";
	Sleep(10);
	gotoxy(30, 14);
	cout << "■                                      ■";
	Sleep(10);
	gotoxy(30, 15);
	cout << "■        팀원 : 201811162 김성윤       ■";
	Sleep(10);
	gotoxy(30, 16);
	cout << "■                                      ■";
	Sleep(10);
	gotoxy(30, 17);
	cout << "■■■■■■■■■■■■■■■■■■■■■";
	gotoxy(32, 20);
	cout << "||  'q'를 누르면 메뉴로 돌아갑니다.  || ";

	char ch = _getch();

	if (ch == 'q') {
		system("cls");
		show_menu();
	}
	else {
		maker();
	}

}
int SetGame::show_cur_block(int shape, int angle, int x, int y)
{
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
				cout << "■";

			}
		}
	}
	SetColor(BLACK);
	gotoxy(77, 23);
	return 0;
}
//시나리오 설명
void SetGame::story_stage1() {

	char arr1[100] = "(stage1) 홍대 입구역";
	gotoxy(13, 3);
	for (int i = 0; i < sizeof(arr1); i++) {
		cout << arr1[i];
		Sleep(10);
		if (arr1[i] == NULL) {
			break;
		}
	}
	char arr2[100] = "현재 시각 8시 23분...";
	gotoxy(13, 5);
	for (int i = 0; i < sizeof(arr2); i++) {
		cout << arr2[i];
		Sleep(10);
		if (arr2[i] == NULL) {
			break;
		}
	}
	char arr3[100] = "열차를 3분이내에 출발시켜라!";
	gotoxy(13, 7);
	for (int i = 0; i < sizeof(arr3); i++) {
		cout << arr3[i];
		Sleep(10);
		if (arr3[i] == NULL) {
			break;
		}
	}
	Sleep(2000);
	system("cls");
}
void SetGame::story_stage2() {
	SetColor(WHITE);
	char arr1[100] = "(stage2) 신촌역";
	gotoxy(13, 3);
	for (int i = 0; i < sizeof(arr1); i++) {
		cout << arr1[i];
		Sleep(10);
		if (arr1[i] == NULL) {
			break;
		}
	}
	char arr2[100] = "현재 시각 8시 26분...";
	gotoxy(13, 5);
	for (int i = 0; i < sizeof(arr2); i++) {
		cout << arr2[i];
		Sleep(10);
		if (arr2[i] == NULL) {
			break;
		}
	}
	char arr3[100] = "열차를 3분이내에 출발시켜라";
	gotoxy(13, 7);
	for (int i = 0; i < sizeof(arr3); i++) {
		cout << arr3[i];
		Sleep(10);
		if (arr3[i] == NULL) {
			break;
		}
	}
	Sleep(2000);
	system("cls");
}
void SetGame::story_stage3() {
	SetColor(WHITE);
	char arr1[100] = "(stage3) 동대문 역사 문화공원역";
	gotoxy(13, 3);
	for (int i = 0; i < sizeof(arr1); i++) {
		cout << arr1[i];
		Sleep(10);
		if (arr1[i] == NULL) {
			break;
		}
	}
	char arr2[100] = "현재 시각 8시 29분...";
	gotoxy(13, 5);
	for (int i = 0; i < sizeof(arr2); i++) {
		cout << arr2[i];
		Sleep(10);
		if (arr2[i] == NULL) {
			break;
		}
	}
	char arr3[100] = "열차를 3분이내에 출발시켜라";
	gotoxy(13, 7);
	for (int i = 0; i < sizeof(arr3); i++) {
		cout << arr3[i];
		Sleep(10);
		if (arr3[i] == NULL) {
			break;
		}
	}
	Sleep(2000);
	system("cls");

}
void SetGame::story_stage4() {
	SetColor(WHITE);
	char arr1[100] = "(stage4) 왕십리 역";
	gotoxy(13, 3);
	for (int i = 0; i < sizeof(arr1); i++) {
		cout << arr1[i];
		Sleep(10);
		if (arr1[i] == NULL) {
			break;
		}
	}
	char arr2[100] = "현재 시각 8시 32분...";
	gotoxy(13, 5);
	for (int i = 0; i < sizeof(arr2); i++) {
		cout << arr2[i];
		Sleep(10);
		if (arr2[i] == NULL) {
			break;
		}
	}
	char arr3[100] = "열차를 3분이내에 출발시켜라";
	gotoxy(13, 7);
	for (int i = 0; i < sizeof(arr3); i++) {
		cout << arr3[i];
		Sleep(10);
		if (arr3[i] == NULL) {
			break;
		}
	}
	Sleep(2000);
	system("cls");
}
void SetGame::story_stage5() {
	SetColor(WHITE);

	char arr1[100] = "(stage5) 건대 입구역";
	gotoxy(13, 3);
	for (int i = 0; i < sizeof(arr1); i++) {
		cout << arr1[i];
		Sleep(10);
		if (arr1[i] == NULL) {
			break;
		}
	}

	char arr2[100] = "Zzz..........";
	gotoxy(13, 5);
	for (int i = 0; i < sizeof(arr2); i++) {
		cout << arr2[i];
		Sleep(20);
		if (arr2[i] == NULL) {
			break;
		}
	}
	char arr3[100] = "동훈은 졸고있다...";
	gotoxy(13, 7);
	for (int i = 0; i < sizeof(arr3); i++) {
		cout << arr3[i];
		Sleep(10);
		if (arr3[i] == NULL) {
			break;
		}
	}
	
	char arr4[100] = "현재 시각 8시 35분...";
	gotoxy(13, 9);
	for (int i = 0; i < sizeof(arr4); i++) {
		cout << arr4[i];
		Sleep(10);
		if (arr4[i] == NULL) {
			break;
		}
	}
	char arr5[100] = "열차를 3분이내에 출발시켜라";
	gotoxy(13, 11);
	for (int i = 0; i < sizeof(arr5); i++) {
		cout << arr5[i];
		Sleep(10);
		if (arr5[i] == NULL) {
			break;
		}
	}
	Sleep(2000);
	system("cls");
}
void SetGame::story_stage5_clear() {
	//		역내 안내 방송
	//		"이번역은 건대 건대 입구역입니다"
	//		(문 열리는 소리)

	SetColor(WHITE);
	char arr1[100] = "..........";
	gotoxy(13, 3);
	for (int i = 0; i < sizeof(arr1); i++) {
		cout << arr1[i];
		Sleep(10);
		if (arr1[i] == NULL) {
			break;
		}
	}
	char arr2[100] = "동훈은 계속 졸고있다...";
	gotoxy(13, 5);
	for (int i = 0; i < sizeof(arr2); i++) {
		cout << arr2[i];
		Sleep(10);
		if (arr2[i] == NULL) {
			break;
		}
	}
	Sleep(2000);
	system("cls");

	//	역내 안내 방송
	//	"이번역은 잠실 송파구청역입니다. 내리는 문은 왼쪽입니다."

	PlaySound(TEXT("jamsil2.wav"), NULL, SND_ASYNC | SND_NOSTOP);

	system("cls");
	for (int i = 0; i < 7; i++) {
		
		if(i == 0 || i == 6) {
			gotoxy(13, 5); SetColor(WHITE); Sleep(550);
			cout << "■■■■■■■■■■■■■■■■■■■■■■■■■■";
			gotoxy(13, 6);
			cout << "■                                                ■";
			gotoxy(13, 7);
			cout << "■        이번 역은 잠실 송파구청역입니다.        ■";
			gotoxy(13, 8);
			cout << "■                                                ■";
			gotoxy(13, 9);
			cout << "■■■■■■■■■■■■■■■■■■■■■■■■■■";
		}
		else if(i == 1 || i == 5) {
			gotoxy(13, 5); SetColor(GRAY); Sleep(550);
			cout << "■■■■■■■■■■■■■■■■■■■■■■■■■■";
			gotoxy(13, 6);
			cout << "■                                                ■";
			gotoxy(13, 7);
			cout << "■        이번 역은 잠실 송파구청역입니다.        ■";
			gotoxy(13, 8);
			cout << "■                                                ■";
			gotoxy(13, 9);
			cout << "■■■■■■■■■■■■■■■■■■■■■■■■■■";
		}
		else if(i == 2 || i == 4) {
			gotoxy(13, 5); SetColor(DARK_GRAY); Sleep(550);
			cout << "■■■■■■■■■■■■■■■■■■■■■■■■■■";
			gotoxy(13, 6);
			cout << "■                                                ■";
			gotoxy(13, 7);
			cout << "■        이번 역은 잠실 송파구청역입니다.        ■";
			gotoxy(13, 8);
			cout << "■                                                ■";
			gotoxy(13, 9);
			cout << "■■■■■■■■■■■■■■■■■■■■■■■■■■";
		}
		else if (i == 3) {
			gotoxy(13, 5); SetColor(BLACK); Sleep(550);
			cout << "■■■■■■■■■■■■■■■■■■■■■■■■■■";
			gotoxy(13, 6);
			cout << "■                                                ■";
			gotoxy(13, 7);
			cout << "■        이번 역은 잠실 송파구청역입니다.        ■";
			gotoxy(13, 8);
			cout << "■                                                ■";
			gotoxy(13, 9);
			cout << "■■■■■■■■■■■■■■■■■■■■■■■■■■";
		}
	}

	system("cls");

	char arr3[100] = "	' 어! 여기가 어디지 ?  잠실????????' ";
	gotoxy(13, 3);
	for (int i = 0; i < sizeof(arr3); i++) {
		cout << arr3[i];
		Sleep(20);
		if (arr3[i] == NULL) {
			break;
		}
	}

	char arr4[100] = "	동훈 :  '또 졸았네 ㅠㅠ 지금이...  ";
	gotoxy(13, 5);
	for (int i = 0; i < sizeof(arr4); i++) {
		cout << arr4[i];
		Sleep(20);
		if (arr4[i] == NULL) {
			break;
		}
	}
	char arr5[100] = "	8시 40분이니까.. 그래도 아직 시간은 남아있네 다행이다 ' ";
	gotoxy(13, 7);
	for (int i = 0; i < sizeof(arr5); i++) {
		cout << arr5[i];
		Sleep(20);
		if (arr5[i] == NULL) {
			break;
		}
	}
	Sleep(2000);
	system("cls");
}
void SetGame::story_stage6() {
	SetColor(WHITE);
	char arr1[100] = "(stage6) 잠실역";
	gotoxy(13, 3);
	for (int i = 0; i < sizeof(arr1); i++) {
		cout << arr1[i];
		Sleep(20);
		if (arr1[i] == NULL) {
			break;
		}
	}
	char arr3[100] = "현재 시각 8시 40분...";
	gotoxy(13, 5);
	for (int i = 0; i < sizeof(arr3); i++) {
		cout << arr3[i];
		Sleep(20);
		if (arr3[i] == NULL) {
			break;
		}
	}
	char arr4[100] = "3분 내에 동훈이를 강변역으로 보내야한다!!";
	gotoxy(13, 7);
	for (int i = 0; i < sizeof(arr4); i++) {
		cout << arr4[i];
		Sleep(20);
		if (arr4[i] == NULL) {
			break;
		}
	}
	char arr5[100] = "하지만 사람이 너무 많다.";
	gotoxy(13, 9);
	for (int i = 0; i < sizeof(arr5); i++) {
		cout << arr5[i];
		Sleep(20);
		if (arr5[i] == NULL) {
			break;
		}
	}
	char arr6[100] = "테트리스 블록을 깨트려 빠르게 열차를 출발시켜라!";
	gotoxy(13, 13);
	for (int i = 0; i < sizeof(arr6); i++) {
		cout << arr6[i];
		Sleep(20);
		if (arr6[i] == NULL) {
			break;
		}
	}
	Sleep(2000);
	system("cls");
}

void SetGame::story_stage7() {
	SetColor(WHITE);
	char arr1[100] = "(stage7) 강변역";
	gotoxy(13, 3);
	for (int i = 0; i < sizeof(arr1); i++) {
		cout << arr1[i];
		Sleep(10);
		if (arr1[i] == NULL) {
			break;
		}
	}
	char arr2[100] = "현재 시각 8시 45분...";
	gotoxy(13, 5);
	for (int i = 0; i < sizeof(arr2); i++) {
		cout << arr2[i];
		Sleep(10);
		if (arr2[i] == NULL) {
			break;
		}
	}
	char arr3[100] = "열차를 3분이내에 출발시켜라";
	gotoxy(13, 7);
	for (int i = 0; i < sizeof(arr3); i++) {
		cout << arr3[i];
		Sleep(10);
		if (arr3[i] == NULL) {
			break;
		}
	}
	Sleep(2000);
	system("cls");
}

void SetGame::story_ending()
{
	SetColor(WHITE);
	char arr1[100] = "현재 시각 8시 50분...";
	gotoxy(13, 3);
	for (int i = 0; i < sizeof(arr1); i++) {
		cout << arr1[i];
		Sleep(20);
		if (arr1[i] == NULL) {
			break;
		}
	}

	char arr2[100] = "무사히 건대입구역에 도착한 동훈이는 1교시에 늦지않았다.";
	gotoxy(13, 5);
	for (int i = 0; i < sizeof(arr2); i++) {
		cout << arr2[i];
		Sleep(20);
		if (arr2[i] == NULL) {
			break;
		}
	}

	char arr3[100] = "수업을 잘 듣는 착실한 대학생 동훈이는";
	gotoxy(13, 7);
	for (int i = 0; i < sizeof(arr3); i++) {
		cout << arr3[i];
		Sleep(20);
		if (arr3[i] == NULL) {
			break;
		}
	}

	char arr4[100] = "좋은 학점으로 졸업했다.";
	gotoxy(13, 9);
	for (int i = 0; i < sizeof(arr4); i++) {
		cout << arr4[i];
		Sleep(20);
		if (arr4[i] == NULL) {
			break;
		}
	}

	char arr5[100] = "덕분에 좋은 직장을 얻었고 높은 연봉을 받았다.";
	gotoxy(13, 11);
	for (int i = 0; i < sizeof(arr5); i++) {
		cout << arr5[i];
		Sleep(20);
		if (arr5[i] == NULL) {
			break;
		}
	}

	char arr6[100] = "그렇게 평생 행복하게 오래 오래 살았다고 한다.";
	gotoxy(13, 13);
	for (int i = 0; i < sizeof(arr6); i++) {
		cout << arr6[i];
		Sleep(20);
		if (arr6[i] == NULL) {
			break;
		}
	}

	char arr7[100] = "Ending....";
	gotoxy(20, 19);
	for (int i = 0; i < sizeof(arr7); i++) {
		cout << arr7[i];
		Sleep(20);
		if (arr7[i] == NULL) {
			break;
		}
	}
	Sleep(2000);
	system("cls");
}
void SetGame::story_gameover()
{
	//		역내 안내방송
	//		" 저희 열차 역내 사고로 인해 출발하지 못하고 있습니다.
	//		승객 여러분께 대단히 죄송합니다."

	PlaySound(TEXT("gameover.wav"), NULL, SND_FILENAME | SND_ASYNC);

	SetColor(WHITE);

	char arr1[100] = "결국 열차는 지연운행 되고 말았다....";
	gotoxy(30, 10);
	for (int i = 0; i < sizeof(arr1); i++) {
		cout << arr1[i];
		Sleep(20);
		if (arr1[i] == NULL) {
			break;
		}
	}

	char arr2[100] = "그렇게 동훈이는 지각을 해야했다...";
	gotoxy(30, 12);
	for (int i = 0; i < sizeof(arr2); i++) {
		cout << arr2[i];
		Sleep(20);
		if (arr2[i] == NULL) {
			break;
		}
	}
	char arr3[100] = "Game Over";
	gotoxy(41, 15); SetColor(RED);
	for (int i = 0; i < sizeof(arr2); i++) {
		cout << arr3[i];
		Sleep(20);
		if (arr3[i] == NULL) {
			break;
		}
	}
	SetColor(WHITE);
}
SetGame::~SetGame()
{
}
