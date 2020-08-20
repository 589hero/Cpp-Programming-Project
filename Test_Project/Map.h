#pragma once
#include "SetGame.h"
class Map
{
public:
	char total_block[MAP_ROW][MAP_COL];
	Map();
	bool s_item_check; //저장된 블록 사용 여부 체크
	void init();

	~Map();
};

