#include "gamebase.h"

//�����o�֐�(doMainLoop)�̒�`
void GameBase::doMainLoop(int scmd) {
	ChangeWindowMode(scmd); //�E�B���h�E���[�h
	if (DxLib_Init() == -1) return; //DxLib������
	SetDrawScreen(DX_SCREEN_BACK); //�`�ʑΏ̉�ʂ̎w��
	setIdouHosei();

	//�t�H���g�n���h���F����(�t�H���g���̕�����C�T�C�Y�C�����C�^�C�v)
	largefont = CreateFontToHandle(0, 100, 9, DX_FONTTYPE_EDGE);
	smallfont = CreateFontToHandle(0, 32, 9, DX_FONTTYPE_NORMAL);

	//�G���[�����C�G���[������΃��b�Z�[�W�{�b�N�X��\��
	try {
		LoadFiles();
	}
	catch (int errcode) {
		MessageBox(NULL, "�t�@�C���ǂݍ��݃G���[", "���b�Z�[�W", MB_OK);
		return;
	}

	//�t�@�C���̓ǂݍ��݁C�^�C�g����ʐݒ�
	LoadFiles();
	setGameState(GAME_TITLE); 

	//���C�����[�v
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0) {
		ClsDrawScreen();  //��ʏ���
		//gstage�̊e��Ԃɂ����鏈��
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
	
		ScreenFlip(); //����ʐ؂�ւ�
		anmcounter = anmcounter + 1;
	}
	DxLib_End();
}

//(setGameState)�̒�`
GAMESTATE GameBase::setGameState(GAMESTATE state) {
	if (gstate != state) {
		gstate = state;
		starttime = GetNowCount(); //��ʐ؂�ւ����̊J�n���ԋL�^
		if (gstate == GAME_MAIN) initStage(); //�������֐��Ăяo��
	}
	return gstate;
}

int col = GetColor(255, 255, 255);

//(drawGameTitle)�C�^�C�g�����
void GameBase::drawGameTitle() {
	int col1 = GetColor(255, 0, 255); 
	int w = GetDrawStringWidthToHandle("GAME", 4, largefont);
	           //������̕��̒�`�F����(�\�����镶���C�������C�t�H���g�n���h��)
	           //(������)�S�p1������2
	DrawStringToHandle(320 - w / 2, 160, "GAME", col1, largefont);
	           //�����̕\���F����(���W�C������C�F�C�t�H���g�n���h��)

	w = GetDrawStringWidthToHandle("Start Soon", 10, smallfont);
	DrawStringToHandle(320 - w / 2, 300, "Start Soon", col, smallfont);


	if (GetNowCount() - starttime > 5000) {
		setGameState(GAME_MAIN);
	}


}

//(drawGameMain)�C�Q�[�����e
void GameBase::drawGameMain() {
	DrawStringToHandle(80, 20, "Z�ŃQ�[���I�[�o�[,C�ŃN���A", col, smallfont);
	int key = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	if (key & PAD_INPUT_A) setGameState(GAME_OVER);
	if (key & PAD_INPUT_C) setGameState(GAME_CLEAR);
}

//(drawGameClear),�Q�[���N���A��
void GameBase::drawGameClear() {
	int col2 = GetColor(0, 255, 255);
	int w = GetDrawStringWidthToHandle("GAMECLEAR", 9, largefont);
	DrawStringToHandle(320 - w / 2, 160, "GAMECLEAR", col2, largefont);

	w = GetDrawStringWidthToHandle("Return Title Soon", 17, smallfont);
	DrawStringToHandle(320 - w / 2, 300, "Return Title Soon", col, smallfont);

	//4�b�Ń^�C�g����ʂɖ߂�
	if (GetNowCount() - starttime > 4000) {
		setGameState(GAME_TITLE);
	}
}

//(drawGameOver),�Q�[���I�[�o�[��
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

//(getAnmCnt),���݂�anmcounter�̒l��Ԃ�
unsigned int GameBase::getAnmCnt() {
	return anmcounter;
}

unsigned int GameBase::anmcounter = 0; //anmcounter����

//�␳�ړ��ʂ����߂�
void GameBase::setIdouHosei() {
	float frametime = 0;
	unsigned int s = GetNowCount();  //�J�n����s
	for (int i = 0; i < 30; i++) {
		ScreenFlip();
		unsigned int e = GetNowCount();   //�I������e
		frametime = frametime + e - s;
		s = e;
	}
	//30�񕽋όo�ߎ���
	frametime = frametime / 30;
	//�e�ړ��ʂ̕␳�l�i�[
	for (int i = 1; i < 20; i = i + 1) {
		idouryo[i] = i / frametime * 16.67;
	}
}

//�␳��̈ړ���(���Ɛ��ŏꍇ����)
float GameBase::Idouhosei(int idou) {
	if (idou < 0) {
		return(-idouryo[-idou]);
	}
	else {
		return(idouryo[idou]);
	}
}

float GameBase::idouryo[20];//idouryo����

