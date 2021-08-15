#include "gamebase.h"
#include "anmdraw.h"
#include "mychara.h"
#include "tkchara.h"

class ShootGame :public GameBase {
	mychara mycnt;
	tkchara tkcnt;
	void LoadFiles()throw(int);
	void initStage();
	void drawGameMain();
	void atarihantei();
	void isAtari(Charactor* a, Charactor* b);
};

void ShootGame::LoadFiles()throw(int) {
	mycnt.LoadFiles();
	tkcnt.LoadFiles();
}
void ShootGame::initStage() {
	mycnt.init();
	tkcnt.init();
}
void ShootGame::drawGameMain() {
	mycnt.move();
	tkcnt.move();
	atarihantei();
	if (mycnt.isGameOver() == true) {
		setGameState(GAME_OVER);
	}
	if (tkcnt.isGameClear() == true) {
		setGameState(GAME_OVER);
	}
}

void ShootGame::isAtari(Charactor* a, Charactor* b) {
	int ax1 = a->x + (a->image_w - a->bounds_w) / 2;
	int ay1 = a->y + (a->image_h - a->bounds_h) / 2;
	int ax2 = a->x + (a->image_w - a->bounds_w) / 2;
	int ay2 = a->y + (a->image_h - a->bounds_h) / 2;
	int bx1 = b->x + (b->image_w - b->bounds_w) / 2;
	int by1 = b->y + (b->image_h - b->bounds_h) / 2;
	int bx2 = b->x + (b->image_w - b->bounds_w) / 2;
	int by2 = b->y + (b->image_h - b->bounds_h) / 2;

	if ((ax1 < bx2) && (bx1 < ax2) && (ay1 < by2) && (by1 < ay2)) {
		switch (a->amd) {
		case A_NORMAL:
			a->life = 0;
			break;
		case A_HARD:
			a->life = a->life - 1;
			break;
		}

		switch (b->amd) {
		case A_NORMAL:
			b->life = 0;
			break;
		case A_HARD:
			b->life = b->life - 1;
			break;
		}
	}
}

//“–‚½‚è”»’è
void ShootGame::atarihantei() {
	list<Charactor>* mglist, * tklist;
	mglist = mycnt.getMglist();
	tklist = tkcnt.getTklist();
	list < Charactor>::iterator it, it2;
	for (it = tklist->begin(); it != tklist->end(); ++it) {
		if((*it).life >0 && (*it).amd !=A_GHOST){
			for (it2 = mglist->begin(); it2 != mglist->end(); ++it2) {
				isAtari(&(*it2), &(*it));
			}
		}
	}
}


int WINAPI WinMain(HINSTANCE hI, HINSTANCE hp, LPSTR lpC, int nC) {
	ShootGame *sg = new ShootGame();
	sg->doMainLoop(TRUE);
	delete sg;
}

