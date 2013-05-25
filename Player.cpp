#include "Player.h"
#include "Jitama.h"
#include "DxLib.h"

Player::Player(){
	//�R���X�g���N�^
	x = 0;
	y = 0;
}

void Player::update(){
	//�L�[���̓`�F�b�N
	int key = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	if(key & PAD_INPUT_UP)		y -= 4;
	if(key & PAD_INPUT_DOWN)	y += 4;
	if(key & PAD_INPUT_LEFT)	x -= 4;
	if(key & PAD_INPUT_RIGHT)	x += 4;



	//�ړ��͈̓`�F�b�N
	if( x < 0) x= 0;
	if( y < 0) y= 0;
	if( x > 640) x= 640;
	if( y > 480) y= 480;
}

void Player::draw(){
	DrawGraph(x, y, graph, TRUE);
}

void Player::setGraph(GraphHandle graph){
	this->graph = graph;
}
