#pragma once
#include "Stage.h"

class Stage_data {
private:
	Stage data[10];
public:
	Stage_data();
	Stage getStage(int level);
	~Stage_data();
};
