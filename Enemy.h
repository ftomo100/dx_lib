#pragma once
//Enemy.h
//���\�b�h������
//Enemy�E�E�E�R���X�g���N�^
//update�E�E�E���t���[���ɍX�V����
//draw�E�E�E�`��
//setGraph�E�E�O���t�B�b�N�n���h�����Z�b�g
//speed�E�E�E�ړ����x

typedef int GraphHandle;

class Enemy {
public:
	int x;
	int y;
	GraphHandle graph;
	int speed;

	Enemy();
	void update();
	void draw();
	void setGraph(GraphHandle graph);
};
