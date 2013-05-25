#pragma once
//Jitama.h
//���@�����˂���e������
//Jitama�E�E�E�R���X�g���N�^
//update�E�E�E���t���[���ɍX�V����
//draw�E�E�E�`��
//setGraph�E�E�O���t�B�b�N�n���h�����Z�b�g

typedef int GraphHandle;

class Jitama {
public:
	int x;
	int y;
	GraphHandle graph;
	int life;

	Jitama();
	void update();
	void draw();
	void setGraph(GraphHandle graph);
};
