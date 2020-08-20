#pragma once
#include <string>

using namespace std;

class Stage
{
private: //각 스테이지마다의 난이도 설정
	int	speed;	//숫자가 낮을수록 속도가 빠르다
	int stick_rate;		//막대가 나오는 확률 0~99 , 99면 막대기만 나옴
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