#include "Jitama.h"
#include "DxLib.h"

Jitama::Jitama(){
	//�R���X�g���N�^
	//�������Ɏ󂯎�������W�ɃZ�b�g����
	x = 0;
	y = 0;
}

void Jitama::update(){

	//�E�ֈړ�����B
	x += 10;
}

void Jitama::draw(){
	DrawGraph(x, y, graph, TRUE);
}

void Jitama::setGraph(GraphHandle graph){
	this->graph = graph;
}
