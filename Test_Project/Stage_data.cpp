#include "Stage_data.h"

Stage_data::Stage_data()
{
	data[0].setValue(40, 20, 3, 3, 800, "ȫ���Ա�"); // 20
	data[1].setValue(38, 18, 3, 3, 760, "����");     // 18
	data[2].setValue(35, 18, 3, 3, 720, "���빮���繮ȭ����"); // 18
	data[3].setValue(30, 17, 3, 3, 680, "�սʸ�"); // 17
	data[4].setValue(25, 16, 3, 3, 640, "�Ǵ��Ա�"); // 16
	data[5].setValue(20, 14, 3, 3, 600, "���"); // 14
	data[6].setValue(15, 12, 3, 3, 560, "����"); // 12
}

Stage Stage_data::getStage(int level) {
	return data[level];
}

Stage_data::~Stage_data()
{
}
