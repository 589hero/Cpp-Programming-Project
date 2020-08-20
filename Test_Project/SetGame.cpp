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
	//�������� �ʱ�ȭ
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
	
	gotoxy(42, 23); Sleep(10); cout << "�� ||  ���ӽ���  ||";
	gotoxy(42, 25); Sleep(10); cout << "�� ||   ����Ű   ||";
	gotoxy(42, 27); Sleep(10); cout << "�� ||   ������   ||";
	gotoxy(42, 29); Sleep(10); cout << "�� ||  ��������  ||";
	// �޴��� ȭ���Դϴ�.
	int x = 37, y = 23;
	char keytemp2;
	
	gotoxy(x, y); cout << "��\b";
	
	while (enter_game == false) { // enter_game�� true�� �Ǹ� menu()�� �������ɴϴ�.

		keytemp2 = _getch();

		if (keytemp2 == EXT_KEY) {

			keytemp2 = _getch();

			switch (keytemp2) {
			case KEY_DOWN:
				if (y < 29) {
					gotoxy(x, y); cout << " "; // ���� ��ġ�� �ִ� ���� �����ݴϴ�.
					y += 2;
					gotoxy(x, y); cout << "��\b";
				}

				else { // y�� ��ǥ�� 21�� ��, �� �޴��׸��� �� ���� ����Ű�� �ִ� ��쿡�� ���� �������� �ʽ��ϴ�.
					gotoxy(x, 29); cout << "��\b";
				}
				break;

			case KEY_UP:
				if (y > 23) {
					gotoxy(x, y); cout << " "; // ���� ��ġ�� �ִ� ���� �����ݴϴ�.
					y -= 2;
					gotoxy(x, y); cout << "��\b";
				}
				else { // y�� ��ǥ�� 23�� ��, �� �޴��׸��� �� ���� ����Ű�� �ִ� ��쿡�� ���� �������� �ʽ��ϴ�.
					gotoxy(x, 23); cout << "��\b";
				}
				break;
			}
		}

		else if (keytemp2 == ENTER) {
			if (y == 23) { // ���� ����
				system("cls");
				enter_game = true; // ���� ������ ������ enter_game�� ���� �Ǿ� menu()�Լ��� ������������ �մϴ�.
			}

			else if (y == 25) { // ���� ����
				cout << "\b "; // ���� �����ݴϴ�.
				system("cls");
				keyInfo();
			}

			else if (y == 27) { // ������
				cout << "\b "; // ���� �����ݴϴ�.
				system("cls");
				maker();
			}

			else if (y == 29) { // ��������
				system("cls");
				exit(0);
			}
		}
	}
	

	system("cls");
}

