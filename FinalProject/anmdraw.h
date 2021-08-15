#ifndef INCLUDE_ANMDRAW_H_
#define INCLUDE_ANMDRAW_H_

#include <vector>
#include "DxLib.h"
#include "gamebase.h"
using namespace std;

class AnmDraw {
	//画像のグラフィックハンドル記憶する構造体宣言，アニメパターン
	struct anmpat {
		vector<int> vecghlist;
		int anmgap;  //表示間隔
		anmpat() { anmgap = 1; }
	};
	vector<anmpat> vecaplist;

public:
	//コンストラクタ
	AnmDraw() {
		vecaplist.push_back(anmpat());
	}

	int setImage(int apid, int ghandle); //グラフィックハンドルセット
	int setGap(int apid, int gap);  //表示間隔セット

	void draw(int apid, int x, int y);
	void draw(int apid, int x, int y, float rad); //アニメーション回転表示
};


#endif
