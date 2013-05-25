#include "Enemy.h"
#include "DxLib.h"

Enemy::Enemy(){
	//コンストラクタ
	//ランダムな座標に登場
	//移動速度はランダムに設定
	x = 640 + GetRand(30);
	y = GetRand(480);
	speed = GetRand(3) + 1;
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
