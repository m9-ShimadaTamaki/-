#ifndef INCLUDE_MYCHARA_H_
#define INCLUDE_MYCHARA_H_
#include "anmdraw.h"
#include "charactor.h"
#include <list>
using namespace std;

class mychara {
	list<Charactor> mylist; //���L����
	list<Charactor> mglist; //�e
	AnmDraw myanm;
	AnmDraw mganm;
	int trigger;
public:
	void LoadFiles() throw(int); //�摜�ǂݍ���
	void init(); //������
	void move(); //�ړ�
	//���W�̎擾
	float getx() { return(mylist.front().x); }
	float gety() { return(mylist.front().y); }
	list<Charactor>* getMglist() { return (&mglist); }
	//�Q�[���I�[�o�[����
	bool isGameOver() {
		if (mylist.front().life < 1)return true;
		return false;
	}
};

#endif
