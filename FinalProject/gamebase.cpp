#include "gamebase.h"

//メンバ関数(doMainLoop)の定義
void GameBase::doMainLoop(int scmd) {
	ChangeWindowMode(scmd); //ウィンドウモード
	if (DxLib_Init() == -1) return; //DxLib初期化
	SetDrawScreen(DX_SCREEN_BACK); //描写対称画面の指定
	setIdouHosei();

	//フォントハンドル：引数(フォント名の文字列，サイズ，太さ，タイプ)
	largefont = CreateFontToHandle(0, 100, 9, DX_FONTTYPE_EDGE);
	smallfont = CreateFontToHandle(0, 32, 9, DX_FONTTYPE_NORMAL);

	//エラー処理，エラーがあればメッセージボックスを表示
	try {
		LoadFiles();
	}
	catch (int errcode) {
		MessageBox(NULL, "ファイル読み込みエラー", "メッセージ", MB_OK);
		return;
	}

	//ファイルの読み込み，タイトル画面設定
	LoadFiles();
	setGameState(GAME_TITLE); 

	//メインループ
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0) {
		ClsDrawScreen();  //画面消去
		//gstageの各状態における処理
		switch (gstate) {
		case GAME_TITLE:
			drawGameTitle();
			break;
		case GAME_MAIN:
			drawGameMain();
			break;
		case GAME_OVER:
			drawGameOver();
			break;
		case GAME_CLEAR:
				drawGameClear();
				break;
		}
	
		ScreenFlip(); //裏画面切り替え
		anmcounter = anmcounter + 1;
	}
	DxLib_End();
}

//(setGameState)の定義
GAMESTATE GameBase::setGameState(GAMESTATE state) {
	if (gstate != state) {
		gstate = state;
		starttime = GetNowCount(); //画面切り替え時の開始時間記録
		if (gstate == GAME_MAIN) initStage(); //初期化関数呼び出し
	}
	return gstate;
}

int col = GetColor(255, 255, 255);

//(drawGameTitle)，タイトル画面
void GameBase::drawGameTitle() {
	int col1 = GetColor(255, 0, 255); 
	int w = GetDrawStringWidthToHandle("GAME", 4, largefont);
	           //文字列の幅の定義：引数(表示する文字，文字数，フォントハンドル)
	           //(文字数)全角1文字で2
	DrawStringToHandle(320 - w / 2, 160, "GAME", col1, largefont);
	           //文字の表示：引数(座標，文字列，色，フォントハンドル)

	w = GetDrawStringWidthToHandle("Start Soon", 10, smallfont);
	DrawStringToHandle(320 - w / 2, 300, "Start Soon", col, smallfont);


	if (GetNowCount() - starttime > 5000) {
		setGameState(GAME_MAIN);
	}


}

//(drawGameMain)，ゲーム内容
void GameBase::drawGameMain() {
	DrawStringToHandle(80, 20, "Zでゲームオーバー,Cでクリア", col, smallfont);
	int key = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	if (key & PAD_INPUT_A) setGameState(GAME_OVER);
	if (key & PAD_INPUT_C) setGameState(GAME_CLEAR);
}

//(drawGameClear),ゲームクリア時
void GameBase::drawGameClear() {
	int col2 = GetColor(0, 255, 255);
	int w = GetDrawStringWidthToHandle("GAMECLEAR", 9, largefont);
	DrawStringToHandle(320 - w / 2, 160, "GAMECLEAR", col2, largefont);

	w = GetDrawStringWidthToHandle("Return Title Soon", 17, smallfont);
	DrawStringToHandle(320 - w / 2, 300, "Return Title Soon", col, smallfont);

	//4秒でタイトル画面に戻る
	if (GetNowCount() - starttime > 4000) {
		setGameState(GAME_TITLE);
	}
}

//(drawGameOver),ゲームオーバー時
void GameBase::drawGameOver() {
	int col3 = GetColor(200,0,0);

	int w = GetDrawStringWidthToHandle("GAMEOVER", 9, largefont);
	DrawStringToHandle(320 - w / 2, 160, "GAMEOVER", col3, largefont);

	w = GetDrawStringWidthToHandle("Return Title Soon", 17, smallfont);
	DrawStringToHandle(320 - w / 2, 300, "Return Title Soon", col, smallfont);


	if (GetNowCount() - starttime > 4000) {
		setGameState(GAME_TITLE);
	}
}

//(getAnmCnt),現在のanmcounterの値を返す
unsigned int GameBase::getAnmCnt() {
	return anmcounter;
}

unsigned int GameBase::anmcounter = 0; //anmcounter実体

//補正移動量を求める
void GameBase::setIdouHosei() {
	float frametime = 0;
	unsigned int s = GetNowCount();  //開始時刻s
	for (int i = 0; i < 30; i++) {
		ScreenFlip();
		unsigned int e = GetNowCount();   //終了時刻e
		frametime = frametime + e - s;
		s = e;
	}
	//30回平均経過時間
	frametime = frametime / 30;
	//各移動量の補正値格納
	for (int i = 1; i < 20; i = i + 1) {
		idouryo[i] = i / frametime * 16.67;
	}
}

//補正後の移動量(負と正で場合分け)
float GameBase::Idouhosei(int idou) {
	if (idou < 0) {
		return(-idouryo[-idou]);
	}
	else {
		return(idouryo[idou]);
	}
}

float GameBase::idouryo[20];//idouryo実体

