#ifndef INCLUDE_ANMDRAW_H_
#define INCLUDE_ANMDRAW_H_

#include <vector>
#include "DxLib.h"
#include "gamebase.h"
using namespace std;

class AnmDraw {
	//�摜�̃O���t�B�b�N�n���h���L������\���̐錾�C�A�j���p�^�[��
	struct anmpat {
		vector<int> vecghlist;
		int anmgap;  //�\���Ԋu
		anmpat() { anmgap = 1; }
	};
	vector<anmpat> vecaplist;

public:
	//�R���X�g���N�^
	AnmDraw() {
		vecaplist.push_back(anmpat());
	}

	int setImage(int apid, int ghandle); //�O���t�B�b�N�n���h���Z�b�g
	int setGap(int apid, int gap);  //�\���Ԋu�Z�b�g

	void draw(int apid, int x, int y);
	void draw(int apid, int x, int y, float rad); //�A�j���[�V������]�\��
};


#endif
