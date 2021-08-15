#include "Mychara.h"

void mychara::LoadFiles()throw(int) {
	int gh[3];
	//	画像分割読み込み：引数(パス，分割総数，横：縦分割数，分割後の大きさ，保存場所)
	if (LoadDivGraph("my.jpg", 3, 3, 1, 48, 32, gh) == -1)
		throw(-1);
	for (int i = 0; i < 3; i = i + 1){
		myanm.setImage(0,gh[i]);
	}
	myanm.setGap(0, 6);
	gh[0] = LoadGraph("mg.jpg");
	if (gh[0] == -1)throw(-1);
	mganm.setImage(0, gh[0]);
}

void mychara::init() {
	mylist.clear();
	Charactor jiki;
	jiki.x = 0; jiki.y = 200; jiki.anm = &myanm;
	jiki.life = 1;
	jiki.image_w = 48; jiki.image_h = 32;
	jiki.bounds_w = 20; jiki.bounds_h = 20;
	jiki.amd = A_NORMAL;
	mylist.push_back(jiki); //データをlistへ
	trigger = 0;
}
void mychara::move() {
	list<Charactor>::iterator it;   //イテレータ使用して最初の要素取り出す
	it = mylist.begin();
	(*it).anm->draw(0, (*it).x, (*it).y);

	//移動
	int key = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	float df = GameBase::Idouhosei(4);
	if (key & PAD_INPUT_UP) (*it).y = (*it).y - df;
	if (key & PAD_INPUT_DOWN) (*it).y = (*it).y + df;
	if (key & PAD_INPUT_LEFT) (*it).x = (*it).x - df;
	if (key & PAD_INPUT_RIGHT) (*it).x = (*it).x + df;
	//画面からはみ出さない調整
	if ((*it).x < 0) (*it).x = 0;
	if ((*it).x >592) (*it).x = 592;
	if ((*it).y < 0) (*it).y = 0;
	if ((*it).y > 448) (*it).y = 448;
	(*it).anm->draw(0, (*it).x, (*it).y);

	//弾丸発射
	if (key & PAD_INPUT_A && (trigger == 0)) {
		Charactor newmg;
		newmg.x = (*it).x + 24; newmg.y = (*it).y + 8;
		newmg.anm = &mganm;
		newmg.life = 1;
		newmg.image_w = 64; newmg.image_h = 16;
		newmg.bounds_w = 48; newmg.bounds_h = 12;
		newmg.amd = A_NORMAL;
		mglist.push_back(newmg);
		trigger = 20;
	}
	if (trigger > 0) trigger = trigger - 1; //弾丸発射クールタイムの作成
	 //弾丸の移動表示
	it = mglist.begin();
	//画面内に弾丸があるかの場合分け
	while (it != mglist.end()) {
		if ((*it).x < 650 && (*it).life>0) {
			(*it).x = (*it).x + GameBase::Idouhosei(10); //直進
			(*it).anm->draw(0, (*it).x, (*it).y);
			++it;
		}
		else {
			it = mglist.erase(it);
		}
	}
}