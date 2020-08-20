#include "Map.h"
#include <cstdlib>
#include <ctime>

Map::Map()
{
	init();
}

void Map::init() {
	srand((unsigned)time(NULL));

	for (int i = UPPER_WALL; i < LOWER_WALL; i++) {
		for (int j = LEFT_WALL; j <= RIGHT_WALL; j++) {
			if ((j == LEFT_WALL) || (j == RIGHT_WALL)) {
				total_block[i][j] = 1;
			}
			else {
				total_block[i][j] = 0;
			}
		}
	}

	for (int j = LEFT_WALL; j <= RIGHT_WALL; j++) {			//화면의 제일 밑의 줄은 1로 채운다.
		total_block[UPPER_WALL][j] = 1;
		total_block[LOWER_WALL][j] = 1;
	}
	s_item_check = false;
}


Map::~Map()
{
}
