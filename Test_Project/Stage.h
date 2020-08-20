#pragma once
#include <string>

using namespace std;

class Stage
{
private: //�� �������������� ���̵� ����
	int	speed;	//���ڰ� �������� �ӵ��� ������
	int stick_rate;		//���밡 ������ Ȯ�� 0~99 , 99�� ����⸸ ����
	int clear_upper_line;
	int clear_lower_line;
	int remain_block_limit;
	string station_name;

public:
	Stage();
	Stage(int, int, int, int, int, string);
	void setValue(int, int, int, int, int, string);

	int getSpeed();
	int getStick_rate();
	int getClear_upper_line();
	int getClear_lower_line();
	int getRemain_block_limit();
	string getStation_name();
	~Stage();
};