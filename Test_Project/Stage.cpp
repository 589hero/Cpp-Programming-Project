#include "Stage.h"

Stage::Stage()
	:speed(-1), stick_rate(-1), clear_upper_line(-1), clear_lower_line(-1), station_name("") {
}

Stage::~Stage() {
}

Stage::Stage(int speed, int stick_rate, int clear_upper_line, int clear_lower_line, int remain_block_limit, string name)
	:speed(speed), stick_rate(stick_rate), clear_upper_line(clear_upper_line), clear_lower_line(clear_lower_line), remain_block_limit(remain_block_limit), station_name(name) {
}

void Stage::setValue(int speed, int stick_rate, int clear_upper_line, int clear_lower_line, int remain_block_limit, string name) {
	this->speed = speed;
	this->stick_rate = stick_rate;
	this->clear_upper_line = clear_upper_line;
	this->clear_lower_line = clear_lower_line;
	this->remain_block_limit = remain_block_limit;
	this->station_name = name;
}

int Stage::getSpeed() {
	return this->speed;
}

int Stage::getStick_rate() {
	return this->stick_rate;
}

int Stage::getClear_upper_line() {
	return this->clear_upper_line;
}

int Stage::getClear_lower_line()
{
	return this->clear_lower_line;
}

int Stage::getRemain_block_limit()
{
	return this->remain_block_limit;
}

string Stage::getStation_name()
{
	return this->station_name;
}
