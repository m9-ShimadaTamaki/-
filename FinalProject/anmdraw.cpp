#include "anmdraw.h"

//�O���t�B�b�N�n���h���Z�b�g
int AnmDraw::setImage(int apid, int ghandle) {
	if (apid >= vecaplist.size()) {
		vecaplist.push_back(anmpat()); //�V�����A�j���p�^�[���̒ǉ�
		apid = vecaplist.size() - 1; //�ǉ������A�j���p�^�[�����w��apid
	}
	vecaplist.at(apid).vecghlist.push_back(ghandle);  //�����̗v�f�ɒǉ�
	return(apid);
}

//1�R�}�̕\�����ԃZ�b�g
int AnmDraw::setGap(int apid, int gap) {
	if (apid >= vecaplist.size()) {
		vecaplist.push_back(anmpat());
		apid = vecaplist.size() - 1;
	}
	vecaplist.at(apid).anmgap = gap;
	return(apid);
}

//�A�j���[�V�����`��
void AnmDraw::draw(int apid, int x, int y) {
	//�A�j���p�^�[���������̏ꍇ
	if (vecaplist.at(apid).vecghlist.size() > 1) {
		int curpat = GameBase::getAnmCnt() / vecaplist.at(apid).anmgap % vecaplist.at(apid).vecghlist.size();
		   //anmcounter��1�R�}�\���Ԋu % �R�}��)�C�\�����ׂ��C���f�b�N�X
		DrawGraph(x, y, vecaplist.at(apid).vecghlist.at(curpat), true);
           //�Ō�̈����F���ߐF�L��
	}
	//�A�j���p�^�[��1�ŃA�j���̕K�v���Ȃ��ꍇ
	else {
		DrawGraph(x, y, vecaplist.at(apid).vecghlist.at(0), true);
	}
}

//�A�j���[�V������]�`��
void AnmDraw::draw(int apid, int x, int y, float rad) {
	if (vecaplist.at(apid).vecghlist.size() > 1) {
		int curpat = GameBase::getAnmCnt() / vecaplist.at(apid).anmgap % vecaplist.at(apid).vecghlist.size();
		DrawRotaGraph(x, y, 1.0, rad, vecaplist.at(apid).vecghlist.at(curpat), TRUE, FALSE);
		  //����(��]���S�̍��W�C�p�x�Cghandle���C���ߐF�L��(TRUE)�C���E���]�`��(TRUE)
	}
	else {
		DrawRotaGraph(x, y, 1.0, rad, vecaplist.at(apid).vecghlist.at(0), TRUE, FALSE);
	}
}
