#pragma once
#include "SetGame.h"
class Map
{
public:
	char total_block[MAP_ROW][MAP_COL];
	Map();
	bool s_item_check; //����� ��� ��� ���� üũ
	void init();

	~Map();
};

