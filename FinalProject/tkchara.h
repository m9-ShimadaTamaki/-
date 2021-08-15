#ifndef INCLUDE_TKCHARA_H_
#define INCLUDE_TKCHARA_H_
#include "anmdraw.h"
#include "charactor.h"
#include <list>
using namespace std;

const int PATMAX = 12;

class tkchara {
	list<Charactor> tklist; //	�G�L����
	list<Charactor> mglist; //�e
	AnmDraw tkanm;
	int tkpat[12][3];//�p�^�[���i�[�z��
	int curpat, repeat;//�p�^�[���ǂݎ�莞�Ɏg�p����ϐ�
public:
	tkchara();
	void LoadFiles() throw(int); //�摜�ǂݍ���
	void init(); //������
	void move(); //�ړ�
	list<Charactor>* getTklist() { return (&tklist); }
	bool isGameClear() {
		if (tklist.front().life < 1)return true;
		return false;
	}
};

#endif
