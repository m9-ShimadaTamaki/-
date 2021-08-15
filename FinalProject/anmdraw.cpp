#include "anmdraw.h"

//グラフィックハンドルセット
int AnmDraw::setImage(int apid, int ghandle) {
	if (apid >= vecaplist.size()) {
		vecaplist.push_back(anmpat()); //新しいアニメパターンの追加
		apid = vecaplist.size() - 1; //追加したアニメパターンを指すapid
	}
	vecaplist.at(apid).vecghlist.push_back(ghandle);  //既存の要素に追加
	return(apid);
}

//1コマの表示時間セット
int AnmDraw::setGap(int apid, int gap) {
	if (apid >= vecaplist.size()) {
		vecaplist.push_back(anmpat());
		apid = vecaplist.size() - 1;
	}
	vecaplist.at(apid).anmgap = gap;
	return(apid);
}

//アニメーション描写
void AnmDraw::draw(int apid, int x, int y) {
	//アニメパターンが複数の場合
	if (vecaplist.at(apid).vecghlist.size() > 1) {
		int curpat = GameBase::getAnmCnt() / vecaplist.at(apid).anmgap % vecaplist.at(apid).vecghlist.size();
		   //anmcounter÷1コマ表示間隔 % コマ数)，表示すべきインデックス
		DrawGraph(x, y, vecaplist.at(apid).vecghlist.at(curpat), true);
           //最後の引数：透過色有効
	}
	//アニメパターン1つでアニメの必要性ない場合
	else {
		DrawGraph(x, y, vecaplist.at(apid).vecghlist.at(0), true);
	}
}

//アニメーション回転描写
void AnmDraw::draw(int apid, int x, int y, float rad) {
	if (vecaplist.at(apid).vecghlist.size() > 1) {
		int curpat = GameBase::getAnmCnt() / vecaplist.at(apid).anmgap % vecaplist.at(apid).vecghlist.size();
		DrawRotaGraph(x, y, 1.0, rad, vecaplist.at(apid).vecghlist.at(curpat), TRUE, FALSE);
		  //引数(回転中心の座標，角度，ghandle数，透過色有効(TRUE)，左右反転描写(TRUE)
	}
	else {
		DrawRotaGraph(x, y, 1.0, rad, vecaplist.at(apid).vecghlist.at(0), TRUE, FALSE);
	}
}
