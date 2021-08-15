#ifndef INCLUDE_CHARACTOR_H_
#define INCLUDE_CHARACTOR_H_
#include "anmdraw.h"

enum ATARIMODE {
	A_GHOST, A_NORMAL, A_HARD, A_MORTAL //���薳�C�������ď��ŁC�������Ă��ϋv�C�s��
};

struct Charactor{
public:
	float x, y;
	AnmDraw *anm;
	int life;
	int image_w; //�C���[�W�̑傫��
	int image_h;
	int bounds_w; //����̈�̑傫��
	int bounds_h;
	ATARIMODE amd; //�����蔻�葮��

};


#endif