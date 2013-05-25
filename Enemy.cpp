#include "Enemy.h"
#include "DxLib.h"

Enemy::Enemy(){
	//�R���X�g���N�^
	//�����_���ȍ��W�ɓo��
	//�ړ����x�̓����_���ɐݒ�
	x = 640 + GetRand(30);
	y = GetRand(480);
	speed = GetRand(10) + 1;
}

void Enemy::update(){
	x -= speed;
}

void Enemy::draw(){
	DrawGraph(x, y, graph, TRUE);
}

void Enemy::setGraph(GraphHandle graph){
	this->graph = graph;
}
