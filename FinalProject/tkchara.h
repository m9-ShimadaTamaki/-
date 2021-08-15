#ifndef INCLUDE_TKCHARA_H_
#define INCLUDE_TKCHARA_H_
#include "anmdraw.h"
#include "charactor.h"
#include <list>
using namespace std;

const int PATMAX = 12;

class tkchara {
	list<Charactor> tklist; //	敵キャラ
	list<Charactor> mglist; //弾
	AnmDraw tkanm;
	int tkpat[12][3];//パターン格納配列
	int curpat, repeat;//パターン読み取り時に使用する変数
public:
	tkchara();
	void LoadFiles() throw(int); //画像読み込み
	void init(); //初期化
	void move(); //移動
	list<Charactor>* getTklist() { return (&tklist); }
	bool isGameClear() {
		if (tklist.front().life < 1)return true;
		return false;
	}
};

#endif
