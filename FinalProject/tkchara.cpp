#include "tkchara.h"

void tkchara::LoadFiles()throw(int) {
	int gh[3];
	//	画像分割読み込み：引数(パス，分割総数，横：縦分割数，分割後の大きさ，保存場所)
	if (LoadDivGraph("tk.jpg", 3, 3, 1, 48, 40, gh) == -1)
		throw(-1);
	for (int i = 0; i < 3; i = i + 1) {
		tkanm.setImage(0, gh[i]);
	}
	tkanm.setGap(0, 6);
}

void tkchara::init() {
	tklist.clear();
	Charactor teki;
	teki.x = 580; teki.y = 200; teki.anm = &tkanm;
	teki.life = 10;
	teki.image_w = 48; teki.image_h = 40;
	teki.bounds_w = 20; teki.bounds_h = 25;
	teki.amd = A_HARD;
	tklist.push_back(teki);//データをlistへ
	curpat = 0;
	repeat = tkpat[curpat][0];
}
void tkchara::move() {
	list<Charactor>::iterator it;   //イテレータ使用して最初の要素取り出す
	it = tklist.begin();
	(*it).anm->draw(0, (*it).x, (*it).y);
	//移動処理，格納した行動パターンのくり返し
	(*it).x = (*it).x + tkpat[curpat][1];
	(*it).y = (*it).y + tkpat[curpat][2];
	if (repeat > 0) {
		repeat = repeat - 1;
	}
	else {
		curpat = curpat + 1;
		if (curpat >= PATMAX) curpat = 0;
		repeat = tkpat[curpat][0];
	}
}

//敵の行動パターン
tkchara::tkchara() {
	int temp[12][3] = { {120,-2,0},{100,0,0},{120,2,0},{40,0,-4},{120,-2,0},{100,0,0},{120,2,0},{80,0,4}, {120,-2,0},{100,0,0},{120,2,0},{40,0,-4} };
	//引数(回数，x,y移動量)
	memcpy(tkpat, temp, sizeof(int) * 36);//メモリコピー引数
}