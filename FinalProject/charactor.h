#ifndef INCLUDE_CHARACTOR_H_
#define INCLUDE_CHARACTOR_H_
#include "anmdraw.h"

enum ATARIMODE {
	A_GHOST, A_NORMAL, A_HARD, A_MORTAL //判定無，当たって消滅，当たっても耐久，不死
};

struct Charactor{
public:
	float x, y;
	AnmDraw *anm;
	int life;
	int image_w; //イメージの大きさ
	int image_h;
	int bounds_w; //判定領域の大きさ
	int bounds_h;
	ATARIMODE amd; //当たり判定属性

};


#endif