int SetGame::show_story()
{
	char arr1[100] = "�����̴� ���� ��ħ 1���� �������ִ�. ����ð� 8�� 20�� ������ ������...";
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

	char arr2[100] = "�����̴� �� �ڴٰ� ���ڱ� ���� ������ ���... �ʹ� �� �ܰ� ����...";
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

	char arr3[100] = "���� ��½ �� ������ �� �ð踦 ����.";
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
	char arr4[100] = "��¦ ��� ���� �޾Ƴ� ������ �� �Ͼ ����ö�� Ÿ������.";
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

	char arr5[100] = "������ ���� ȫ���Ա��� ��ó";
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

	char arr6[100] = "�����̴� ���� 1���� ������ ���� �ʰ� �Ǵ��Ա����� ������ �� ������?";
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
	char arr7[100] = "����ö ����ĭ�� �ð� ���� �̳��� ä���� ������ ��߽��Ѷ�!!!";
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
	cout << "�ƹ�Ű�� ������ ������ ���۵˴ϴ�.";
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

	gotoxy(30, 4); cout << "�������<GAME KEY>�������";
	Sleep(10);
	gotoxy(30, 5); cout << "��                              ��";
	Sleep(10);
	gotoxy(30, 6); cout << "��  UP   : Rotate Block         ��";
	Sleep(10);
	gotoxy(30, 7); cout << "��                              ��";
	Sleep(10);
	gotoxy(30, 8); cout << "��  DOWN : Move One-Step Down   ��";
	Sleep(10);
	gotoxy(30, 9); cout << "��                              ��";
	Sleep(10);
	gotoxy(30, 10);cout << "��  SPACE: Move Bottom Down     ��";
	Sleep(10);
	gotoxy(30, 11);cout << "��                              ��";
	Sleep(10);
	gotoxy(30, 12);cout << "��  LEFT : Move Left            ��";
	Sleep(10);
	gotoxy(30, 13);cout << "��                              ��";
	Sleep(10);
	gotoxy(30, 14);cout << "��  RIGHT: Move Right           ��";
	Sleep(10);
	gotoxy(30, 15);cout << "��                              ��";
	Sleep(10);
	gotoxy(30, 16);cout << "��   a   : ���Ʒ� ��ȯ          ��";
	Sleep(10);
	gotoxy(30, 17);cout << "��                              ��";
	Sleep(10);
	gotoxy(30, 18);cout << "��   1   : ����������         ��";
	Sleep(10);
	gotoxy(30, 19);cout << "��                              ��";
	Sleep(10);
	gotoxy(30, 20);cout << "��   2   : ������ ȣ��        ��";
	Sleep(10);
	gotoxy(30, 21);cout << "��                              ��";
	Sleep(10);
	gotoxy(30, 22);cout << "��   ESC : �Ͻ�����             ��";
	Sleep(10);
	gotoxy(30, 23);cout << "��                              ��";
	Sleep(10);
	gotoxy(30, 24);cout << "������������������";

	gotoxy(28, 27);
	cout << "||  'q'�� ������ �޴��� ���ư��ϴ�.  || ";

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
	cout << "���������< Credit >���������";
	Sleep(10);
	gotoxy(30, 8);
	cout << "��                                      ��";
	Sleep(10);
	gotoxy(30, 9);
	cout << "��        ���� : 201811186 �鵿��       ��";
	Sleep(10);
	gotoxy(30, 10);
	cout << "��                                      ��";
	Sleep(10);
	gotoxy(30, 11);
	cout << "��        ���� : 201411196 �迵��       ��";
	Sleep(10);
	gotoxy(30, 12);
	cout << "��                                      ��";
	Sleep(10);
	gotoxy(30, 13);
	cout << "��        ���� : 201811169 ������       ��";
	Sleep(10);
	gotoxy(30, 14);
	cout << "��                                      ��";
	Sleep(10);
	gotoxy(30, 15);
	cout << "��        ���� : 201811162 �輺��       ��";
	Sleep(10);
	gotoxy(30, 16);
	cout << "��                                      ��";
	Sleep(10);
	gotoxy(30, 17);
	cout << "����������������������";
	gotoxy(32, 20);
	cout << "||  'q'�� ������ �޴��� ���ư��ϴ�.  || ";

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
				cout << "��";

			}
		}
	}
	SetColor(BLACK);
	gotoxy(77, 23);
	return 0;
}
//�ó����� ����
void SetGame::story_stage1() {

	char arr1[100] = "(stage1) ȫ�� �Ա���";
	gotoxy(13, 3);
	for (int i = 0; i < sizeof(arr1); i++) {
		cout << arr1[i];
		Sleep(10);
		if (arr1[i] == NULL) {
			break;
		}
	}
	char arr2[100] = "���� �ð� 8�� 23��...";
	gotoxy(13, 5);
	for (int i = 0; i < sizeof(arr2); i++) {
		cout << arr2[i];
		Sleep(10);
		if (arr2[i] == NULL) {
			break;
		}
	}
	char arr3[100] = "������ 3���̳��� ��߽��Ѷ�!";
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
	char arr1[100] = "(stage2) ���̿�";
	gotoxy(13, 3);
	for (int i = 0; i < sizeof(arr1); i++) {
		cout << arr1[i];
		Sleep(10);
		if (arr1[i] == NULL) {
			break;
		}
	}
	char arr2[100] = "���� �ð� 8�� 26��...";
	gotoxy(13, 5);
	for (int i = 0; i < sizeof(arr2); i++) {
		cout << arr2[i];
		Sleep(10);
		if (arr2[i] == NULL) {
			break;
		}
	}
	char arr3[100] = "������ 3���̳��� ��߽��Ѷ�";
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
	char arr1[100] = "(stage3) ���빮 ���� ��ȭ������";
	gotoxy(13, 3);
	for (int i = 0; i < sizeof(arr1); i++) {
		cout << arr1[i];
		Sleep(10);
		if (arr1[i] == NULL) {
			break;
		}
	}
	char arr2[100] = "���� �ð� 8�� 29��...";
	gotoxy(13, 5);
	for (int i = 0; i < sizeof(arr2); i++) {
		cout << arr2[i];
		Sleep(10);
		if (arr2[i] == NULL) {
			break;
		}
	}
	char arr3[100] = "������ 3���̳��� ��߽��Ѷ�";
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
	char arr1[100] = "(stage4) �սʸ� ��";
	gotoxy(13, 3);
	for (int i = 0; i < sizeof(arr1); i++) {
		cout << arr1[i];
		Sleep(10);
		if (arr1[i] == NULL) {
			break;
		}
	}
	char arr2[100] = "���� �ð� 8�� 32��...";
	gotoxy(13, 5);
	for (int i = 0; i < sizeof(arr2); i++) {
		cout << arr2[i];
		Sleep(10);
		if (arr2[i] == NULL) {
			break;
		}
	}
	char arr3[100] = "������ 3���̳��� ��߽��Ѷ�";
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

	char arr1[100] = "(stage5) �Ǵ� �Ա���";
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
	char arr3[100] = "������ �����ִ�...";
	gotoxy(13, 7);
	for (int i = 0; i < sizeof(arr3); i++) {
		cout << arr3[i];
		Sleep(10);
		if (arr3[i] == NULL) {
			break;
		}
	}
	
	char arr4[100] = "���� �ð� 8�� 35��...";
	gotoxy(13, 9);
	for (int i = 0; i < sizeof(arr4); i++) {
		cout << arr4[i];
		Sleep(10);
		if (arr4[i] == NULL) {
			break;
		}
	}
	char arr5[100] = "������ 3���̳��� ��߽��Ѷ�";
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
	//		���� �ȳ� ���
	//		"�̹����� �Ǵ� �Ǵ� �Ա����Դϴ�"
	//		(�� ������ �Ҹ�)

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
	char arr2[100] = "������ ��� �����ִ�...";
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

	//	���� �ȳ� ���
	//	"�̹����� ��� ���ı�û���Դϴ�. ������ ���� �����Դϴ�."

	PlaySound(TEXT("jamsil2.wav"), NULL, SND_ASYNC | SND_NOSTOP);

	system("cls");
	for (int i = 0; i < 7; i++) {
		
		if(i == 0 || i == 6) {
			gotoxy(13, 5); SetColor(WHITE); Sleep(550);
			cout << "���������������������������";
			gotoxy(13, 6);
			cout << "��                                                ��";
			gotoxy(13, 7);
			cout << "��        �̹� ���� ��� ���ı�û���Դϴ�.        ��";
			gotoxy(13, 8);
			cout << "��                                                ��";
			gotoxy(13, 9);
			cout << "���������������������������";
		}
		else if(i == 1 || i == 5) {
			gotoxy(13, 5); SetColor(GRAY); Sleep(550);
			cout << "���������������������������";
			gotoxy(13, 6);
			cout << "��                                                ��";
			gotoxy(13, 7);
			cout << "��        �̹� ���� ��� ���ı�û���Դϴ�.        ��";
			gotoxy(13, 8);
			cout << "��                                                ��";
			gotoxy(13, 9);
			cout << "���������������������������";
		}
		else if(i == 2 || i == 4) {
			gotoxy(13, 5); SetColor(DARK_GRAY); Sleep(550);
			cout << "���������������������������";
			gotoxy(13, 6);
			cout << "��                                                ��";
			gotoxy(13, 7);
			cout << "��        �̹� ���� ��� ���ı�û���Դϴ�.        ��";
			gotoxy(13, 8);
			cout << "��                                                ��";
			gotoxy(13, 9);
			cout << "���������������������������";
		}
		else if (i == 3) {
			gotoxy(13, 5); SetColor(BLACK); Sleep(550);
			cout << "���������������������������";
			gotoxy(13, 6);
			cout << "��                                                ��";
			gotoxy(13, 7);
			cout << "��        �̹� ���� ��� ���ı�û���Դϴ�.        ��";
			gotoxy(13, 8);
			cout << "��                                                ��";
			gotoxy(13, 9);
			cout << "���������������������������";
		}
	}

	system("cls");

	char arr3[100] = "	' ��! ���Ⱑ ����� ?  ���????????' ";
	gotoxy(13, 3);
	for (int i = 0; i < sizeof(arr3); i++) {
		cout << arr3[i];
		Sleep(20);
		if (arr3[i] == NULL) {
			break;
		}
	}

	char arr4[100] = "	���� :  '�� ���ҳ� �Ф� ������...  ";
	gotoxy(13, 5);
	for (int i = 0; i < sizeof(arr4); i++) {
		cout << arr4[i];
		Sleep(20);
		if (arr4[i] == NULL) {
			break;
		}
	}
	char arr5[100] = "	8�� 40���̴ϱ�.. �׷��� ���� �ð��� �����ֳ� �����̴� ' ";
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
	char arr1[100] = "(stage6) ��ǿ�";
	gotoxy(13, 3);
	for (int i = 0; i < sizeof(arr1); i++) {
		cout << arr1[i];
		Sleep(20);
		if (arr1[i] == NULL) {
			break;
		}
	}
	char arr3[100] = "���� �ð� 8�� 40��...";
	gotoxy(13, 5);
	for (int i = 0; i < sizeof(arr3); i++) {
		cout << arr3[i];
		Sleep(20);
		if (arr3[i] == NULL) {
			break;
		}
	}
	char arr4[100] = "3�� ���� �����̸� ���������� �������Ѵ�!!";
	gotoxy(13, 7);
	for (int i = 0; i < sizeof(arr4); i++) {
		cout << arr4[i];
		Sleep(20);
		if (arr4[i] == NULL) {
			break;
		}
	}
	char arr5[100] = "������ ����� �ʹ� ����.";
	gotoxy(13, 9);
	for (int i = 0; i < sizeof(arr5); i++) {
		cout << arr5[i];
		Sleep(20);
		if (arr5[i] == NULL) {
			break;
		}
	}
	char arr6[100] = "��Ʈ���� ����� ��Ʈ�� ������ ������ ��߽��Ѷ�!";
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
	char arr1[100] = "(stage7) ������";
	gotoxy(13, 3);
	for (int i = 0; i < sizeof(arr1); i++) {
		cout << arr1[i];
		Sleep(10);
		if (arr1[i] == NULL) {
			break;
		}
	}
	char arr2[100] = "���� �ð� 8�� 45��...";
	gotoxy(13, 5);
	for (int i = 0; i < sizeof(arr2); i++) {
		cout << arr2[i];
		Sleep(10);
		if (arr2[i] == NULL) {
			break;
		}
	}
	char arr3[100] = "������ 3���̳��� ��߽��Ѷ�";
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
	char arr1[100] = "���� �ð� 8�� 50��...";
	gotoxy(13, 3);
	for (int i = 0; i < sizeof(arr1); i++) {
		cout << arr1[i];
		Sleep(20);
		if (arr1[i] == NULL) {
			break;
		}
	}

	char arr2[100] = "������ �Ǵ��Ա����� ������ �����̴� 1���ÿ� �����ʾҴ�.";
	gotoxy(13, 5);
	for (int i = 0; i < sizeof(arr2); i++) {
		cout << arr2[i];
		Sleep(20);
		if (arr2[i] == NULL) {
			break;
		}
	}

	char arr3[100] = "������ �� ��� ������ ���л� �����̴�";
	gotoxy(13, 7);
	for (int i = 0; i < sizeof(arr3); i++) {
		cout << arr3[i];
		Sleep(20);
		if (arr3[i] == NULL) {
			break;
		}
	}

	char arr4[100] = "���� �������� �����ߴ�.";
	gotoxy(13, 9);
	for (int i = 0; i < sizeof(arr4); i++) {
		cout << arr4[i];
		Sleep(20);
		if (arr4[i] == NULL) {
			break;
		}
	}

	char arr5[100] = "���п� ���� ������ ����� ���� ������ �޾Ҵ�.";
	gotoxy(13, 11);
	for (int i = 0; i < sizeof(arr5); i++) {
		cout << arr5[i];
		Sleep(20);
		if (arr5[i] == NULL) {
			break;
		}
	}

	char arr6[100] = "�׷��� ��� �ູ�ϰ� ���� ���� ��Ҵٰ� �Ѵ�.";
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
	//		���� �ȳ����
	//		" ���� ���� ���� ���� ���� ������� ���ϰ� �ֽ��ϴ�.
	//		�°� �����в� ����� �˼��մϴ�."

	PlaySound(TEXT("gameover.wav"), NULL, SND_FILENAME | SND_ASYNC);

	SetColor(WHITE);

	char arr1[100] = "�ᱹ ������ �������� �ǰ� ���Ҵ�....";
	gotoxy(30, 10);
	for (int i = 0; i < sizeof(arr1); i++) {
		cout << arr1[i];
		Sleep(20);
		if (arr1[i] == NULL) {
			break;
		}
	}

	char arr2[100] = "�׷��� �����̴� ������ �ؾ��ߴ�...";
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
