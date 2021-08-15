#ifndef INCLUDE_GAMEBASE_H_
#define INCLUDE_GAMEBASE_H_
//重複定義回避

#include "DxLib.h"

//画面モードを表す列挙体
enum GAMESTATE {
	GAME_TITLE=1, GAME_MAIN, GAME_OVER, GAME_CLEAR 
};

//クラス宣言
class GameBase {
	virtual void LoadFiles() {}
	virtual void initStage() {} //ステージ初期化
	GAMESTATE gstate; //現在の画面モードを表す変数
	int starttime;  //画面開始時間
	static unsigned int anmcounter;  //アニメーション用,グローバル変数
	static float idouryo[20]; //配列，補正移動量
	void setIdouHosei();  //補正移動量セット

protected:
	virtual void drawGameTitle(); //タイトル画面
	virtual void drawGameMain(); //ゲーム内容
	virtual void drawGameClear(); //クリア画面
	virtual void drawGameOver(); //オーバー画面
	GAMESTATE setGameState(GAMESTATE state); //gstate変更関数
	int largefont, smallfont; //フォントの記憶

public:
	virtual ~GameBase(){} //デストラクタ
	void doMainLoop(int); //メインループ実行
	static unsigned int getAnmCnt(); //anmcounterを取得
	static float Idouhosei(int); //補正移動量を返す変数
};

#endif