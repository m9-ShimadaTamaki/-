#include "tkchara.h"

void tkchara::LoadFiles()throw(int) {
	int gh[3];
	//	�摜�����ǂݍ��݁F����(�p�X�C���������C���F�c�������C������̑傫���C�ۑ��ꏊ)
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
	tklist.push_back(teki);//�f�[�^��list��
	curpat = 0;
	repeat = tkpat[curpat][0];
}
void tkchara::move() {
	list<Charactor>::iterator it;   //�C�e���[�^�g�p���čŏ��̗v�f���o��
	it = tklist.begin();
	(*it).anm->draw(0, (*it).x, (*it).y);
	//�ړ������C�i�[�����s���p�^�[���̂���Ԃ�
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

//�G�̍s���p�^�[��
tkchara::tkchara() {
	int temp[12][3] = { {120,-2,0},{100,0,0},{120,2,0},{40,0,-4},{120,-2,0},{100,0,0},{120,2,0},{80,0,4}, {120,-2,0},{100,0,0},{120,2,0},{40,0,-4} };
	//����(�񐔁Cx,y�ړ���)
	memcpy(tkpat, temp, sizeof(int) * 36);//�������R�s�[����
}