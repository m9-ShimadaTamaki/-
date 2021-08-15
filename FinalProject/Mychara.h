#ifndef INCLUDE_MYCHARA_H_
#define INCLUDE_MYCHARA_H_
#include "anmdraw.h"
#include "charactor.h"
#include <list>
using namespace std;

class mychara {
	list<Charactor> mylist; //自キャラ
	list<Charactor> mglist; //弾
	AnmDraw myanm;
	AnmDraw mganm;
	int trigger;
public:
	void LoadFiles() throw(int); //画像読み込み
	void init(); //初期化
	void move(); //移動
	//座標の取得
	float getx() { return(mylist.front().x); }
	float gety() { return(mylist.front().y); }
	list<Charactor>* getMglist() { return (&mglist); }
	//ゲームオーバー判定
	bool isGameOver() {
		if (mylist.front().life < 1)return true;
		return false;
	}
};

#endif
