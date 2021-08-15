#ifndef INCLUDE_GAMEBASE_H_
#define INCLUDE_GAMEBASE_H_
//�d����`���

#include "DxLib.h"

//��ʃ��[�h��\���񋓑�
enum GAMESTATE {
	GAME_TITLE=1, GAME_MAIN, GAME_OVER, GAME_CLEAR 
};

//�N���X�錾
class GameBase {
	virtual void LoadFiles() {}
	virtual void initStage() {} //�X�e�[�W������
	GAMESTATE gstate; //���݂̉�ʃ��[�h��\���ϐ�
	int starttime;  //��ʊJ�n����
	static unsigned int anmcounter;  //�A�j���[�V�����p,�O���[�o���ϐ�
	static float idouryo[20]; //�z��C�␳�ړ���
	void setIdouHosei();  //�␳�ړ��ʃZ�b�g

protected:
	virtual void drawGameTitle(); //�^�C�g�����
	virtual void drawGameMain(); //�Q�[�����e
	virtual void drawGameClear(); //�N���A���
	virtual void drawGameOver(); //�I�[�o�[���
	GAMESTATE setGameState(GAMESTATE state); //gstate�ύX�֐�
	int largefont, smallfont; //�t�H���g�̋L��

public:
	virtual ~GameBase(){} //�f�X�g���N�^
	void doMainLoop(int); //���C�����[�v���s
	static unsigned int getAnmCnt(); //anmcounter���擾
	static float Idouhosei(int); //�␳�ړ��ʂ�Ԃ��ϐ�
};

#endif